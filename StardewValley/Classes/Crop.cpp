#include "Crop.h"

// 定义静态成员变量
std::unordered_map<std::string, int> Crop::growthTimes;
std::unordered_map<std::string, int> Crop::waterThresholds;
std::unordered_map<std::string, int> Crop::fertilizerThresholds;

// 构造函数，初始化作物的名称、种植季节和其他属性
Crop::Crop(const std::string& name, const std::string& season)
    : name(name), season(season), isWatered(false), isFertilized(false), isDiseasedFlag(false), daysSincePlanted(0), growthStage(Stage1) {
    // 创建精灵并添加到节点中
    sprite = cocos2d::Sprite::create(name + "-1.png"); // 初始显示 Stage1 的图片
    this->addChild(sprite);
}

// 更新作物状态，参数为经过的天数
void Crop::update(int days) {
    daysSincePlanted += days; // 增加种植后的天数
    if (daysSincePlanted >= growthTimes[name]) {
        growthStage = Harvestable; // 如果达到生长总天数，进入可收获阶段
    }
    else if (daysSincePlanted >= growthTimes[name] * 0.75) {
        growthStage = Stage3; // 如果达到总天数的75%，进入阶段3
    }
    else if (daysSincePlanted >= growthTimes[name] * 0.25) {
        growthStage = Stage2; // 如果达到总天数的25%，进入阶段2
    }
    setGrowthStageImage(); // 更新显示的图片
}

// 浇水操作
void Crop::water() {
    isWatered = true; // 标记为已浇水
    showWaterAnimation(); // 显示浇水动画
}

// 施肥操作
void Crop::fertilize() {
    isFertilized = true; // 标记为已施肥
    showFertilizeAnimation(); // 显示施肥动画
}

// 检查作物是否生病
void Crop::checkDisease() {
    if (!isWatered || !isFertilized) {
        isDiseasedFlag = true; // 如果未浇水或未施肥，标记为生病
    }
}

// 检查当前季节是否适合种植该作物
bool Crop::isSeasonValid(const std::string& currentSeason) const {
    return season == currentSeason; // 比较当前季节和种植季节
}

// 获取当前作物的生长阶段
Crop::GrowthStage Crop::getGrowthStage() const {
    return growthStage;
}

// 检查作物是否可以收获
bool Crop::isReadyToHarvest() const {
    return daysSincePlanted >= growthTimes[name]; // 如果种植天数达到总天数，返回true
}

// 更新显示的图片
void Crop::setGrowthStageImage() {
    std::string imagePath;
    switch (growthStage) {
    case Stage1: imagePath = name + "-1.png"; break; // 阶段1的图片
    case Stage2: imagePath = name + "-2.png"; break; // 阶段2的图片
    case Stage3: imagePath = name + "-3.png"; break; // 阶段3的图片
    case Harvestable: imagePath = name + "-harvest.png"; break; // 可收获阶段的图片
    }
    sprite->setTexture(imagePath); // 更新精灵的图片
}

// 显示浇水动画
void Crop::showWaterAnimation() {
    // 创建浇水动画的精灵
    auto waterSprite = cocos2d::Sprite::create("water.png");
    waterSprite->setPosition(sprite->getPosition()); // 将动画精灵放置在作物上方
    this->addChild(waterSprite);

    // 创建动画帧
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("water-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // 每帧间隔0.2秒
    animation->setLoops(3); // 循环3次

    // 播放动画
    auto animate = cocos2d::Animate::create(animation);
    waterSprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // 动画结束后移除精灵
}

// 显示施肥动画
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
    animation->setDelayPerUnit(0.2f); // 每帧间隔0.2秒
    animation->setLoops(3); // 循环3次

    // 播放动画
    auto animate = cocos2d::Animate::create(animation);
    fertilizeSprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // 动画结束后移除精灵
}

// 初始化作物的参数
void Crop::initializeCropParameters() {
    // 设置不同作物的生长天数
    growthTimes["Turnip"] = 10;
    growthTimes["Potato"] = 15;
    growthTimes["Radish"] = 12;
    growthTimes["Onion"] = 14;
    growthTimes["Carrot"] = 13;
    growthTimes["Spinach"] = 11;

    // 设置不同作物的缺水阈值
    waterThresholds["Turnip"] = 3;
    waterThresholds["Potato"] = 4;
    waterThresholds["Radish"] = 3;
    waterThresholds["Onion"] = 3;
    waterThresholds["Carrot"] = 3;
    waterThresholds["Spinach"] = 2;

    // 设置不同作物的缺肥阈值
    fertilizerThresholds["Turnip"] = 5;
    fertilizerThresholds["Potato"] = 6;
    fertilizerThresholds["Radish"] = 4;
    fertilizerThresholds["Onion"] = 5;
    fertilizerThresholds["Carrot"] = 4;
    fertilizerThresholds["Spinach"] = 3;
}