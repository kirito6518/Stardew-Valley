#include "NPCTask.h"
#include "BackpackManager.h" 
#include "ShopItemManager.h"


// ע�͵� GameTimeManager ������
#if 0
#include "GameTimeManager.h" // ������һ��������Ϸʱ�����
#endif

NPCTask::NPCTask(const std::string& npcName, const std::string& description, const std::string& requiredItem, int requiredItemCount)
    : npcName(npcName), description(description), needItemName(needItemName), requiredItemCount(requiredItemCount), cooldownTime(0.0f), cooldownEndTime(0.0f)
{

    //�˴�дһ�����������������ƷΨһ��ʶ��������������Ʒ���������

}

//����Ƿ��ܹ��ύ
bool NPCTask::canComplete()
{
    std::string getItem= needItemName;
    getItem.pop_back();
    // ��鱳�����Ƿ����㹻��������Ʒ
    auto item = BackpackManager::getInstance()->getItemByName(getItem);
    if (item == nullptr) {
        return false;
    }

    if (item->getCount() < requiredItemCount) {
        return false;
    }

    return true;
}

//�������
void NPCTask::complete()
{


    if (canComplete())
    {
        std::string getItem = needItemName;
        getItem.pop_back();
        // ��ȡ�����е�������Ʒ
        auto item = BackpackManager::getInstance()->getItemByName(getItem);
        // �ӱ����м���������Ʒ
        item->decreaseCount(requiredItemCount);

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

//��������״̬
void NPCTask::renewTask()
{
    //���ж��Ƿ���������ȴ��
    //���ǣ�����ShopItem* needItem��������Ʒ��Ϊ ��1��
    //����������ƷΨһ��ʶ���������������Ʒ������
}