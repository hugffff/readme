#include"LoginScene.h"
#include"HelloWorldScene.h"

USING_NS_CC;
Scene* LoginScene::createLoginScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}
bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size wndSize = getContentSize();
	auto label = Label::create();
	label->setString("Hit The Brick");
	label->setPosition(Vec2(240, 300));
	this->addChild(label, 1);
	//����
	auto spriteBack = Sprite::create("HelloWorld.png");
	spriteBack->setPosition(Vec2(wndSize.width/2,wndSize.height/2));
	this->addChild(spriteBack);
	//
	//�������˳��Ĳ˵���ť
	auto menuItemImageEnter = MenuItemImage::create("Enter_Normal.png", "Enter_Push.png", CC_CALLBACK_1(LoginScene::EnterGame,this));
	menuItemImageEnter->setPosition(Vec2(wndSize.width / 2 + menuItemImageEnter->getContentSize().width - 400,30));
	auto menuItemImageOut = MenuItemImage::create("Out_Normal.png", "Out_push.png", CC_CALLBACK_1(LoginScene::OutGame, this));
	menuItemImageOut->setPosition(Vec2(wndSize.width / 2 + menuItemImageEnter->getContentSize().width -150, 30));
	auto menu = Menu::create(menuItemImageEnter, menuItemImageOut, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}
//������Ϸ
void LoginScene::EnterGame(Ref* obj)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1,scene));//���ݿ��ƽ�����һ������,�߱�����Ч��
}
//�˳���Ϸ
void LoginScene::OutGame(Ref* obj)
{
	Director::getInstance()->end();
}