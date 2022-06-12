#include "brick.h"
#include "Ball.h"
#include"HelloWorldScene.h"
#include <algorithm>
USING_NS_CC;
Brick::Brick(std::string Path, Ball* ball):ball(ball)
{
	initWithTMXFile(Path);
	init();
	this->autorelease();//释放
}
bool Brick::init()//对于地图初始化
{
	if (!TMXTiledMap::init())
	{
		return false;
	}
	auto layer = this->getLayer("Block");
	Size map_size = this->getMapSize();//获得的地图大小
	for (int i = 0; i < map_size.height; i++)//利用循环往地图中添加砖块
	{
		for (int j = 0; j < map_size.width; j++)
		{
			auto location = layer->getTileGIDAt(Vec2(j, i));
			CCLOG("i:%d j:%d location:%d", i, j, location);
			if (!(location== 0))
			{
				auto spritebrick = layer->getTileAt(Vec2(j, i));
				container.push_back(spritebrick);
			}
		}
	}
	scheduleUpdate();
	return true;
}
void Brick::update(float dot)
{
	//循环判断砖块撞击并对实时状态进行更新
	for (auto goal_brick = container.begin(); !(goal_brick== container.end()); goal_brick++) {
		if (ball->getBoundingBox().intersectsRect((*goal_brick)->getBoundingBox()))//进行撞击判断
		{
			auto rect = (*goal_brick)->getCenterRect();//取碰撞的砖块矩形
			auto position = ball->vec_ball;
			auto Min_X = std::min(std::abs(position.x - rect.getMinX()), std::abs(position.x - rect.getMaxX()));
			auto Min_Y = std::min(std::abs(position.y - rect.getMinY()), std::abs(position.y - rect.getMaxY()));
			if (Min_X> Min_Y)
			{
				ball->vec_ball.y = -ball->vec_ball.y;
			}
			else 
			{
				ball->vec_ball.x = -ball->vec_ball.x;
			}//对于左右碰撞向量的不同处理
			(*goal_brick)->removeFromParent();//将砖块从场景中移除
			container.erase(goal_brick);//同步移除容器中的brick
			if (container.empty())
			{
				auto label = Label::create();
				label->setString("You Win The Game");
				label->setPosition(Vec2(240, 300));
				this->addChild(label, 1);
				auto scene = HelloWorld::createScene();
				Director::getInstance()->replaceScene(TransitionCrossFade::create(3, scene));
			}
			break;
		}
	}
}
