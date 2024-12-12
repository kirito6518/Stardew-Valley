#include "BackpackLayer.h"
#include "BackpackManager.h"
#include "Item.h"

USING_NS_CC;

// 创建背包层
BackpackLayer* BackpackLayer::create(const std::string& backpackBgPath, int maxItems)
{
    auto layer = new (std::nothrow) BackpackLayer();
    if (layer && layer->init(backpackBgPath, maxItems))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

// 初始化背包层
bool BackpackLayer::init(const std::string& backpackBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初始化背包背景
    backpackBgSprite = Sprite::create(backpackBgPath);
    if (!backpackBgSprite)
    {
        CCLOG("Failed to load backpack background image: %s", backpackBgPath.c_str());
        return false;
    }

    backpackBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    backpackBgSprite->setPosition(visibleSize / 2);
    this->addChild(backpackBgSprite, 3);

    auto backpackSize = backpackBgSprite->getContentSize();

    // 添加隐藏按钮
    auto hideButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(BackpackLayer::hideBackpack, this));

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2 + backpackSize.width / 2, visibleSize.height / 2 + backpackSize.height / 2));

    auto menu = Menu::create(hideButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    // 初始化背包状态
    this->maxItems = maxItems;
    this->currentItems = 0;

    // 初始化物品详细信息UI
    itemNameLabel = Label::createWithSystemFont("", "Arial", 24);
    itemNameLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel);

    itemCountLabel = Label::createWithSystemFont("", "Arial", 24);
    itemCountLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    itemCountLabel->setVisible(false);
    this->addChild(itemCountLabel);

    useButton = MenuItemFont::create("Use", [this](Ref* sender) {
        auto item = static_cast<Item*>(sender);
        bool success = item->useItem();

        if (success)
        {
            useResultLabel->setString("Use Success!");
        }
        else
        {
            useResultLabel->setString("Use Failed!");
        }

        useResultLabel->setVisible(true);

        this->scheduleOnce([this](float dt) {
            useResultLabel->setVisible(false);
            }, 2.0f, "hide_use_result");
        });

    useButton->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
    useButton->setVisible(false);
    auto useMenu = Menu::create(useButton, nullptr);
    useMenu->setPosition(Vec2::ZERO);
    this->addChild(useMenu);

    useResultLabel = Label::createWithSystemFont("", "Arial", 24);
    useResultLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
    useResultLabel->setVisible(false);
    this->addChild(useResultLabel);

    return true;
}

// 添加物品图标到背包
bool BackpackLayer::addItem(Sprite* itemSprite)
{
    if (currentItems >= maxItems)
    {
        CCLOG("Backpack is full! Cannot add more items.");
        return false;
    }

    float x = 100 + (currentItems % 5) * 80;
    float y = 400 - (currentItems / 5) * 80;
    itemSprite->setPosition(Vec2(x, y));

    this->addChild(itemSprite);
    itemSprites.pushBack(itemSprite);

    currentItems++;
    return true;
}

// 移除物品图标
void BackpackLayer::removeItem(Sprite* itemSprite)
{
    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParent();
    currentItems--;
}

// 隐藏背包
void BackpackLayer::hideBackpack(Ref* sender)
{
    BackpackManager::getInstance()->hideBackpack();
}

// 显示物品详细信息
void BackpackLayer::showItemDetails(Item* item)
{
    itemNameLabel->setString(item->getName());
    itemCountLabel->setString("Count: " + std::to_string(item->getCount()));

    itemNameLabel->setVisible(true);
    itemCountLabel->setVisible(true);
    useButton->setVisible(true);
}

// 隐藏物品详细信息
void BackpackLayer::hideItemDetails()
{
    itemNameLabel->setVisible(false);
    itemCountLabel->setVisible(false);
    useButton->setVisible(false);
}