#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <string>
#include <vector>

USING_NS_CC;

// 动物类
class Animal : public Node {
public:

    // 构造函数
    Animal(const std::string& name, const std::string& productType, int numOfChild, int numOfAdult, int numOfOld);
 
    std::string name; // 动物名称
    std::string productType; // 产品名称
    std::vector<Sprite*> sprites; // 用于显示动物的精灵
    int numOfChild; // 该动物类型的幼年个体的数目
    int numOfAdult; // 该动物类型的成年个体的数目
    int numOfOld; // 该动物类型的老年个体的数目

    // 静态成员变量，存储动物的参数
    Animation* animations; // 动物的动画
};

#endif // ANIMAL_H