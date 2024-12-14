#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "cocos2d.h"
#include "Item.h"

/**
 * @class ItemManager
 * @brief ��Ʒ�������࣬���𴴽��͹�����Ʒ����
 *
 * ItemManager ��һ�������࣬���ڴ����͹�����Ʒ�������ṩ�˴�����Ʒ����ȡ��Ʒ���ͷ���Ʒ�ȹ��ܡ�
 */
class ItemManager
{
public:
    /**
     * @brief ��ȡ ItemManager �ĵ���ʵ����
     * @return ���� ItemManager �ĵ���ʵ����
     */
    static ItemManager* getInstance();

    /**
     * @brief ����һ����Ʒ����
     * @param itemImagePath ��Ʒͼ���·����
     * @param itemName ��Ʒ�����ơ�
     * @param category ��Ʒ�ķ��ࡣ
     * @return ���ش�������Ʒ�����������ʧ���򷵻� nullptr��
     */
    Item* createItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category);

    /**
     * @brief �������ƻ�ȡ��Ʒ����
     * @param itemName ��Ʒ�����ơ�
     * @return ���ض�Ӧ����Ʒ�������δ�ҵ��򷵻� nullptr��
     */
    Item* getItemByName(const std::string& itemName);

    /**
     * @brief �ͷ���Ʒ����
     * @param item Ҫ�ͷŵ���Ʒ����
     */
    void releaseItem(Item* item);

private:
    /**
     * @brief ���캯������ʼ�� ItemManager��
     */
    ItemManager();

    /**
     * @brief �����������ͷ�������Ʒ����
     */
    ~ItemManager();

    cocos2d::Vector<Item*> items; ///< ��Ʒ�����б�
};

#endif // __ITEM_MANAGER_H__