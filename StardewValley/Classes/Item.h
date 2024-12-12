#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

// ��Ʒ����ö��
enum class ItemCategory
{
    FISHING,   // ������
    PLANTING,  // ��ֲ��
    BREEDING,  // ��ֳ��
    TOOL,      // ����
    OTHER      // ����
};

class Item : public cocos2d::Node
{
public:
    // ������Ʒ������ͼ��·�������ơ�����
    static Item* create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // ��ʼ������
    virtual bool init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    // ��ȡ��Ʒ����
    const std::string& getName() const { return itemName; }

    // ��ȡ��Ʒͼ��
    Sprite* getIcon() const { return itemIcon; }

    // ��ȡ��Ʒ����
    int getCount() const { return itemCount; }

    // ��ȡ��Ʒ����
    ItemCategory getCategory() const { return itemCategory; }

    // ������Ʒ����
    void increaseCount(int amount = 1);

    // ������Ʒ����
    void decreaseCount(int amount = 1);

    // ʹ����Ʒ������ʹ�ý��
    bool useItem();

    // �����Ʒͼ��ʱ�Ļص�
    void onItemClicked(Ref* sender);

private:
    std::string itemName;       // ��Ʒ����
    Sprite* itemIcon;           // ��Ʒͼ��
    int itemCount;              // ��Ʒ����
    ItemCategory itemCategory;  // ��Ʒ����
};

#endif // __ITEM_H__