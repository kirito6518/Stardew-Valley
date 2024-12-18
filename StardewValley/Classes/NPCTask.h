#ifndef NPCTASK_H
#define NPCTASK_H

#include "cocos2d.h"

USING_NS_CC;

class NPCTask : public Node {
public:
    NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount);

    // ��ȡ NPC ����
    std::string getNPCName() const { return npcName; }

    // ��ȡ��������
    std::string getDescription() const { return description; }

    // ��ȡ������Ʒ����
    std::string getRequiredItem() const { return requiredItem; }

    // ��ȡ������Ʒ����
    int getRequiredItemCount() const { return requiredItemCount; }

    // ��������Ƿ�������
    bool canComplete() const;

    // �������
    void complete();

    // ����������ȴʱ��
    void setCooldown(float cooldownTime);

    // ��������Ƿ�����ȴ��
    bool isOnCooldown() const;

    // ��ȡ������ȴʣ��ʱ��
    float getRemainingCooldown() const;

private:
    std::string npcName;          // NPC ����
    std::string description;      // ��������
    std::string requiredItem;     // ������Ʒ����
    int requiredItemCount;        // ������Ʒ����
    bool completed;               // �����Ƿ������
    float cooldownTime;           // ������ȴʱ��
    float cooldownEndTime;        // ������ȴ����ʱ��
};

#endif // NPCTASK_H