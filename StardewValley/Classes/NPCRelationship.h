#pragma once
#ifndef NPCRELATIONSHIP_H
#define NPCRELATIONSHIP_H

// ��ϵ�ࣺ����NPC����ҵĹ�ϵ
class NPCRelationship {
public:
    // ���캯������ʼ����ϵ�ȼ�
    NPCRelationship(int level);
    ~NPCRelationship(); // ��������

    // ���ӹ�ϵ�ȼ�
    void increaseLevel();
    // ���ٹ�ϵ�ȼ�
    void decreaseLevel();
    // ��ȡ��ǰ��ϵ�ȼ�
    int getLevel() const;

private:
    int _level; // ��ϵ�ȼ���0:İ����, 1:����, 2:������
};

#endif // NPCRELATIONSHIP_H