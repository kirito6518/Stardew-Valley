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



private:
    // 私有构造函数，防止外部直接实例化
    AnimalManager();

    // 单例实例
    static AnimalManager* _instance;
};

#endif // _ANIMAL_MANAGER_H