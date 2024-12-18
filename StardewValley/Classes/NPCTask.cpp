#include "NPCTask.h"
#include "BackpackManager.h" 

// ע�͵� GameTimeManager ������
#if 0
#include "GameTimeManager.h" // ������һ��������Ϸʱ�����
#endif

NPCTask::NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount)
    : npcName(npcName), description(description), requiredItem(requiredItem), requiredItemCount(requiredItemCount), completed(false), cooldownTime(0.0f), cooldownEndTime(0.0f)
{
}

bool NPCTask::canComplete() const
{
    // ��鱳�����Ƿ����㹻��������Ʒ
    auto item = BackpackManager::getInstance()->getItemByName(requiredItem);
    return item != nullptr && item->getCount() >= requiredItemCount;
}

void NPCTask::complete()
{
    if (canComplete())
    {
        // �ӱ������Ƴ�������Ʒ
        //BackpackManager::getInstance()->removeItem(requiredItem, requiredItemCount);

        // �������Ϊ�����
        completed = true;

        // ����������ȴʱ��
        setCooldown(60.0f); // ������ȴʱ��Ϊ 60 ��
    }
}

void NPCTask::setCooldown(float cooldownTime)
{
    this->cooldownTime = cooldownTime;

    // ģ�⵱ǰʱ��
    float currentTime = 0.0f; // ���赱ǰʱ��Ϊ 0
    this->cooldownEndTime = currentTime + cooldownTime;
}

bool NPCTask::isOnCooldown() const
{
    // ģ�⵱ǰʱ��
    float currentTime = 0.0f; // ���赱ǰʱ��Ϊ 0
    return currentTime < cooldownEndTime;
}

float NPCTask::getRemainingCooldown() const
{
    // ģ�⵱ǰʱ��
    float currentTime = 0.0f; // ���赱ǰʱ��Ϊ 0
    if (currentTime < cooldownEndTime)
    {
        return cooldownEndTime - currentTime;
    }
    return 0.0f;
}