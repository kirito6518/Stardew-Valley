#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include "BackpackLayer.h"
#include "Item.h"

USING_NS_CC;

/**
 * @class BackpackManager
 * @brief �����������࣬�������������ʾ����Ʒ����ӡ��Ƴ���
 *
 * BackpackManager ��һ�������࣬���ڹ���������ʾ����Ʒ����ӡ��Ƴ����������� BackpackLayer ���н�����
 * ���ṩ�����Ʒ���Ƴ���Ʒ����鱳���Ƿ������ȹ��ܡ�
 */
class BackpackManager : public cocos2d::Layer
{
public:
    /**
     * @brief ��ȡ BackpackManager �ĵ���ʵ����
     * @return ���� BackpackManager �ĵ���ʵ����
     */
    static BackpackManager* getInstance();

    /**
     * @brief ��ʾ�������档
     * @param parent ��������Ҫ��ӵ��ĸ��ڵ㡣
     */
    void showBackpack(cocos2d::Node* parent);

    /**
     * @brief ���ر������档
     */
    void hideBackpack();

    /**
     * @brief �򱳰��������Ʒ��
     * @param itemImagePath ��Ʒͼ���·����
     * @param itemName ��Ʒ�����ơ�
     * @param count �����Ʒ��������Ĭ��Ϊ1
     * @param category ��Ʒ�ķ��ࡣ
     * @return �����Ƿ�ɹ������Ʒ��
     */
    bool addItem(const std::string& itemImagePath, const std::string& itemName, ItemCategory category ,int count=1);
    
    /**
     * @brief �ӱ������Ƴ���Ʒ��
     * @param item Ҫ�Ƴ�����Ʒ����
     */
    void removeItem(Item* item);

    /**
     * @brief ��鱳���Ƿ�������
     * @return ���ر����Ƿ�������
     */
    bool isFull() const;

    // ��ȡ������Ʒ������
    const cocos2d::Vector<Item*>& getItems() { return items; }

    //������Ʒ���ֻ��ʵ��
    Item* getItemByName(const std::string& itemName);

    BackpackLayer* backpackLayer; ///< ���������
    Scene* mainMap;
private:
    /**
     * @brief ���캯������ʼ�� BackpackManager��
     */
    BackpackManager();

    /**
     * @brief �����������ͷ���Դ��
     */
    ~BackpackManager();
    cocos2d::Vector<Item*> items; ///< �����е���Ʒ�б�
    int maxItems; ///< �����������Ʒ����
    int currentItems; ///< ��ǰ�����е���Ʒ����
};

#endif // __BACKPACK_MANAGER_H__