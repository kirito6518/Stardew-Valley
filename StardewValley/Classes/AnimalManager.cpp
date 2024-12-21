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

// 静态成员变量初始化
AnimalManager* AnimalManager::_instance = nullptr;

// 获取单例实例
AnimalManager* AnimalManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) AnimalManager();
        if (_instance && _instance->init())
        {
            _instance->autorelease();
            _instance->retain(); // 增加引用计数，防止被释放
        }
        else
        {
            CC_SAFE_DELETE(_instance);
            _instance = nullptr;
        }
    }
    return _instance;
}

// 私有构造函数
AnimalManager::AnimalManager()
{
    // 私有构造函数，防止外部直接实例化
}

// 初始化
bool AnimalManager::init() {

    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();

    timeRecord = (unsigned int)time(nullptr);
    Time = 30; // 设置生长时间为 30 秒

    ranchLayer = Sprite::create("ui/RanchLayer.png"); // 800 * 464
    ranchLayer->setAnchorPoint(Vec2(0.5, 0.5));
    ranchLayer->setPosition(visibleSize / 2);
    ranchLayer->retain();
    this->addChild(ranchLayer, 3);
    {
        // 创建out按钮
        outButton = MenuItemImage::create(
            "ui/close_normal.png",
            "ui/close_pressed.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        outButton->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto outButtonListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        outButtonListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                outButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        outButtonListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
                outButton->setNormalImage(Sprite::create("ui/close_normal.png")); 
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                HideRanch(nullptr);
            }
            else
            {
                // 如果触摸结束时不在按钮上，恢复按钮状态
                outButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(outButtonListener, outButton);

        // 添加按钮到层
        this->addChild(outButton, 3);
    }

    {
        // 创建猪的买入按钮
        BuyButtonPig = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        BuyButtonPig->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto BuyButtonPigListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        BuyButtonPigListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                BuyButtonPig->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        BuyButtonPigListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
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
                // 如果触摸结束时不在按钮上，恢复按钮状态
                BuyButtonPig->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonPigListener, BuyButtonPig);

        // 添加按钮到层
        this->addChild(BuyButtonPig, 3);
    }
    {
        // 创建猪的屠宰按钮
        KillButtonPig = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        KillButtonPig->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto KillButtonPigListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        KillButtonPigListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                KillButtonPig->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        KillButtonPigListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
                KillButtonPig->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Pig");
            }
            else
            {
                // 如果触摸结束时不在按钮上，恢复按钮状态
                KillButtonPig->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonPigListener, KillButtonPig);

        // 添加按钮到层
        this->addChild(KillButtonPig, 3);
    }

    {
        // 创建牛的买入按钮
        BuyButtonCow = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        BuyButtonCow->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto BuyButtonCowListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        BuyButtonCowListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                BuyButtonCow->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        BuyButtonCowListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
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
                // 如果触摸结束时不在按钮上，恢复按钮状态
                BuyButtonCow->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonCowListener, BuyButtonCow);

        // 添加按钮到层
        this->addChild(BuyButtonCow, 3);
    }
    {
        // 创建牛的屠宰按钮
        KillButtonCow = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        KillButtonCow->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto KillButtonCowListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        KillButtonCowListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                KillButtonCow->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        KillButtonCowListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
                KillButtonCow->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Cow");
            }
            else
            {
                // 如果触摸结束时不在按钮上，恢复按钮状态
                KillButtonCow->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonCowListener, KillButtonCow);

        // 添加按钮到层
        this->addChild(KillButtonCow, 3);
    }

    {
        // 创建羊的买入按钮
        BuyButtonSheep = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        BuyButtonSheep->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto BuyButtonSheepListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        BuyButtonSheepListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                BuyButtonSheep->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        BuyButtonSheepListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
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
                // 如果触摸结束时不在按钮上，恢复按钮状态
                BuyButtonSheep->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonSheepListener, BuyButtonSheep);

        // 添加按钮到层
        this->addChild(BuyButtonSheep, 3);
    }
    {
        // 创建羊的屠宰按钮
        KillButtonSheep = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        KillButtonSheep->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto KillButtonSheepListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        KillButtonSheepListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                KillButtonSheep->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        KillButtonSheepListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
                KillButtonSheep->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Sheep");
            }
            else
            {
                // 如果触摸结束时不在按钮上，恢复按钮状态
                KillButtonSheep->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonSheepListener, KillButtonSheep);

        // 添加按钮到层
        this->addChild(KillButtonSheep, 3);
    }

    {
        // 创建鸡的买入按钮
        BuyButtonChook = MenuItemImage::create(
            "ui/BuyChildNormal.png",
            "ui/BuyChildSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        BuyButtonChook->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto BuyButtonChookListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        BuyButtonChookListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                BuyButtonChook->setNormalImage(Sprite::create("ui/BuyChildSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        BuyButtonChookListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
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
                // 如果触摸结束时不在按钮上，恢复按钮状态
                BuyButtonChook->setNormalImage(Sprite::create("ui/BuyChildNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(BuyButtonChookListener, BuyButtonChook);

        // 添加按钮到层
        this->addChild(BuyButtonChook, 3);
    }
    {
        // 创建鸡的屠宰按钮
        KillButtonChook = MenuItemImage::create(
            "ui/KillAdultNormal.png",
            "ui/KillAdultSelected.png",
            CC_CALLBACK_1(AnimalManager::HideRanch, this));
        //设置位置
        KillButtonChook->setPosition(visibleSize / 2);

        // 创建触摸监听器
        auto KillButtonChookListener = EventListenerTouchOneByOne::create();

        // 触摸开始
        KillButtonChookListener->onTouchBegan = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为按下状态
                KillButtonChook->setNormalImage(Sprite::create("ui/KillAdultSelected.png"));
                return true;
            }
            return false;
            };

        // 触摸结束
        KillButtonChookListener->onTouchEnded = [this](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            if (rect.containsPoint(locationInNode))
            {
                // 设置按钮为正常状态
                KillButtonChook->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
                int audioId2 = AudioEngine::play2d("audio/click.mp3");
                RemoveAnimal("Chook");
            }
            else
            {
                // 如果触摸结束时不在按钮上，恢复按钮状态
                KillButtonChook->setNormalImage(Sprite::create("ui/KillAdultNormal.png"));
            }
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(KillButtonChookListener, KillButtonChook);

        // 添加按钮到层
        this->addChild(KillButtonChook, 3);
    }

    // 初始化猪
    animals[0] = new Animal("Pig", "Pork", 0, 0, 0);

    // 初始化牛
    animals[1] = new Animal("Cow", "Beef", 0, 0, 0);

    // 初始化羊
    animals[2] = new Animal("Sheep", "Mutton", 0, 0, 0);

    // 初始化鸡
    animals[3] = new Animal("Chook", "Chicken", 0, 0, 0);

    // 加载动画
    for (int i = 0; i < 4; i++) {
        std::string name = animals[i]->name;
        CreateAnimations(name);
    }

    // 加载数目
    for (int i = 0; i < 4; i++) {
        // 创建最新的
        animalNum[i]= Label::createWithTTF("", "fonts/Gen.ttf", 1);
        animalNum[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
        animalNum[i]->setPosition(ranchLayer->getPosition() + Vec2(280, 140 - 120 * i));
        this->addChild(animalNum[i], 3);
    }

    return true;
}

// 根据名字加载动画
void AnimalManager::CreateAnimations(std::string& name) {
    int num = 0;
    // 加载 动物动画 图片 128 * 64的
    Texture2D* texture;
    if (name == "Pig") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Pig.png");
        num = 0; // 获得动物编号
    }
    else if (name == "Cow") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Cow.png");
        num = 1; // 获得动物编号
    }
    else if (name == "Sheep") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Sheep.png");
        num = 2; // 获得动物编号
    }
    else if (name == "Chook") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Chook.png");
        num = 3; // 获得动物编号
    }

    // 动物动画 是一个图片，每帧的宽度为 64 像素，高度为 64 像素
    Vector<SpriteFrame*> frames;
    auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, 64, 64));
    frames.pushBack(frame);
    frame = SpriteFrame::createWithTexture(texture, Rect(64, 0, 64, 64));
    frames.pushBack(frame);
    // 创建动画
    animals[num]->animations = Animation::createWithSpriteFrames(frames, 0.1f); // 每帧间隔多少秒
    animals[num]->animations->retain(); // 保留动画，防止被释放
}

