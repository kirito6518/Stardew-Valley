#include "Animal.h"

// ��̬��Ա�����Ķ���
std::unordered_map<std::string, int> Animal::productTimes;
std::unordered_map<std::string, std::string> Animal::productTypes;
std::unordered_map<std::string, int> Animal::hungerThresholds;
std::unordered_map<std::string, int> Animal::feedAmounts;
std::unordered_map<std::string, int> Animal::lifespans;

Animal::Animal(const std::string& name, const std::string& breedSeason)
    : name(name), breedSeason(breedSeason), daysSinceLastProduct(0), fertilizerCount(0), daysSinceLastFed(0),
    productType(productTypes[name]), hungerThreshold(hungerThresholds[name]), feedAmount(feedAmounts[name]), lifespan(lifespans[name]) {
    // �������鲢��ӵ�����ڵ�
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
        showHungryAnimation(); // ��ʾ��������
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
    // �������������ľ���
    auto hungrySprite = cocos2d::Sprite::create("hungry.png");
    hungrySprite->setPosition(sprite->getPosition()); // ��������������ڶ����Ϸ�
    this->addChild(hungrySprite);

    // ��������֡
    auto animation = cocos2d::Animation::create();
    for (int i = 1; i <= 3; ++i) {
        animation->addSpriteFrameWithFile("hungry-" + std::to_string(i) + ".png");
    }
    animation->setDelayPerUnit(0.2f); // ÿ֡��� 0.2 ��
    animation->setLoops(3); // ѭ�� 3 ��

    // ���Ŷ���
    auto animate = cocos2d::Animate::create(animation);
    hungrySprite->runAction(cocos2d::Sequence::create(animate, cocos2d::RemoveSelf::create(), nullptr)); // �����������Ƴ�����
}

// ��ʼ���������
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