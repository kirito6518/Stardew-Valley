#ifndef __FISHING_MANAGER_H__
#define __FISHING_MANAGER_H__

#include "cocos2d.h"
#include "Item.h"
#include "BackpackManager.h"
#include "ItemManager.h"
#include <cstdlib>

USING_NS_CC;

class FishingManager : public Node
{
public:

	// 构造函数，启动随机数系统
	FishingManager();

	// 随机给予
	void Fishing();

	// 打开箱子随机给予金币
	void OpenBox();

};

#endif // __FISHING_MANAGER_H__