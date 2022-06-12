#include"GameOverScene.h"
#include"HelloWorldScene.h"

USING_NS_CC;
Scene* GameOverScene::createGameOverScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size wndSize = getContentSize();
	auto label = Label::create();
	label->setString("GameOver");
	label->setPosition(Vec2(240, 300));
	this->addChild(label, 1);
	//����
	//
	//�������˳��Ĳ˵���ť
	auto menuItemImageEnter = MenuItemImage::create("Enter_Normal.png", "Enter_Push.png", CC_CALLBACK_1(GameOverScene::EnterGame, this));
	menuItemImageEnter->setPosition(Vec2(wndSize.width / 2 + menuItemImageEnter->getContentSize().width - 250, 30));
	auto menuItemImageOut = MenuItemImage::create("Out_Normal.png", "Out_push.png", CC_CALLBACK_1(GameOverScene::OutGame, this));
	menuItemImageOut->setPosition(Vec2(wndSize.width / 2 + menuItemImageEnter->getContentSize().width - 50, 30));
	auto menu = Menu::create(menuItemImageEnter, menuItemImageOut, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}
//������Ϸ
void GameOverScene::EnterGame(Ref* obj)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));//���ݿ��ƽ�����һ������,�߱�����Ч��
}
//�˳���Ϸ
void GameOverScene::OutGame(Ref* obj)
{
	Director::getInstance()->end();
}