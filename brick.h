#pragma once
#include "cocos2d.h"
#include <string>
#include <list>
class Ball;
class Brick:public cocos2d::TMXTiledMap {
public:
	Ball* ball;
	std::list<cocos2d::Sprite*> container;
	bool init() override;
	Brick(std::string Path, Ball* ball);
	void update(float dot);
};
