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

    // ��ȡ���ڴ�С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    {
        // ����һ����ǩ
        auto Author = Label::createWithTTF("Author List \n\n\nGu Zhen\nLv Kuichen\nHu Yongjie", "fonts/Gen.ttf", 24);
        Author->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - Author->getContentSize().height));

        // ����ǩ��ӵ�������
        this->addChild(Author, 1);
    }

    {
        //���һ����ť�����������л�����Ļ
        auto toHollowWorld = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [](Ref* sender) {
            // �л����µĳ���
            auto HollowWorldScene = HelloWorld::createScene();
            Director::getInstance()->replaceScene(HollowWorldScene);
            });
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