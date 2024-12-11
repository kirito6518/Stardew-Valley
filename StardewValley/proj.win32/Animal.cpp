#include "Animal.h"

// 构造函数
Animal::Animal(std::string name, int productTime, std::string productType, std::string breedSeason)
    : name(name), productTime(productTime), productType(productType), breedSeason(breedSeason),
    daysSinceLastProduct(0), fertilizerCount(0) {
}

// 检查是否可以生产产品
bool Animal::canProduce() const {
    return daysSinceLastProduct >= productTime;
}

// 更新动物状态
void Animal::update(int days) {
    daysSinceLastProduct += days;
}

// 收集产品（包括肥料）
void Animal::collectProduct() {
    if (canProduce()) {
        // 重置生产计时
        daysSinceLastProduct = 0;
        // 生成肥料
        fertilizerCount += 1; // 每次生产产品时生成 1 个肥料
    }
}

// 检查是否可以繁殖
bool Animal::canBreed(const std::string& currentSeason) const {
    return currentSeason == breedSeason;
}

// 繁殖行为
Animal* Animal::breed() const {
    // 繁殖时生成一个新的动物实例
    return new Animal(name, productTime, productType, breedSeason);
}