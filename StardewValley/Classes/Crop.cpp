#include "Crop.h"

Crop::Crop(const std::string& cropName, const std::string& imagePath, int maxGrowthTime, int maxWaterDays, int maxFertilizerDays)
    : _cropName(cropName), _growthStage(0), _growthTime(0), _maxGrowthTime(maxGrowthTime),
    _waterDays(0), _maxWaterDays(maxWaterDays), _fertilizerDays(0), _maxFertilizerDays(maxFertilizerDays), _lastWaterTime(0.0f), _lastFertilizerTime(0.0f), _yield(100) {
    // ��ʼ�����ﾫ��
    this->initWithFile(imagePath);

    // ��ʼ��״̬��ǩ
    _statusLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
    _statusLabel->setPosition(Vec2(96, -this->getContentSize().height / 2 + 300)); // ����λ��
    _statusLabel->setColor(Color3B::WHITE); // ����������ɫΪ��ɫ
    this->addChild(_statusLabel, 1); // ���ò㼶Ϊ1

    // ������־
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


    if (_lastWaterTime + _maxWaterDays < _growthTime) {
        _waterDays = static_cast<int>(_growthTime - (_lastWaterTime + _maxWaterDays));
    }
    else {
        _waterDays = 0;
    }

    // ����ȱ������
    if (_lastFertilizerTime + _maxFertilizerDays < _growthTime) {
        _fertilizerDays = static_cast<int>(_growthTime - (_lastFertilizerTime + _maxFertilizerDays));
    }
    else {
        _fertilizerDays = 0;
    }

    // ����״̬��ǩ
    if (_waterDays > 0 && _growthStage != 4) {
        _statusLabel->setString("Water shortage");
    }
    else if (_fertilizerDays > 0 && _growthStage != 4) {
        _statusLabel->setString("");
    }
    else if (_growthStage == 4) {
        _statusLabel->setString("Harvestable");
    }
    else {
        _statusLabel->setString("");
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

    // ����ȱˮ״̬
    if (_waterDays > 0) {
        _waterDays--;
        if (_waterDays == 0) {
            // �ָ���ˮ״̬
        }
        else if (_waterDays > 7) {
            _yield -= 30; // ȱˮ����7�죬��������30
        }
    }

    // ����ȱ��״̬
    if (_fertilizerDays > 0) {
        _fertilizerDays--;
        if (_fertilizerDays == 0) {
            // �ָ�ʩ��״̬
        }
        else if (_fertilizerDays > 10) {
            _yield -= 50; // ȱ�ʳ���10�죬��������50
        }
        else if (_fertilizerDays > 15) {
            _yield -= 90; // ȱ�ʳ���15�죬��������90
        }
    }

    // ����״̬��ǩ
    if (_waterDays > 0) {
        _statusLabel->setString("ȱˮ");
    }
    else if (_fertilizerDays > 0) {
        _statusLabel->setString("ȱ��");
    }
    else if (_growthStage == 4) {
        _statusLabel->setString("���ջ�");
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

bool Crop::harvest() {
    if (_growthStage == 4) {
        // �ջ�����
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