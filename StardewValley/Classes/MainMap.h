
#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //��ʼ��
    virtual bool init();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // ʵ��create����
    CREATE_FUNC(MainMap);

};

#endif // __MainMap_H__

