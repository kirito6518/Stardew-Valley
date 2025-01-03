#include "Crop.h"
#include "FarmManager.h"

Crop::Crop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays, int maxPestDays, CropType cropType, SeasonRestriction seasonRestriction)
    : _cropName(cropName), _growthStage(0), _growthTime(0), _maxGrowthTime(maxGrowthTime),
    _waterDays(0), _maxWaterDays(maxWaterDays), _fertilizerDays(0), _maxFertilizerDays(maxFertilizerDays),
    _lastWaterTime(0.0f), _lastFertilizerTime(0.0f), _lastPestControlTime(0.0f), _maxPestDays(maxPestDays), _yield(10),
    _cropType(cropType), _seasonRestriction(seasonRestriction) {
    // 初始化作物精灵
    this->initWithFile(imagePath);

    // 初始化状态标签
    _statusLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
    _statusLabel->setPosition(Vec2(96, -this->getContentSize().height / 2 + 120)); // 调整位置
    _statusLabel->setColor(Color3B::WHITE); // 设置文字颜色为红色
    this->addChild(_statusLabel, 1); // 设置层级为1

    // 调试日志
    CCLOG("Crop position: %f, %f", this->getPosition().x, this->getPosition().y);
    CCLOG("Label position: %f, %f", _statusLabel->getPosition().x, _statusLabel->getPosition().y);
}

Crop::~Crop() {}


