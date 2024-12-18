#include "ShopItem.h"
#include "ShopItemManager.h"
#include "BackpackManager.h"
USING_NS_CC;

// 创建商店物品
ShopItem* ShopItem::create(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice)
{
    auto shopItem = new (std::nothrow) ShopItem(); // 创建一个新的 ShopItem 对象
    if (shopItem && shopItem->init(itemImagePath, itemName, sellingPrice,buyingPrice)) // 初始化物品
    {
        shopItem->autorelease(); // 自动释放对象
        return shopItem; // 返回创建的物品
    }
    CC_SAFE_DELETE(shopItem); // 如果初始化失败，删除对象
    return nullptr; // 返回空指针
}

// 初始化商店物品
bool ShopItem::init(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice)
{
    if (!Node::init()) // 调用基类的初始化方法
    {
        return false; // 如果基类初始化失败，返回 false
    }

    // 初始化物品属性
    this->itemName = itemName; // 设置物品名称
    this->sellingPrice = sellingPrice; // 设置物品卖出价格
    this->buyingPrice = buyingPrice;//设置物品买入价格

    // 创建物品图标
    itemIcon = Sprite::create(itemImagePath);
    if (!itemIcon) // 检查图标是否创建成功
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // 如果图标创建失败，返回 false
    }
    itemIcon->retain(); // 保留 itemIcon

    // 将物品实例注册到 ShopItemManager
    ShopItemManager::getInstance()->addShopItem(itemName, this);

    return true; // 初始化成功，返回 true
}

