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

//洞穴场景
class Cave : public Scene {
public:

	static Scene* createScene();

	// 初始化
	virtual bool init();

	// 实现create函数
	CREATE_FUNC(Cave);

	// 每帧更新
	void update(float dt);

	// 碰撞开始监听器
	bool onContactBegin(PhysicsContact& contact);

	// 添加一个矿物
	void AddMine(Sprite* mine, PhysicsBody* minesBox, Vec2 position);

	// 随机生成矿物
	void CreateMine();

	// 打开选项
	void OpenLayer();

	// 隐藏选项
	void HideLayer(Ref* sender);

	// 在屏幕下方显示可以带走的宝石
	void Gem(Vec2 targetCameraPosition);
	
	Scene* mainMap;

	Sprite* caveSprite; // 地图
	Sprite* gemSprite1; // 可以被带走的宝石
	Sprite* gemSprite2; // 可以被带走的宝石
	Sprite* gemSprite3; // 可以被带走的宝石
	Sprite* gemSprite4; // 可以被带走的宝石
	Sprite* gemSprite5; // 可以被带走的宝石

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

	ChooseMineLayer* chooseMineLayer; // 选择是否带出的Layer

	int gem; // 可以带出的矿物，分别是1-5，0就是未选出来

	int place; // 位置，0空地，7矿物
};

#endif // CAVE_H