#include "Ball.h"
#include "Paddle.h"
#include"GameOverScene.h"
USING_NS_CC;
Ball* Ball::createWithTexture(cocos2d::Texture2D* t2d, Paddle* paddle)//用Texture2D创建小球
{
    Ball* sprite_Ball = new (std::nothrow) Ball();
    sprite_Ball->initWithTexture(t2d);
    sprite_Ball->paddle = paddle;
    return sprite_Ball;
}
Ball::Ball()
{
    vec_ball = Vec2(0, 0);//球的向量
}
Ball::~Ball()
{
}
float Ball::length()//取球的半径
{
    float length= getTexture()->getContentSize().width / 2;
    return length;
}
void Ball::onEnter()
{
    Sprite::onEnter();
    schedule(CC_SCHEDULE_SELECTOR(Ball::move));//计时器小球移动
}
void Ball::move(float dot)//对于小球进行移动的实现
{
    auto max_size = Director::getInstance()->getVisibleSize();//取屏幕大小，方便之后做边界判断
    //移动球
    this->setPosition(vec_ball * dot+getPosition());//设定初始位置
    //不让球超过两侧以及最上端
    if (getPosition().x > max_size.width)
    {
        setPositionX(max_size.width);
        vec_ball.x *= -1;//球移动超过右边，作反向向量
    }
    else if (getPosition().x < 0)
    {
        setPositionX(0);
        vec_ball.x *= -1;//对于越过左边处理
    }
    if (getPositionY() > max_size.height)
    {
        setPositionY(max_size.height);
        vec_ball.y *= -1;//球碰到上端的处理
    }
    this->ColldeWithPaddle(paddle);
    if (this->getPositionY() < 0)
    {
        auto scene = GameOverScene::createGameOverScene();
        Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
    }
}
void Ball::ColldeWithPaddle(Paddle* pad)
{
    auto PaddleRect = pad->getRect();//获取底座矩形，便于判断碰撞
    PaddleRect.origin.x += pad->getPosition().x;
    PaddleRect.origin.y += pad->getPosition().y;
    float Highest_Y = PaddleRect.getMaxY();//取矩形最上端
    float Lowest_Y = PaddleRect.getMinY();//取得矩形最底部
    float Left_of_X = PaddleRect.getMinX();//取矩形左侧值
    float Right_of_X = PaddleRect.getMaxX();//取右侧的值
    float Middle_Y = PaddleRect.getMidY();//取矩形中部
    if (getPosition().x < Right_of_X&& getPosition().x > Left_of_X)//小球进入了矩形两端的x的范围
    {
        float angle = 0;
        bool Collision = false;//定义bool类型撞击为假
        if (getPosition().y <= Highest_Y + length()&& getPosition().y > Middle_Y)//撞击上侧
        {
            setPosition(getPosition().x, Highest_Y + length());
            angle = (float)M_PI / 2;
            Collision= true;
        }
        else if (getPosition().y < Middle_Y && getPosition().y >= Lowest_Y - length())//下侧
        {
            setPosition(getPosition().x,Lowest_Y - length());
            angle= -(float)M_PI / 2;   
            Collision = true;
        }
        if (Collision)//确定碰撞事件为真后进行角度计算获得方向
        {
            float ColledeAngle = (pad->getPosition() - getPosition()).getAngle() + angle;//获得角度
            float New_vec = vec_ball.getLength() * 1.0f;
            float Vec_Angle = -vec_ball.getAngle() + ColledeAngle*0.5f;
            vec_ball = Vec2::forAngle(Vec_Angle) * New_vec;//根据角度计算小球运行方向向量
        }
    }
}
