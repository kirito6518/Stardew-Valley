#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
//��������
Scene* HelloWorld::createScene()
{
    //��������
    return HelloWorld::create();
}
// ���ļ�������ʱ����ӡ���õĴ�����Ϣ�������Ƿֶδ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// �ڡ�init���ϣ�����Ҫ��ʼ������ʵ��
bool HelloWorld::init()
{
    // ����addChild����ڶ������������⣬���������ͼ�����
    // ���飬�˵�����ǩ����ͼ�������ͼ��Խ����ʾԽ����
    // ͬһͼ�㣬�����е�������
    if ( !Scene::init() )
    {
        return false;
    }
    // ��ȡ��Ϸ��Ļ���
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    {
        // ���ͼƬ
        auto sprite = Sprite::create("HelloWorld.png");
        // �������������Ļ����
        sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        // ��������Ϊ�Ӿ�����ӵ��˲�
        this->addChild(sprite, 0);
    }

    {
        //���һ����ť����������ִ���˳�����
        //ִ��menuCloseCallback�������
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //��������
        const float x = visibleSize.width - closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // �����˵�������һ���Զ��ͷŶ���
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // ��ӵ�ͼ��
        this->addChild(menu, 1);
    }

    {
        // ���һ���ı�
        // ʹ���Լ����ֿ�
        auto label = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 40);
        // ����ǩ���ڰ�ť��
        const float x = visibleSize.width - label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x - 30, y + 5));
        // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(label, 2);
    }

    {
        //���һ����ť���������󲥷���������
        //ִ�в������������ĺ�����δʵ�֣�
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //��������
        const float x = visibleSize.width / 4 * 3 - closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // �����˵�������һ���Զ��ͷŶ���
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // ��ӵ�ͼ��
        this->addChild(menu, 1);
    }

    {
        // ���һ���ı�
        // ʹ���Լ����ֿ�
        auto label = Label::createWithTTF("Author\n  List", "fonts/Marker Felt.ttf", 20);
        // ����ǩ���ڰ�ť��
        const float x = visibleSize.width / 4 * 3 - label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x - 30, y + 5));
        // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(label, 2);
    }

    {
        //���һ����ť������������ش浵
        //ִ�м��ش浵�ĺ�����δʵ�֣�
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //��������
        const float x = visibleSize.width / 4 + closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // �����˵�������һ���Զ��ͷŶ���
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // ��ӵ�ͼ��
        this->addChild(menu, 1);
    }

    {
        // ���һ���ı�
        // ʹ���Լ����ֿ�
        auto label = Label::createWithTTF("Load", "fonts/Marker Felt.ttf", 40);
        // ����ǩ���ڰ�ť��
        const float x = visibleSize.width / 4 + label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x + 25, y + 5));
        // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(label, 2);
    }

    {
        //���һ����ť������������һ���´浵
        //ִ�д����´浵�ĺ�����δʵ�֣�
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //��������
        const float x = closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // �����˵�������һ���Զ��ͷŶ���
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // ��ӵ�ͼ��
        this->addChild(menu, 1);
    }

    {
        // ���һ���ı�
        // ʹ���Լ����ֿ�
        auto label = Label::createWithTTF(" Start A\nNew Game", "fonts/Marker Felt.ttf", 15);
        // ����ǩ���ڰ�ť��
        const float x = label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x + 30, y + 10));
        // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(label, 2);
    }

    return true;
}
// �˳�
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //�ر�cocos2d-x��Ϸ�������˳�Ӧ�ó���
    Director::getInstance()->end();
    /*Ҫ�ڲ��˳�Ӧ�ó��������µ����ر���iOS��Ļ��������ڣ����벻Ҫ��������ʹ��Director:��getInstance����->end���������Ǵ�����RootViewController.mm�д������Զ����¼���������ʾ*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
