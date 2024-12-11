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
    void MainMap::update(float dt);

private:
    cocos2d::Sprite* mapSprite;    
    Player player;
};

#endif // __MainMap_H__