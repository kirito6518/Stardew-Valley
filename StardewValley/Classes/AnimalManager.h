#ifndef _ANIMAL_MANAGER_H
#define _ANIMAL_MANAGER_H

#include "cocos2d.h"
#include <string>
#include "Animal.h"

USING_NS_CC;

// 动物管理器
class AnimalManager : public Layer {
public:

    // 获取单例实例
    static AnimalManager* getInstance();

    // 初始化
    virtual bool init();

    // 加载动画
    void CreateAnimations(std::string& name);

    // 增加动物（只增加幼年个体）
    bool AnimalManager::AddAnimal(const std::string& name);

    // 删除动物（只删除成年个体）
    bool AnimalManager::RemoveAnimal(const std::string& name);

    // 删除一个老年个体（老死）
    void OldDie(const std::string& name);

    // 每帧更新，如果到指定时间，所有个体会成长一个阶段
    void UpdateAnimals(float dt);

    // 关闭牧场
    void HideRanch(Ref* sender);

    // 生成一对随机浮点数 (x, y)，并返回 Vec2
    Vec2 GenerateRandomPosition();

    // 生成四种动物的数目
    void CreateNumber();

    Sprite* ranchLayer; // 牧场界面
    MenuItemImage* outButton; // 退出按钮

    MenuItemImage* BuyButtonPig; // 买入
    MenuItemImage* KillButtonPig; // 屠宰
    MenuItemImage* BuyButtonCow; // 买入
    MenuItemImage* KillButtonCow; // 屠宰
    MenuItemImage* BuyButtonSheep; // 买入
    MenuItemImage* KillButtonSheep; // 屠宰
    MenuItemImage* BuyButtonChook; // 买入
    MenuItemImage* KillButtonChook; // 屠宰

    Animal* animals[4]; // 四种动物，0是猪，1是牛，2是羊，3是鸡
    Label* animalNum[4]; // 四种动物的数量显示

    unsigned int timeRecord; // 记录上次记录的时间，从而规划动物的长大
    unsigned int Time; // 每个阶段的生长时间

    Scene* mainMap;
private:
    // 私有构造函数，防止外部直接实例化
    AnimalManager();

    // 单例实例
    static AnimalManager* _instance;
};

#endif // _ANIMAL_MANAGER_H