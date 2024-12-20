#include "TaskItem.h"
#include "TaskItemManager.h"

// ����������Ʒ
TaskItem* TaskItem::create(const std::string& itemImagePath, const std::string& itemName, int ItemId)
{
    auto taskItem = new (std::nothrow) TaskItem(); // ����һ���µ� TaskItem ����
    if (taskItem && taskItem->init(itemImagePath, itemName, ItemId)) // ��ʼ����Ʒ
    {
        taskItem->autorelease(); // �Զ��ͷŶ���
        return taskItem; // ���ش�������Ʒ
    }
    CC_SAFE_DELETE(taskItem); // �����ʼ��ʧ�ܣ�ɾ������
    return nullptr; // ���ؿ�ָ��
}

// ��ʼ��������Ʒ
bool TaskItem::init(const std::string& itemImagePath, const std::string& itemName, int ItemId)
{
    if (!Node::init()) // ���û���ĳ�ʼ������
    {
        return false; // ��������ʼ��ʧ�ܣ����� false
    }

    // ��ʼ����Ʒ����
    this->itemName = itemName; // ������Ʒ����

    //������Ʒ��ʶ��
    ItemId = ItemId;

    // ������Ʒͼ��
    itemIcon = cocos2d::Sprite::create(itemImagePath);
    if (!itemIcon) // ���ͼ���Ƿ񴴽��ɹ�
    {
        CCLOG("Failed to load item image: %s", itemImagePath.c_str());
        return false; // ���ͼ�괴��ʧ�ܣ����� false
    }
    itemIcon->retain(); // ���� itemIcon

    // ����Ʒʵ��ע�ᵽ TaskItemManager
    TaskItemManager::getInstance()->addTaskItem(this);

    return true; // ��ʼ���ɹ������� true
}