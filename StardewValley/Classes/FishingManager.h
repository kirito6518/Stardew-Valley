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

	// ���캯�������������ϵͳ
	FishingManager();

	// �������
	void Fishing();

	// ���������������
	void OpenBox();

};

#endif // __FISHING_MANAGER_H__