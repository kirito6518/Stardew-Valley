#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    // 初始化
    virtual bool init();

    // 前往主菜单场景
    void toMenu(Ref*);

    // 键盘按下事件处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 键盘释放事件处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 背包按钮的回调函数
    void onBackpackButtonClicked(Ref* sender);

    // 实现create函数
    CREATE_FUNC(MainMap);

private:
    cocos2d::Sprite* mapSprite;
    cocos2d::Sprite* playerSprite; // 主角精灵
    cocos2d::Animation* walkAnimations[6]; // 六个方向的行走动画
    cocos2d::Animation* idleAnimations[6]; // 六个方向的待机动画
    cocos2d::Vec2 targetPosition; // 目标位置
    bool isMoving; // 是否正在移动

    // 键盘状态
    bool isWPressed, isAPressed, isSPressed, isDPressed;

    // 最后一次行走的方向索引
    int lastDirectionIndex;

    // 创建六个方向的行走动画
    void createWalkAnimations();

    // 创建六个方向的待机动画
    void createIdleAnimations();

    // 根据方向选择动画
    int getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to);

    // 移动主角到目标位置
    void movePlayerTo(const cocos2d::Vec2& position);

    // 更新主角位置
    void updatePlayerPosition(float dt);

    // 每帧更新
    void update(float dt);
};

#endif // __MainMap_H__