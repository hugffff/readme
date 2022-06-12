#pragma once
#ifndef BALL_H
#include "cocos2d.h"
class Paddle;
class Ball :public cocos2d::Sprite
{
public:
	Ball();
	virtual ~Ball();
	//半径
	float length();
	void onEnter() override;
	//小球移动
	void move(float dot);
	//检测碰撞
	cocos2d::Vec2 vec_ball;
	Paddle* paddle;
	void ColldeWithPaddle(Paddle* pad);
	static Ball* createWithTexture(cocos2d::Texture2D* t2d, Paddle* paddle);
};

#define BALL_H
#endif // BALL_H
