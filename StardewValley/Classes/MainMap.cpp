#include "HelloWorldScene.h"
#include "MainMap.h"
#include "cocos2d.h"

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
        // ���ص�ͼ
        mapSprite = Sprite::create("Farm_Combat.png");
        mapSprite->setAnchorPoint(Vec2(0.5, 0.5));
        mapSprite->setPosition(visibleSize / 2);
        this->addChild(mapSprite, 0);
        mapSprite->setScale(1.2f); // �� sprite �Ŵ�ԭ���� 1.2��
    }


    //���һ����ť�����������л�����Ļ
    {
        {
            auto toHollowWorld = MenuItemImage::create(
                "CloseNormal.png", 
                "CloseSelected.png",
                CC_CALLBACK_1(MainMap::toMenu, this));
            //��������
            const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
            const float y = toHollowWorld->getContentSize().height / 2;
            toHollowWorld->setPosition(Vec2(x, y));
            // �����˵�������һ���Զ��ͷŶ���
            auto menu = Menu::create(toHollowWorld, NULL);
            menu->setPosition(Vec2::ZERO);
            // ��ӵ�ͼ��
            this->addChild(menu, 1);
        }
        {
            // ���һ���ı�
            auto toHollowWorld = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 35);
            // ����ǩ���ڰ�ť��
            const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
            const float y = toHollowWorld->getContentSize().height / 2;
            toHollowWorld->setPosition(Vec2(x - 20, y + 5));
            // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
            this->addChild(toHollowWorld, 2);
        }
    }


    //���һ����ť����������򿪱���
    {
        // ����������ť
        auto backpackButton = MenuItemImage::create(
            "BagBottom_normal.png",  // ��ť����״̬��ͼƬ
            "BagBottom_pressed.png", // ��ť����״̬��ͼƬ
            CC_CALLBACK_1(MainMap::onBackpackButtonClicked, this));

        //��������
        const float x = visibleSize.width - backpackButton->getContentSize().width / 2;
        const float y = visibleSize.height - backpackButton->getContentSize().height / 2 + 12;
        backpackButton->setPosition(Vec2(x, y));
        backpackButton->setScale(0.8f);
        // �����˵�������һ���Զ��ͷŶ���
        auto menu = Menu::create(backpackButton, NULL);
        menu->setPosition(Vec2::ZERO);
        // ��ӵ�ͼ��
        this->addChild(menu, 1);
    }

    // �������Ǿ���
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");
    playerSprite = Sprite::createWithTexture(texture, Rect(0, 0, 96.0, 96.0)); // ���������´����ĵ�һ֡
    playerSprite->setPosition(visibleSize / 2); // ��ʼλ������Ļ����
    this->addChild(playerSprite, 1);

    // ����������������߶���
    createWalkAnimations();

    // ������������Ĵ�������
    createIdleAnimations();

    // ��ʼ��Ŀ��λ��
    targetPosition = playerSprite->getPosition();
    isMoving = false;

    // ��ʼ������״̬
    isWPressed = isAPressed = isSPressed = isDPressed = false;

    // ��ʼ�����һ�����ߵķ�������
    lastDirectionIndex = 0; // Ĭ������

    // ע������¼�
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainMap::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainMap::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ÿ֡��������λ��
    this->scheduleUpdate();

    return true;
}

// �л������˵�
void MainMap::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}

// ����������������߶���
void MainMap::createWalkAnimations()
{
    // ���� walk.png ͼƬ
    auto texture = Director::getInstance()->getTextureCache()->addImage("walk.png");

    // walk.png ��һ�� 6 �����ͼƬ��ÿ֡�Ŀ��Ϊ 72 ���أ��߶�Ϊ 96 ����
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // ÿ�������� 8 ֡

    // ����ÿ�������֡��Χ
    // ����˳���¡������ϡ��ϡ����ϡ���
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 �������ƫ����

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // ���ݷ���ƫ��������֡������
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // ��������
        walkAnimations[i] = Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡��� 0.1 ��
        walkAnimations[i]->retain(); // ������������ֹ���ͷ�
    }
}

// ������������Ĵ�������
void MainMap::createIdleAnimations()
{
    // ���� idle.png ͼƬ
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");

    // idle.png ��һ�� 6 �����ͼƬ��ÿ֡�Ŀ��Ϊ 72 ���أ��߶�Ϊ 96 ����
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // ÿ�������� 8 ֡

    // ����ÿ�������֡��Χ
    // ����˳���¡������ϡ��ϡ����ϡ���
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 �������ƫ����

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // ���ݷ���ƫ��������֡������
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // ��������
        idleAnimations[i] = Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡��� 0.1 ��
        idleAnimations[i]->retain(); // ������������ֹ���ͷ�
    }
}

// ���ݷ���ѡ�񶯻�
int MainMap::getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to)
{
    Vec2 direction = to - from;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));

    // ���ݽǶ�ȷ������
    if (angle >= -22.5f && angle < 22.5f) return 5; // ��
    if (angle >= 22.5f && angle < 67.5f) return 4;  // ����
    if (angle >= 67.5f && angle < 112.5f) return 3; // ��
    if (angle >= 112.5f && angle < 157.5f) return 2; // ����
    if (angle >= 157.5f || angle < -157.5f) return 1; // ��
    if (angle >= -157.5f && angle < -112.5f) return 1; // ����
    if (angle >= -112.5f && angle < -67.5f) return 0; // ��
    if (angle >= -67.5f && angle < -22.5f) return 5; // ����

    return 5; // Ĭ����
}

// ���̰����¼�����
void MainMap::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key pressed: %d", keyCode); // �����������
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            isWPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            isAPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isSPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            isDPressed = true;
            break;
        default:
            break;
    }
}

// �����ͷ��¼�����
void MainMap::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key released: %d", keyCode); // �����������
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            isWPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            isAPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isSPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            isDPressed = false;
            break;
        default:
            break;
    }
}

// ��������λ��
void MainMap::updatePlayerPosition(float dt)
{
    Vec2 direction = Vec2::ZERO;

    if (isWPressed) direction.y += 1; // ��
    if (isAPressed) direction.x -= 1; // ��
    if (isSPressed) direction.y -= 1; // ��
    if (isDPressed) direction.x += 1; // ��

    if (direction != Vec2::ZERO)
    {
        // ����Ŀ��λ��
        targetPosition = playerSprite->getPosition() + direction * 100 * dt; // ÿ���ƶ� 100 ����

        // ���ݷ���ѡ�񶯻�
        int directionIndex = getDirectionIndex(playerSprite->getPosition(), targetPosition);

        // �����ܶ�����
        playerSprite->runAction(RepeatForever::create(Animate::create(walkAnimations[directionIndex])));

        // ��������λ��
        playerSprite->setPosition(targetPosition);

        // ��¼���һ�����ߵķ�������
        lastDirectionIndex = directionIndex;
    }
    else
    {
        // ֹͣ����
        playerSprite->stopAllActions();

        // ���Ŵ�������
        playerSprite->runAction(RepeatForever::create(Animate::create(idleAnimations[lastDirectionIndex])));
    }
}

// ÿ֡����
void MainMap::update(float dt)
{
    updatePlayerPosition(dt);
}

// ������ť�Ļص�����
void MainMap::onBackpackButtonClicked(Ref* sender)
{
    // ���õ�����������ʾ������
    BackpackManager::getInstance()->showBackpack(this);
}