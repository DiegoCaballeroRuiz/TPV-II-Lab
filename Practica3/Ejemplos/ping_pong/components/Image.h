// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Texture;

struct Image: ecs::Component {

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_IMAGE
	//
	__CMPID_DECL__(ecs::cmp::_IMAGE)

	Image() :
			_tex(nullptr) {
	}
	Image(Texture *tex) :
			_tex(tex) {
	}
	virtual ~Image() {
	}

	Texture *_tex;
};

