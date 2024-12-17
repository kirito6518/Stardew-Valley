#ifndef __SHOP_MANAGER_H__
#define __SHOP_MANAGER_H__

#include "cocos2d.h"
#include "ShopLayer.h"
#include "Item.h"

USING_NS_CC;

/**
 * @class ShopManager
 * @brief �̵�������࣬��������̵����ʾ����Ʒ����ӡ��Ƴ���
 *
 * ShopManager ��һ�������࣬���ڹ����̵����ʾ����Ʒ����ӡ��Ƴ����������� ShopLayer ���н�����
 * ���ṩ�����Ʒ���Ƴ���Ʒ������̵��Ƿ������ȹ��ܡ�
 */
class ShopManager : public cocos2d::Layer
{
public:
    /**
     * @brief ��ȡ ShopManager �ĵ���ʵ����
     * @return ���� ShopManager �ĵ���ʵ����
     */
    static ShopManager* getInstance();

    /**
     * @brief ��ʾ�̵���档
     * @param parent �̵����Ҫ��ӵ��ĸ��ڵ㡣
     */
    void showShop(cocos2d::Node* parent);

    /**
     * @brief �����̵���档
     */
    void hideShop();

    /**
     * @brief ���̵��������Ʒ��
     * @param item Ҫ��ӵ���Ʒ����
     * @param amount �����Ʒ��������Ĭ��Ϊ1
     * @return �����Ƿ�ɹ������Ʒ��
     */
    bool addItem(Item* item, int amount = 1);

    /**
     * @brief ���̵����Ƴ���Ʒ��
     * @param item Ҫ�Ƴ�����Ʒ����
     */
    void removeItem(Item* item);

    /**
     * @brief ����̵��Ƿ�������
     * @return �����̵��Ƿ�������
     */
    bool isFull() const;

    /**
     * @brief ������Ʒ��
     * @param item Ҫ�������Ʒ����
     * @return �����Ƿ�ɹ�������Ʒ��
     */
    bool buyItem(Item* item);

    // ��ȡ������Ʒ������
    const cocos2d::Vector<Item*>& getItems() { return items; }

    // ������Ʒ���ֻ��ʵ��
    Item* getItemByName(const std::string& itemName);

    ShopLayer* shopLayer; ///< �̵�����

    Scene* mainMap;

private:

    static ShopManager* instance; // ����ʵ��

    /**
     * @brief ���캯������ʼ�� ShopManager��
     */
    ShopManager();

    /**
     * @brief �����������ͷ���Դ��
     */
    ~ShopManager();

    cocos2d::Vector<Item*> items; ///< �̵��е���Ʒ�б�
    int maxItems; ///< �̵�������Ʒ����
    int currentItems; ///< ��ǰ�̵��е���Ʒ����
};

#endif // __SHOP_MANAGER_H__