#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include "BackpackLayer.h"
#include "Item.h"

class BackpackManager
{
public:
    static BackpackManager* getInstance();

    void showBackpack(cocos2d::Node* parent);
    void hideBackpack();

    // �����Ʒ������
    bool addItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // �Ƴ���Ʒ
    void removeItem(Item* item);

    // ��鱳���Ƿ�����
    bool isFull() const;

private:
    BackpackManager();
    ~BackpackManager();

    cocos2d::Layer* backpackLayer; // ������
    int maxItems;                  // ������Ʒ����
    int currentItems;              // ��ǰ�����е���Ʒ����

    // ��Ʒ����
    cocos2d::Vector<Item*> items;
};

#endif // __BACKPACK_MANAGER_H__