#include "BackpackManager.h"

USING_NS_CC;

BackpackManager* BackpackManager::getInstance()
{
    static BackpackManager instance; // ��̬ʵ����ȷ��ȫ��Ψһ
    return &instance;
}

/*�˴��ݶ�*/
BackpackManager::BackpackManager()
{
    // ��ʼ��������
    backpackLayer = BackpackLayer::create("backpack.png", 40); // ��������ͼƬΪ "backpack.png"������Ϊ 40 ����Ʒ
    backpackLayer->retain(); // ���������㣬��ֹ���ͷ�

    // ��ʼ������״̬
    maxItems = 40;
    currentItems = 0;
}
/*�˴��ݶ�*/

BackpackManager::~BackpackManager()
{
    backpackLayer->release(); // �ͷű�����
}

void BackpackManager::showBackpack(Node* parent)
{
    if (backpackLayer->getParent() == nullptr)
    {

        parent->addChild(backpackLayer,2); // ����������ӵ���ǰ����
    }
}

void BackpackManager::hideBackpack()
{
    backpackLayer->removeFromParentAndCleanup(false); // �Ӹ��ڵ��Ƴ�������������
}

bool BackpackManager::addItem(const std::string& itemImagePath)
{
    if (isFull())
    {
        log("Backpack is full! Cannot add more items.");
        return false;
    }

    // ���ñ�����������Ʒ����
    static_cast<BackpackLayer*>(backpackLayer)->addItem(itemImagePath);

    // ���µ�ǰ��Ʒ����
    currentItems++;
    return true;
}

bool BackpackManager::isFull() const
{
    return currentItems >= maxItems;
}