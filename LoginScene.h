#ifndef CLOGIN_SCENE_H
#define CLOGIN_SCENE_H

#include"cocos2d.h"
class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createLoginScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void EnterGame(Ref* obj);
    void OutGame(Ref* obj);

    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
};
#endif
