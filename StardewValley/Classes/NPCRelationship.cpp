#include "NPCRelationship.h"

// 构造函数：初始化关系等级
NPCRelationship::NPCRelationship(int level) : _level(level), _specialTaskCompleted(false) {}

NPCRelationship::~NPCRelationship() {}

// 增加关系等级
void NPCRelationship::increaseLevel(int tasksCompleted)
{
    _level += tasksCompleted;
    if (_level > 100)
        _level = 100;

    if (_level >= 100 && _specialTaskCompleted)
    {
        // 建立恋人关系
        _level = 4;
    }
    else if (_level >= 90)
    {
        _level = 3; // 至交
    }
    else if (_level >= 60)
    {
        _level = 2; // 好友
    }
    else if (_level >= 30)
    {
        _level = 1; // 朋友
    }
    else
    {
        _level = 0; // 陌生人
    }
}

// 减少关系等级
void NPCRelationship::decreaseLevel() {
    if (_level > 0) _level--;
}

// 获取当前关系等级
int NPCRelationship::getLevel() const {
    return _level;
}

void NPCRelationship::setSpecialTaskCompleted(bool completed)
{
    _specialTaskCompleted = completed;
}

bool NPCRelationship::isSpecialTaskCompleted() const
{
    return _specialTaskCompleted;
}