void Crop::update(float dt) {
    _growthTime += dt;

    if (_growthTime < _maxGrowthTime / 3.0f) {
        _growthStage = 1;
    }
    else if (_growthTime < _maxGrowthTime * 2.0f / 3.0f) {
        _growthStage = 2;
    }
    else if (_growthTime < _maxGrowthTime) {
        _growthStage = 3;
    }
    else {
        _growthStage = 4;
    }

    // 根据作物类型更新图像
    switch (_cropType) {
    case ONION:
        switch (_growthStage) {
        case 1:
            this->setTexture("crops/Onion-1.png");
            break;
        case 2:
            this->setTexture("crops/Onion-2.png");
            break;
        case 3:
            this->setTexture("crops/Onion-3.png");
            break;
        case 4:
            this->setTexture("crops/Onion-harvest.png");
            break;
        }
        break;
    case POTATO:
        switch (_growthStage) {
        case 1:
            this->setTexture("crops/Potato-1.png");
            break;
        case 2:
            this->setTexture("crops/Potato-2.png");
            break;
        case 3:
            this->setTexture("crops/Potato-3.png");
            break;
        case 4:
            this->setTexture("crops/Potato-harvest.png");
            break;
        }
        break;
    case RADISH:
        switch (_growthStage) {
        case 1:
            this->setTexture("crops/Radish-1.png");
            break;
        case 2:
            this->setTexture("crops/Radish-2.png");
            break;
        case 3:
            this->setTexture("crops/Radish-3.png");
            break;
        case 4:
            this->setTexture("crops/Radish-harvest.png");
            break;
        }
        break;
    case CARROT: 
        switch (_growthStage) {
        case 1:
            this->setTexture("crops/Carrot-1.png");
            break;
        case 2:
            this->setTexture("crops/Carrot-2.png");
            break;
        case 3:
            this->setTexture("crops/Carrot-3.png");
            break;
        case 4:
            this->setTexture("crops/Carrot-harvest.png");
            break;
        }
        break;
    case TURNIP: 
        switch (_growthStage) {
        case 1:
            this->setTexture("crops/Turnip-1.png");
            break;
        case 2:
            this->setTexture("crops/Turnip-2.png");
            break;
        case 3:
            this->setTexture("crops/Turnip-3.png");
            break;
        case 4:
            this->setTexture("crops/Turnip-harvest.png");
            break;
        }
        break;
    case SPINACH: 
        switch (_growthStage) {
        case 1:
            this->setTexture("crops/Spinach-1.png");
            break;
        case 2:
            this->setTexture("crops/Spinach-2.png");
            break;
        case 3:
            this->setTexture("crops/Spinach-3.png");
            break;
        case 4:
            this->setTexture("crops/Spinach-harvest.png");
            break;
        }
        break;
    }

    // 更新缺水天数
    if (_lastWaterTime + _maxWaterDays < _growthTime) {
        _waterDays = static_cast<int>(_growthTime - (_lastWaterTime + _maxWaterDays));
    }
    else {
        _waterDays = 0;
    }
    // 更新缺肥天数
    if (_lastFertilizerTime + _maxFertilizerDays < _growthTime) {
        _fertilizerDays = static_cast<int>(_growthTime - (_lastFertilizerTime + _maxFertilizerDays));
    }
    else {
        _fertilizerDays = 0;
    }
    // 更新虫害天数
    if (_lastPestControlTime + _maxPestDays < _growthTime) {
        _pestDays = static_cast<int>(_growthTime - (_lastPestControlTime + _maxPestDays));
    }
    else {
        _pestDays = 0;
    }

    // 计算产量影响
    int waterYield = _yield;
    if (_waterDays > 30 && _growthStage != 4) {
        // 植物死亡
        if (_farmManager) {
            _farmManager->removeCrop(this);
        }
        this->removeFromParent();
        return;
    }
    else if (_waterDays == 21) {
        waterYield = waterYield - 4;
    }
    else if (_waterDays == 15) {
        waterYield = waterYield - 3;
    }

    int fertilizerYield = waterYield;
    if (_fertilizerDays >= 21 && _fertilizerDays <= 25) {
        int fertilizerImpact = 1;
        fertilizerYield = fertilizerYield - fertilizerImpact;
    }
    else if (_fertilizerDays == 1) {
        int fertilizerImpact = 5;
        fertilizerYield = fertilizerYield + fertilizerImpact;
    }

    int pestYield = fertilizerYield;
    if (_pestDays > 27 && _growthStage != 4) {
        // 植物死亡
        if (_farmManager) {
            _farmManager->removeCrop(this);
        }
        this->removeFromParent();
        return;
    }
    else if (_pestDays == 9) {
        pestYield = pestYield - 2;
    }
    else if (_pestDays == 15) {
        pestYield = pestYield - 2;
    }
    else if (_pestDays == 21) {
        pestYield = pestYield - 2;
    }
    if (pestYield <= 0) {
        pestYield = 1;
    }

    _yield = pestYield;

    // 更新状态标签
    if (_growthStage == 4) {
        _statusLabel->setString("Harvestable");
    }
    else {
        std::string status;
        if (_waterDays > 0) {
            status += "Water |";
        }
        if (_fertilizerDays > 0) {
            status += "Fertilizer |";
        }
        if (_pestDays > 0) {
            status += "Pest";
        }
        if (status.empty()) {
            _statusLabel->setString("");
        }
        else {
            _statusLabel->setString(status);
        }
    }
}
/**
void Crop::update(float dt) {

    _growthTime += dt;

    if (_growthTime < _maxGrowthTime / 3) {
        _growthStage = 1;
    }
    else if (_growthTime < _maxGrowthTime * 2 / 3) {
        _growthStage = 2;
    }
    else if (_growthTime < _maxGrowthTime) {
        _growthStage = 3;
    }
    else {
        _growthStage = 4;
    }

    switch (_growthStage) {
    case 1:
        this->setTexture("crops/Onion-1.png");
        break;
    case 2:
        this->setTexture("crops/Onion-2.png");
        break;
    case 3:
        this->setTexture("crops/Onion-3.png");
        break;
    case 4:
        this->setTexture("crops/Onion-harvest.png");
        break;
    }

    // 更新缺水状态
    if (_waterDays > 0) {
        _waterDays--;
        if (_waterDays == 0) {
            // 恢复浇水状态
        }
        else if (_waterDays > 7) {
            _yield -= 30; // 缺水超过7天，产量减少30
        }
    }

    // 更新缺肥状态
    if (_fertilizerDays > 0) {
        _fertilizerDays--;
        if (_fertilizerDays == 0) {
            // 恢复施肥状态
        }
        else if (_fertilizerDays > 10) {
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
    else if (_growthStage == 4) {
        _statusLabel->setString("可收获");
    }
    else {
        _statusLabel->setString("");
    }
}
**/

void Crop::water() {
    _lastWaterTime = _growthTime;
}

void Crop::fertilize() {
    _lastFertilizerTime = _growthTime;
}

void Crop::controlPest() {
    _lastPestControlTime = _growthTime;
}

void Crop::setFarmManager(FarmManager* farmManager) {
    _farmManager = farmManager;
}

bool Crop::harvest() {
    if (_growthStage == 4) {
        _growthStage = 0;
        _growthTime = 0;
        return true;
    }
    return false;
}

int Crop::getGrowthStage() const {
    return _growthStage;
}

int Crop::getWaterDays() const {
    return _waterDays;
}

int Crop::getFertilizerDays() const {
    return _fertilizerDays;
}

int Crop::getPestDays() const {
    return _pestDays;
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