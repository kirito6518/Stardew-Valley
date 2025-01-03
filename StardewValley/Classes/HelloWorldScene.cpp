#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AuthorListScene.h"
#include "MainMap.h"
#include "BackpackManager.h"
#include "HelpScene.h"


USING_NS_CC;
using namespace CocosDenshion;

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

    // 加载音效
    SimpleAudioEngine::getInstance()->preloadEffect("audio/start.mp3");

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
        auto closeItem = MenuItemImage::create(
            "ui/CloseNormal.png", 
            "ui/CloseSelected.png", 
            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
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
        auto toAuthorList = MenuItemImage::create("ui/CloseNormal.png", 
            "ui/CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::toAuthorlist, this));
            
        //设置坐标
        const float x = visibleSize.width / 4 * 3 - toAuthorList->getContentSize().width / 2;
        const float y = toAuthorList->getContentSize().height / 2;
        toAuthorList->setPosition(Vec2(x, y));
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(toAuthorList, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    {
        // 添加一段文本
        // 使用自己的字库
        auto toAuthorList = Label::createWithTTF("Author\n  List", "fonts/Marker Felt.ttf", 20);
        // 将标签放在按钮里
        const float x = visibleSize.width / 4 * 3 - toAuthorList->getContentSize().width / 2;
        const float y = toAuthorList->getContentSize().height / 2;
        toAuthorList->setPosition(Vec2(x - 30, y + 5));
        // 将标签作为子标签添加到此图层
        this->addChild(toAuthorList, 2);
    }

    {
        //添加一个按钮，左键点击后加载存档
        //执行帮助
        auto closeItem = MenuItemImage::create(
            "ui/CloseNormal.png",
            "ui/CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::toHelp, this));
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
        auto label = Label::createWithTTF("Help", "fonts/Marker Felt.ttf", 40);
        // 将标签放在按钮里
        const float x = visibleSize.width / 4 + label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x + 25, y + 5));
        // 将标签作为子标签添加到此图层
        this->addChild(label, 2);
    }

    {
        //添加一个按钮，左键点击后开启一个新存档
        //执行创建新存档的函数
        auto closeItem = MenuItemImage::create(
            "ui/CloseNormal.png", 
            "ui/CloseSelected.png", 
            CC_CALLBACK_1(HelloWorld::toMainMap, this));
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
        auto label = Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 20);
        // 将标签放在按钮里
        const float x = label->getContentSize().width / 2;
        const float y = label->getContentSize().height / 2;
        label->setPosition(Vec2(x + 20, y + 20));
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

//前往作者名单场景
void HelloWorld::toAuthorlist(Ref* ref)
{
    auto authorListScene = AuthorListScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, authorListScene));
}


//前往主地图场景
void HelloWorld::toMainMap(Ref* ref)
{
    // 播放音效
    SimpleAudioEngine::getInstance()->playEffect("audio/start.mp3");
    mainMapScene = MainMap::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mainMapScene));
}

// 前往帮助场景
void HelloWorld::toHelp(Ref* ref) {
    auto HelpScene = Help::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelpScene));
}


