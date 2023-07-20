#include "tfm.hpp"



void TfmPlayer::sendEmote(int emoteId)
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::Emote);
	packet.writeByte(emoteId);
	packet.writeByte(playerCode);
	tfm::network::sendPacket(packet);
}

