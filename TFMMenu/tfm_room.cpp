#include "tfm.hpp"

std::vector<TfmPlayer*> tfm::room::players;
std::vector<TfmObject*> tfm::room::objects;
int tfm::room::roundCode = 0;

TfmPlayer* tfm::room::getPlayerByName(char* playerName)
{
	for (int i = 0; i < players.size(); i++)
	{
		TfmPlayer* currentPlayer = players[i];

		if (strcmp(playerName, currentPlayer->playerName.c_str()) == 0)
			return currentPlayer;
	}

	return nullptr;
}

TfmPlayer* tfm::room::getPlayerByCode(int playerCode)
{
	for (int i = 0; i < players.size(); i++)
	{
		TfmPlayer* currentPlayer = players[i];

		if (currentPlayer->playerCode == playerCode)
			return currentPlayer;
	}

	return nullptr;
}

TfmPlayer* tfm::room::getPlayerByName(std::string playerName)
{
	return getPlayerByName(playerName.c_str());
}

void tfm::room::sendAllPlayersEmote(int emoteId)
{
	for (int i = 0; i < players.size(); i++)
	{
		TfmPlayer* currentPlayer = players[i];
		if (currentPlayer)
			currentPlayer->sendEmote(emoteId);
	}
}

void tfm::room::sendChatMessage(char* message)
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::ChatMessage);
	packet.writeUTF(message);
	tfm::network::sendPacket(packet);
}

void tfm::room::changeGravity(int velX, int velY)
{
	ByteArray packet;
	packet.writeIdentifier(tfm::identifiers::send::GravitySkill);
	packet.writeShort(velX);
	packet.writeShort(velY);
	tfm::network::sendPacket(packet);
}

std::vector<TfmObject*> tfm::room::getAllObjects()
{
	return objects;
}

std::vector<TfmPlayer*> tfm::room::getAllPlayers()
{
	return players;
}