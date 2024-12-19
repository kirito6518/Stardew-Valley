#include "ShopLayer.h"
#include "ShopManager.h"
#include "ShopItem.h"  
#include "AppDelegate.h"
#include "MainMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

// �����̵��
ShopLayer* ShopLayer::create(const std::string& shopBgPath, int maxItems)
{
    auto layer = new (std::nothrow) ShopLayer();
    if (layer && layer->init(shopBgPath, maxItems))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

// ��ʼ���̵��
bool ShopLayer::init(const std::string& shopBgPath, int maxItems)
{
    if (!Layer::init())
    {
        return false;
    }

    //��ȡ��������
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����̵걳��ͼƬ
    shopBgSprite = Sprite::create(shopBgPath);
    if (!shopBgSprite)
    {
        //CCLOG("Failed to load shop background image: %s", shopBgPath.c_str());
        return false;
    }

    shopBgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    shopBgSprite->setPosition(visibleSize / 2);
    this->addChild(shopBgSprite, 2);

    // ��ȡ�̵걳��ͼ�ߴ缰����
    auto shopSize = shopBgSprite->getContentSize();
    auto shopPos = shopBgSprite->getPosition();

    // �����̵�����ͼƬ
    shopSprite = Sprite::create("ui/shop.png");
    shopSprite->setAnchorPoint(Vec2(0.5, 0.5));
    shopSprite->setAnchorPoint(Vec2(0.5, 0));
    shopSprite->setPosition(Vec2(shopPos.x, shopPos.y + shopSize.height / 2));
    this->addChild(shopSprite, 0);

    //��ʼ��ʣ��ui
    LeftUI = Sprite::create("ui/leftUI.png");
    LeftUI->setAnchorPoint(Vec2(0, 1));
    LeftUI->setPosition(Vec2(shopPos.x-shopSize.width/2, shopPos.y - shopSize.height / 2));
    this->addChild(LeftUI, 0);

    //��ʼ��ʣ���Ҿ���
    leftCoin = Sprite::create("tool/coin.png");
    leftCoin->setScale(0.6f);
    leftCoin->setAnchorPoint(Vec2(0, 1));
    leftCoin->setPosition(Vec2(shopPos.x, shopPos.y + shopSize.height / 2));
    this->addChild(leftCoin, 2);

    //��ʼ��ʣ���ұ�ǩ��ǰ��
    itemLeftLabel1 = Label::createWithTTF("Your Remaining", "fonts/Gen.ttf", 25);
    itemLeftLabel1->setAnchorPoint(Vec2(0, 1));
    this->addChild(itemLeftLabel1, 2);

    //��ʼ��ʣ���ұ�ǩ����
    itemLeftLabel2 = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    itemLeftLabel2->setAnchorPoint(Vec2(0, 1));
    this->addChild(itemLeftLabel2, 2);

    // �����رհ�ť
    closeButton = MenuItemImage::create(
        "ui/close_normal.png",
        "ui/close_pressed.png",
        CC_CALLBACK_1(ShopLayer::hideShop, this));

    if (!closeButton)
    {
        //CCLOG("Failed to create closeButton!");
        return false;
    }

    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->setPosition(Vec2(visibleSize.width / 2 + shopSize.width / 2, visibleSize.height / 2 + shopSize.height / 2));
    this->addChild(closeButton);

    // ��ʼ���̵�����
    this->maxItems = maxItems;
    this->currentItems = 0;

    // ��ʼ����Ʒ���Ʊ�ǩ
    itemNameLabel = Label::createWithTTF("", "fonts/Gen.ttf", 20);
    itemNameLabel->setAnchorPoint(Vec2(0, 1));
    itemNameLabel->setVisible(false);
    this->addChild(itemNameLabel, 3);

    //��ʼ�������Ҿ���
    needCoin = Sprite::create("tool/coin.png");
    needCoin->setScale(0.7f);
    needCoin->setAnchorPoint(Vec2(1, 1));
    needCoin->setVisible(false);
    this->addChild(needCoin, 2);

    // ��ʼ����Ʒ�۸��ǩ
    itemPriceLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    itemPriceLabel->setAnchorPoint(Vec2(1, 1));
    itemPriceLabel->setVisible(false);
    this->addChild(itemPriceLabel, 3);

    // ��ʼ����������ǩ
    buyResultLabel = Label::createWithTTF("", "fonts/Gen.ttf", 25);
    buyResultLabel->setAnchorPoint(Vec2(0.5, 0.5));
    buyResultLabel->setVisible(false);
    this->addChild(buyResultLabel, 3);

    // ��ʼ����Ʒ��ϢUI
    itemDetailUI = Sprite::create("ui/itemDetaUI.png");
    itemDetailUI->setAnchorPoint(Vec2(1, 1));
    itemDetailUI->setVisible(false);
    this->addChild(itemDetailUI, 0);

    // ��ʼ����Ʒ��Ϣ��ǩ
    itemDetailLabel = Label::createWithTTF("", "fonts/Gen.ttf", 30);
    itemDetailLabel->setAnchorPoint(Vec2(0, 1));
    itemDetailLabel->setVisible(false);
    this->addChild(itemDetailLabel, 3);
    

    // ���ع���ť
    buyButton = MenuItemImage::create(
        "ui/buy_button_normal.png",  // ����״̬��ͼƬ
        "ui/buy_button_pressed.png", // ����״̬��ͼƬ
        CC_CALLBACK_1(ShopLayer::onBuyButtonClicked, this)); // ����ص�����
    buyButton->setAnchorPoint(Vec2(1, 1));
    buyButton->setPosition(Vec2(shopPos.x - shopSize.width / 2 - 20, shopPos.y - 40));
    this->addChild(buyButton, 3);

    // Ĭ�Ϲر� buyButton ������¼�����
    buyButton->setEnabled(false);

    // �������¼�������
    setupCombinedMouseListener();

    // ��ʼ���̵���Ӳ���
    gridWidth = 80;
    gridHeight = 80;
    gridSpacing = 8;
    gridStartX = (visibleSize.width - shopSize.width) / 2 + 8;
    gridStartY = (visibleSize.height + shopSize.height) / 2 - 10;

    return true;
}

// �����Ʒ���̵�
bool ShopLayer::addItem(Sprite* itemSprite)
{
    if (currentItems >= maxItems)
    {
        CCLOG("Shop is full! Cannot add more items.");
        return false;
    }

    auto shopSize = shopBgSprite->getContentSize();
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��Ʒ��������ڳ�ʼ�����ƫ����
    int dx, dy;
    itemSprite->setAnchorPoint(Vec2(0, 1));

    // ȷ�� itemSprite û�и��ڵ�
    if (itemSprite->getParent() != nullptr)
    {
        CCLOG("Item sprite already has a parent!");
        return false;
    }

    dx = (currentItems % 10) * (gridWidth + gridSpacing);
    dy = (currentItems / 10) * (gridHeight + gridSpacing);

    itemSprite->setPosition(Vec2(gridStartX + dx, gridStartY - dy));
    // ����Ʒͼ����ӵ��̵��
    this->addChild(itemSprite, 2);
    itemSprites.pushBack(itemSprite);

    // Ϊ��Ʒͼ�������û����ݣ��� ShopItem ����
    ShopItem* item = static_cast<ShopItem*>(itemSprite->getUserData());  
    if (item)
    {
        itemSprite->setUserData(item);
    }

    currentItems++;
    return true;
}

// �Ƴ���Ʒ
void ShopLayer::removeItem(Sprite* itemSprite)
{
    // ������ƷUI
    itemDetailUI->setVisible(false);
    itemDetailLabel->setVisible(false);

    // �������ť�İ󶨼��ɼ�
    buyButton->setUserData(nullptr);
    buyButton->setVisible(false);

    itemSprites.eraseObject(itemSprite);
    itemSprite->removeFromParent();
    currentItems--;
}

// �����̵�
void ShopLayer::hideShop(Ref* sender)
{
    ShopManager::getInstance()->hideShop();

    // ���� mainmap �Ļָ�ʱ����µĺ���
    dynamic_cast<MainMap*>(ShopManager::getInstance()->mainMap)->hideShop(sender);
}

// �������ť�Ļص�����
void ShopLayer::onBuyButtonClicked(Ref* sender)
{
    auto item = static_cast<ShopItem*>(buyButton->getUserData());  

    if (item)
    {
        bool success = ShopManager::getInstance()->buyItem(item);

        if (success)
        {
            int leftCoinCount = 0;
            auto coinYouHave = BackpackManager::getInstance()->getItemByName("Coin");
            if (coinYouHave) {
                leftCoinCount = coinYouHave->getCount();
            }
            std::string itemLeftLabel2Str = ":  " + std::to_string(leftCoinCount);
            // ������Ч
            SimpleAudioEngine::getInstance()->playEffect("audio/coins.mp3");
            itemLeftLabel2->setString(itemLeftLabel2Str);
            buyResultLabel->setString("Buy Success!");
        }
        else
        {
            // ������Ч
            SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");
            buyResultLabel->setString("You Don't Have enough Coins Left!");
        }

        buyResultLabel->setVisible(true);

        this->scheduleOnce([this](float dt) {
            buyResultLabel->setVisible(false);
            }, 1.0f, "hide_buy_result");
    }
}

// �������¼����̵���Ԫ�صĽ���
void ShopLayer::setupCombinedMouseListener()
{
    // �Ƴ�֮ǰ�󶨵��¼�������
    _eventDispatcher->removeEventListenersForTarget(this);

    // ������Ч
    SimpleAudioEngine::getInstance()->preloadEffect("audio/click.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("audio/coins.mp3");

    // ��ȡ�̵걳��ͼ�ߴ缰����
    auto shopSize = shopBgSprite->getContentSize();
    auto shopPos = shopBgSprite->getPosition();

    //����ʣ��uiͼ��λ��
    LeftUI->setPosition(Vec2(shopPos.x - shopSize.width / 2, shopPos.y - shopSize.height / 2));

    //��ȡʣ��uiͼ��������Ϣ
    auto LeftUIPos = LeftUI->getPosition();
    auto LeftUISize = LeftUI->getContentSize();

    //��������ʣ��uiͼ��λ��
    itemLeftLabel1->setPosition(LeftUIPos+Vec2(20,-14));
    leftCoin->setPosition(LeftUIPos + Vec2(245,-9));
    itemLeftLabel2->setPosition(LeftUIPos + Vec2(300, -14));
    int leftCoinCount=0;
    auto coinYouHave = BackpackManager::getInstance()->getItemByName("Coin");
    if (coinYouHave) {
        leftCoinCount = coinYouHave->getCount();
    }
    std::string itemLeftLabel2Str = ":  " + std::to_string(leftCoinCount);
    itemLeftLabel2->setString(itemLeftLabel2Str);
    
    auto mouseListener = EventListenerMouse::create();

    // ����ƶ��¼�
    mouseListener->onMouseMove = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        // ����������Ʒͼ�꣬�������Ƿ���ͣ��ĳ����Ʒ��
        for (auto itemSprite : itemSprites)
        {
            // ��ȡ��Ʒ����ĵ�ǰ����
            Vec2 itemPosition = itemSprite->getPosition();
            // ������Ʒ����ı߽��
            Rect itemBoundingBox = Rect(itemPosition.x, itemPosition.y - gridHeight, gridWidth, gridHeight);

            if (itemBoundingBox.containsPoint(mousePosition))
            {
                // ��ȡ��Ʒ����
                ShopItem* item = static_cast<ShopItem*>(itemSprite->getUserData());  
                if (item)
                {
                    // ��ʾ��Ʒ����
                    itemNameLabel->setString(item->getName());
                    itemNameLabel->setPosition(itemPosition + Vec2(0, 30)); // ����Ʒλ���Ϸ���ʾ
                    itemNameLabel->setVisible(true);
                }
                return;
            }
        }

        // �����겻���κ���Ʒ�ϣ�������Ʒ����
        itemNameLabel->setVisible(false);
        };

    // ������¼�
    mouseListener->onMouseDown = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ�̵걳��ͼ�ߴ缰����
        auto shopSize = shopBgSprite->getContentSize();
        auto shopPos = shopBgSprite->getPosition();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        // ����Ƿ����� closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� closeButton���л�������״̬��ͼƬ
            closeButton->setNormalImage(Sprite::create("ui/close_pressed.png"));
            return;
        }

        // ����Ƿ����� buyButton
        if (buyButton->isVisible()) {
            Vec2 buyButtonPosition = buyButton->getPosition();
            Size buyButtonSize = buyButton->getContentSize();
            Rect buyButtonBoundingBox = Rect(buyButtonPosition.x - buyButtonSize.width,
                buyButtonPosition.y - buyButtonSize.height,
                buyButtonSize.width, buyButtonSize.height);

            if (buyButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� buyButton���л�������״̬��ͼƬ
                buyButton->setNormalImage(Sprite::create("ui/buy_button_pressed.png"));
                return;
            }
        }

        // ����������Ʒͼ�꣬�������Ƿ�����ĳ����Ʒ
        for (auto itemSprite : itemSprites)
        {
            // ��ȡ��Ʒ����ĵ�ǰ����
            Vec2 itemPosition = itemSprite->getPosition();
            // ������Ʒ����ı߽��
            Rect itemBoundingBox = Rect(itemPosition.x, itemPosition.y - gridHeight, gridWidth, gridHeight);

            if (itemBoundingBox.containsPoint(mousePosition))
            {
                // ��ȡ��Ʒ����
                ShopItem* item = static_cast<ShopItem*>(itemSprite->getUserData());
                if (item)
                {
                    // ������Ч
                    SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

                    // ��ʾ��ƷUI
                    itemDetailUI->setVisible(true);
                    itemDetailUI->setPosition(Vec2(shopPos.x - shopSize.width / 2, shopPos.y + shopSize.height / 2)); // ���̵������ʾ

                    // ��ʾ��Ʒ��Ϣ��ǩ
                    itemDetailLabel->setString(item->getName());
                    itemDetailLabel->setVisible(true);
                    itemDetailLabel->setPosition(Vec2(shopPos.x - shopSize.width / 2 - itemDetailUI->getContentSize().width + 25,
                        shopPos.y + shopSize.height / 2 - 25)); // ���̵������ʾ

                    // ��ʾ��Ʒ�۸�
                    std::string label = " :  "+ std::to_string(item->getBuyingPrice());
                    itemPriceLabel->setString(label);
                    itemPriceLabel->setPosition(Vec2(shopPos.x - shopSize.width /2 -55, shopPos.y +3)); // ���̵������ʾ
                    itemPriceLabel->setVisible(true);

                    //��ʾ������ͼ��
                    needCoin->setPosition(Vec2(shopPos.x - shopSize.width / 2 - 85, shopPos.y +7));// ���̵������ʾ
                    needCoin->setVisible(true);

                    // ��ʾ����ť
                    buyButton->setUserData(item); // ����Ʒ�����빺��ť����
                    buyButton->setVisible(true);
                    buyButton->setPosition(Vec2(shopPos.x - shopSize.width / 2 - 15, shopPos.y - 40)); // ���̵������ʾ
                    buyButton->setEnabled(true); // ���� buyButton ������¼�����
                }
                return;
            }
        }

        // �������Ĳ�����Ʒͼ�꣬���ض�Ӧ����ƷUI�������������¼�����
        buyResultLabel->setVisible(false);
        needCoin->setVisible(false);
        itemDetailUI->setVisible(false);
        itemDetailLabel->setVisible(false);
        itemPriceLabel->setVisible(false);
        buyButton->setVisible(false);
        buyButton->setEnabled(false);
        };

    // ����ͷ��¼�
    mouseListener->onMouseUp = [this](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 mousePosition = mouseEvent->getLocationInView();

        // ��ȡ�̵걳��ͼ�ߴ缰����
        auto shopSize = shopBgSprite->getContentSize();
        auto shopPos = shopBgSprite->getPosition();

        // ��ȡ����ͷ��ƫ����
        Vec2 cameraOffset = this->getParent()->getPosition();

        // ���������ת��Ϊ����ڳ���������
        mousePosition -= cameraOffset;

        // ����Ƿ����� closeButton
        Vec2 closeButtonPosition = closeButton->getPosition();
        Size closeButtonSize = closeButton->getContentSize();
        Rect closeButtonBoundingBox = Rect(closeButtonPosition.x - closeButtonSize.width,
            closeButtonPosition.y,
            closeButtonSize.width, closeButtonSize.height);

        if (closeButtonBoundingBox.containsPoint(mousePosition))
        {
            // �������� closeButton���л�������״̬��ͼƬ�������̵��
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
            hideShop(nullptr); // �����̵��

            // ������Ч
            SimpleAudioEngine::getInstance()->playEffect("audio/click.mp3");

            // ������ƷUI
            itemDetailUI->setVisible(false);
            itemDetailLabel->setVisible(false);
            needCoin->setVisible(false);
            itemPriceLabel->setVisible(false);
            // �������ť�İ󶨼��ɼ�
            buyButton->setUserData(nullptr);
            buyButton->setVisible(false);
        }
        else
        {
            // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
            closeButton->setNormalImage(Sprite::create("ui/close_normal.png"));
        }

        // ����Ƿ����� buyButton
        if (buyButton) {
            Vec2 buyButtonPosition = buyButton->getPosition();
            Size buyButtonSize = buyButton->getContentSize();
            Rect buyButtonBoundingBox = Rect(buyButtonPosition.x - buyButtonSize.width,
                buyButtonPosition.y - buyButtonSize.height,
                buyButtonSize.width, buyButtonSize.height);

            if (buyButtonBoundingBox.containsPoint(mousePosition))
            {
                // �������� buyButton���л�������״̬��ͼƬ��ִ�й����߼�
                buyButton->setNormalImage(Sprite::create("ui/buy_button_normal.png"));
                buyResultLabel->setPosition(shopPos + Vec2(0, 50));
                buyButton->activate(); // ִ�й����߼�
            }
            else
            {
                // �����������ʱ���ڰ�ť�����ڣ�Ҳ�л�������״̬
                buyButton->setNormalImage(Sprite::create("ui/buy_button_normal.png"));
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}