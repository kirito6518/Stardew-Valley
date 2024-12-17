#include "Crop.h"

Crop::Crop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays)
    : _cropName(cropName), _growthStage(0), _growthTime(0), _maxGrowthTime(maxGrowthTime),
    _waterDays(0), _maxWaterDays(maxWaterDays), _fertilizerDays(0), _maxFertilizerDays(maxFertilizerDays), _yield(100) {
    // 初始化作物精灵
    this->initWithFile(imagePath);

    // 初始化状态标签
    _statusLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
    _statusLabel->setPosition(this->getContentSize() / 2);
    this->addChild(_statusLabel);
}

Crop::~Crop() {}

void Crop::update(float dt) {
    // 更新生长时间
    _growthTime += dt;

    // 判断生长阶段
    if (_growthTime < _maxGrowthTime / 4) {
        _growthStage = 1; // 幼苗阶段
    }
    else if (_growthTime < _maxGrowthTime * 3 / 4) {
        _growthStage = 2; // 成熟阶段
    }
    else {
        _growthStage = 3; // 可收获阶段
    }

    // 更新缺水状态
    if (_waterDays > 0) {
        _waterDays--;
        if (_waterDays > 7) {
            _yield -= 30; // 缺水超过7天，产量减少30
        }
    }

    // 更新缺肥状态
    if (_fertilizerDays > 0) {
        _fertilizerDays--;
        if (_fertilizerDays > 10) {
            _yield -= 50; // 缺肥超过10天，产量减少50
        }
        else if (_fertilizerDays > 15) {
            _yield -= 90; // 缺肥超过15天，产量减少90
        }
    }

    // 更新状态标签
    if (_waterDays > 0) {
        _statusLabel->setString("缺水");
    }
    else if (_fertilizerDays > 0) {
        _statusLabel->setString("缺肥");
    }
    else if (_growthStage == 3) {
        _statusLabel->setString("可收获");
    }
    else {
        _statusLabel->setString("");
    }
}

void Crop::water() {
    _waterDays = 0; // 浇水后缺水状态清零
}

void Crop::fertilize() {
    _fertilizerDays = 0; // 施肥后缺肥状态清零
}

bool Crop::harvest() {
    if (_growthStage == 3) {
        // 收获作物
        _growthStage = 0;
        _growthTime = 0;
        return true;
    }
    return false;
}

int Crop::getGrowthStage() const {
    return _growthStage;
}

int Crop::getYield() const {
    return _yield;
}

std::string Crop::get_Name() const {
    return _cropName;
}

void Crop::setPosition(const Vec2& position) {
    Sprite::setPosition(position);
}

Vec2 Crop::get_Position() const {
    return Sprite::getPosition();
}