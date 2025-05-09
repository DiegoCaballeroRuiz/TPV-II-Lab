// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"
#include "netwrok_messages.h"
#include <iostream>

#include "../sdlutils/SDLNetUtils.h"
#include "Game.h"
#include "LittleWolf.h"
#include "../utils/Vector2D.h"

Networking::Networking(Game* game) :
		_game(game),
		_sock(), //
		_socketSet(), //
		_p(), //
		_srvadd(), //
		_clientId(), //
		_masterId() {
}

Networking::~Networking() {
}

bool Networking::init(char* host, Uint16 port) {

	if (SDLNet_ResolveHost(&_srvadd, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_sock = SDLNet_UDP_Open(0);
	if (!_sock) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_p = SDLNet_AllocPacket(512);
	if (!_p) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(_socketSet, _sock);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, _p, _sock, _srvadd);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(_socketSet, 3000) > 0) {
		if (SDLNet_SocketReady(_sock)) {
			if (SDLNetUtils::deserializedReceive(m0, _p, _sock) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(_p->data);
					_clientId = m1._client_id;
					_masterId = m1._master_id;
					std::cout << ">> " << (int)_masterId << std::endl;
					std::cout << ">> " << (int)_clientId << std::endl;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int)_clientId << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = _clientId;
	return (SDLNetUtils::serializedSend(m, _p, _sock, _srvadd) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	MsgWithId m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, _p, _sock) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			m1.deserialize(_p->data);
			_masterId = m1._master_id;
			handle_new_client(m1._client_id);
			break;

		case _DISCONNECTED:
			m1.deserialize(_p->data);
			_masterId = m1._master_id;
			handle_disconnet(m1._client_id);
			break;

		case _PLAYER_STATE:
			m2.deserialize(_p->data);
			handle_player_state(m2);
			break;

		case _PLAYER_INFO:
			m5.deserialize(_p->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			m3.deserialize(_p->data);
			handle_shoot(m3);
			break;

		case _DEAD:
			m4.deserialize(_p->data);
			handle_dead(m4);
			break;

		case _RESTART:
			handle_restart();
			break;

		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != _clientId)
		_game->getLittleWolf()->addPlayer(id);
}

void Networking::handle_disconnet(Uint8 id) {

	_game->getLittleWolf()->removePlayer(id);
	if (id == _masterId) {
		Uint8 newId = _game->getLittleWolf()->getFirstExistingPlayer();
		_masterId  = newId;
	}
}


void Networking::send_shoot(Uint8 id, LittleWolf::Line fov) {
	ShootMsg m;

	m._client_id = _clientId;
	m._type = _SHOOT;

	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_shoot(const ShootMsg &m) {
	if (m._client_id != _clientId) {

		if(is_master()) _game->getLittleWolf()->shoot(m._client_id);
	}
}

void Networking::send_dead(Uint8 id) {
	MsgWithId m;
	m._type = _DEAD;
	m._client_id = id;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_dead(const MsgWithId &m) {
	if(is_master()) _game->getLittleWolf()->killPlayer(m._client_id);
}

void Networking::send_my_info(float ax, float ay, float bx, float by, float whereX, float whereY, float velocityX, float velocityY,	float speed, float acceleration, float theta, LittleWolf::PlayerState state) {
	PlayerInfoMsg m = { ax, ay, bx, by, whereX, whereY, velocityX, velocityY, speed, acceleration, theta, state };
	
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}



void Networking::handle_player_info(const PlayerInfoMsg &m) {
	if (m._client_id != _clientId) {
		LittleWolf::Player player;
		
		player.id = m._client_id;
		player.where = { m.whereX, m.whereY };
		player.speed = m.speed;
		player.acceleration = m.acceleration;
		player.fov = { {m.ax, m.ay}, {m.bx, m.by} };
		player.state = m.state;
		player.theta = m.theta;
		player.velocity = { m.velocityX, m.velocityY };

		_game->getLittleWolf()->updatePlayer(m._client_id, player);
	}
}

void Networking::send_restart() {
	Msg m;
	m._type = _RESTART;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_restart() {
	_game->getLittleWolf()->restart();
}

void Networking::send_player_state(Uint8 id, LittleWolf::PlayerState state) {
	PlayerStateMsg m;
	m._client_id = id;
	m._type = _PLAYER_STATE;

	m.state = state;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_player_state(const PlayerStateMsg &m) {
	if (m._client_id != _clientId) {
		_game->getLittleWolf()->updateState(m._client_id, m.state);
	}
}