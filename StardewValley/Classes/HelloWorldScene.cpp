#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
//创建场景
Scene* HelloWorld::createScene()
{
    //创建场景
    return HelloWorld::create();
}
// 当文件不存在时，打印有用的错误消息，而不是分段错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// 在“init”上，您需要初始化您的实例
bool HelloWorld::init()
{
    // 关于addChild后面第二个参数的问题，这个参数是图层参数
    // 精灵，菜单，标签共用图层参数，图层越大显示越靠上
    // 同一图层，先运行的在上面
    if ( !Scene::init() )
    {
        return false;
    }
    // 获取游戏屏幕宽高
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    {
        // 添加图片
        auto sprite = Sprite::create("HelloWorld.png");
        // 将精灵放置在屏幕中央
        sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        // 将精灵作为子精灵添加到此层
        this->addChild(sprite, 0);
    }

    {
        //添加一个按钮，左键点击后执行退出函数
        //执行menuCloseCallback这个函数
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //设置坐标
        const float x = visibleSize.width - closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    {
        // 添加一段文本
        // 使用自己的字库
        auto label = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 40);
        // 将标签放在按钮里
        const float x = visibleSize.width - label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x - 30, y + 5));
        // 将标签作为子标签添加到此图层
        this->addChild(label, 2);
    }

    {
        //添加一个按钮，左键点击后播放制作名单
        //执行播放作者名单的函数（未实现）
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //设置坐标
        const float x = visibleSize.width / 4 * 3 - closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    {
        // 添加一段文本
        // 使用自己的字库
        auto label = Label::createWithTTF("Author\n  List", "fonts/Marker Felt.ttf", 20);
        // 将标签放在按钮里
        const float x = visibleSize.width / 4 * 3 - label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x - 30, y + 5));
        // 将标签作为子标签添加到此图层
        this->addChild(label, 2);
    }

    {
        //添加一个按钮，左键点击后加载存档
        //执行加载存档的函数（未实现）
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //设置坐标
        const float x = visibleSize.width / 4 + closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    {
        // 添加一段文本
        // 使用自己的字库
        auto label = Label::createWithTTF("Load", "fonts/Marker Felt.ttf", 40);
        // 将标签放在按钮里
        const float x = visibleSize.width / 4 + label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x + 25, y + 5));
        // 将标签作为子标签添加到此图层
        this->addChild(label, 2);
    }

    {
        //添加一个按钮，左键点击后开启一个新存档
        //执行创建新存档的函数（未实现）
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
        //设置坐标
        const float x = closeItem->getContentSize().width / 2;
        const float y = closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    {
        // 添加一段文本
        // 使用自己的字库
        auto label = Label::createWithTTF(" Start A\nNew Game", "fonts/Marker Felt.ttf", 15);
        // 将标签放在按钮里
        const float x = label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x + 30, y + 10));
        // 将标签作为子标签添加到此图层
        this->addChild(label, 2);
    }

    return true;
}
// 退出
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //关闭cocos2d-x游戏场景并退出应用程序
    Director::getInstance()->end();
    /*要在不退出应用程序的情况下导航回本机iOS屏幕（如果存在），请不要如上所述使用Director:：getInstance（）->end（），而是触发在RootViewController.mm中创建的自定义事件，如下所示*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
