#include "tfm.hpp"

std::vector<TfmPacketHandlerData> tfm::packets::handlers::recv::packetHandlers;

bool tfm::packets::handlers::recv::addPacketHandler(const int identifier[], f_TfmPacketHandler handler)
{
	return addPacketHandler(identifier[0], identifier[1], handler);
}


f_TfmPacketHandler tfm::packets::handlers::recv::getPacketHandler(int c, int cc)
{
	for (int i = 0; i < packetHandlers.size(); i++)
	{
		TfmPacketHandlerData packetHandlerData = packetHandlers[i];
		if (packetHandlerData.c == c && packetHandlerData.cc == cc)
			return packetHandlerData.handler;
	}

	return nullptr;
}

bool tfm::packets::handlers::recv::addPacketHandler(int c, int cc, f_TfmPacketHandler handler)
{
	// In case the packet handler already exists:
	if (getPacketHandler(c, cc) != nullptr)
		return false;

	TfmPacketHandlerData data = { c, cc, handler };
	packetHandlers.push_back(data);
	return true;
}

void tfm::packets::handlers::recv::handlePlayerMovement(ByteArray* packet)
{
	int playerCode = packet->readInt();
	int roundCode = packet->readInt();
	bool droiteEnCours = packet->readBoolean();
	bool gaucheEnCours = packet->readBoolean();
	int posX = packet->readShort();
	int posY = packet->readShort();
	int vx = packet->readShort();
	int vy = packet->readShort();
	bool jump = packet->readBoolean();
	int jumpImg = packet->readByte();
	int portal = packet->readByte();

	TfmPlayer* tfmPlayer = tfm::room::getPlayerByCode(playerCode);

	if (tfmPlayer)
	{
		tfmPlayer->posX = posX;
		tfmPlayer->posY = posY;
	}

	tfm::room::roundCode = roundCode;

}

void tfm::packets::handlers::recv::handlePlayerCrouch(ByteArray* packet)
{
	if (!variables::isTfmOriginal && variables::packetArr)
		packet = variables::packetArr;
}

void tfm::packets::handlers::recv::handlePlaceObject(ByteArray* packet)
{
	int objectId = packet->readInt();
	int code = packet->readShort();
	int px = packet->readShort();
	int py = packet->readShort();
	int angle = packet->readShort();

	switch (code)
	{
		case enums::TfmObjects::Box:
			log("A box was created with id: [%i]", objectId);
			break;
	}

}
