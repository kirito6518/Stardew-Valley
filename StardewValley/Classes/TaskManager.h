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

    //��������б�
    bool addTaskList(NPCTask* task);

    //������������״̬
    void renewTask();

    //��ȡMainMapʵ��
    Scene* mainMap;

    TaskLayer* taskLayer; ///< �����б�����

private:


    static TaskManager* instance; ///< ����ʵ��
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