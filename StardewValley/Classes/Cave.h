#ifndef CAVE_H
#define CAVE_H

#include "cocos2d.h"
#include "chipmunk.h"
#include "Player.h"
#include "Item.h"
#include "BackpackManager.h"
#include "ItemManager.h"
#include <vector>
#include <cstring>

USING_NS_CC;

//��Ѩ����
class Cave : public Scene {
public:

	static Scene* createScene();

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

	// ���һ������
	void AddMine(Sprite* mine, PhysicsBody* minesBox, Vec2 position);

	// ������ɿ���
	void CreateMine();

	Sprite* caveSprite; // ��ͼ

	Sprite* caveUpBoundary; // ��ͼ�ϱ߽�
	PhysicsBody* caveUpBoundaryBox;
	Sprite* caveRightBoundary; // ��ͼ�ұ߽�
	PhysicsBody* caveRightBoundaryBox;
	Sprite* caveLeftBoundary; // ��ͼ��߽�
	PhysicsBody* caveLeftBoundaryBox;
	Sprite* caveDownBoundary; // ��ͼ�±߽�
	PhysicsBody* caveDownBoundaryBox;

	Player player; // ���
	PhysicsBody* playerBox;
	Sprite* black; // �ڰ��� 

	Sprite* ladder; //��ȥ������
	PhysicsBody* ladderBox;

	std::vector<Sprite*> mines; // ������ʮ��
	std::vector<PhysicsBody*> minesBox;
	int numOfMines; // ������Ŀ

	int place; // λ�ã�0�յأ�7����
};

#endif // CAVE_H