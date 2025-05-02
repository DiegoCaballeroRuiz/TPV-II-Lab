// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../sdlutils/SDLNetUtils.h"
#include "LittleWolf.h"

enum MsgType : Uint8 {
	_NONE = 0, //
	_CONNECTION_REQUEST, //
	_CONNECTION_ACCEPTED, //
	_CONNECTION_REJECTED, //
	_DISCONNECTED,
	_NEW_CLIENT_CONNECTED, //
	_PLAYER_STATE, // sent frequently to boradcast the state
	_PLAYER_INFO, // sent only the first time the player connects
	_SHOOT, //
	_DEAD, //
	_RESTART
};

struct Msg {
	Uint8 _type;

	_IMPL_SERIALIAZION_(_type)
};

struct MsgWithId: Msg {
	Uint8 _client_id;

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,_client_id)
};

struct MsgWithMasterId: MsgWithId {
	Uint8 _master_id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,_master_id)
};

struct PlayerStateMsg: MsgWithId {

	LittleWolf::PlayerState state;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, int(state))

};

struct PlayerInfoMsg: MsgWithId {

	float ax, ay, bx, by;			// To create fov
	float whereX, whereY;			// To create where(wrt. to the grid)
	float velocityX, velocityY;	    // To create velocity
	float speed;					// maximum speed
	float acceleration;				// acceleration
	float theta;					// rotation (in rad)
	LittleWolf::PlayerState state;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, ax, ay, bx, by, whereX, whereY, velocityX, velocityY, speed, acceleration, theta, (int)state);
};
struct ShootMsg: MsgWithId {


	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId);

};
