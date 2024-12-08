#include "AuthorListScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;

Scene* AuthorListScene::createScene()
{
    return AuthorListScene::create();
}

bool AuthorListScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 获取窗口大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    {
        // 创建一个标签
        auto Author = Label::createWithTTF("Author List \n\n\nGu Zhen\nLv Kuichen\nHu Yongjie", "fonts/Gen.ttf", 24);
        Author->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - Author->getContentSize().height));

        // 将标签添加到场景中
        this->addChild(Author, 1);
    }

    {
        //添加一个按钮，左键点击后切回主屏幕
        auto toHollowWorld = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [](Ref* sender) {
            // 切换到新的场景
            auto HollowWorldScene = HelloWorld::createScene();
            Director::getInstance()->replaceScene(HollowWorldScene);
            });
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