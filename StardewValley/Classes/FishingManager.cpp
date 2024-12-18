#include "FishingManager.h"

USING_NS_CC;

// ���캯�������������ϵͳ
FishingManager::FishingManager() {
	srand((unsigned)(time(0)));
}

// �������һ����
void FishingManager::Fishing() {
	auto num = rand() % 100 + 1;
	if (num >= 1 && num <= 65) {
		// CCLOG("Nothing!");
	}
	else if (num >= 66 && num <= 75) { // ������������
		Item* initItem = ItemManager::getInstance()->getItem("Box");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 76 && num <= 80) { // ������A
		Item* initItem = ItemManager::getInstance()->getItem("FishA");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 81 && num <= 85) {// ������B
		Item* initItem = ItemManager::getInstance()->getItem("FishB");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 86 && num <= 90) {// ������C
		Item* initItem = ItemManager::getInstance()->getItem("FishC");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 91 && num <= 95) {// ������D
		Item* initItem = ItemManager::getInstance()->getItem("FishD");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
	else if (num >= 96 && num <= 100) {// ������E
		Item* initItem = ItemManager::getInstance()->getItem("FishE");
		BackpackManager::getInstance()->addItem(initItem, 1);
	}
}

// ���������������
void FishingManager::OpenBox() {
	auto num = rand() % 20 + 1;
	Item* initItem = ItemManager::getInstance()->getItem("Coin");
	BackpackManager::getInstance()->addItem(initItem, num);
}