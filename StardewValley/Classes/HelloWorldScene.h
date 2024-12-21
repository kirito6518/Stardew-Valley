﻿
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainMap.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // 前往作者名单场景
    void toAuthorlist(Ref*);

    // 前往主地图场景
    void toMainMap(Ref*);

    // 前往帮助场景
    void toHelp(Ref*);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    Scene* mainMapScene; // 主地图场景
};

#endif // __HELLOWORLD_SCENE_H__
