#include "NPCTask.h"
#include "BackpackManager.h" 
#include "TaskItemManager.h"
#include "TaskItem.h"
#include "NPC.h"
#include "NPCManager.h"
#include "TaskManager.h"
#include <chrono>

// ע�͵� GameTimeManager ������
#if 0
#include "GameTimeManager.h" // ������һ��������Ϸʱ�����
#endif

float Clock::getElapsedTime()
{
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime);
    return duration.count() / 1000000.0f; // ������
}

NPCTask::NPCTask(std::string npcName)
    : npcName(npcName), cooldownTime(0.0f), cooldownEndTime(0.0f)
{
    haveTask = true;//��ʼΪ������
    needItem = nullptr;

    // �����ȡ��ƷΨһ��ʶ��
    std::random_device rd;
    std::mt19937 gen(rd());
    int minItemId = 1;
    int maxItemId = 20; // ����������Ʒ��Ψһ��ʶ����Χ����

    int getOnlyNum;
    if (npcName == "Alice") { // �곤
        getOnlyNum = gen() % 4 + 1; // 1-5
    }
    else if (npcName == "Bob") { // ���
        getOnlyNum = gen() % 5 + 6; // 6-10
    }
    else if (npcName == "Mary") { // ũ��
        getOnlyNum = gen() % 6 + 11; // 11-16
    }
    else if (npcName == "Annie") { // ����
        getOnlyNum = gen() % 4 + 17; // 17-20
    }
    else {
        getOnlyNum = 1;
    }
    
    auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
    if (item) {
        needItem = item;
        needItemName = item->getName();
    }

    // �����ȡ��Ҫ��Ʒ������1-10��
    std::uniform_int_distribution<> dis(1, 10);
    needItemCount = dis(gen);


    //�˴���Ӧÿ��npc�����Ƕ�Ӧ��List����
    if (npcName == "Alice") {
        taskList = Sprite::create("ui/Alice_task.png");
    }
    else if (npcName == "Bob") {
        taskList = Sprite::create("ui/Bob_task.png");
    }
    else if (npcName == "Mary") {
        taskList = Sprite::create("ui/Mary_task.png");
    }
    else if (npcName == "Annie") {
        taskList = Sprite::create("ui/Annie_task.png");
    }
    else {
        taskList = Sprite::create("ui/default_task.png");
    }
    taskList->retain();
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

void NPCTask::complete()
{
    if (canComplete())
    {
        haveTask = false;
        // ����������Ӻøж�
        int difficulty = needItemCount;
        int goodwillIncrease = difficulty * 2;
        NPC* npc = NPCManager::getInstance()->getNPCByName(npcName);
        if (npc)
        {
            npc->_relationship.increaseLevel(goodwillIncrease);
        }

        // ����Ƿ������������
        if (npcName == "Alice" && needItemName == "GamA" && needItemCount == 99)
        {
            if (npc)
            {
                npc->_relationship.setSpecialTaskCompleted(true);
            }
        }

        // ����������ȴʱ��
        setCooldown(3.0f);
    }
}

void NPCTask::setCooldown(float cooldownTime)
{
    this->cooldownTime = cooldownTime;
    this->cooldownEndTime = Clock::getElapsedTime() + cooldownTime; // ����Clock::getElapsedTime()��ȡ��ǰʱ��
}

bool NPCTask::isOnCooldown() const
{
    float currentTime = Clock::getElapsedTime();
    return currentTime < cooldownEndTime;
}

float NPCTask::getRemainingCooldown() const
{
    float currentTime = Clock::getElapsedTime();
    if (currentTime < cooldownEndTime)
    {
        return cooldownEndTime - currentTime;
    }
    return 0.0f;
}

void NPCTask::renewTask()
{
    if (isOnCooldown())
    {
        haveTask = false;
    }
    else if (haveTask)
    {
        // ����Ѿ���������ˢ��
        return;
    }
    else
    {
        haveTask = true;
        needItem = nullptr;

        // �����ȡ��ƷΨһ��ʶ��
        std::random_device rd;
        std::mt19937 gen(rd());
        int getOnlyNum;
        if (npcName == "Alice") { // �곤
            getOnlyNum = gen() % 5 + 1; // 1-5
        }
        else if (npcName == "Bob") { // ���
            getOnlyNum = gen() % 5 + 6; // 6-10
        }
        else if (npcName == "Mary") { // ũ��
            getOnlyNum = gen() % 6 + 11; // 11-17
        }
        else if (npcName == "Annie") { // ����
            getOnlyNum = gen() % 4 + 17; // 17-20
        }
        else {
            getOnlyNum = 1;
        }

        auto item = TaskItemManager::getInstance()->getTaskItemById(getOnlyNum);
        if (item) {
            needItem = item;
            needItemName = item->getName();
        }

        // �����ȡ��Ҫ��Ʒ������1-10��
        std::uniform_int_distribution<> dis(1, 10);
        needItemCount = dis(gen);
    }
}