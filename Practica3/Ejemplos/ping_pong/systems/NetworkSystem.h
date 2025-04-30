// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "../ecs/System.h"

struct Transform;

class NetworkSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::_sys_NETWORK)

	NetworkSystem();
	virtual ~NetworkSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

	bool connect();
	void disconnect();

	inline Uint8 getSide() {
		return _side;
	}

	inline bool isReday() {
		return _connected;
	}

	inline bool isHost() {
		return _host;
	}

	inline Uint16 getPort() {
		return _port;
	}

	void sendPaddlePosition(Transform *tr);
	void sendBallPosition(Transform *tr);
	void sendBallVelocity(Transform *tr);
	void sendStarRoundtRequest();
	void sendStarGameRequest();

private:

	bool initHost();
	bool initClient();
	bool initConnection(Uint16 port);

	void handleConnectionRequest();
	void handlePaddlePos();
	void handleBallPos();
	void handleBallVel();
	void handleStartGameRequest();
	void handleStartRoundRequest();
	void handleStartTheGame();
	void handleStartTheRound();
	void handleBallExit();
	void handleGameOver();
	void handleDisconnecting();

	void tellOtherClientToStartRound();
	void tellOtherClientToStartGame();
	void tellOtherClientBallExit(Uint8 side);

	bool _host;
	Uint8 _side; // 0 left 1 right
	UDPsocket _sock;
	UDPpacket *_p;
	SDLNet_SocketSet _sockSet;
	Uint16 _port;

	bool _connected;
	IPaddress _otherPlayerAddr;

};

