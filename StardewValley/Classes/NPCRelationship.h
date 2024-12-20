#pragma once
#ifndef NPCRELATIONSHIP_H
#define NPCRELATIONSHIP_H

// ��ϵ�ࣺ����NPC����ҵĹ�ϵ
class NPCRelationship {
public:
    // ���캯������ʼ����ϵ�ȼ�
    NPCRelationship(int level = 0);
    ~NPCRelationship(); // ��������

    // ���ӹ�ϵ�ȼ�
    void increaseLevel(int tasksCompleted);
    // ���ٹ�ϵ�ȼ�
    void decreaseLevel();
    // ��ȡ��ǰ��ϵ�ȼ�
    int getLevel() const;

    void setSpecialTaskCompleted(bool completed);
    bool isSpecialTaskCompleted() const;

private:
    int _level; // ��ϵ�ȼ���0:İ����, 1:����, 2:����, 3:����, 4:���ˣ�
    bool _specialTaskCompleted; // �Ƿ������������
};

#endif // NPCRELATIONSHIP_H