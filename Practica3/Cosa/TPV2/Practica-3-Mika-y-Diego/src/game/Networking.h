// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "netwrok_messages.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	Uint8 client_id() {
		return _clientId;
	}

	bool is_master() {
		return _clientId == _masterId;
	}

	std::string getName() {
		std::string name;
		charToString(name, _name);
		return name;
	}

	void send_state(Uint8 id, float ax, float ay, float bx, float by, float whereX, float whereY, float velocityX, float velocityY, float speed,
		float acceleration, float theta, int hp, int state, int score);
	void send_my_info(float ax, float ay, float bx, float by, float whereX, float whereY, float velocityX, float velocityY,
		float speed, float acceleration, float theta, int hp, int state, int score);
	
	void send_shoot(Uint8 id);
	void send_dead(Uint8 id);
	void send_damage(Uint8 id, float damage, Uint8 shooter);
	void send_restart();
	void send_name();

private:
	void charToString(std::string& str, const char c_str[11]);
	void stringToChar(std::string& str, char c_str[11]);

	void handle_new_client(Uint8 id);
	void handle_disconnet(Uint8 id);
	void handle_player_state(const PlayerStateMsg &m);
	void handle_player_info(const PlayerInfoMsg& m);
	void handle_shoot(const ShootMsg &m);
	void handle_dead(const MsgWithId &m);
	void handle_damage(const DamageMsg& m);
	void handle_restart();
	void handle_name(const NameMsg& m);

	UDPsocket _sock;
	SDLNet_SocketSet _socketSet;
	UDPpacket *_p;
	IPaddress _srvadd;
	Uint8 _clientId;
	Uint8 _masterId;
	char _name[11];
};

