#include "AnimalManager.h"
#include <cstring>
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
    Time = 30; // ��������ʱ��Ϊ 60 ��

    ranchLayer = Sprite::create("ui/RanchLayer.png"); // 800 * 464
    ranchLayer->setAnchorPoint(Vec2(0.5, 0.5));
    ranchLayer->setPosition(visibleSize / 2);
    ranchLayer->retain();
    this->addChild(ranchLayer, 3);
    {
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
        this->addChild(outButton, 3);
    }
    {
        // ����������밴ť
        BuyButtonPig = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        BuyButtonPig->setPosition(visibleSize / 2);

        // ��������������
        auto BuyButtonPigListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        BuyButtonPigListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonPig->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        BuyButtonPigListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonPig->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
                Item* initItem = ItemManager::getInstance()->getItem("Coin");
                if (initItem->getCount() >= 2) {
                    initItem->decreaseCount(2);
                    AddAnimal("Pig");
                }
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                BuyButtonPig->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonPigListener, BuyButtonPig);

        // ��Ӱ�ť����
        this->addChild(BuyButtonPig, 3);
    }
    {
        // ����������װ�ť
        KillButtonPig = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        KillButtonPig->setPosition(visibleSize / 2);

        // ��������������
        auto KillButtonPigListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        KillButtonPigListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonPig->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        KillButtonPigListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonPig->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                RemoveAnimal("Pig");
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                KillButtonPig->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonPigListener, KillButtonPig);

        // ��Ӱ�ť����
        this->addChild(KillButtonPig, 3);
    }
    // ��ʼ����
    animals[0] = new Animal("Pig", "Pork", 0, 0, 0);

    // ��ʼ��ţ
    animals[1] = new Animal("Cow", "Beef", 0, 0, 0);

    // ��ʼ����
    animals[2] = new Animal("Sheep", "Mutton", 0, 0, 0);

    // ��ʼ����
    animals[3] = new Animal("Chicken", "Chicken", 0, 0, 0);

    // ���ض���
    for (int i = 0; i < 4; i++) {
        std::string name = animals[i]->name;
        CreateAnimations(name);
    }

    // ������Ŀ
    for (int i = 0; i < 4; i++) {
        // �������µ�
        animalNum[i]= Label::createWithTTF("", "fonts/Gen.ttf", 1);
        animalNum[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
        animalNum[i]->setPosition(ranchLayer->getPosition() + Vec2(280, 140 - 120 * i));
        this->addChild(animalNum[i], 3);
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
            if (animals[i]->sprites.size() > 19) { // ��ֹ���ﳬ��20ֻ
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
            CreateNumber(); // ����
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
                CreateNumber(); // ����
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
    CreateNumber();
    AnimalManager::getInstance()->outButton->setPosition(ranchLayer->getPosition() + Vec2(348, 205));
    AnimalManager::getInstance()->BuyButtonPig->setPosition(ranchLayer->getPosition() + Vec2(140,140));
    AnimalManager::getInstance()->KillButtonPig->setPosition(ranchLayer->getPosition() + Vec2(280, 140));
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
    std::uniform_real_distribution<float> distX(-72.0f, 360.0f);

    // ���� y �ķ�Χ��468 �� 1044
    std::uniform_real_distribution<float> distY(472.0f, 1044.0f);

    // ������������� x �� y
    float x = distX(gen);
    float y = distY(gen);

    // �������ɵ�����������ԣ�ʹ�� Vec2
    return Vec2(x, y);
}

// �������ֶ������Ŀ��ÿ֡����
void AnimalManager::CreateNumber() {
    for (int i = 0; i < 4; i++) {
        // �Ƴ���һ��
        if (animalNum[i]->getParent()) {
            this->removeChild(animalNum[i]);
        }
        // �������µ�
        animalNum[i] = Label::createWithTTF(std::to_string(animals[i]->numOfChild)+ "           " + std::to_string(animals[i]->numOfAdult) + "           " + std::to_string(animals[i]->numOfOld), "fonts/Gen.ttf", 20);
        animalNum[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
        animalNum[i]->setPosition(ranchLayer->getPosition() + Vec2(-75, 140 - 80 * i));
        this->addChild(animalNum[i], 3);
    }
}
