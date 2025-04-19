// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <SDL_net.h>

using namespace std;

// SDL misc functions

void error() {
	cout << "Error: " << SDLNet_GetError() << endl;
	exit(1);
}

// print address
inline void print_address(IPaddress ip, bool newline = false) {
	std::cout << (ip.host & 0xFF) << "." //
			<< ((ip.host >> 8) & 0xFF) << "." //
			<< ((ip.host >> 16) & 0xFF) << "." //
			<< ((ip.host >> 24) & 0xFF) << ":" << ip.port;

	if (newline)
		std::cout << std::endl;
}

// print an IPv4
inline void print_ip(Uint32 ip, bool newline = false) {
	std::cout << (ip & 0xFF) << "." //
			<< ((ip >> 8) & 0xFF) << "." //
			<< ((ip >> 16) & 0xFF) << "." //
			<< ((ip >> 24) & 0xFF);
	if (newline)
		std::cout << std::endl;
}

inline Uint16 sdlnet_htons(Uint16 v) {
	Uint16 nv;
	SDLNet_Write16(v, &nv);
	return nv;
}

inline Uint16 sdlnet_ntohs(Uint16 nv) {
	return SDLNet_Read16(&nv);
}

// server
void server(Uint16 port) {
}

// client
void client(const char *host, Uint16 port) {
}

int main(int argc, char **argv) {

	// initialize SDLNet
	if (SDLNet_Init() < 0) {
		error();
	}

	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(static_cast<Uint16>(atoi(argv[2]))); // start in server mode
	} else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], static_cast<Uint16>(atoi(argv[3]))); // start in client mode
	} else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000" << endl;
	}

	// finalize SDLNet
	SDLNet_Quit();

	return 0;
}
