#ifndef TASKLAYER_H
#define TASKLAYER_H

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

class TaskLayer : public Layer {
public:
    static TaskLayer* create();
    bool init() override;

    // ������������
    void addTask(NPCTask* task);

    // �Ƴ�����
    void removeTask(NPCTask* task);

    // ��������UI
    void updateTaskUI(NPCTask* task);

private:
    void setupMouseListener();
    void onTaskClicked(NPCTask* task);
    void completeTask(Ref* sender);

    Vector<NPCTask*> taskList;
    Sprite* taskBgSprite;
    Label* taskLabel;
    MenuItemImage* completeButton;
};

#endif // TASKLAYER_H