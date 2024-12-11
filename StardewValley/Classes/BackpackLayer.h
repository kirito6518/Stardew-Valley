
#include "cocos2d.h"

USING_NS_CC;

class BackpackLayer : public cocos2d::Layer
{
public:
    // ���������㣬���뱳������ͼƬ·������Ʒ����
    static BackpackLayer* create(const std::string& backpackBgPath, int maxItems);

    // ��ʼ������
    virtual bool init(const std::string& backpackBgPath, int maxItems);

    // �����Ʒ������
    bool addItem(const std::string& itemImagePath);


private:
    // ������������
    cocos2d::Sprite* backpackBgSprite;

    // ��Ʒ����
    cocos2d::Vector<cocos2d::Sprite*> itemSprites;

    // ������Ʒ����
    int maxItems;

    // ��ǰ�����е���Ʒ����
    int currentItems;
};