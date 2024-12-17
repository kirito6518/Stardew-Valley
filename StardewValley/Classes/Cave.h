#ifndef CAVE_H
#define CAVE_H

#include "cocos2d.h"
#include "chipmunk.h"
#include "Player.h"

USING_NS_CC;

//��Ѩ����
class Cave : public cocos2d::Scene {
public:

	static cocos2d::Scene* createScene();

	// ��ʼ��
	virtual bool init();

	// ʵ��create����
	CREATE_FUNC(Cave);

	// ÿ֡����
	void updatePlayerPosition(float dt);

	// ÿ֡����
	void updateCameraPosition(float dt);

	// ��ײ��ʼ������
	bool onContactBegin(PhysicsContact& contact);

	Sprite* caveSprite; // ��ͼ

	Player player; // ���
	PhysicsBody* playerBox;

	Vector<Sprite*> Mines; // ����
	Vector<PhysicsBody*> MinesBox;

};

#endif // CAVE_H