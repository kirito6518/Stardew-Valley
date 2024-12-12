#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "Item.h" // ȷ������ Item.h

USING_NS_CC;

class BackpackLayer : public cocos2d::Layer
{
public:
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    virtual bool init(const std::string& backpackBgPath, int maxItems);

    bool addItem(Sprite* itemSprite);
    void removeItem(Sprite* itemSprite);

    void hideBackpack(Ref* sender);

    // ��ʾ��Ʒ��ϸ��Ϣ
    void showItemDetails(Item* item);

    // ������Ʒ��ϸ��Ϣ
    void hideItemDetails();

private:
    cocos2d::Sprite* backpackBgSprite;
    cocos2d::Vector<cocos2d::Sprite*> itemSprites;
    int maxItems;
    int currentItems;

    cocos2d::Label* itemNameLabel;
    cocos2d::Label* itemCountLabel;
    cocos2d::MenuItem* useButton;
    cocos2d::Label* useResultLabel;
};

#endif // __BACKPACK_LAYER_H__