#ifndef CGAMEOVER_SCENE_H
#define CGAMEOVER_SCENE_H

#include"cocos2d.h"
class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createGameOverScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void EnterGame(Ref* obj);
    void OutGame(Ref* obj);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};
#endif
