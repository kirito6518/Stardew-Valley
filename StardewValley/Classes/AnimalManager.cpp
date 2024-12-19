#include "AnimalManager.h"
#include <string>
#include "cocos2d.h"
#include <ctime>

USING_NS_CC;

// ��̬��Ա������ʼ��
AnimalManager* AnimalManager::_instance = nullptr;

// ��ȡ����ʵ��
AnimalManager* AnimalManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) AnimalManager();
        if (_instance && _instance->init())
        {
            _instance->autorelease();
            _instance->retain(); // �������ü�������ֹ���ͷ�
        }
        else
        {
            CC_SAFE_DELETE(_instance);
            _instance = nullptr;
        }
    }
    return _instance;
}

// ˽�й��캯��
AnimalManager::AnimalManager()
{
    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
}

// ��ʼ��
bool AnimalManager::init() {

    if (!Layer::init())
    {
        return false;
    }

    timeRecord = (unsigned int)time(nullptr);
    Time = 10; // ��������ʱ��Ϊ 60 ��

    Sprite* sprite = Sprite::create(); // ����һ���յľ���

    // ��ʼ����
    animals[0] = new Animal("Pig", "Pork", sprite, 0, 0, 0);
    for (auto sprite : animals[0]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // �������ê��
        sprite->retain();
    }

    // ��ʼ��ţ
    animals[1] = new Animal("Cow", "Beef", sprite, 0, 0, 0);
    for (auto sprite : animals[1]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // ����ţ��ê��
        sprite->retain();
    }

    // ��ʼ����
    animals[2] = new Animal("Sheep", "Mutton", sprite, 0, 0, 0);
    for (auto sprite : animals[2]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // �������ê��
        sprite->retain();
    }

    // ��ʼ����
    animals[3] = new Animal("Chicken", "Chicken", sprite, 0, 0, 0);
    for (auto sprite : animals[3]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // ���ü���ê��
        sprite->retain();
    }

    // ���ض���
    for (int i = 0; i < 4; i++) {
        for (auto sprite : animals[i]->sprites) {
            std::string name = animals[i]->name;
            CreateAnimations(name);
            sprite->runAction(RepeatForever::create(Animate::create(animals[i]->animations)));
        }
    }

    return true;
}

// �������ּ��ض���
void AnimalManager::CreateAnimations(std::string& name) {
    int num = 0;
    // ���� ���ﶯ�� ͼƬ 128 * 64��
    Texture2D* texture;
    if (name == "Pig") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Pig.png");
        num = 0; // ��ö�����
    }
    else if (name == "Cow") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Cow.png");
        num = 1; // ��ö�����
    }
    else if (name == "Sheep") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Sheep.png");
        num = 2; // ��ö�����
    }
    else if (name == "Chicken") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Chicken.png");
        num = 3; // ��ö�����
    }

    // ���ﶯ�� ��һ��ͼƬ��ÿ֡�Ŀ��Ϊ 64 ���أ��߶�Ϊ 64 ����
    Vector<SpriteFrame*> frames;
    auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, 64, 64));
    frames.pushBack(frame);
    frame = SpriteFrame::createWithTexture(texture, Rect(64, 0, 64, 64));
    frames.pushBack(frame);
    // ��������
    animals[num]->animations = Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡���������
    animals[num]->animations->retain(); // ������������ֹ���ͷ�
}

// ���Ӷ��ֻ����������壩
bool AnimalManager::AddAnimal(const std::string& name) {
    for (int i = 0; i < 4; i++) {
        if (animals[i]->name == name) {
            if (animals[i]->sprites.size() > 20) { // ��ֹ���ﳬ��20ֻ
                break;
            }
            animals[i]->numOfChild++; // �����������
            // ���һ���µľ���
            Sprite* newSprite = Sprite::create();
            newSprite->setAnchorPoint(Vec2(0.5, 0.5));
            newSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2)); // ����λ��Ϊ��Ļ����
            mainMap->addChild(newSprite, 1); // ����Ϊ 1
            animals[i]->sprites.push_back(newSprite);
            newSprite->runAction(RepeatForever::create(Animate::create(animals[i]->animations)));
            return true;
            break;
        }
    }
    return false;
}

// ɾ�����ֻɾ��������壩
bool AnimalManager::RemoveAnimal(const std::string& name) {
    for (int i = 0; i < 4; i++) {
        if (animals[i]->name == name) {
            if (animals[i]->numOfAdult > 0) {
                animals[i]->numOfAdult--; // ���ٳ������
                // ɾ��һ������
                if (!animals[i]->sprites.empty()) {
                    Sprite* spriteToRemove = animals[i]->sprites.back();
                    if (spriteToRemove->getParent() == mainMap) {
                        mainMap->removeChild(spriteToRemove);
                    }
                    animals[i]->sprites.pop_back();
                }
                return true;
                break;
            }
        }
    }
    return false;
}

// ÿ֡���£������ָ��ʱ�䣬���и����ɳ�һ���׶�
void AnimalManager::update(float dt) {
    // ��ȡ��ǰʱ��
    unsigned int currentTime = (unsigned)(time(0));

    // �����ǰʱ���ȥ��¼ʱ���ֵ�ﵽ�趨��ʱ��
    if (currentTime - timeRecord >= Time) {
        timeRecord = currentTime; // ���¼�¼ʱ��

        // �������ж���
        for (int i = 0; i < 4; i++) {
            Animal* animal = animals[i];
            if (animal->numOfOld > 0) { // ������ȥ
                for (int j = 0; j < animal->numOfOld; j++) {
                    OldDie(animal->name);
                }
                animal->numOfOld = 0;
                CCLOG("OldDie!");
            }
            if (animal->numOfAdult > 0) { // ���������
                animal->numOfOld += animal->numOfAdult;
                animal->numOfAdult = 0;
            }
            if (animal->numOfChild > 0) { // ��������
                animal->numOfAdult += animal->numOfChild;
                animal->numOfChild = 0;
            }
        }
    }
}

// ɾ��һ��������壨������
void AnimalManager::OldDie(const std::string& name) {
    for (int i = 0; i < 4; i++) {
        if (animals[i]->name == name) {
            if (animals[i]->numOfOld > 0) {
                animals[i]->numOfOld--; // �����������
                // ɾ��һ������
                if (!animals[i]->sprites.empty()) {
                    Sprite* spriteToRemove = animals[i]->sprites.back();
                    if (spriteToRemove->getParent() == mainMap) {
                        mainMap->removeChild(spriteToRemove);
                    }
                    animals[i]->sprites.pop_back();
                }
                break;
            }
        }
    }
}
