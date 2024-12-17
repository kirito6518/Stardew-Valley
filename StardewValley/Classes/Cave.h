#ifndef CAVE_H
#define CAVE_H

#include "cocos2d.h"
#include "chipmunk.h"
#include "Player.h"

USING_NS_CC;

//洞穴场景
class Cave : public cocos2d::Scene {
public:

	static cocos2d::Scene* createScene();

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

	Sprite* caveSprite; // 地图

	Player player; // 玩家
	PhysicsBody* playerBox;

	Vector<Sprite*> Mines; // 矿物
	Vector<PhysicsBody*> MinesBox;

};

#endif // CAVE_H