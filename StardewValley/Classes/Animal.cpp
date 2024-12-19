#include "Animal.h"
#include <string>
#include "cocos2d.h"

USING_NS_CC;

// ���캯��
Animal::Animal(const std::string& name, const std::string& productType, Sprite* sprite, int numOfChild, int numOfAdult, int numOfOld, Animation* animations) {
    this->name = name;
    this->productType = productType;
    this->sprite = sprite;
    this->numOfChild = numOfChild;
    this->numOfAdult = numOfAdult;
    this->numOfOld = numOfOld;

    // ��̬��Ա�������洢����Ĳ���
    this->animations = animations;
}