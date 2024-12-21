#pragma once
#ifndef __TASK_ITEM_H__
#define __TASK_ITEM_H__

#include "cocos2d.h"

/**
 * @class TaskItem
 * @brief ������Ʒ�࣬��ʾ�����еĵ�����Ʒ��
 *
 * TaskItem ���ʾ�����еĵ�����Ʒ����������Ʒ�����ơ�������ͼ�����Ϣ��
 * ���ṩ��������Ʒ�Ļ���������
 */
class TaskItem : public cocos2d::Node
{
public:
    // ����һ�� TaskItem ����
    static TaskItem* create(const std::string& itemImagePath, const std::string& itemName, int ItemId);

    // ��ʼ�� TaskItem ����
    bool init(const std::string& itemImagePath, const std::string& itemName, int ItemId);

    // ��ȡ��Ʒ������
    const std::string& getName() const { return itemName; }

    // ��ȡ��Ʒ��ͼ�꾫��
    cocos2d::Sprite* getIcon() const { return itemIcon; }

    // ��ȡ��Ʒ��Ψһ��ʶ��
    int getTaskId() const { return taskId; }

    int getRarity() const { return rarity; }

    void setRarity(int r) { rarity = r; }

private:

    int taskId; ///< ��Ʒ��Ψһ��ʶ��
    std::string itemName; ///< ��Ʒ������
    cocos2d::Sprite* itemIcon; ///< ��Ʒ��ͼ�꾫��
    int rarity; // ��Ʒ��ϡ�ж�
};

#endif // __TASK_ITEM_H__