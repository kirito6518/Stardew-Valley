#include "NPCTask.h"
#include "BackpackManager.h" 
#include "TaskItemManager.h"
#include "TaskItem.h"


// ע�͵� GameTimeManager ������
#if 0
#include "GameTimeManager.h" // ������һ��������Ϸʱ�����
#endif

NPCTask::NPCTask(std::string npcName)
    : npcName(npcName), cooldownTime(0.0f), cooldownEndTime(0.0f)
{
    haveTask = true;//��ʼΪ������
    needItem = nullptr;

    int getOnlyNum = 1;//�˴�Ӧͨ�������ȡ��ƷΨһ��ʶ������ʱ��д��
    auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
    if (item) {
        needItem = item;
        needItemName = item->getName();
    }
    
    //�˴�дһ���������,������������Ʒ����,�˴���ʱ��д��
    needItemCount = 1;

    //�˴���Ӧÿ��npc�����Ƕ�Ӧ��List����
    if (npcName == "Alice") {
        taskList = Sprite::create("ui/Alice_task.png");
        taskList->retain();
    }
    else if (npcName == "Bob") {

    }
    else {//�˴�Ϊ��׳�Լ���
        taskList = Sprite::create("ui/Alice_task.png");
        taskList->retain();
    }
}

//����Ƿ��ܹ��ύ
bool NPCTask::canComplete()
{

    // ��鱳�����Ƿ����㹻��������Ʒ
    auto item = BackpackManager::getInstance()->getItemByName(needItemName);
    if (item == nullptr) {
        return false;
    }

    if (item->getCount() < needItemCount) {
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
        item->decreaseCount(needItemCount);

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
    //���ǣ�����haveItemΪ false
    //��������haveItemΪture ,��������ƷΨһ��ʶ���������������Ʒ������
    //����
    haveTask = true;//�����Ƿ���ȴ�жϴ˴��Ƿ���Ҫ����
    needItem = nullptr;

    int getOnlyNum = 1;//�˴�Ӧͨ�������ȡ��ƷΨһ��ʶ������ʱ��д��
    auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
    if (item) {
        needItem = item;
        needItemName = item->getName();
    }

    //�˴�дһ���������,������������Ʒ����,�˴���ʱ��д��
    needItemCount = 1;
}