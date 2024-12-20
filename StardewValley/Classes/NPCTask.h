#ifndef NPCTASK_H
#define NPCTASK_H

#include "cocos2d.h"
#include "TaskItemManager.h"
#include "TaskItem.h"

USING_NS_CC;

class NPCTask : public Node {
public:
    NPCTask(std::string npcName);

    // ��ȡ NPC ����
    std::string getNPCName() const { return npcName; }

    // ��ȡ������Ʒ����
    std::string getRequiredItem() const { return needItemName; }

    // ��ȡ������Ʒ����
    int getRequiredItemCount() const { return needItemCount; }

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

    //��ȡ����������Ʒʵ��
    TaskItem* getNeedItem() { return needItem; }

    //��ȡlist����
    Sprite* getIcon() { return taskList; }
private:
    
    TaskItem* needItem;           //������Ʒ
    Sprite* taskList;             //�ý�ɫ�������б���
    bool haveTask;                //�ж��Ƿ�������
    std::string npcName;          // NPC ����
    std::string needItemName;     // ������Ʒ����
    int needItemCount;        // ������Ʒ����
    float cooldownTime;           // ������ȴʱ��
    float cooldownEndTime;        // ������ȴ����ʱ��
};

#endif // NPCTASK_H