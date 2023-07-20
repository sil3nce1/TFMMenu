#include "tfm.hpp"



void tfm::packets::handlers::registerHandlers()
{
	recv::addPacketHandler(tfm::identifiers::recv::MouseMovement, (f_TfmPacketHandler)recv::handlePlayerMovement);
	recv::addPacketHandler(tfm::identifiers::recv::Crouch, (f_TfmPacketHandler)recv::handlePlayerCrouch);
	recv::addPacketHandler(tfm::identifiers::recv::PlaceObject, (f_TfmPacketHandler)recv::handlePlaceObject);

	send::addPacketHandler(tfm::identifiers::send::CorrectVersion, (f_TfmPacketHandler)send::handleCorrectVersion);
	send::addPacketHandler(tfm::identifiers::send::Login, (f_TfmPacketHandler)send::handleLogin);
	send::addPacketHandler(tfm::identifiers::send::OldProtocol, (f_TfmPacketHandler)send::handleOldProtocol);
}