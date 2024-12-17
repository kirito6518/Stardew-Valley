#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "Item.h"
#include <unordered_map>
#include <unordered_set>

class ItemManager
{
public:
    // ��ȡ����ʵ��
    static ItemManager* getInstance();

    // ���һ�� Item ʵ��
    void addItem(const std::string& itemName, Item* item);

    // �Ƴ�һ�� Item ʵ��
    void removeItem(const std::string& itemName);

    // ��ȡһ�� Item ʵ��
    Item* getItem(const std::string& itemName);

    //���ItemManager
    void destroyInstance();


    // ������� Item ʵ��
    void clearAllItems();

    // ����������Ʒ�б�
    void setSellableItems(const std::unordered_set<std::string>& sellableItemNames);

private:
    static ItemManager* instance; // ����ʵ��
    std::unordered_map<std::string, Item*> items; // ȫ����Ʒʵ��ӳ��
};

#endif // __ITEM_MANAGER_H__
