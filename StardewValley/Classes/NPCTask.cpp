#include "NPCTask.h"

// ���캯������ʼ�������ID�����֡����������ͺͽ���
NPCTask::NPCTask(int id, const std::string& name, const std::string& description, const std::string& type, int reward)
    : _id(id), _name(name), _description(description), _type(type), _reward(reward), _status("δ����") {
}

NPCTask::~NPCTask() {}

// ���������״̬
void NPCTask::setStatus(const std::string& status) {
    _status = status;
}

// ��ȡ�����״̬
std::string NPCTask::getStatus() const {
    return _status;
}

// ��ȡ�����ID
int NPCTask::getId() const {
    return _id;
}

// ��ȡ���������
std::string NPCTask::getName() const {
    return _name;
}

// ��ȡ���������
std::string NPCTask::getDescription() const {
    return _description;
}

// ��ȡ���������
std::string NPCTask::getType() const {
    return _type;
}

// ��ȡ����Ľ���
int NPCTask::getReward() const {
    return _reward;
}