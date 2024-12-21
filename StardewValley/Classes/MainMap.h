#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"
#include "Player.h"
#include "BackpackLayer.h"
#include "chipmunk.h"
#include "SeasonManager.h"
#include "NPCManager.h"
#include "FarmManager.h"
#include "Cave.h"
#include "FishingManager.h"
#include "EventManager.h"

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

    //��ձ�����Ʒ
    void clearBackpack();

    //���س�ʼ����
    void getInitBackpack();

    //�����̵�
    void toShop();

    //�����̵����
    void hideShop(Ref* sender);

    //���س�ʼ�̵�
    void getInitShop();

    //�������ť�Ļص�����
    void onTaskButtonClicked(Ref* sender);

    //�����������
    void hideTask(Ref* sender);

    // ʵ��create����
    CREATE_FUNC(MainMap);

    // ÿ֡����
    void update(float dt);

    // ��ײ��ʼ������
    bool onContactBegin(PhysicsContact& contact);

    // �ɳ�
    void updateFarm(float dt);

    //��������
    void addDay(float dt);

    // ������Ʒ��MainMap��ʹ���߼�,0���ڿյأ�1������ũ����2������ũ����3���㣬4·��5������6�̵�
    void SetUseItemInMainMap();

    // �ص�mainmapʱ����
    void BackFromCave();

    // ������
    void OpenRanch();

    // ��������
    void HideRanch(Ref* sender);


    SeasonManager seasonManager; // ���� SeasonManager ʵ��
    EventManager eventManager;
    Label* seasonLabel; // ���� ������ʾ�� Label
    Label* dayLabel; // ���� ������ʾ�� Label
    Label* eventLabel; // ���� ������ʾ�� Label
    FishingManager* fishingManager; // �������������
    Scene* caveScene; // ��Ѩ����

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
    Sprite* cropsLeft; // ũ���󲿷�
    PhysicsBody* cropsLeftBox;
    Sprite* cropsRight; // ũ���Ҳ���
    PhysicsBody* cropsRightBox;
    Sprite* shop; // ����
    PhysicsBody* shopBox;
    PhysicsBody* fenceBox;
    Sprite* road; // ·
    Sprite* fence; // դ��
    PhysicsBody* roadBox;
    Sprite* ranch;// ����
    PhysicsBody* ranchBox;

    Player player; // ���
    PhysicsBody* playerBox;

    MenuItemImage* toHollowWorldButton; // ���ز˵��İ�ť
    Label* toHollowWorldWord; // ���ز˵���ť������
    MenuItemImage* backpackButton; // ���������İ�ť
    MenuItemImage* taskButton;//�����������İ�ť
    FarmManager farmManager; // ���� FarmManager ʵ��

    int place; // ����λ��,0���ڿյأ�1������ũ����2������ũ����3���㣬4·��5������6�̵�

    int audioId0;//0�ű�������
    int audioId1;//1�ű�������
    int audioId2;//2�ű�������
};

#endif // __MainMap_H__