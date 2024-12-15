#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

/**
 * @enum ItemCategory
 * @brief ��Ʒ����ö�٣���������Ʒ�����͡�
 */
enum class ItemCategory
{
    Consumable, ///< ����Ʒ
    Equipment,  ///< װ��
    Quest       ///< ������Ʒ
};

/**
 * @class Item
 * @brief ��Ʒ�࣬��ʾ�����еĵ�����Ʒ��
 *
 * Item ���ʾ�����еĵ�����Ʒ����������Ʒ�����ơ����ࡢ������ͼ�����Ϣ��
 * ���ṩ�����ӡ�������Ʒ�����ķ������Լ�ʹ����Ʒ�Ĺ��ܡ�
 */
class Item : public cocos2d::Node
{
public:
    /**
     * @brief ����һ�� Item ����
     * @param itemImagePath ��Ʒͼ���·����
     * @param itemName ��Ʒ�����ơ�
     * @param category ��Ʒ�ķ��ࡣ
     * @return ���ش����� Item �����������ʧ���򷵻� nullptr��
     */
    static Item* create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief ��ʼ�� Item ����
     * @param itemImagePath ��Ʒͼ���·����
     * @param itemName ��Ʒ�����ơ�
     * @param category ��Ʒ�ķ��ࡣ
     * @return �����Ƿ��ʼ���ɹ���
     */
    bool init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief ������Ʒ��������
     * @param amount ���ӵ�������Ĭ��Ϊ 1��
     */
    void increaseCount(int amount = 1);

    /**
     * @brief ������Ʒ��������
     * @param amount ���ٵ�������Ĭ��Ϊ 1��
     */
    void decreaseCount(int amount = 1);

    /**
     * @brief ʹ����Ʒ��
     * @return ����ʹ����Ʒ�Ƿ�ɹ���
     */
    bool useItem(bool success=false);

    /**
     * @brief ��ȡ��Ʒ�����ơ�
     * @return ������Ʒ�����ơ�
     */
    const std::string& getName() const { return itemName; }

    /**
     * @brief ��ȡ��Ʒ��������
     * @return ������Ʒ��������
     */
    int getCount() const { return itemCount; }

    /**
     * @brief ��ȡ��Ʒ��ͼ�꾫�顣
     * @return ������Ʒ��ͼ�꾫�顣
     */
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    void update updateCountLabel

private:
    std::string itemName; ///< ��Ʒ������
    ItemCategory itemCategory; ///< ��Ʒ�ķ���
    int itemCount; ///< ��Ʒ������
    cocos2d::Label* itemCountLabel; ///< ��Ʒ������ǩ
    cocos2d::Sprite* itemIcon; ///< ��Ʒ��ͼ�꾫��
};

#endif // __ITEM_H__