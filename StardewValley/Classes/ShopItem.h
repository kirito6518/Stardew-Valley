#ifndef __SHOP_ITEM_H__
#define __SHOP_ITEM_H__

#include "cocos2d.h"


/**
 * @class ShopItem
 * @brief �̵���Ʒ�࣬��ʾ�̵��еĵ�����Ʒ��
 *
 * ShopItem ���ʾ�̵��еĵ�����Ʒ����������Ʒ�����ơ��۸�ͼ�����Ϣ��
 * ���ṩ�˹�����Ʒ�Ĺ��ܡ�
 */
class ShopItem : public cocos2d::Node
{
public:

    // ����һ�� ShopItem ����
    static ShopItem* create(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice);

    // ��ʼ�� ShopItem ����
    bool init(const std::string& itemImagePath, const std::string& itemName, int sellingPrice, int buyingPrice);

    // ��ȡ��Ʒ������
    const std::string& getName() const { return itemName; }

    // ��ȡ��Ʒ�Ĺ���۸�
    int getBuyingPrice() const { return buyingPrice; }

    // ��ȡ��Ʒ��ͼ�꾫��
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    

private:

    std::string itemName; ///< ��Ʒ������
    cocos2d::Sprite* itemIcon; ///< ��Ʒ��ͼ�꾫��
    cocos2d::Label* itemCountLabel; ///< ��Ʒ������ǩ�����̵��У�������Ʒ������Ϊ1
    int sellingPrice;///< ��Ʒ�������۸�
    int buyingPrice;///< ��Ʒ������۸�
};

#endif // __SHOP_ITEM_H__