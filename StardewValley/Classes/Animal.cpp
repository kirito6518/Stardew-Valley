#include "Animal.h"
#include <string>
#include "cocos2d.h"

USING_NS_CC;

// 构造函数
Animal::Animal(const std::string& name, const std::string& productType, Sprite* sprite, int numOfChild, int numOfAdult, int numOfOld, Animation* animations) {
    this->name = name;
    this->productType = productType;
    this->sprite = sprite;
    this->numOfChild = numOfChild;
    this->numOfAdult = numOfAdult;
    this->numOfOld = numOfOld;

    // 静态成员变量，存储动物的参数
    this->animations = animations;
}