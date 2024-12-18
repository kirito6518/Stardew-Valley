#include "ShopManager.h"
#include "ShopLayer.h"
#include "ShopItem.h"  
#include "ShopItemManager.h" 
#include "BackpackManager.h"
#include "ItemManager.h"

USING_NS_CC;

// 初始化单例实例
ShopManager* ShopManager::instance = nullptr;

// 获取单例实例
ShopManager* ShopManager::getInstance()
{
    if (!instance)
    {
        instance = new ShopManager();
    }
    return instance;
}

// 构造函数
ShopManager::ShopManager()
{
    shopLayer = ShopLayer::create("ui/backpack.png", 30); // 创建商店层，10*3格子
    shopLayer->retain(); // 保留商店层，防止被释放

    maxItems = 30;           // 设置商店物品上限
    currentItems = 0;        // 初始化当前物品数量

    //此处加载所有商店中会出现的物品
    // 第一个数字为卖出价格，第二个数字为买入价格
    ShopItem::create("crops/OnionSeed.png", "Onion\nSeed", 0, 1);

}

// 析构函数
ShopManager::~ShopManager()
{
    shopLayer->release(); // 释放商店层
}

// 显示商店
void ShopManager::showShop(Node* parent)
{
    if (shopLayer->getParent() == nullptr)
    {
        parent->addChild(shopLayer, 2); // 将商店层添加到当前场景
    }
}

// 隐藏商店
void ShopManager::hideShop()
{
    shopLayer->removeFromParentAndCleanup(false); // 从父节点移除，但保留对象
}

// 添加物品到商店
bool ShopManager::addItem(ShopItem* newitem)
{
    if (!newitem)
    {
        return false;
    }

    if (isFull())
    {
        //log("Shop is full! Cannot add more items.");
        return false;
    }


    // 检查是否已有相同物品
    for (auto item : items)
    {
        if (item->getName() == newitem->getName())  {return false;}
    }

    newitem->retain(); // 防止其在被销毁时为空

    // 添加物品到商店
    items.pushBack(newitem);

    // 获取物品图标并设置用户数据
    auto itemSprite = newitem->getIcon();  
    itemSprite->setUserData(newitem); // 将 ShopItem 对象与物品图标关联

    // 将物品图标添加到商店层
    static_cast<ShopLayer*>(shopLayer)->addItem(itemSprite);

    // 更新当前物品数量
    currentItems++;
    return true;
}

// 移除物品
void ShopManager::removeItem(ShopItem* item)  // 替换 Item*
{
    items.eraseObject(item);
    static_cast<ShopLayer*>(shopLayer)->removeItem(item->getIcon());
    currentItems--;
}

// 检查商店是否已满
bool ShopManager::isFull() const
{
    return currentItems >= maxItems;
}

// 购买物品
bool ShopManager::buyItem(ShopItem* item)  // 替换 Item*
{
    // 这里可以实现购买逻辑，例如检查玩家是否有足够的金币，然后从玩家背包中扣除金币并添加物品

    int coinCount = 0;
    std::string toBuyitemName = item->getName();
    Item* coin = BackpackManager::getInstance()->getItemByName("Coin");
    if (coin) {
        coinCount = coin->getCount();
    }
    else {
        return false;
    }

    //获取物品价格
    int Price = ShopItemManager::getInstance()->getShopItem(toBuyitemName)->getBuyingPrice();

    if (coinCount >= Price) {
        coin->decreaseCount(Price);
        Item* getitem = ItemManager::getInstance()->getItem(toBuyitemName);
        BackpackManager::getInstance()->addItem(getitem,1);
        return true;
    }

    return false;
}

// 根据物品名字获得实例
ShopItem* ShopManager::getItemByName(const std::string& itemName) { 
    // 遍历物品列表
    for (auto item : items)
    {
        // 检查物品名称是否匹配
        if (item->getName() == itemName)
        {
            return item; // 返回匹配的物品实例
        }
    }

    return nullptr; // 如果没有找到匹配的物品，返回 nullptr
}