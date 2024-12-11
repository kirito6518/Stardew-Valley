#include "Crop.h"

// 静态成员变量的定义
std::unordered_map<std::string, int> Crop::growthTimes;
std::unordered_map<std::string, int> Crop::waterThresholds;
std::unordered_map<std::string, int> Crop::fertilizerThresholds;

Crop::Crop(const std::string& name, const std::string& season)
    : name(name), season(season), isWatered(false), isFertilized(false), isDiseasedFlag(false), daysSincePlanted(0), growthStage(Stage1) {
    // 创建精灵并添加到作物节点
    sprite = cocos2d::Sprite::create(name + "-1.png"); // 初始显示 Stage1 图片
    this->addChild(sprite);
}

void Crop::update(int days) {
    daysSincePlanted += days;
    if (daysSincePlanted >= growthTimes[name]) {
        growthStage = Harvestable;
    }
    else if (daysSincePlanted >= growthTimes[name] * 0.75) {
        growthStage = Stage3;
    }
    else if (daysSincePlanted >= growthTimes[name] * 0.25) {
        growthStage = Stage2;
    }
    setGrowthStageImage(); // 更新显示的图片
}

void Crop::water() {
    isWatered = true;
    showWaterAnimation(); // 显示浇水动画
}

void Crop::fertilize() {
    isFertilized = true;
    showFertilizeAnimation(); // 显示施肥动画
}

void Crop::checkDisease() {
    if (!isWatered || !isFertilized) {
        isDiseasedFlag = true;
    }
}

bool Crop::isSeasonValid(const std::string& currentSeason) const {
    return season == currentSeason;
}

Crop::GrowthStage Crop::getGrowthStage() const {
    return growthStage;
}

// 新增：检查作物是否可以收获
bool Crop::isReadyToHarvest() const {
    return daysSincePlanted >= growthTimes[name];
}

void Crop::setGrowthStageImage() {
    std::string imagePath;
    switch (growthStage) {
    case Stage1: imagePath = name + "-1.png"; break;
    case Stage2: imagePath = name + "-2.png"; break;
    case Stage3: imagePath = name + "-3.png"; break;
    case Harvestable: imagePath = name + "-harvest.png"; break;
    }
    sprite->setTexture(imagePath); // 切换精灵的图片
}

void Crop::showWaterAnimation() {
    // 创建缺水动画的精灵
    auto waterSprite = cocos2d::Sprite::create("water.png");
    waterSprite->setPosition(sprite->getPosition()); // 将动画精灵放置在作物上方
    this->addChild(waterSprite);

    // 创建动画帧
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("water-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // 每帧间隔 0.2 秒
    animation->setLoops(3); // 循环 3 次

    // 播放动画
    auto animate = cocos2d::Animate::create(animation);
    waterSprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // 动画结束后移除精灵
}

void Crop::showFertilizeAnimation() {
    // 创建施肥动画的精灵
    auto fertilizeSprite = cocos2d::Sprite::create("fertilize.png");
    fertilizeSprite->setPosition(sprite->getPosition()); // 将动画精灵放置在作物上方
    this->addChild(fertilizeSprite);

    // 创建动画帧
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("fertilize-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // 每帧间隔 0.2 秒
    animation->setLoops(3); // 循环 3 次

    // 播放动画
    auto animate = cocos2d::Animate::create(animation);
    fertilizeSprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // 动画结束后移除精灵
}

// 初始化作物参数
void Crop::initializeCropParameters() {
    growthTimes["Turnip"] = 10;
    growthTimes["Potato"] = 15;
    growthTimes["Radish"] = 12;
    growthTimes["Onion"] = 14;
    growthTimes["Carrot"] = 13;
    growthTimes["Spinach"] = 11;

    waterThresholds["Turnip"] = 3;
    waterThresholds["Potato"] = 4;
    waterThresholds["Radish"] = 3;
    waterThresholds["Onion"] = 3;
    waterThresholds["Carrot"] = 3;
    waterThresholds["Spinach"] = 2;

    fertilizerThresholds["Turnip"] = 5;
    fertilizerThresholds["Potato"] = 6;
    fertilizerThresholds["Radish"] = 4;
    fertilizerThresholds["Onion"] = 5;
    fertilizerThresholds["Carrot"] = 4;
    fertilizerThresholds["Spinach"] = 3;
}