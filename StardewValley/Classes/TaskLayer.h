#ifndef __TASK_LAYER_H__
#define __TASK_LAYER_H__

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

/**
 * @class TaskLayer
 * @brief 任务列表层类，负责显示和管理任务列表中的任务。
 *
 * TaskLayer 是一个 Cocos2d-x 的 Layer，用于显示任务列表界面。它包含了 NPC 名称、任务详情、
 * 任务所需物品及数量等信息。用户可以通过该层与任务列表进行交互，例如查看任务详情、完成任务等。
 */
class TaskLayer : public cocos2d::Layer
{
public:
    // 创建一个 TaskLayer 对象
    static TaskLayer* create();

    // 初始化 TaskLayer
    bool init();

    //添加任务列表到layer中
    bool addList(Sprite* taskList);

    // 向任务列表中添加任务
    void addTask(const std::string& npcName, const std::string& taskDescription);

    // 移除任务
    void removeTask(const std::string& npcName);

    //关闭任务界面
    void closeTaskUI(Ref* sender);

    // 获取所有任务的向量
    const Vector<NPCTask*>& getTasks() const { return tasks; }


    // 设置鼠标事件监听器
    void setupMouseListener();

private:
    cocos2d::Vector<Sprite*> lists;//所有任务列表精灵
    Vector <NPCTask*> tasks;//所有任务
    cocos2d::Sprite* taskUI; ///< 任务界面
    cocos2d::Sprite* taskList;//具体任务列表
    cocos2d::MenuItemImage* closeButton; ///< 关闭任务详情按钮

    cocos2d::Label* nowGoodwill;//当前好感度
    cocos2d::Label* rewardGoodwill;//奖励好感度
    cocos2d::Sprite* needItem;//需求物品
    cocos2d::Label* needItemCount;//需求物品数量

};

#endif // __TASK_LAYER_H__