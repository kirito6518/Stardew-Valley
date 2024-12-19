#include "Animal.h"
#include <string>
#include "cocos2d.h"

USING_NS_CC;

// ¹¹Ôìº¯Êý
Animal::Animal(const std::string& name, const std::string& productType, Sprite* sprite, int numOfChild, int numOfAdult, int numOfOld) {

    this->name = name;
    this->productType = productType;
    this->sprites.push_back(sprite);
    this->numOfChild = numOfChild;
    this->numOfAdult = numOfAdult;
    this->numOfOld = numOfOld;

}