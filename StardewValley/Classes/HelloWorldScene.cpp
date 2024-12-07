#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //��ʼ��
    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    //��������������һ����ť��������
    // ���һ�����С�X��ͼ��Ĳ˵�������ò˵�����˳�����
    // ������޸�����
    //
    // ��ӡ��رա�ͼ�����˳����ȡ�����һ���Զ��ͷŶ���
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        // �ոպð������½�
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // ��������������һ���ı���������
    // ���һ����ǩ��ʾ��Exit��
    // ��������ʼ����ǩ
    // ���������һ����ǩ�������ֱ������֣��ֿ⣬��С��ʹ���Դ���TTF�ֿ⣬Ҳ����ʹ��Windows�Դ��ֿ⣬���ĺ���������
    auto label = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 40);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // ����ǩ���ڰ�ť����
        float x = origin.x + visibleSize.width - label->getContentSize().width / 2;
        float y = origin.y + label->getContentSize().height / 2;
        label->setPosition(Vec2(x - 30, y + 8));

        // ����ǩ��Ϊ�ӱ�ǩ��ӵ���ͼ��
        this->addChild(label, 1);
    }

    // ��ӡ�HelloWorld����������
    // ��������ʾ��һ�ž���
    // ��������������һ��ͼƬ��������
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // �������������Ļ����
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //�ر�cocos2d-x��Ϸ�������˳�Ӧ�ó���
    Director::getInstance()->end();

    /*Ҫ�ڲ��˳�Ӧ�ó��������µ����ر���iOS��Ļ��������ڣ����벻Ҫ��������ʹ��Director:��getInstance����->end���������Ǵ�����RootViewController.mm�д������Զ����¼���������ʾ*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
