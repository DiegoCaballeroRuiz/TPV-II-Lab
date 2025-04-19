// This file is part of the course TPV2@UCM - Samir Genaim

#include "NetworkSystem.h"

#include <iostream>

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "BallSystem.h"
#include "GameCtrlSystem.h"
#include "network_messages.h"
#include "PaddlesSystem.h"

NetworkSystem::NetworkSystem() :
		_host(false), //
		_side(0), //
		_sock(), //
		_p(), //
		_sockSet(), //
		_port(), //
		_connected(false), //
		_otherPlayerAddr() {

}

NetworkSystem::~NetworkSystem() {
	if (_p != nullptr) {
		SDLNet_UDP_Close(_sock);
		SDLNet_FreePacket(_p);
	}
}

void NetworkSystem::recieve(const Message &m) {
	if (!_host)
		return;

	switch (m.id) {
	case _m_ROUND_START:
		tellOtherClientToStartRound();
		break;
	case _m_NEW_GAME:
		tellOtherClientToStartGame();
		break;
	case _m_BALL_EXIT:
		tellOtherClientBallExit(
				static_cast<GameCtrlSystem::Side>(m.ball_exit.side));
		break;
	default:
		break;
	}
}

void NetworkSystem::initSystem() {
}

bool NetworkSystem::connect() {

	char choice;
	bool done = false;
	bool success = false;

	while (!done) {
		std::cout << "Do you want to be host, client or exit [h/c/e]? "
				<< std::endl;
		std::cin >> choice;
		switch (choice) {
		case 'h':
		case 'H':
			success = initHost();
			done = true;
			break;
		case 'c':
		case 'C':
			success = initClient();
			done = true;
			break;
		case 'e':
		case 'E':
			done = true;
			break;
		default:
			break;
		}
	}

	return success;
}

void NetworkSystem::disconnect() {
	if (!_connected)
		return;

	net::Message m;

	m.id = net::_DISCONNECTING;
	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock);

}

void NetworkSystem::update() {
	net::Message m;
	while (SDLNetUtils::deserializedReceive(m, _p, _sock) > 0) {
		switch (m.id) {
		case net::_CONNECTION_REQUEST:
			handleConnectionRequest();
			break;
		case net::_PADDLE_POS:
			handlePaddlePos();
			break;
		case net::_BALL_POS:
			handleBallPos();
			break;
		case net::_BALL_VEL:
			handleBallVel();
			break;
		case net::_START_GAME_REQUEST:
			handleStartGameRequest();
			break;
		case net::_START_ROUND_REQUEST:
			handleStartRoundRequest();
			break;
		case net::_START_THE_GAME:
			handleStartTheGame();
			break;
		case net::_START_THE_ROUND:
			handleStartTheRound();
			break;
		case net::_BALL_EXIT:
			handleBallExit();
			break;
		case net::_DISCONNECTING:
			handleDisconnecting();
			break;
		default:
			break;
		}

	}

}

bool NetworkSystem::initConnection(Uint16 port) {
	_sock = SDLNet_UDP_Open(port);
	if (!_sock) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_sockSet = SDLNet_AllocSocketSet(1);
	if (!_sockSet) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(_sockSet, _sock);
	_p = SDLNet_AllocPacket(512);
	if (!_p) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_port = SDLNetUtils::getSocketPort(_sock);

	return true;
}

bool NetworkSystem::initHost() {

	Uint16 port;
	std::cout << "Enter a port number to use: ";
	if (!(std::cin >> port)) {
		std::cerr << "Invalid port" << std::endl;
		return false;
	}

	if (!initConnection(port))
		return false;

	_host = true;
	_side = 0;
	_connected = false;
	return true;

}

bool NetworkSystem::initClient() {

	Uint16 port;
	std::string host;

	std::cout << "Enter the host and port (separated by space) of the host: "
			<< std::endl;
	if (!(std::cin >> host >> port)) {
		std::cerr << "Invalid host/port" << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&_otherPlayerAddr, host.c_str(), port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_host = false;

	initConnection(0);

	net::Message m;

	m.id = net::_CONNECTION_REQUEST;
	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock);

	if (SDLNet_CheckSockets(_sockSet, 3000) > 0) {
		if (SDLNet_SocketReady(_sock)) {
			SDLNetUtils::deserializedReceive(m, _p, _sock);
			if (m.id == net::_REQUEST_ACCEPTED) {
				net::ReqAccMsg m;
				m.deserialize(_p->data);
				_side = m.side;
				_host = false;
				_connected = true;
			}

		}
	}

	if (!_connected) {
		std::cout << "Could not connect to the other player " << std::endl;
		return false;
	}

	return true;

}

