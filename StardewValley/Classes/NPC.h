#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>
#include "NPCRelationship.h"

class NPC : public cocos2d::Sprite {
public:
    // 构造函数：初始化NPC的ID、名字和精灵图像
    NPC(int id, const std::string& name, const std::string& spritePath);
    ~NPC(); // 析构函数

    // 设置和获取NPC的对话内容
    void setDialogue(const std::vector<std::string>& dialogues);
    std::string getRandomDialogue() const;

    // 设置和获取NPC与玩家的关系等级
    void setRelationship(int level);
    int getRelationship() const;

    // 添加任务到NPC的任务列表
    void addTask(const std::string& task);
    std::vector<std::string> getTasks() const;

    // 设置和获取NPC的位置
    void setLocation(const cocos2d::Vec2& location);
    cocos2d::Vec2 getLocation() const;

    // 玩家与NPC交互时触发的函数
    void interactWithPlayer();

    // 移除对话框
    void removeDialogue();

    bool _isDialogueVisible = false; // 对话框是否可见

    void setSpecialTaskCompleted(bool completed);
    bool isSpecialTaskCompleted() const;

    //获取当前关系等级
    int getFavorability()const { return _relationship.getFavorability(); }


    int _id; // NPC的唯一ID
    std::string _name; // NPC的名字
    std::vector<std::string> _dialogues; // NPC的对话内容
    NPCRelationship _relationship; // 与玩家的关系等级
    std::vector<std::string> _tasks; // NPC发布的任务列表
    cocos2d::Vec2 _location; // NPC的位置
private:
    
};

#endif // NPC_H