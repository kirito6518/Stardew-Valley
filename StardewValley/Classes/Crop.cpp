#include "Crop.h"

// ��̬��Ա�����Ķ���
std::unordered_map<std::string, int> Crop::growthTimes;
std::unordered_map<std::string, int> Crop::waterThresholds;
std::unordered_map<std::string, int> Crop::fertilizerThresholds;

Crop::Crop(const std::string& name, const std::string& season)
    : name(name), season(season), isWatered(false), isFertilized(false), isDiseasedFlag(false), daysSincePlanted(0), growthStage(Stage1) {
    // �������鲢��ӵ�����ڵ�
    sprite = cocos2d::Sprite::create(name + "-1.png"); // ��ʼ��ʾ Stage1 ͼƬ
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
    setGrowthStageImage(); // ������ʾ��ͼƬ
}

void Crop::water() {
    isWatered = true;
    showWaterAnimation(); // ��ʾ��ˮ����
}

void Crop::fertilize() {
    isFertilized = true;
    showFertilizeAnimation(); // ��ʾʩ�ʶ���
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

// ��������������Ƿ�����ջ�
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
    sprite->setTexture(imagePath); // �л������ͼƬ
}

void Crop::showWaterAnimation() {
    // ����ȱˮ�����ľ���
    auto waterSprite = cocos2d::Sprite::create("water.png");
    waterSprite->setPosition(sprite->getPosition()); // ��������������������Ϸ�
    this->addChild(waterSprite);

    // ��������֡
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("water-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // ÿ֡��� 0.2 ��
    animation->setLoops(3); // ѭ�� 3 ��

    // ���Ŷ���
    auto animate = cocos2d::Animate::create(animation);
    waterSprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // �����������Ƴ�����
}

void Crop::showFertilizeAnimation() {
    // ����ʩ�ʶ����ľ���
    auto fertilizeSprite = cocos2d::Sprite::create("fertilize.png");
    fertilizeSprite->setPosition(sprite->getPosition()); // ��������������������Ϸ�
    this->addChild(fertilizeSprite);

    // ��������֡
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("fertilize-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // ÿ֡��� 0.2 ��
    animation->setLoops(3); // ѭ�� 3 ��

    // ���Ŷ���
    auto animate = cocos2d::Animate::create(animation);
    fertilizeSprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // �����������Ƴ�����
}

// ��ʼ���������
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