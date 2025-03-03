#pragma once 

#include "../ecs/Component.h"

class Texture;
class Transform;
class ImageWithFrames : public ecs::Component {
	Texture* _texture;
	Transform* _transform;
	int _frameWidth, _frameHeight, _currentFrameX, _currentFrameY, _frameCountX, _frameCountY;
	float _lastFrameChange;
public:
	__CMPID_DECL__(ecs::cmp::IMAGEWTEXTURE)
	ImageWithFrames(Texture* gridTexture, int frameWidth, int frameHeight, int frameCountX, int frameCountY);

	void render() override;
	void initComponent() override;
};