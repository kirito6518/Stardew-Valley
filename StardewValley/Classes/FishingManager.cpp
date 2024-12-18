#include "FishingManager.h"

USING_NS_CC;

// ���캯�������������ϵͳ
FishingManager::FishingManager() {
	srand((unsigned)(time(0)));
}

// ������������Ʒ
void FishingManager::Fishing() {
	Item* initItem = nullptr;
	auto num = rand() % 100 + 1;
	if (num >= 1 && num <= 65) {
		// CCLOG("Nothing!");
	}
	else if (num >= 66 && num <= 75) { // ������������
		initItem = ItemManager::getInstance()->getItem("Box");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 76 && num <= 80) { // ������A
		initItem = ItemManager::getInstance()->getItem("FishA");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 81 && num <= 85) {// ������B
		initItem = ItemManager::getInstance()->getItem("FishB");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 86 && num <= 90) {// ������C
		initItem = ItemManager::getInstance()->getItem("FishC");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 91 && num <= 95) {// ������D
		initItem = ItemManager::getInstance()->getItem("FishD");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 96 && num <= 100) {// ������E
		initItem = ItemManager::getInstance()->getItem("FishE");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
}

// ���������������
void FishingManager::OpenBox() {
	auto num = rand() % 5 + 1;
	Item* initItem = nullptr;
	initItem = ItemManager::getInstance()->getItem("Coin");
	BackpackManager::getInstance()->addItem(initItem, num);
}