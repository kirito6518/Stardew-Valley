
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
        mapSprite = Sprite::create("MainMap.png");
        mapSprite->setAnchorPoint(Vec2(0.5, 0.5));
        mapSprite->setPosition(visibleSize / 2);
        this->addChild(mapSprite, 0);
        mapSprite->setScale(1.8f); // �� sprite �Ŵ�ԭ���� 1.8��
    }

    {
        //���һ����ť�����������л�����Ļ
        auto toHollowWorld = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainMap::toMenu, this));

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
               // ʹ���Լ����ֿ�
        auto toHollowWorld = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 35);
        // ����ǩ���ڰ�ť��
        const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
        const float y = toHollowWorld->getContentSize().height / 2;
        toHollowWorld->setPosition(Vec2(x - 20, y + 5));
        // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(toHollowWorld, 2);
    }


    return true;
}


// �л������˵�
void MainMap::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}
