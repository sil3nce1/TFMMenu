#include "tfm.hpp"



void tfm::me::marryPlayer(char* playerName)
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::Tribulle);
	packet.writeShort(24);
	packet.writeInt(2);
	packet.writeUTF(playerName);
	packet.writeByte(1);
	tfm::network::sendPacket(packet);
}

void tfm::me::sendCrouch()
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::Crouch);
	packet.writeByte(1);
	tfm::network::sendPacket(packet);
}

void tfm::me::sendMeep(int posX, int posY)
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::Meep);
	packet.writeShort(posX);
	packet.writeShort(posY);
	tfm::network::sendPacket(packet);
}