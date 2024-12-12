#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include "BackpackLayer.h"


//���� BackpackManager ������, �������������������ں��߼�
class BackpackManager
{
public:
    // ��ȡ����ʵ��
    static BackpackManager* getInstance();

    // ��ʾ������
    void showBackpack(cocos2d::Node* parent);

    // ���ر�����
    void hideBackpack();

    // �����Ʒ������
    bool addItem(const std::string& itemImagePath);

    // ��鱳���Ƿ�����
    bool isFull() const;

private:
    BackpackManager();  // ���캯��˽�л�
    ~BackpackManager(); // ��������

    cocos2d::Layer* backpackLayer; // ������
    int maxItems;                  // ������Ʒ����
    int currentItems;              // ��ǰ�����е���Ʒ����
};

#endif // __BACKPACK_MANAGER_H__