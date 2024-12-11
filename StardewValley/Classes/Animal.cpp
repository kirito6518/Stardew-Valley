#include "Animal.h"

// 静态成员变量的定义
std::unordered_map<std::string, int> Animal::productTimes;
std::unordered_map<std::string, std::string> Animal::productTypes;
std::unordered_map<std::string, int> Animal::hungerThresholds;
std::unordered_map<std::string, int> Animal::feedAmounts;
std::unordered_map<std::string, int> Animal::lifespans;

Animal::Animal(const std::string& name, const std::string& breedSeason)
    : name(name), breedSeason(breedSeason), daysSinceLastProduct(0), fertilizerCount(0), daysSinceLastFed(0),
    productType(productTypes[name]), hungerThreshold(hungerThresholds[name]), feedAmount(feedAmounts[name]), lifespan(lifespans[name]) {
    // 创建精灵并添加到动物节点
    sprite = cocos2d::Sprite::create(name + ".png");
    this->addChild(sprite);
}

bool Animal::canProduce() const {
    return daysSinceLastProduct >= productTimes[name];
}

void Animal::update(int days) {
    daysSinceLastProduct += days;
    daysSinceLastFed += days;
    if (isHungry()) {
        showHungryAnimation(); // 显示饥饿动画
    }
}

void Animal::collectProduct() {
    if (canProduce()) {
        daysSinceLastProduct = 0;
        fertilizerCount += 1;
    }
}

bool Animal::canBreed(const std::string& currentSeason) const {
    return currentSeason == breedSeason && daysSinceLastFed < hungerThreshold;
}

Animal* Animal::breed() const {
    return new Animal(name, breedSeason);
}

void Animal::feed() {
    daysSinceLastFed = 0;
}

bool Animal::isHungry() const {
    return daysSinceLastFed >= hungerThreshold;
}

void Animal::showHungryAnimation() {
    // 创建饥饿动画的精灵
    auto hungrySprite = cocos2d::Sprite::create("hungry.png");
    hungrySprite->setPosition(sprite->getPosition()); // 将动画精灵放置在动物上方
    this->addChild(hungrySprite);

    // 创建动画帧
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("hungry-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // 每帧间隔 0.2 秒
    animation->setLoops(3); // 循环 3 次

    // 播放动画
    auto animate = cocos2d::Animate::create(animation);
    hungrySprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // 动画结束后移除精灵
}

// 初始化动物参数
void Animal::initializeAnimalParameters() {
    productTimes["Chicken"] = 2;
    productTimes["Cow"] = 5;
    productTimes["Pig"] = 4;
    productTimes["Sheep"] = 3;

    productTypes["Chicken"] = "Egg";
    productTypes["Cow"] = "Milk";
    productTypes["Pig"] = "Pork";
    productTypes["Sheep"] = "Wool";

    hungerThresholds["Chicken"] = 3;
    hungerThresholds["Cow"] = 5;
    hungerThresholds["Pig"] = 4;
    hungerThresholds["Sheep"] = 3;

    feedAmounts["Chicken"] = 5;
    feedAmounts["Cow"] = 25;
    feedAmounts["Pig"] = 20;
    feedAmounts["Sheep"] = 10;

    lifespans["Chicken"] = 30;
    lifespans["Cow"] = 60;
    lifespans["Pig"] = 45;
    lifespans["Sheep"] = 40;
}