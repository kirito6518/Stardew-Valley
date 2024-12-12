#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
USING_NS_CC;
class Player : public cocos2d::Sprite
{
public:

    // ���캯��
    Player();

    // ��ʼ������
    virtual bool init();

    // ʵ�� CREATE_FUNC ��
    CREATE_FUNC(Player);

    // ���̰����¼�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �����ͷ��¼�����
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

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

    // ��������λ��
    void updatePlayerPosition(float dt);

    // ÿ֡����
    void update(float dt);
};

#endif // __Player_H__