void NetworkSystem::sendPaddlePosition(Transform *tr) {
	if (!_connected)
		return;

	net::PaddelPosMsg m;
	m.id = net::_PADDLE_POS;
	m.side = _side;
	m.x = tr->_pos.getX();
	m.y = tr->_pos.getY();
	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);
}

void NetworkSystem::sendBallPosition(Transform *tr) {
	if (!_connected)
		return;

	net::BallPosMsg m;
	m.id = net::_BALL_POS;
	m.side = _side;
	m.x = tr->_pos.getX();
	m.y = tr->_pos.getY();
	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);
}

void NetworkSystem::sendBallVelocity(Transform *tr) {
	if (!_connected || !_host)
		return;

	net::BallVelMsg m;
	m.id = net::_BALL_VEL;
	m.side = _side;
	m.x = tr->_vel.getX();
	m.y = tr->_vel.getY();
	std::cout << ">> " << m.x << " " << m.y << std::endl;

	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);
}

void NetworkSystem::handleConnectionRequest() {

	if (!_connected && _host) {
		_otherPlayerAddr = _p->address;
		_connected = true;
		net::ReqAccMsg m;
		m.id = net::_REQUEST_ACCEPTED;
		m.side = 1 - _side;
		SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);
	}
}

void NetworkSystem::sendStarRoundtRequest() {
	assert(!isHost());

	net::StartRequestMsg m;

	m.id = net::_START_ROUND_REQUEST;
	m.side = _side;
	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);

}

void NetworkSystem::sendStarGameRequest() {
	assert(!isHost());

	net::StartRequestMsg m;

	m.id = net::_START_GAME_REQUEST;
	m.side = _side;
	_p->address = _otherPlayerAddr;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);

}

void NetworkSystem::handlePaddlePos() {
	net::PaddelPosMsg m;
	m.deserialize(_p->data);
	_mngr->getSystem<PaddlesSystem>()->changePaddlePos(m.side, m.x, m.y);
}

void NetworkSystem::handleBallPos() {
	assert(!_host);
	net::BallPosMsg m;
	m.deserialize(_p->data);
	_mngr->getSystem<BallSystem>()->changeBallPos(m.x, m.y);
}

void NetworkSystem::handleBallVel() {
	assert(!_host);
	net::BallVelMsg m;
	m.deserialize(_p->data);
	_mngr->getSystem<BallSystem>()->changeBallVel(m.x, m.y);
}

void NetworkSystem::handleStartGameRequest() {
	_mngr->getSystem<GameCtrlSystem>()->startGame();
}

void NetworkSystem::handleStartRoundRequest() {
	_mngr->getSystem<GameCtrlSystem>()->startRound();
}

void NetworkSystem::handleStartTheGame() {
	assert(!_host);
	_mngr->getSystem<GameCtrlSystem>()->startGame();
}

void NetworkSystem::handleStartTheRound() {
	assert(!_host);
	_mngr->getSystem<GameCtrlSystem>()->startRound();
}

void NetworkSystem::handleGameOver() {
	assert(!_host);
	_mngr->getSystem<GameCtrlSystem>()->gameOver();
}

void NetworkSystem::handleBallExit() {
	net::BallExitMsg m;
	m.deserialize(_p->data);
	_mngr->getSystem<GameCtrlSystem>()->onBallExit(m.side);
}

void NetworkSystem::handleDisconnecting() {
	_connected = false;
	_host = true;
	_mngr->getSystem<GameCtrlSystem>()->stopTheGame();
}

void NetworkSystem::tellOtherClientToStartRound() {
	net::Message m;

	m.id = net::_START_THE_ROUND;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);

}

void NetworkSystem::tellOtherClientToStartGame() {
	net::Message m;

	m.id = net::_START_THE_GAME;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);
}

void NetworkSystem::tellOtherClientBallExit(Uint8 side) {
	net::BallExitMsg m;

	m.id = net::_BALL_EXIT;
	m.side = side;
	SDLNetUtils::serializedSend(m, _p, _sock, _otherPlayerAddr);

}

