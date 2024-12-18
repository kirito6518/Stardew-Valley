#ifndef __SHOP_LAYER_H__
#define __SHOP_LAYER_H__

#include "cocos2d.h"
#include "ShopItem.h" 


USING_NS_CC;

/**
 * @class ShopLayer
 * @brief �̵���࣬������ʾ�͹����̵��е���Ʒ��
 *
 * ShopLayer ��һ�� Cocos2d-x �� Layer��������ʾ�̵���档���������̵�ı�������Ʒͼ�ꡢ��Ʒ������
 * ��Ʒ���Ƶ���Ϣ���û�����ͨ���ò����̵���н��������繺����Ʒ����ʾ��Ʒ����ȡ�
 */
class ShopLayer : public cocos2d::Layer
{
public:

    // ����һ�� ShopLayer ����
    static ShopLayer* create(const std::string& shopBgPath, int maxItems);

    // ��ʼ�� ShopLayer
    bool init(const std::string& shopBgPath, int maxItems);

    // ���̵��������Ʒ
    bool addItem(cocos2d::Sprite* itemSprite);

    // ���̵����Ƴ���Ʒ
    void removeItem(cocos2d::Sprite* itemSprite);

    // �����̵����
    void hideShop(Ref* sender);

    // ��ȡ������Ʒ������
    const cocos2d::Vector<Sprite*>& getItemSprites() const { return itemSprites; }

    // �������ť�Ļص�����
    void onBuyButtonClicked(Ref* sender);

    // ����¼�����������Ʒ�Ľ���
    void setupCombinedMouseListener();

    MenuItemImage* closeButton; // �̵�رհ�ť

    cocos2d::Sprite* shopBgSprite; ///< �̵걳������
    cocos2d::Sprite* shopSprite;//�̵�����ͼƬ

    int gridWidth; ///< �̵���ӵĿ�ȣ�������
    int gridHeight; ///< �̵���ӵĸ߶ȣ�������
    int gridSpacing; ///< �̵����֮��ļ��
    float gridStartX; ///< �̵���ӵ���ʼ X ����
    float gridStartY; ///< �̵���ӵ���ʼ Y ����

    int maxItems; ///< �̵�������Ʒ����
    int currentItems; ///< ��ǰ�̵��е���Ʒ����

private:

    cocos2d::Vector<cocos2d::Sprite*> itemSprites; ///< �̵��е���Ʒͼ���б�
    cocos2d::Label* itemNameLabel; ///< ��Ʒ���Ʊ�ǩ
    cocos2d::Label* itemPriceLabel; ///< ��Ʒ�۸��ǩ

    cocos2d::MenuItemImage* buyButton; ///< ������Ʒ��ť
    cocos2d::Label* buyResultLabel; ///< ������Ʒ�����ǩ

    cocos2d::Sprite* itemDetailUI; // ��ʾ��Ʒ����Ľ���
    cocos2d::Label* itemDetailLabel; // ��ʾ��Ʒ���飨���ƣ��ı�ǩ
};

#endif // __SHOP_LAYER_H__