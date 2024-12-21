#include "HelloWorldScene.h"
#include "HelpScene.h"


USING_NS_CC;

Scene* Help::createScene()
{
    return Help::create();
}

bool Help::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ��ȡ���ڴ�С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    help = Sprite::create("ui/HelpBackGround.png");
    help->setAnchorPoint(Vec2(0.5f, 0.5f));
    help->setPosition(visibleSize / 2);
    this->addChild(help, 0);

    {
        //���һ����ť�����������л�����Ļ
        auto toHollowWorld = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Help::toMenu, this));
           
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
void Help::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}