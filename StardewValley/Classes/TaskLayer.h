#ifndef TASKLAYER_H
#define TASKLAYER_H

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

class TaskLayer : public Layer {
public:
    static TaskLayer* create();
    bool init() override;

    // 添加任务到任务层
    void addTask(NPCTask* task);

    // 移除任务
    void removeTask(NPCTask* task);

    // 更新任务UI
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