#include "AnimalManager.h"
#include <cstring>
#include "cocos2d.h"
#include <ctime>
#include "ItemManager.h"
#include "BackpackManager.h"
#include "MainMap.h"
#include <random>
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

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
    Time = 30; // ��������ʱ��Ϊ 30 ��

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
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
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
                int audioId2 = AudioEngine::play2d("audio/coins.mp3");
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
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
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

    {
        // ����ţ�����밴ť
        BuyButtonCow = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        BuyButtonCow->setPosition(visibleSize / 2);

        // ��������������
        auto BuyButtonCowListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        BuyButtonCowListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonCow->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        BuyButtonCowListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonCow->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/coins.mp3");
                Item* initItem = ItemManager::getInstance()->getItem("Coin");
                if (initItem->getCount() >= 2) {
                    initItem->decreaseCount(2);
                    AddAnimal("Cow");
                }
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                BuyButtonCow->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonCowListener, BuyButtonCow);

        // ��Ӱ�ť����
        this->addChild(BuyButtonCow, 3);
    }
    {
        // ����ţ�����װ�ť
        KillButtonCow = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        KillButtonCow->setPosition(visibleSize / 2);

        // ��������������
        auto KillButtonCowListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        KillButtonCowListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonCow->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        KillButtonCowListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonCow->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Cow");
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                KillButtonCow->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonCowListener, KillButtonCow);

        // ��Ӱ�ť����
        this->addChild(KillButtonCow, 3);
    }

    {
        // ����������밴ť
        BuyButtonSheep = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        BuyButtonSheep->setPosition(visibleSize / 2);

        // ��������������
        auto BuyButtonSheepListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        BuyButtonSheepListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonSheep->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        BuyButtonSheepListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonSheep->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/coins.mp3");
                Item* initItem = ItemManager::getInstance()->getItem("Coin");
                if (initItem->getCount() >= 2) {
                    initItem->decreaseCount(2);
                    AddAnimal("Sheep");
                }
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                BuyButtonSheep->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonSheepListener, BuyButtonSheep);

        // ��Ӱ�ť����
        this->addChild(BuyButtonSheep, 3);
    }
    {
        // ����������װ�ť
        KillButtonSheep = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        KillButtonSheep->setPosition(visibleSize / 2);

        // ��������������
        auto KillButtonSheepListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        KillButtonSheepListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonSheep->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        KillButtonSheepListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonSheep->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Sheep");
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                KillButtonSheep->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonSheepListener, KillButtonSheep);

        // ��Ӱ�ť����
        this->addChild(KillButtonSheep, 3);
    }

    {
        // �����������밴ť
        BuyButtonChook = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        BuyButtonChook->setPosition(visibleSize / 2);

        // ��������������
        auto BuyButtonChookListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        BuyButtonChookListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonChook->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        BuyButtonChookListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                BuyButtonChook->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/coins.mp3");
                Item* initItem = ItemManager::getInstance()->getItem("Coin");
                if (initItem->getCount() >= 2) {
                    initItem->decreaseCount(2);
                    AddAnimal("Chook");
                }
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                BuyButtonChook->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonChookListener, BuyButtonChook);

        // ��Ӱ�ť����
        this->addChild(BuyButtonChook, 3);
    }
    {
        // �����������װ�ť
        KillButtonChook = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //����λ��
        KillButtonChook->setPosition(visibleSize / 2);

        // ��������������
        auto KillButtonChookListener = EventListenerTouchOneByOne::create();

        // ������ʼ
        KillButtonChookListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonChook->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // ��������
        KillButtonChookListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // ���ð�ťΪ����״̬
                KillButtonChook->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Chook");
            }
            else
            {
                // �����������ʱ���ڰ�ť�ϣ��ָ���ť״̬
                KillButtonChook->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonChookListener, KillButtonChook);

        // ��Ӱ�ť����
        this->addChild(KillButtonChook, 3);
    }

    // ��ʼ����
    animals[0] = new Animal("Pig", "Pork", 0, 0, 0);

    // ��ʼ��ţ
    animals[1] = new Animal("Cow", "Beef", 0, 0, 0);

    // ��ʼ����
    animals[2] = new Animal("Sheep", "Mutton", 0, 0, 0);

    // ��ʼ����
    animals[3] = new Animal("Chook", "Chicken", 0, 0, 0);

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
    else if (name == "Chook") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Chook.png");
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
            mainMap->addChild(newSprite, 2); // ����Ϊ 2
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
            while (animal->numOfOld > 0) { // ������ȥ
                OldDie(animal->name);
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
    // ����ui
    CreateNumber();
    AnimalManager::getInstance()->outButton->setPosition(ranchLayer->getPosition() + Vec2(348, 205));
    AnimalManager::getInstance()->BuyButtonPig->setPosition(ranchLayer->getPosition() + Vec2(140,140));
    AnimalManager::getInstance()->KillButtonPig->setPosition(ranchLayer->getPosition() + Vec2(280, 140));
    AnimalManager::getInstance()->BuyButtonCow->setPosition(ranchLayer->getPosition() + Vec2(140, 60));
    AnimalManager::getInstance()->KillButtonCow->setPosition(ranchLayer->getPosition() + Vec2(280, 60));
    AnimalManager::getInstance()->BuyButtonSheep->setPosition(ranchLayer->getPosition() + Vec2(140, -20));
    AnimalManager::getInstance()->KillButtonSheep->setPosition(ranchLayer->getPosition() + Vec2(280, -20));
    AnimalManager::getInstance()->BuyButtonChook->setPosition(ranchLayer->getPosition() + Vec2(140, -100));
    AnimalManager::getInstance()->KillButtonChook->setPosition(ranchLayer->getPosition() + Vec2(280, -100));
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
                    CreateNumber(); // ����
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
