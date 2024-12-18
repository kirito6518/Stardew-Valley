#include "BringMine.h"
#include "cocos2d.h"
#include "Cave.h"

USING_NS_CC;

// 静态成员变量初始化
ChooseMineLayer* ChooseMineLayer::_instance = nullptr;

// 获取单例实例
ChooseMineLayer* ChooseMineLayer::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) ChooseMineLayer();
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
ChooseMineLayer::ChooseMineLayer()
{
    // 私有构造函数，防止外部直接实例化
}

// 初始化
bool ChooseMineLayer::init() {

    if (!Layer::init())
    {
        return false;
    }

    chooseMine = 0;

    const auto visibleSize = Director::getInstance()->getVisibleSize();

    chooseLayer = Sprite::create("ui/BigLayer.png"); // 800*464
    chooseLayer->setAnchorPoint(Vec2(0.5, 0.5));
    chooseLayer->setPosition(visibleSize / 2);
    this->addChild(chooseLayer, 3);

    // 创建yes按钮
    yesButton = MenuItemImage::create(
        "ui/yes_normal.png",
        "ui/yes_pressed.png",
        CC_CALLBACK_1(ChooseMineLayer::ChangeMine, this));
    //设置位置
    const float x = visibleSize.width / 2 - 240;
    const float y = visibleSize.height / 2 - 136;
    yesButton->setPosition(Vec2(x, y));

    // 创建触摸监听器
    auto yesButtonListener = EventListenerTouchOneByOne::create();

    // 触摸开始
    yesButtonListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 设置按钮为按下状态
            yesButton->setNormalImage(Sprite::create("ui/yes_pressed.png"));
            return true;
        }
        return false;
        };

    // 触摸结束
    yesButtonListener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 设置按钮为正常状态
            yesButton->setNormalImage(Sprite::create("ui/yes_normal.png"));
            ChangeMine(nullptr);
        }
        else
        {
            // 如果触摸结束时不在按钮上，恢复按钮状态
            yesButton->setNormalImage(Sprite::create("ui/yes_normal.png"));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(yesButtonListener, yesButton);

    // 添加按钮到层
    this->addChild(yesButton, 3);

    // 创建no按钮
    noButton = MenuItemImage::create(
        "ui/no_normal.png",
        "ui/no_pressed.png",
        CC_CALLBACK_1(ChooseMineLayer::NoChangeMine, this));
    //设置位置
    const float noX = visibleSize.width / 2 + 240; // 与yes按钮关于屏幕中心竖线对称
    const float noY = visibleSize.height / 2 - 136;
    noButton->setPosition(Vec2(noX, noY));

    // 创建触摸监听器
    auto noButtonListener = EventListenerTouchOneByOne::create();

    // 触摸开始
    noButtonListener->onTouchBegan = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 设置按钮为按下状态
            noButton->setNormalImage(Sprite::create("ui/no_pressed.png"));
            return true;
        }
        return false;
        };

    // 触摸结束
    noButtonListener->onTouchEnded = [this](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            // 设置按钮为正常状态
            noButton->setNormalImage(Sprite::create("ui/no_normal.png"));
            NoChangeMine(nullptr);
        }
        else
        {
            // 如果触摸结束时不在按钮上，恢复按钮状态
            noButton->setNormalImage(Sprite::create("ui/no_normal.png"));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(noButtonListener, noButton);

    // 添加按钮到层
    this->addChild(noButton, 3);

    return true;
}

// 改变矿物
void ChooseMineLayer::ChangeMine(Ref* sender) {
    dynamic_cast<Cave*>(cave)->gem = chooseMine;
    this->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
    dynamic_cast<Cave*>(cave)->HideLayer(sender); // 重新开始时间更新
}

// 不改变矿物
void ChooseMineLayer::NoChangeMine(Ref* sender) {
    this->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
    dynamic_cast<Cave*>(cave)->HideLayer(sender);
}