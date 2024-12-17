#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"
#include "BackpackLayer.h"
#include "chipmunk.h"
#include "SeasonManager.h"
#include "NPCManager.h"

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

    // 隐藏背包
    void hideBackpack(Ref* sender);

    // 实现create函数
    CREATE_FUNC(MainMap);

    // 每帧更新
    void MainMap::updatePlayerPosition(float dt);

    // 每帧更新
    void MainMap::updateCameraPosition(float dt);

    // 碰撞开始监听器
    bool MainMap::onContactBegin(PhysicsContact& contact);

    
    //增加天数
    void MainMap::addDay(float dt);


    // 设置物品在MainMap的使用逻辑,0是在空地，1是在左农场，2是在右农场
    void SetUseItemInMainMap();

    BackpackManager* Bag;
    SeasonManager seasonManager; // 声明 SeasonManager 实例
    Label* seasonLabel; // 声明 季节显示的 Label
    Label* dayLabel; // 声明 天数显示的 Label

    Item* OnionSeed;// 洋葱种子

private:
    Sprite* mapSprite; // 地图

    Sprite* upBoundary; // 地图上边界
    PhysicsBody* upBoundaryBox;
    Sprite* rightBoundary; // 地图右边界
    PhysicsBody* rightBoundaryBox;
    Sprite* leftBoundary; // 地图左边界
    PhysicsBody* leftBoundaryBox;
    Sprite* downBoundary_left; // 地图下边界左半部分
    PhysicsBody* downBoundary_leftBox;
    Sprite* downBoundary_right; // 地图下边界右半部分
    PhysicsBody* downBoundary_rightBox;
    Sprite* upWater; // 水池上半部分
    PhysicsBody* upWaterBox;
    Sprite* middleWater; // 水池中间部分
    PhysicsBody* middleWaterBox;
    Sprite* downWater; // 水池下半部分
    PhysicsBody* downWaterBox;
    Sprite* fishing; // 钓鱼部分
    PhysicsBody* fishingBox;
    Sprite* CropsLeft; // 农田左部分
    PhysicsBody* CropsLeftBox;
    Sprite* CropsRight; // 农田右部分
    PhysicsBody* CropsRightBox;
    Sprite* home; // 房屋
    PhysicsBody* homeBox;
    Sprite* fence; // 栅栏
    PhysicsBody* fenceBox;
    Sprite* road; // 路
    PhysicsBody* roadBox;
    Sprite* ranch;// 牧场
    PhysicsBody* ranchBox;

    Player player; // 玩家
    PhysicsBody* playerBox;

    MenuItemImage* toHollowWorldButton; // 返回菜单的按钮
    Label* toHollowWorldWord; // 返回菜单按钮的文字
    MenuItemImage* backpackButton; // 开启背包的文字
    NPCManager npcManager; // 声明 NPC 管理器实例

    int place;// 设置位置,0是在空地，1是在左农场，2是在右农场
};

#endif // __MainMap_H__