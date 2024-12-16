#include "NPCRelationship.h"

// 构造函数：初始化关系等级
NPCRelationship::NPCRelationship(int level) : _level(level) {}

NPCRelationship::~NPCRelationship() {}

// 增加关系等级
void NPCRelationship::increaseLevel() {
    if (_level < 2) _level++;
}

// 减少关系等级
void NPCRelationship::decreaseLevel() {
    if (_level > 0) _level--;
}

// 获取当前关系等级
int NPCRelationship::getLevel() const {
    return _level;
}