#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Help : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    //前往主菜单场景
    void toMenu(Ref*);

    // 实现 "init" 方法
    CREATE_FUNC(Help);

    Sprite* help;
};

#endif // __HELP_SCENE_H__