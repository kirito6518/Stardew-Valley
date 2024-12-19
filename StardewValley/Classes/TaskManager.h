#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "cocos2d.h"
#include "TaskLayer.h"
#include "NPCTask.h"

USING_NS_CC;

/**
 * @class TaskManager
 * @brief ����������࣬���������������ɡ��Ƴ�����ɡ�
 *
 * TaskManager ��һ�������࣬���ڹ�����������ɡ��Ƴ�����ɡ��������� TaskLayer ���н�����
 * ���ṩ��������Ƴ����񡢼�������Ƿ���ɵȹ��ܡ�
 */
class TaskManager : public cocos2d::Layer
{
public:
    //��ȡ TaskManager �ĵ���ʵ��
    static TaskManager* getInstance();

    //��ʾ�����б����
    void showTaskList(Node* parent);

    //���������б����
    void hideTaskList();

    //����NPC���ָ���������
    void renewTask(const std::string& npcName);

    //��ȡMainMapʵ��
    Scene* mainMap;

private:


    static TaskManager* instance; ///< ����ʵ��
    TaskLayer* taskLayer; ///< �����б�����
    Vector < NPCTask*> tasks; ///< �����б�

    /**
     * @brief ���캯������ʼ�� TaskManager��
     */
    TaskManager();

    /**
     * @brief �����������ͷ���Դ��
     */
    ~TaskManager();
};

#endif // __TASK_MANAGER_H__