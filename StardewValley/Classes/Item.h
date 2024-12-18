#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <functional>

//��Ʒ����ö�٣���������Ʒ�����͡�
enum class ItemCategory
{
    Tool,         // ����
    Fish,         // ��
    Seed,         // ����
    Crops,        // �����Ʒ
    AnimalProduct,// �����Ʒ������ͼ�����
    Food,         // ʳ��
    Consumable,   // ����Ʒ
    Equipment,    // װ��
    Quest,        // ������Ʒ
    Mine          // ����     
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

    // ����һ���ص��������ͣ����ڴ���ʹ���߼�
    using UseItemCallback = std::function<bool()>;

    // �����Զ���� useItem �ص�����
    void setUseItemCallback(UseItemCallback callback)
    {
        useItemCallback = callback;
    }



    //����һ�� Item ����
    static Item* create(const std::string& itemImagePath, const std::string& itemName, ItemCategory category,
                           int sellingPrice=0, int buyingPrice=0,int amount=0);

    //��ʼ�� Item ����
    bool init(const std::string& itemImagePath, const std::string& itemName, ItemCategory category, 
              int sellingPrice, int buyingPrice,int amount);

    //������Ʒ��������
    void increaseCount(int amount = 1);

    //������Ʒ������
    void decreaseCount(int amount = 1);

    //ʹ����Ʒ�߼�
    bool useItem();

    //�����Ʒ
    void clearItem();
 
    // ʹ����Ʒ����������һ���ص�����������ʹ���߼�
    bool useItem(int count, UseItemCallback callback);

    //��ȡ��Ʒ������
    const std::string& getName() const { return itemName; }

    //��ȡ��Ʒ��������
    int getCount() const { return itemCount; }

    //��ȡ��Ʒ�����۸�
    int getsellingPrice() const { return sellingPrice; }

    //��ȡ��Ʒ����۸�
    int getbuyingPrice() const { return buyingPrice; }

    //��ȡ��Ʒ����
    ItemCategory getitemCategory() const { return itemCategory; }

    // ��ȡ��Ʒ��ͼ�꾫��
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    void updateCountLabel();

private:
    UseItemCallback useItemCallback; // �����Զ���� useItem �ص�����

    std::string itemName; ///< ��Ʒ������
    ItemCategory itemCategory; ///< ��Ʒ�ķ���

    int sellingPrice;//��Ʒ�����۸�
    int buyingPrice;//��Ʒ����۸�
    int itemCount; ///< ��Ʒ������
    cocos2d::Label* itemCountLabel; ///< ��Ʒ������ǩ
    cocos2d::Sprite* itemIcon; ///< ��Ʒ��ͼ�꾫��



};

#endif // __ITEM_H__