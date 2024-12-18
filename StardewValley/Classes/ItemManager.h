#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "Item.h"
USING_NS_CC;

class ItemManager
{
public:
    // ��ȡ����ʵ��
    static ItemManager* getInstance();

    // ���һ�� Item ʵ��
    void addItem(const std::string& itemName, Item* item);


    // ��ȡһ�� Item ʵ��
    Item* getItem(const std::string& itemName);

    //���ItemManager
    void destroyInstance();


    // ������� Item ʵ��
    void clearAllItems();


private:

    static ItemManager* instance; // ����ʵ��
    cocos2d::Vector<Item*> items; ///< ��Ʒ�б�
};

#endif // __ITEM_MANAGER_H__
