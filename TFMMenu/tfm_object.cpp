#include "tfm.hpp"



void TfmObject::sendDelete()
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::DemolitionSkill);
	packet.writeInt(objectId);
	tfm::network::sendPacket(packet);
}

void TfmObject::sendAntiGravity()
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::AntigravitySkill);
	packet.writeInt(objectId);
	tfm::network::sendPacket(packet);
}