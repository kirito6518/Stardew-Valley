#include "NPCRelationship.h"

// ���캯������ʼ����ϵ�ȼ�
NPCRelationship::NPCRelationship(int level) : _level(level) {}

NPCRelationship::~NPCRelationship() {}

// ���ӹ�ϵ�ȼ�
void NPCRelationship::increaseLevel() {
    if (_level < 2) _level++;
}

// ���ٹ�ϵ�ȼ�
void NPCRelationship::decreaseLevel() {
    if (_level > 0) _level--;
}

// ��ȡ��ǰ��ϵ�ȼ�
int NPCRelationship::getLevel() const {
    return _level;
}