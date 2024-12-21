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

    // 获取窗口大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    help = Sprite::create("ui/HelpBackGround.png");
    help->setAnchorPoint(Vec2(0.5f, 0.5f));
    help->setPosition(visibleSize / 2);
    this->addChild(help, 0);

    {
        //添加一个按钮，左键点击后切回主屏幕
        auto toHollowWorld = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Help::toMenu, this));
           
        //设置坐标
        const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
        const float y = toHollowWorld->getContentSize().height / 2;
        toHollowWorld->setPosition(Vec2(x, y));
        // 创建菜单，它是一个自动释放对象
        auto menu = Menu::create(toHollowWorld, NULL);
        menu->setPosition(Vec2::ZERO);
        // 添加到图层
        this->addChild(menu, 1);
    }

    {
        // 添加一段文本
        // 使用自己的字库
        auto toHollowWorld = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 35);
        // 将标签放在按钮里
        const float x = visibleSize.width - toHollowWorld->getContentSize().width / 2;
        const float y = toHollowWorld->getContentSize().height / 2;
        toHollowWorld->setPosition(Vec2(x - 20, y + 5));
        // 将标签作为子标签添加到此图层
        this->addChild(toHollowWorld, 2);
    }


    return true;
}


// 切换到主菜单
void Help::toMenu(Ref* ref)
{
    auto HollowWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HollowWorldScene);
}