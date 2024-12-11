#ifndef __MainMap_H__
#define __MainMap_H__

#include "cocos2d.h"
#include "BackpackManager.h"

class MainMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    // ��ʼ��
    virtual bool init();

    // ǰ�����˵�����
    void toMenu(Ref*);

    // ���̰����¼�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �����ͷ��¼�����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ������ť�Ļص�����
    void onBackpackButtonClicked(Ref* sender);

    // ʵ��create����
    CREATE_FUNC(MainMap);

private:
    cocos2d::Sprite* mapSprite;
    cocos2d::Sprite* playerSprite; // ���Ǿ���
    cocos2d::Animation* walkAnimations[6]; // ������������߶���
    cocos2d::Animation* idleAnimations[6]; // ��������Ĵ�������
    cocos2d::Vec2 targetPosition; // Ŀ��λ��
    bool isMoving; // �Ƿ������ƶ�

    // ����״̬
    bool isWPressed, isAPressed, isSPressed, isDPressed;

    // ���һ�����ߵķ�������
    int lastDirectionIndex;

    // ����������������߶���
    void createWalkAnimations();

    // ������������Ĵ�������
    void createIdleAnimations();

    // ���ݷ���ѡ�񶯻�
    int getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to);

    // �ƶ����ǵ�Ŀ��λ��
    void movePlayerTo(const cocos2d::Vec2& position);

    // ��������λ��
    void updatePlayerPosition(float dt);

    // ÿ֡����
    void update(float dt);
};

#endif // __MainMap_H__