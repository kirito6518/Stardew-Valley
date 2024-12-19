#include "AnimalManager.h"
#include <string>
#include "cocos2d.h"
#include <ctime>
#include "ItemManager.h"
#include "BackpackManager.h"
#include "MainMap.h"
#include <random>

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

    const auto visibleSize = Director::getInstance()->getVisibleSize();

    timeRecord = (unsigned int)time(nullptr);
    Time = 60; // ��������ʱ��Ϊ 60 ��

    ranchLayer = Sprite::create("ui/RanchLayer.png"); // 800 * 464
    ranchLayer->setAnchorPoint(Vec2(0.5, 0.5));
    ranchLayer->setPosition(visibleSize / 2);
    ranchLayer->retain();

    // ����out��ť
    outButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(AnimalManager::HideRanch, this));
    //����λ��
    outButton->setPosition(visibleSize / 2);

    // ��������������
    auto outButtonListener = EventListenerTouchOneByOne::create();

    // ������ʼ
    outButtonListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // ���ð�ťΪ����״̬
            outButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return true;
        }
        return false;
        };

    // ��������
    outButtonListener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // ���ð�ťΪ����״̬
            outButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            HideRanch(nullptr);
        }
        else
        {
            // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
            outButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(outButtonListener, outButton);

    // ��Ӱ�ť����
    ranchLayer->addChild(outButton, 3);

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
            newSprite->setPosition(GenerateRandomPosition()); // �������λ��
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
                Item* initItem = ItemManager::getInstance()->getItem(animals[i]->productType);
                BackpackManager::getInstance()->addItem(initItem, 1);
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
void AnimalManager::UpdateAnimals(float dt) {
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
                // CCLOG("OldDie!");
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

    outButton->setPosition(ranchLayer->getPosition() + Vec2(400, 10));
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

// �ر�����
void AnimalManager::HideRanch(Ref* sender) {
    dynamic_cast<MainMap*>(mainMap)->HideRanch(sender);
}

// ����һ����������� (x, y)�������� Vec2
Vec2 AnimalManager::GenerateRandomPosition() {
    // ����һ�������������
    std::random_device rd;  // ���ڻ�ȡ�������
    std::mt19937 gen(rd()); // ʹ�� Mersenne Twister �㷨���������

    // ���� x �ķ�Χ��-80 �� 376
    std::uniform_real_distribution<float> distX(-80.0f, 376.0f);

    // ���� y �ķ�Χ��468 �� 1044
    std::uniform_real_distribution<float> distY(468.0f, 1044.0f);

    // ������������� x �� y
    float x = distX(gen);
    float y = distY(gen);

    // �������ɵ�����������ԣ�ʹ�� Vec2
    return Vec2(x, y);
}
