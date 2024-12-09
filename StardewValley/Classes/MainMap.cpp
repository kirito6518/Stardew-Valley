
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
    if (!Scene::init()) {
        return false;
    }

    auto _visibleSize = Director::getInstance()->getVisibleSize();
/*    

    // 创建地图精灵
    _mapSprite = Sprite::create("MainMap.png");
    _mapSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _mapSprite->setPosition(_visibleSize.width/2,_visibleSize.height/2);
    this->addChild(_mapSprite,0);*/

    auto map= Sprite::create("MainMap.png");
    map->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    map->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
    this->addChild(map);
   

    return true;
}


