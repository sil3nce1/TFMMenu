#include "tfm.hpp"

int tfm::network::lastPacketId = 0;
f_send tfm::network::oSend = nullptr;
f_recv tfm::network::oRecv = nullptr;
SOCKET tfm::network::socket;

int tfm::network::sendPacket(ByteArray packet)
{
	ByteArray dataArr;
	dataArr.writeByte(packet.getLength());
	dataArr.writeByte(lastPacketId);
	dataArr.writeBytes(packet.getData(), packet.getLength());
	return oSend(socket, dataArr.getData(), dataArr.getLength(), 0);
}

void tfm::network::recvPacket(ByteArray packet)
{
	if (!variables::isTfmOriginal)
		me::sendCrouch();

	ByteArray* byteArr = new ByteArray(packet.getData(), packet.getLength(), true);
	variables::packetArr = byteArr;
}