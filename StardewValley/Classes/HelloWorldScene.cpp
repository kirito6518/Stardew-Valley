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
    //初始化
    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    //这个函数可以添加一个按钮！！！！
    // 添加一个带有“X”图像的菜单项，单击该菜单项可退出程序
    // 你可以修改它。
    //
    // 添加“关闭”图标以退出进度。它是一个自动释放对象
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
        // 刚刚好挨到左下角
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 这个函数可以添加一段文本！！！！
    // 添加一个标签显示“Exit”
    // 创建并初始化标签
    // 这里是添加一个标签，参数分别是文字，字库，大小。使用自带的TTF字库，也可以使用Windows自带字库，更改函数名即可
    auto label = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 40);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 将标签放在按钮中央
        float x = origin.x + visibleSize.width - label->getContentSize().width / 2;
        float y = origin.y + label->getContentSize().height / 2;
        label->setPosition(Vec2(x - 30, y + 8));

        // 将标签作为子标签添加到此图层
        this->addChild(label, 1);
    }

    // 添加“HelloWorld”启动画面
    // 这里是显示了一张精灵
    // 这个函数可以添加一张图片！！！！
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // 将精灵放置在屏幕中央
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //关闭cocos2d-x游戏场景并退出应用程序
    Director::getInstance()->end();

    /*要在不退出应用程序的情况下导航回本机iOS屏幕（如果存在），请不要如上所述使用Director:：getInstance（）->end（），而是触发在RootViewController.mm中创建的自定义事件，如下所示*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
