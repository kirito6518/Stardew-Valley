#ifndef NPCTASK_H
#define NPCTASK_H

#include "cocos2d.h"
#include "ShopItemManager.h"

USING_NS_CC;

class NPCTask : public Node {
public:
    NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount);

    // ��ȡ NPC ����
    std::string getNPCName() const { return npcName; }


    // ��ȡ������Ʒ����
    std::string getRequiredItem() const { return needItemName; }

    // ��ȡ������Ʒ����
    int getRequiredItemCount() const { return requiredItemCount; }

    // ��������Ƿ�������
    bool canComplete();

    // �������
    void complete();

    // ����������ȴʱ��
    void setCooldown(float cooldownTime);

    // ��������Ƿ�����ȴ��
    bool isOnCooldown() const;

    // ��ȡ������ȴʣ��ʱ��
    float getRemainingCooldown() const;

    //��������״̬
    void renewTask();

    //��ȡ�������Ƿ����
    bool getHaveTask() {return haveTask;}
private:
    
    ShopItem* needItem;           //������Ʒ
    bool haveTask;                //�ж��Ƿ�������
    std::string npcName;          // NPC ����
    std::string needItemName;     // ������Ʒ����
    int requiredItemCount;        // ������Ʒ����
    float cooldownTime;           // ������ȴʱ��
    float cooldownEndTime;        // ������ȴ����ʱ��
};

#endif // NPCTASK_H