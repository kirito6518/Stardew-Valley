#include "Animal.h"
#include <string>
#include "cocos2d.h"

USING_NS_CC;

// ���캯��
Animal::Animal(const std::string& name, const std::string& productType, int numOfChild, int numOfAdult, int numOfOld) {

    this->name = name;
    this->productType = productType;
    this->numOfChild = numOfChild;
    this->numOfAdult = numOfAdult;
    this->numOfOld = numOfOld;

}