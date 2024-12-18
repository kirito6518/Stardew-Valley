#include "FishingManager.h"

USING_NS_CC;

// 构造函数，启动随机数系统
FishingManager::FishingManager() {
	srand((unsigned)(time(0)));
}

// 随机给予一条鱼
void FishingManager::Fishing() {
	auto num = rand() % 100 + 1;
	if (num >= 1 && num <= 65) {
		// CCLOG("Nothing!");
	}
	else if (num >= 66 && num <= 75) { // 钓到神秘箱子
		Item* initItem = ItemManager::getInstance()->getItem("Box");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 76 && num <= 80) { // 钓到鱼A
		Item* initItem = ItemManager::getInstance()->getItem("FishA");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 81 && num <= 85) {// 钓到鱼B
		Item* initItem = ItemManager::getInstance()->getItem("FishB");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 86 && num <= 90) {// 钓到鱼C
		Item* initItem = ItemManager::getInstance()->getItem("FishC");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 91 && num <= 95) {// 钓到鱼D
		Item* initItem = ItemManager::getInstance()->getItem("FishD");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 96 && num <= 100) {// 钓到鱼E
		Item* initItem = ItemManager::getInstance()->getItem("FishE");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
}

// 打开箱子随机给予金币
void FishingManager::OpenBox() {
	auto num = rand() % 20 + 1;
	Item* initItem = ItemManager::getInstance()->getItem("Coin");
	BackpackManager::getInstance()->addItem(initItem, num);
}