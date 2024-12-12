
#include "BackpackLayer.h"
#include "BackpackManager.h"
USING_NS_CC;

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

bool BackpackLayer::init(const std::string& backpackBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }


    // 获取窗口大小
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
    this->addChild(backpackBgSprite,3);

    auto backpackSize=backpackBgSprite->getContentSize();

    // 添加背包隐藏按钮
    auto hideButton = MenuItemImage::create(
        "ui/close_normal.png",  // 隐藏按钮正常状态的图片
        "ui/close_pressed.png", // 隐藏按钮按下状态的图片
        CC_CALLBACK_1(BackpackLayer::hideBackpack, this));

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2+ backpackSize.width/2, visibleSize.height / 2 + backpackSize.height / 2)); // 设置隐藏按钮的位置

    auto menu = Menu::create(hideButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    // 初始化背包状态
    this->maxItems = maxItems;
    this->currentItems = 0;

    return true;
}

bool BackpackLayer::addItem(const std::string& itemImagePath)
{
    if (currentItems >= maxItems)
    {
        CCLOG("Backpack is full! Cannot add more items.");
        return false;
    }

    // 创建物品精灵
    auto itemSprite = Sprite::create(itemImagePath);
    if (!itemSprite)
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false;
    }


    /*此处暂定*/
    // 设置物品位置（假设物品从左到右排列）
    float x = 100 + (currentItems % 5) * 80; // 每行 5 个物品，间隔 80
    float y = 400 - (currentItems / 5) * 80; // 每列间隔 80
    itemSprite->setPosition(Vec2(x, y));
    /*此处暂定*/

    // 添加物品到背包
    this->addChild(itemSprite);
    itemSprites.pushBack(itemSprite);

    // 更新当前物品数量
    currentItems++;
    return true;
}


void BackpackLayer::hideBackpack(Ref* sender)
{
    // 调用 BackpackManager 的 hideBackpack 方法
    BackpackManager::getInstance()->hideBackpack();
}