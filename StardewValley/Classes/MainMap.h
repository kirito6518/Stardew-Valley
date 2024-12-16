#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"
#include "BackpackLayer.h"
#include "chipmunk.h"
#include "SeasonManager.h"

USING_NS_CC;

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
    
    //增加天数
    void MainMap::addDay(float dt);

    BackpackManager* Bag;
    SeasonManager seasonManager; // 声明 SeasonManager 实例
    Label* seasonLabel; // 声明 季节显示的 Label
    Label* dayLabel; // 声明 天数显示的 Label
private:
    Sprite* mapSprite; // 地图
    Sprite* upBoundary; // 地图上边界
    Sprite* rightBoundary; // 地图右边界
    Sprite* leftBoundary; // 地图左边界
    Sprite* downBoundary_left; // 地图下边界左半部分
    Sprite* downBoundary_right; // 地图下边界右半部分
    Sprite* upWater; // 水池上半部分
    Sprite* middleWater; // 水池中间部分
    Sprite* downWater; // 水池下半部分
    Sprite* fishing; // 钓鱼部分
    Sprite* CropsLeft; // 农田左部分
    Sprite* CropsRight; // 农田右部分
    Sprite* home; // 房屋
    Sprite* fence; // 栅栏
    Sprite* road; // 路
    Sprite* ranch;// 牧场
    Player player; // 玩家
    MenuItemImage* toHollowWorldButton; // 返回菜单的按钮
    Label* toHollowWorldWord; // 返回菜单按钮的文字
    MenuItemImage* backpackButton; // 开启背包的文字
};

#endif // __MainMap_H__