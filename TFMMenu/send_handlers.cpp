#include "tfm.hpp"

std::vector<TfmPacketHandlerData> tfm::packets::handlers::send::packetHandlers;

bool tfm::packets::handlers::send::addPacketHandler(const int identifier[], f_TfmPacketHandler handler)
{
	return addPacketHandler(identifier[0], identifier[1], handler);
}

f_TfmPacketHandler tfm::packets::handlers::send::getPacketHandler(int c, int cc)
{
	for (int i = 0; i < packetHandlers.size(); i++)
	{
		TfmPacketHandlerData packetHandlerData = packetHandlers[i];
		if (packetHandlerData.c == c && packetHandlerData.cc == cc)
			return packetHandlerData.handler;
	}

	return nullptr;
}

bool tfm::packets::handlers::send::addPacketHandler(int c, int cc, f_TfmPacketHandler handler)
{
	// In case the packet handler already exists:
	if (getPacketHandler(c, cc) != nullptr)
		return false;

	TfmPacketHandlerData data = { c, cc, handler };
	packetHandlers.push_back(data);
	return true;
}

void tfm::packets::handlers::send::handleCorrectVersion(ByteArray* packet)
{
	int version = packet->readShort();
	std::string cKey = packet->readUTF();
	std::string client = packet->readUTF();
	std::string utiliSateur = packet->readUTF();
	int chargeur = packet->readInt();
	std::string emptyString = packet->readUTF();
	std::string h = packet->readUTF();
	std::string serverString = packet->readUTF();
	int x = packet->readInt();
	int xx = packet->readInt();
	std::string xxx = packet->readUTF();

	log("handleCorrectVersion() -> Version: [%i], CKey: [%s]", version, cKey.c_str());
}

void tfm::packets::handlers::send::handleLogin(ByteArray* packet)
{
	std::string username = packet->readUTF();
	std::string password = packet->readUTF();
	std::string url = packet->readUTF();
	std::string startRoom = packet->readUTF();

	tfm::variables::isTfmOriginal = url.find("transformice.com") != std::string::npos;

	packet->setPosition(0);

	for (int i = 0; i < packet->getLength(); i++)
	{
		printf("Packet: [%i] \n", packet->getData()[i]);
	}

	log("handleLogin() -> Username: [%i], Password: [%s], Url: [%s], StartRoom: [%s]", username, password, url, startRoom);
}

void tfm::packets::handlers::send::handleOldProtocol(ByteArray* packet)
{
	log("handleOldProtocol() -> Old Protocol packet sent");
}
