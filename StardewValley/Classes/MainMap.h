#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    // 初始化
    virtual bool init();

    // 前往主菜单场景
    void toMenu(Ref*);

    // 背包按钮的回调函数
    void onBackpackButtonClicked(Ref* sender);

    // 实现create函数
    CREATE_FUNC(MainMap);

    // 每帧更新
    void MainMap::updatePlayerPosition(float dt);

    // 每帧更新
    void MainMap::updateCameraPosition(float dt);

private:
    cocos2d::Sprite* mapSprite; // 地图
    Player player; // 玩家
    MenuItemImage* toHollowWorldButton; // 返回菜单的按钮
    Label* toHollowWorldWord; // 返回菜单按钮的文字
    MenuItemImage* backpackButton; // 开启背包的文字
};

#endif // __MainMap_H__