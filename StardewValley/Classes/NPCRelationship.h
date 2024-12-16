#pragma once
#ifndef NPCRELATIONSHIP_H
#define NPCRELATIONSHIP_H

// 关系类：管理NPC与玩家的关系
class NPCRelationship {
public:
    // 构造函数：初始化关系等级
    NPCRelationship(int level);
    ~NPCRelationship(); // 析构函数

    // 增加关系等级
    void increaseLevel();
    // 减少关系等级
    void decreaseLevel();
    // 获取当前关系等级
    int getLevel() const;

private:
    int _level; // 关系等级（0:陌生人, 1:朋友, 2:浪漫）
};

#endif // NPCRELATIONSHIP_H