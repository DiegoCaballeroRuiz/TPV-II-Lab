// This file is part of the course TPV2@UCM - Samir Genaim


// Components list - must have at least one element
//
struct Transform;
struct Image;
struct Points;
struct TextureSrc;
struct Miraculous;
struct Immunity;
struct Health;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	Points, \
	TextureSrc, \
	Miraculous, \
	Immunity, \
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
class CollisionsSystem;
class GhostSystem;
class StateChangeSystem;
class ImmunitySystem;

#define _SYS_LIST_ \
    FruitSystem, \
	RenderSystem, \
	PacManSystem, \
	CollisionsSystem, \
	GhostSystem, \
	StateChangeSystem, \
	ImmunitySystem

