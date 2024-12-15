#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "Item.h"

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
    /**
     * @brief ����һ�� BackpackLayer ����
     * @param backpackBgPath ��������ͼƬ��·����
     * @param maxItems �����������Ʒ������
     * @return ���ش����� BackpackLayer �����������ʧ���򷵻� nullptr��
     */
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    /**
     * @brief ��ʼ�� BackpackLayer��
     * @param backpackBgPath ��������ͼƬ��·����
     * @param maxItems �����������Ʒ������
     * @return �����Ƿ��ʼ���ɹ���
     */
    bool init(const std::string& backpackBgPath, int maxItems);

    /**
     * @brief �򱳰��������Ʒ��
     * @param itemSprite ��Ʒ��ͼ�꾫�顣
     * @return �����Ƿ�ɹ������Ʒ��
     */
    bool addItem(cocos2d::Sprite* itemSprite);

    /**
     * @brief �ӱ������Ƴ���Ʒ��
     * @param itemSprite ��Ʒ��ͼ�꾫�顣
     */
    void removeItem(cocos2d::Sprite* itemSprite);

    /**
     * @brief ���ر������档
     * @param sender �������ز����Ķ���
     */
    void hideBackpack(cocos2d::Ref* sender);

    /**
     * @brief ��ʾ��Ʒ����ϸ��Ϣ��
     * @param item Ҫ��ʾ����Ʒ����
     */
    void showItemDetails(Item* item);

    /**
     * @brief ������Ʒ����ϸ��Ϣ��
     */
    void hideItemDetails();

    // ��ȡ������Ʒ������
    const cocos2d::Vector<Sprite*>& getItemSprites() const { return itemSprites; }

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
    cocos2d::MenuItemFont* useButton; ///< ʹ����Ʒ��ť
    cocos2d::Label* useResultLabel; ///< ʹ����Ʒ�����ǩ


};

#endif // __BACKPACK_LAYER_H__