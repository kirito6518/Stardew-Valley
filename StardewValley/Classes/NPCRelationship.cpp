#include "NPCRelationship.h"

// 构造函数：初始化关系等级
NPCRelationship::NPCRelationship(int level) : _level(level), _specialTaskCompleted(false) {}

NPCRelationship::~NPCRelationship() {}

// 增加关系等级
void NPCRelationship::increaseLevel(int tasksCompleted) {
    if (_level < 4) {
        if (tasksCompleted >= 6 && _level < 3) {
            _level = 3; // 至交
        }
        else if (tasksCompleted >= 3 && _level < 2) {
            _level = 2; // 好友
        }
        else if (tasksCompleted >= 1 && _level < 1) {
            _level = 1; // 朋友
        }
    }
    if (_level == 3 && _specialTaskCompleted) {
        _level = 4; // 恋人
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

// 设置特殊任务完成状态
void NPCRelationship::setSpecialTaskCompleted(bool completed) {
    _specialTaskCompleted = completed;
}

// 获取特殊任务完成状态
bool NPCRelationship::isSpecialTaskCompleted() const {
    return _specialTaskCompleted;
}