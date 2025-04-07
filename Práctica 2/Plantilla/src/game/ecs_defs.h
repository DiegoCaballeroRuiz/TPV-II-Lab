// This file is part of the course TPV2@UCM - Samir Genaim


// Components list - must have at least one element
//
struct Transform;
struct Image;
struct StarMotion;
struct Points;
struct TextureSrc;
struct Miraculous;
struct Inmunity;
struct Health;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	StarMotion, \
	Points, \
	TextureSrc, \
	Miraculous, \
	Inmunity, \
	Health
	

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	FRUITS, \
	GHOSTS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class FruitSystem;
class RenderSystem;
class PacManSystem;
class GameCtrlSystem;
class CollisionsSystem;
class GhostSystem;
class StarsSystem;

#define _SYS_LIST_ \
    FruitSystem, \
	RenderSystem, \
	PacManSystem, \
	GameCtrlSystem, \
	CollisionsSystem, \
	GhostSystem, \
	StarsSystem

