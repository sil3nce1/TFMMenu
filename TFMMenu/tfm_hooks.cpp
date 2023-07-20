#include "tfm.hpp"

int __stdcall tfm::hooks::hookedSend(SOCKET s, char* buf, int len, int flags)
{
	try
	{
		if (tfm::network::socket == NULL)
			tfm::network::socket = s;

		ByteArray* packet = new ByteArray(buf, len);

		if (packet->readByte(0) != (len - 2))
			packet->setPosition(1);

		int size = packet->readByte();
		tfm::network::lastPacketId = packet->readByte();
		int c = packet->readByte();
		int cc = packet->readByte();

		//log("packet: [%i], [%i], [%i], [%i], [%i]", packet.readByte(0), size, len, c, cc);

		f_TfmPacketHandler handler = tfm::packets::handlers::send::getPacketHandler(c, cc);

		if (handler)
			handler(packet);
		else
			log("hookedSend() -> No handler found for [%i, %i]", c, cc);

		if (packet->isModified())
		{
			char* data = packet->getData();
			int length = packet->getLength();

			memcpy(buf, data, length);
		}
		delete packet;
	}
	catch  (...) 
	{
		goto exit;
	}
	

exit:
	return tfm::network::oSend(s, buf, len, flags);
}

int __stdcall tfm::hooks::hookedRecv(SOCKET s, char* buf, int len, int flags)
{
	int dataLength = tfm::network::oRecv(s, buf, len, flags);

	ByteArray* packet = new ByteArray(buf, dataLength);

	packet->readByte();

	int size = packet->readByte();
	int c = packet->readByte();
	int cc = packet->readByte();

	f_TfmPacketHandler handler = tfm::packets::handlers::recv::getPacketHandler(c, cc);

	if (handler)
		handler(packet);
	else
		log("hookedRecv() -> No handler found for [%i, %i]", c, cc);

	if (packet->isModified())
	{
		memcpy(buf, packet->getData(), packet->getLength());
		dataLength = packet->getLength();
	}
		

	delete packet;

	return dataLength;
}
