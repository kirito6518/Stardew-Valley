#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "Item.h"
#include "MainMap.h"


USING_NS_CC;

/**
 * @class BackpackLayer
 * @brief �������࣬������ʾ�͹������е���Ʒ��
 *
 * BackpackLayer ��һ�� Cocos2d-x �� Layer��������ʾ�������档�������˱����ı�������Ʒͼ�ꡢ��Ʒ������
 * ��Ʒ���Ƶ���Ϣ���û�����ͨ���ò��뱳�����н��������������Ʒ���Ƴ���Ʒ����ʾ��Ʒ����ȡ�
 */
class BackpackLayer : public cocos2d::Layer
{
public:


    //����һ�� BackpackLayer ����
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    //��ʼ�� BackpackLayer
    bool init(const std::string& backpackBgPath, int maxItems);

    //�򱳰��������Ʒ
    bool addItem(cocos2d::Sprite* itemSprite);

    //�ӱ������Ƴ���Ʒ
    void removeItem(cocos2d::Sprite* itemSprite);

   //���ر�������
    void hideBackpack(cocos2d::Ref* sender);

    // ��ȡ������Ʒ������
    const cocos2d::Vector<Sprite*>& getItemSprites() const { return itemSprites; }

    //���ʹ�ð�ť�Ļص�����
    void onUseButtonClicked(Ref* sender);

    //����ݻٰ�ť�Ļص�����
    void onDestroyButtonClicked(Ref* sender);

    //����¼�����������Ʒ�Ľ���
    void setupCombinedMouseListener();



    MenuItemImage* hideButton;//�������ذ�ť

    cocos2d::Sprite* backpackBgSprite; ///< ������������

    int gridWidth; ///< �������ӵĿ�ȣ�������
    int gridHeight; ///< �������ӵĸ߶ȣ�������
    int gridSpacing; ///< ��������֮��ļ��
    float gridStartX; ///< �������ӵ���ʼ X ����
    float gridStartY; ///< �������ӵ���ʼ Y ����

    int maxItems; ///< �����������Ʒ����
    int currentItems; ///< ��ǰ�����е���Ʒ����

private:

    cocos2d::Vector<cocos2d::Sprite*> itemSprites; ///< �����е���Ʒͼ���б�
    cocos2d::Label* itemNameLabel; ///< ��Ʒ���Ʊ�ǩ
    cocos2d::Label* itemCountLabel; ///< ��Ʒ������ǩ

    cocos2d::MenuItemImage* useButton; ///< ʹ����Ʒ��ť
    cocos2d::Label* useResultLabel; ///< ʹ����Ʒ�����ǩ

    cocos2d::MenuItemImage* destroyButton; ///< �ݻ���Ʒ��ť
    cocos2d::Label* destroyResultLabel;///< �ݻ���Ʒ�����ǩ

    cocos2d::Sprite* itemDetaUI;//��ʾ��Ʒ����Ľ���
    cocos2d::Label* itemDataLabel;//��ʾ��Ʒ���飨���ƣ��ı�ǩ


};

#endif // __BACKPACK_LAYER_H__