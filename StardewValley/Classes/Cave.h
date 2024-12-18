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

//洞穴场景
class Cave : public Scene {
public:

	static Scene* createScene();

	// 初始化
	virtual bool init();

	// 实现create函数
	CREATE_FUNC(Cave);

	// 每帧更新
	void updatePlayerPosition(float dt);

	// 每帧更新
	void updateCameraPosition(float dt);

	// 碰撞开始监听器
	bool onContactBegin(PhysicsContact& contact);

	// 添加一个矿物
	void AddMine(Sprite* mine, PhysicsBody* minesBox, Vec2 position);

	// 随机生成矿物
	void CreateMine();

	Sprite* caveSprite; // 地图

	Sprite* caveUpBoundary; // 地图上边界
	PhysicsBody* caveUpBoundaryBox;
	Sprite* caveRightBoundary; // 地图右边界
	PhysicsBody* caveRightBoundaryBox;
	Sprite* caveLeftBoundary; // 地图左边界
	PhysicsBody* caveLeftBoundaryBox;
	Sprite* caveDownBoundary; // 地图下边界
	PhysicsBody* caveDownBoundaryBox;

	Player player; // 玩家
	PhysicsBody* playerBox;
	Sprite* black; // 黑暗矿洞 

	Sprite* ladder; //回去的梯子
	PhysicsBody* ladderBox;

	std::vector<Sprite*> mines; // 矿物，最多十株
	std::vector<PhysicsBody*> minesBox;
	int numOfMines; // 矿物数目

	int place; // 位置，0空地，7矿物
};

#endif // CAVE_H