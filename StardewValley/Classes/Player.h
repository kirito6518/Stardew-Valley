#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "chipmunk.h"

USING_NS_CC;
class Player : public cocos2d::Sprite
{
public:

    // 构造函数
    Player();

    // 初始化函数
    virtual bool init();

    // 实现 CREATE_FUNC 宏
    CREATE_FUNC(Player);

    // 键盘按下事件处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 键盘释放事件处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    cocos2d::Sprite* playerSprite; // 主角精灵
    cocos2d::Animation* walkAnimations[6]; // 六个方向的行走动画
    cocos2d::Animation* idleAnimations[6]; // 六个方向的待机动画
    cocos2d::Vec2 targetPosition; // 目标位置

    // 键盘状态
    bool isWPressed, isAPressed, isSPressed, isDPressed;

    int lastWalkDirectionIndex; // 上一帧行走的方向，如果上一帧未行走就是6
    int lastIdleDirectionIndex; // 上一帧待机的方向，如果上一帧未待机就是6


    // 创建六个方向的行走动画
    void createWalkAnimations();

    // 创建六个方向的待机动画
    void createIdleAnimations();

    // 根据方向选择动画
    int getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to);

    // 更新主角位置
    void updatePlayerPosition(float dt);

    // 每帧更新
    void update(float dt);
};

#endif // __Player_H__