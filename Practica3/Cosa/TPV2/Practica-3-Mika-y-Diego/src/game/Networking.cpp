// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"
#include "netwrok_messages.h"
#include <iostream>

#include "../sdlutils/SDLNetUtils.h"
#include "Game.h"
#include "LittleWolf.h"

Networking::Networking() :
		_sock(), //
		_socketSet(), //
		_p(), //
		_srvadd(), //
		_clientId(), //
		_masterId() {
}

Networking::~Networking() {
}

bool Networking::init(char *host, Uint16 port) {

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
					std::cout << ">> " << (int) _masterId << std::endl;
					std::cout << ">> " << (int) _clientId << std::endl;
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
	std::cout << "Connected with id " << (int) _clientId << std::endl;
#endif

	std::cout << "Write a name:" << std::endl;
	
	char name[100];
	std::cin >> name;

	for (int i = 0; i < 10; ++i) {
		_name[i] = name[i];
	}
	_name[10] = 0;

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
	DamageMsg m6;
	NameMsg m7;

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

		case _DAMAGE:
			m6.deserialize(_p->data);
			handle_damage(m6);
			break;

		case _NAME:
			std::cout << "before deserialization" << std::endl;
			m7.deserialize(_p->data);
			std::cout << "after deserialization" << std::endl;
			handle_name(m7);
			break;

		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != _clientId) {
		Game::Instance()->getLittleWolf().updateState(id, LittleWolf::ALIVE);
		send_name();
	}
}

void Networking::handle_disconnet(Uint8 id) {
	Game::Instance()->getLittleWolf().removePlayer(id);
	if (id == _masterId) {
		Uint8 newId = Game::Instance()->getLittleWolf().getFirstExistingPlayer();
		_masterId = newId;
	}
}

void Networking::send_state(Uint8 id, float ax, float ay, float bx, float by, float whereX, float whereY, float velocityX, float velocityY, float speed,
	float acceleration, float theta, int hp, int state, int score) {
	PlayerStateMsg m;
	m._client_id = id;
	m.ax = ax;
	m.ay = ay;
	m.bx = bx;
	m.by = by;
	m.whereX = whereX;
	m.whereY = whereY;
	m.velocityX = velocityX;
	m.velocityY = velocityY;
	m.speed = speed;
	m.acceleration = acceleration;
	m.theta = theta;
	m.state = state;
	m._type = _PLAYER_STATE;
	m.score = score;
	m.hp = hp;

	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_player_state(const PlayerStateMsg &m) {
		
	LittleWolf::Player player;

	player.id = m._client_id;
	player.where = { m.whereX, m.whereY };
	player.speed = m.speed;
	player.acceleration = m.acceleration;
	player.fov = { {m.ax, m.ay}, {m.bx, m.by} };
	player.state = (LittleWolf::PlayerState)m.state;
	player.theta = m.theta;
	player.velocity = { m.velocityX, m.velocityY };
	player.hp = m.hp;
	player.score = m.score;

	Game::Instance()->getLittleWolf().updatePlayer(m._client_id, player);
}

void Networking::send_shoot(Uint8 id) {
	ShootMsg m;

	m._client_id = _clientId;
	m._type = _SHOOT;

	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_shoot(const ShootMsg &m) {
	sdlutils().soundEffects().at("gunshot").play();

	if (is_master()) {

		Game::Instance()->getLittleWolf().resolveShoot(m._client_id);
	}

}

void Networking::send_dead(Uint8 id) {
	MsgWithId m;
	m._type = _DEAD;
	m._client_id = id;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_dead(const MsgWithId &m) {
	std::cout << "I have to kill player " << (int)m._client_id << std::endl;
	if(!is_master()) Game::Instance()->getLittleWolf().killPlayer(m._client_id);
}

void Networking::send_my_info(float ax, float ay, float bx, float by, float whereX, float whereY, float velocityX, float velocityY, float speed,
	float acceleration, float theta, int hp, int state, int score) {
	PlayerInfoMsg m;
	m._type = _PLAYER_INFO;
	m._client_id = _clientId;
	m.ax = ax;
	m.ay = ay;
	m.bx = bx;
	m.by = by;
	m.whereX = whereX;
	m.whereY = whereY;
	m.velocityX = velocityX;
	m.velocityY = velocityY;
	m.speed = speed;
	m.acceleration = acceleration;
	m.theta = theta;
	m.state = state;
	m.score = score;
	m.hp = hp;
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
		player.state = (LittleWolf::PlayerState) m.state;
		player.theta = m.theta;
		player.velocity = { m.velocityX, m.velocityY };
		player.hp = m.hp;
		player.score = m.score;

		Game::Instance()->getLittleWolf().updatePlayer(m._client_id, player);
	}
}
void Networking::send_restart() {
	Msg m;
	m._type = _RESTART;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_restart() {
	Game::Instance()->getLittleWolf().setRestart(true);
}

void Networking::send_damage(Uint8 id, float damage, Uint8 shooter) {
	DamageMsg m;
	m._client_id = id;
	m._type = _DAMAGE;
	m.damage = damage;
	m.shooter = shooter;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_damage(const DamageMsg& m) {
	if(!is_master()) Game::Instance()->getLittleWolf().hitPlayer(m._client_id, m.damage);
	Game::Instance()->getLittleWolf().addScore(m.shooter);
}

void Networking::send_name() {
	NameMsg m;
	m._client_id = _clientId;
	for (int i = 0; i < 11; ++i) {
		m.name[i] = _name[i];
	}
	m._type = _NAME;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_name(const NameMsg& m) {
	if (_clientId != m._client_id) {
		std::string name;
		charToString(name, _name);
		Game::Instance()->getLittleWolf().updateName(m._client_id, m.name);
	}
}

void Networking::charToString(std::string& str, const char c_str[11]) {
	str = std::string(c_str);
}

void Networking::stringToChar(std::string& str, char c_str[11]) {
	auto i = 0u;
	for (; i < str.size() && i < 10; ++i) c_str[i] = str[i];
	c_str[i] = 0;
}