#include "NPCTask.h"

// 构造函数：初始化任务的ID、名字、描述、类型和奖励
NPCTask::NPCTask(int id, const std::string& name, const std::string& description, const std::string& type, int reward)
    : _id(id), _name(name), _description(description), _type(type), _reward(reward), _status("未接受") {
}

NPCTask::~NPCTask() {}

// 设置任务的状态
void NPCTask::setStatus(const std::string& status) {
    _status = status;
}

// 获取任务的状态
std::string NPCTask::getStatus() const {
    return _status;
}

// 获取任务的ID
int NPCTask::getId() const {
    return _id;
}

// 获取任务的名字
std::string NPCTask::getName() const {
    return _name;
}

// 获取任务的描述
std::string NPCTask::getDescription() const {
    return _description;
}

// 获取任务的类型
std::string NPCTask::getType() const {
    return _type;
}

// 获取任务的奖励
int NPCTask::getReward() const {
    return _reward;
}