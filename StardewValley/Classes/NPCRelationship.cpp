#include "NPCRelationship.h"

// ���캯������ʼ����ϵ�ȼ�
NPCRelationship::NPCRelationship(int level) : _level(level), _specialTaskCompleted(false) {}

NPCRelationship::~NPCRelationship() {}

// ���ӹ�ϵ�ȼ�
void NPCRelationship::increaseLevel(int tasksCompleted) {
    if (_level < 4) {
        if (tasksCompleted >= 6 && _level < 3) {
            _level = 3; // ����
        }
        else if (tasksCompleted >= 3 && _level < 2) {
            _level = 2; // ����
        }
        else if (tasksCompleted >= 1 && _level < 1) {
            _level = 1; // ����
        }
    }
    if (_level == 3 && _specialTaskCompleted) {
        _level = 4; // ����
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

// ���������������״̬
void NPCRelationship::setSpecialTaskCompleted(bool completed) {
    _specialTaskCompleted = completed;
}

// ��ȡ�����������״̬
bool NPCRelationship::isSpecialTaskCompleted() const {
    return _specialTaskCompleted;
}