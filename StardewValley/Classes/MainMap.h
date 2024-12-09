
#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //��ʼ��
    virtual bool init();

    //ǰ�����˵�����
    void toMenu(Ref*);

    // ʵ��create����
    CREATE_FUNC(MainMap);

private:
    cocos2d::Sprite* mapSprite;
};

#endif // __MainMap_H__

