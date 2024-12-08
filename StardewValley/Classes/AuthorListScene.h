#ifndef __AUTHOR_LIST_SCENE_H__
#define __AUTHOR_LIST_SCENE_H__

#include "cocos2d.h"

class AuthorListScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // ʵ�� "init" ����
    CREATE_FUNC(AuthorListScene);
};

#endif // __AUTHOR_LIST_SCENE_H__