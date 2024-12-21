#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Help : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    //ǰ�����˵�����
    void toMenu(Ref*);

    // ʵ�� "init" ����
    CREATE_FUNC(Help);

    Sprite* help;
};

#endif // __HELP_SCENE_H__