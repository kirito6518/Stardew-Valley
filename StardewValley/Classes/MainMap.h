#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"
#include "BackpackLayer.h"
#include "chipmunk.h"
#include "SeasonManager.h"

USING_NS_CC;

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
    void MainMap::updatePlayerPosition(float dt);

    // ÿ֡����
    void MainMap::updateCameraPosition(float dt);
    
    //��������
    void MainMap::addDay(float dt);

    BackpackManager* Bag;
    SeasonManager seasonManager; // ���� SeasonManager ʵ��
    Label* seasonLabel; // ���� ������ʾ�� Label
    Label* dayLabel; // ���� ������ʾ�� Label
private:
    Sprite* mapSprite; // ��ͼ
    Sprite* upBoundary; // ��ͼ�ϱ߽�
    Sprite* rightBoundary; // ��ͼ�ұ߽�
    Sprite* leftBoundary; // ��ͼ��߽�
    Sprite* downBoundary_left; // ��ͼ�±߽���벿��
    Sprite* downBoundary_right; // ��ͼ�±߽��Ұ벿��
    Sprite* upWater; // ˮ���ϰ벿��
    Sprite* middleWater; // ˮ���м䲿��
    Sprite* downWater; // ˮ���°벿��
    Sprite* fishing; // ���㲿��
    Sprite* CropsLeft; // ũ���󲿷�
    Sprite* CropsRight; // ũ���Ҳ���
    Sprite* home; // ����
    Sprite* fence; // դ��
    Sprite* road; // ·
    Sprite* ranch;// ����
    Player player; // ���
    MenuItemImage* toHollowWorldButton; // ���ز˵��İ�ť
    Label* toHollowWorldWord; // ���ز˵���ť������
    MenuItemImage* backpackButton; // ��������������
};

#endif // __MainMap_H__