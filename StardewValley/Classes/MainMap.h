#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    // ��ʼ��
    virtual bool init();

    // ǰ�����˵�����
    void toMenu(Ref*);

    // ������ť�Ļص�����
    void onBackpackButtonClicked(Ref* sender);

    // ʵ��create����
    CREATE_FUNC(MainMap);

    // ÿ֡����
    void MainMap::update(float dt);

private:
    cocos2d::Sprite* mapSprite;    
    Player player;
};

#endif // __MainMap_H__