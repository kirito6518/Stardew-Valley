#include "HelloWorldScene.h"
#include "MainMap.h"
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

Scene* MainMap::createScene()
{
    return MainMap::create();
}

bool MainMap::init()
{
    if (!Scene::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    {
        // 加载地图
        mapSprite = Sprite::create("Farm_Combat.png");
        mapSprite->setAnchorPoint(Vec2(0.5, 0.5));
        mapSprite->setPosition(visibleSize / 2);
        this->addChild(mapSprite, 0);
        mapSprite->setScale(1.2f); // 将 sprite 放大到原来的 1.2倍
    }


    //添加一个按钮，左键点击后切回主屏幕
    {
        {
            auto toHollowWorld = MenuItemImage::create(
                "CloseNormal.png", 
                "CloseSelected.png",
                CC_CALLBACK_1(MainMap::toMenu, this));
            //设置坐标
            const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
            const float y = toHollowWorld->getContentSize().height / 2;
            toHollowWorld->setPosition(Vec2(x, y));
            // 创建菜单，它是一个自动释放对象
            auto menu = Menu::create(toHollowWorld, NULL);
            menu->setPosition(Vec2::ZERO);
            // 添加到图层
            this->addChild(menu, 2);
        }
        {
            // 添加一段文本
            auto toHollowWorld = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 35);
            // 将标签放在按钮里
            const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
            const float y = toHollowWorld->getContentSize().height / 2;
            toHollowWorld->setPosition(Vec2(x - 20, y + 5));
            // 将标签作为子标签添加到此图层
            this->addChild(toHollowWorld, 2);
        }
    }


    //添加一个按钮，左键点击后打开背包
    {
        // 创建背包按钮
        auto backpackButton = MenuItemImage::create(
            "BagBottom_normal.png",  // 按钮正常状态的图片
            "BagBottom_pressed.png", // 按钮按下状态的图片
            CC_CALLBACK_1(MainMap::onBackpackButtonClicked, this));

        //设置坐标
        const float x = visibleSize.width - backpackButton->getContentSize().width / 2;
        const float y = visibleSize.height - backpackButton->getContentSize().height / 2 + 12;
        backpackButton->setPosition(Vec2(x, y));
        backpackButton->setScale(0.8f);
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(backpackButton, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 2);
    }

    // 创建主角精灵
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");
    player.playerSprite = Sprite::createWithTexture(texture, Rect(0, 0, 72, 96)); // 待机是向下待机的第一帧
    player.playerSprite->setPosition(visibleSize / 2); // 初始位置在屏幕中央
    this->addChild(player.playerSprite, 1);

    // 创建六个方向的行走动画
    player.createWalkAnimations();

    // 创建六个方向的待机动画
    player.createIdleAnimations();

    // 初始化目标位置
    player.targetPosition = player.playerSprite->getPosition();
    player.isMoving = false;

    // 初始化键盘状态
    player.isWPressed = player.isAPressed = player.isSPressed = player.isDPressed = false;

    // 初始化最后一次行走的方向索引
    player.lastDirectionIndex = 0; // 默认向下

    // 注册键盘事件
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每帧更新主角位置
    this->scheduleUpdate();

    return true;
}

// 切换到主菜单
void MainMap::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}

// 背包按钮的回调函数
void MainMap::onBackpackButtonClicked(Ref* sender)
{
    // 调用单例管理类显示背包层
    BackpackManager::getInstance()->showBackpack(this);
}

void MainMap::update(float delta)
{
    // 在这里添加每一帧需要更新的逻辑
    // 例如，更新玩家的位置、动画等
    player.update(delta);
}