#ifndef __TASK_LAYER_H__
#define __TASK_LAYER_H__

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

/**
 * @class TaskLayer
 * @brief �����б���࣬������ʾ�͹��������б��е�����
 *
 * TaskLayer ��һ�� Cocos2d-x �� Layer��������ʾ�����б���档�������� NPC ���ơ��������顢
 * ����������Ʒ����������Ϣ���û�����ͨ���ò��������б���н���������鿴�������顢�������ȡ�
 */
class TaskLayer : public cocos2d::Layer
{
public:
    // ����һ�� TaskLayer ����
    static TaskLayer* create();

    // ��ʼ�� TaskLayer
    bool init();

    // �������б����������
    void addTask(const std::string& npcName, const std::string& taskDescription);

    // �Ƴ�����
    void removeTask(const std::string& npcName);

    // ��ʾ��������
    void showTaskDetails(const std::string& npcName);

    // ������������
    void hideTaskDetails();

    // ��ȡ�������������
    const Vector<NPCTask*>& getTasks() const { return tasks; }


    // ��������¼�������
    void setupMouseListener();

private:

    Vector<NPCTask*> tasks;
    cocos2d::Label* taskDetailsLabel; ///< ���������ǩ
    cocos2d::Sprite* taskDetailsUI; ///< �����������
    cocos2d::MenuItemImage* closeButton; ///< �ر��������鰴ť

    cocos2d::Label* nowGoodwill;//��ǰ�øж�
    cocos2d::Label* rewardGoodwill;//�����øж�
    cocos2d::Sprite* needItem;//������Ʒ

};

#endif // __TASK_LAYER_H__