#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"
#include "BackpackLayer.h"
#include "chipmunk.h"
#include "SeasonManager.h"
#include "NPCManager.h"

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

    // ���ر���
    void hideBackpack(Ref* sender);

    // ʵ��create����
    CREATE_FUNC(MainMap);

    // ÿ֡����
    void MainMap::updatePlayerPosition(float dt);

    // ÿ֡����
    void MainMap::updateCameraPosition(float dt);

    // ��ײ��ʼ������
    bool MainMap::onContactBegin(PhysicsContact& contact);

    
    //��������
    void MainMap::addDay(float dt);


    // ������Ʒ��MainMap��ʹ���߼�,0���ڿյأ�1������ũ����2������ũ��
    void SetUseItemInMainMap();

    BackpackManager* Bag;
    SeasonManager seasonManager; // ���� SeasonManager ʵ��
    Label* seasonLabel; // ���� ������ʾ�� Label
    Label* dayLabel; // ���� ������ʾ�� Label

    Item* OnionSeed;// �������

private:
    Sprite* mapSprite; // ��ͼ

    Sprite* upBoundary; // ��ͼ�ϱ߽�
    PhysicsBody* upBoundaryBox;
    Sprite* rightBoundary; // ��ͼ�ұ߽�
    PhysicsBody* rightBoundaryBox;
    Sprite* leftBoundary; // ��ͼ��߽�
    PhysicsBody* leftBoundaryBox;
    Sprite* downBoundary_left; // ��ͼ�±߽���벿��
    PhysicsBody* downBoundary_leftBox;
    Sprite* downBoundary_right; // ��ͼ�±߽��Ұ벿��
    PhysicsBody* downBoundary_rightBox;
    Sprite* upWater; // ˮ���ϰ벿��
    PhysicsBody* upWaterBox;
    Sprite* middleWater; // ˮ���м䲿��
    PhysicsBody* middleWaterBox;
    Sprite* downWater; // ˮ���°벿��
    PhysicsBody* downWaterBox;
    Sprite* fishing; // ���㲿��
    PhysicsBody* fishingBox;
    Sprite* CropsLeft; // ũ���󲿷�
    PhysicsBody* CropsLeftBox;
    Sprite* CropsRight; // ũ���Ҳ���
    PhysicsBody* CropsRightBox;
    Sprite* home; // ����
    PhysicsBody* homeBox;
    Sprite* fence; // դ��
    PhysicsBody* fenceBox;
    Sprite* road; // ·
    PhysicsBody* roadBox;
    Sprite* ranch;// ����
    PhysicsBody* ranchBox;

    Player player; // ���
    PhysicsBody* playerBox;

    MenuItemImage* toHollowWorldButton; // ���ز˵��İ�ť
    Label* toHollowWorldWord; // ���ز˵���ť������
    MenuItemImage* backpackButton; // ��������������
    NPCManager npcManager; // ���� NPC ������ʵ��

    int place;// ����λ��,0���ڿյأ�1������ũ����2������ũ��
};

#endif // __MainMap_H__