// 增加动物（只增加幼年个体）
bool AnimalManager::AddAnimal(const std::string& name) {
    for (int i = 0; i < 4; i++) {
        if (animals[i]->name == name) {
            if (animals[i]->sprites.size() > 19) { // 防止动物超过20只
                break;
            }
            animals[i]->numOfChild++; // 增加幼年个体
            // 添加一个新的精灵
            Sprite* newSprite = Sprite::create();
            newSprite->setAnchorPoint(Vec2(0.5, 0.5));
            newSprite->setPosition(GenerateRandomPosition()); // 设置随机位置
            mainMap->addChild(newSprite, 2); // 层数为 2
            animals[i]->sprites.push_back(newSprite);
            newSprite->runAction(RepeatForever::create(Animate::create(animals[i]->animations)));
            CreateNumber(); // 更新
            return true;
            break;
        }
    }
    return false;
}

// 删除动物（只删除成年个体）
bool AnimalManager::RemoveAnimal(const std::string& name) {
    for (int i = 0; i < 4; i++) {
        if (animals[i]->name == name) {
            if (animals[i]->numOfAdult > 0) {
                animals[i]->numOfAdult--; // 减少成年个体
                Item* initItem = ItemManager::getInstance()->getItem(animals[i]->productType);
                BackpackManager::getInstance()->addItem(initItem, 1);
                // 删除一个精灵
                if (!animals[i]->sprites.empty()) {
                    Sprite* spriteToRemove = animals[i]->sprites.back();
                    if (spriteToRemove->getParent() == mainMap) {
                        mainMap->removeChild(spriteToRemove);
                    }
                    animals[i]->sprites.pop_back();
                }
                CreateNumber(); // 更新
                return true;
                break;
            }
        }
    }
    return false;
}

