#include "AnimalManager.h"
#include <string>
#include "cocos2d.h"
#include <ctime>

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

    timeRecord = (unsigned int)time(nullptr);
    Time = 10; // 设置生长时间为 60 秒

    Sprite* sprite = Sprite::create(); // 创建一个空的精灵

    // 初始化猪
    animals[0] = new Animal("Pig", "Pork", sprite, 0, 0, 0);
    for (auto sprite : animals[0]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // 设置猪的锚点
        sprite->retain();
    }

    // 初始化牛
    animals[1] = new Animal("Cow", "Beef", sprite, 0, 0, 0);
    for (auto sprite : animals[1]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // 设置牛的锚点
        sprite->retain();
    }

    // 初始化羊
    animals[2] = new Animal("Sheep", "Mutton", sprite, 0, 0, 0);
    for (auto sprite : animals[2]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // 设置羊的锚点
        sprite->retain();
    }

    // 初始化鸡
    animals[3] = new Animal("Chicken", "Chicken", sprite, 0, 0, 0);
    for (auto sprite : animals[3]->sprites) {
        sprite->setAnchorPoint(Vec2(0.5, 0.5)); // 设置鸡的锚点
        sprite->retain();
    }

    // 加载动画
    for (int i = 0; i < 4; i++) {
        for (auto sprite : animals[i]->sprites) {
            std::string name = animals[i]->name;
            CreateAnimations(name);
            sprite->runAction(RepeatForever::create(Animate::create(animals[i]->animations)));
        }
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
    else if (name == "Chicken") {
        texture = Director::getInstance()->getTextureCache()->addImage("animal/Chicken.png");
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
            if (animals[i]->sprites.size() > 20) { // 防止动物超过20只
                break;
            }
            animals[i]->numOfChild++; // 增加幼年个体
            // 添加一个新的精灵
            Sprite* newSprite = Sprite::create();
            newSprite->setAnchorPoint(Vec2(0.5, 0.5));
            newSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2)); // 设置位置为屏幕中心
            mainMap->addChild(newSprite, 1); // 层数为 1
            animals[i]->sprites.push_back(newSprite);
            newSprite->runAction(RepeatForever::create(Animate::create(animals[i]->animations)));
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
                // 删除一个精灵
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

// 每帧更新，如果到指定时间，所有个体会成长一个阶段
void AnimalManager::update(float dt) {
    // 获取当前时间
    unsigned int currentTime = (unsigned)(time(0));

    // 如果当前时间减去记录时间的值达到设定的时间
    if (currentTime - timeRecord >= Time) {
        timeRecord = currentTime; // 更新记录时间

        // 遍历所有动物
        for (int i = 0; i < 4; i++) {
            Animal* animal = animals[i];
            if (animal->numOfOld > 0) { // 老年死去
                for (int j = 0; j < animal->numOfOld; j++) {
                    OldDie(animal->name);
                }
                animal->numOfOld = 0;
                CCLOG("OldDie!");
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
                }
                break;
            }
        }
    }
}
