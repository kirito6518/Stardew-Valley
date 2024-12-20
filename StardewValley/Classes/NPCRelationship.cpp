#include "NPCRelationship.h"

// ���캯������ʼ����ϵ�ȼ�
NPCRelationship::NPCRelationship(int level) : _level(level), _specialTaskCompleted(false) {}

NPCRelationship::~NPCRelationship() {}

// ���ӹ�ϵ�ȼ�
void NPCRelationship::increaseLevel(int tasksCompleted)
{
    _level += tasksCompleted;
    if (_level > 100)
        _level = 100;

    if (_level >= 100 && _specialTaskCompleted)
    {
        // �������˹�ϵ
        _level = 4;
    }
    else if (_level >= 90)
    {
        _level = 3; // ����
    }
    else if (_level >= 60)
    {
        _level = 2; // ����
    }
    else if (_level >= 30)
    {
        _level = 1; // ����
    }
    else
    {
        _level = 0; // İ����
    }
}

// ���ٹ�ϵ�ȼ�
void NPCRelationship::decreaseLevel() {
    if (_level > 0) _level--;
}

// ��ȡ��ǰ��ϵ�ȼ�
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