// 每帧更新，如果到指定时间，所有个体会成长一个阶段
void AnimalManager::UpdateAnimals(float dt) {
    // 获取当前时间
    unsigned int currentTime = (unsigned)(time(0));

    // 如果当前时间减去记录时间的值达到设定的时间
    if (currentTime - timeRecord >= Time) {
        timeRecord = currentTime; // 更新记录时间

        // 遍历所有动物
        for (int i = 0; i < 4; i++) {
            Animal* animal = animals[i];
            while (animal->numOfOld > 0) { // 老年死去
                OldDie(animal->name);
                // CCLOG("OldDie!");
            }
            if (animal->numOfAdult > 0) { // 成年变老年
                animal->numOfOld += animal->numOfAdult;
                animal->numOfAdult = 0;
            }
            if (animal->numOfChild > 0) { // 幼年变成年
                animal->numOfAdult += animal->numOfChild;
                animal->numOfChild = 0;
            }
        }
    }
    // 更新ui
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

// 删除一个老年个体（老死）
void AnimalManager::OldDie(const std::string& name) {
    for (int i = 0; i < 4; i++) {
        if (animals[i]->name == name) {
            if (animals[i]->numOfOld > 0) {
                animals[i]->numOfOld--; // 减少老年个体
                // 删除一个精灵
                if (!animals[i]->sprites.empty()) {
                    Sprite* spriteToRemove = animals[i]->sprites.back();
                    if (spriteToRemove->getParent() == mainMap) {
                        mainMap->removeChild(spriteToRemove);
                    }
                    animals[i]->sprites.pop_back();
                    CreateNumber(); // 更新
                }
                break;
            }
        }
    }
}

// 关闭牧场
void AnimalManager::HideRanch(Ref* sender) {
    dynamic_cast<MainMap*>(mainMap)->HideRanch(sender);
}

// 生成一对随机浮点数 (x, y)，并返回 Vec2
Vec2 AnimalManager::GenerateRandomPosition() {
    // 创建一个随机数生成器
    std::random_device rd;  // 用于获取随机种子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法生成随机数

    // 定义 x 的范围：-80 到 376
    std::uniform_real_distribution<float> distX(-72.0f, 360.0f);

    // 定义 y 的范围：468 到 1044
    std::uniform_real_distribution<float> distY(472.0f, 1044.0f);

    // 生成随机浮点数 x 和 y
    float x = distX(gen);
    float y = distY(gen);

    // 返回生成的随机浮点数对，使用 Vec2
    return Vec2(x, y);
}

// 生成四种动物的数目，每帧更新
void AnimalManager::CreateNumber() {
    for (int i = 0; i < 4; i++) {
        // 移除上一个
        if (animalNum[i]->getParent()) {
            this->removeChild(animalNum[i]);
        }
        // 创建最新的
        animalNum[i] = Label::createWithTTF(std::to_string(animals[i]->numOfChild)+ "           " + std::to_string(animals[i]->numOfAdult) + "           " + std::to_string(animals[i]->numOfOld), "fonts/Gen.ttf", 20);
        animalNum[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
        animalNum[i]->setPosition(ranchLayer->getPosition() + Vec2(-75, 140 - 80 * i));
        this->addChild(animalNum[i], 3);
    }
}
