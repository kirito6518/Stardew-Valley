
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


    // ��ȡ���ڴ�С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // ��ʼ����������
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

    // ��ӱ������ذ�ť
    auto hideButton = MenuItemImage::create(
        "ui/close_normal.png",  // ���ذ�ť����״̬��ͼƬ
        "ui/close_pressed.png", // ���ذ�ť����״̬��ͼƬ
        CC_CALLBACK_1(BackpackLayer::hideBackpack, this));

    hideButton->setAnchorPoint(Vec2(1, 0));
    hideButton->setPosition(Vec2(visibleSize.width / 2+ backpackSize.width/2, visibleSize.height / 2 + backpackSize.height / 2)); // �������ذ�ť��λ��

    auto menu = Menu::create(hideButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    // ��ʼ������״̬
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

    // ������Ʒ����
    auto itemSprite = Sprite::create(itemImagePath);
    if (!itemSprite)
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false;
    }


    /*�˴��ݶ�*/
    // ������Ʒλ�ã�������Ʒ���������У�
    float x = 100 + (currentItems % 5) * 80; // ÿ�� 5 ����Ʒ����� 80
    float y = 400 - (currentItems / 5) * 80; // ÿ�м�� 80
    itemSprite->setPosition(Vec2(x, y));
    /*�˴��ݶ�*/

    // �����Ʒ������
    this->addChild(itemSprite);
    itemSprites.pushBack(itemSprite);

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}


void BackpackLayer::hideBackpack(Ref* sender)
{
    // ���� BackpackManager �� hideBackpack ����
    BackpackManager::getInstance()->hideBackpack();
}