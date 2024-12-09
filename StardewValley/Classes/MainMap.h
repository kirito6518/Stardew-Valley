
#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //初始化
    virtual bool init();

    //前往主菜单场景
    void toMenu(Ref*);

    // 实现create函数
    CREATE_FUNC(MainMap);

private:
    cocos2d::Sprite* mapSprite;
};

#endif // __MainMap_H__

