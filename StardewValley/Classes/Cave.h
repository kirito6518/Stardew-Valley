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
#include "BringMine.h"

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

	// ��ѡ��
	void OpenLayer();

	// ����ѡ��
	void HideLayer(Ref* sender);

	// ����Ļ�·���ʾ���Դ��ߵı�ʯ
	void Gem(Vec2 targetCameraPosition);
	
	Scene* mainMap;

	Sprite* caveSprite; // ��ͼ
	Sprite* gemSprite1; // ���Ա����ߵı�ʯ
	Sprite* gemSprite2; // ���Ա����ߵı�ʯ
	Sprite* gemSprite3; // ���Ա����ߵı�ʯ
	Sprite* gemSprite4; // ���Ա����ߵı�ʯ
	Sprite* gemSprite5; // ���Ա����ߵı�ʯ

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

	ChooseMineLayer* chooseMineLayer; // ѡ���Ƿ������Layer

	int gem; // ���Դ����Ŀ���ֱ���1-5��0����δѡ����

	int place; // λ�ã�0�յأ�7����
};

#endif // CAVE_H