#ifndef NPCTASK_H
#define NPCTASK_H

#include <string>

// 任务类：表示一个任务
class NPCTask {
public:
    // 构造函数：初始化任务的ID、名字、描述、类型和奖励
    NPCTask(int id, const std::string& name, const std::string& description, const std::string& type, int reward);
    ~NPCTask(); // 析构函数

    // 设置和获取任务的状态
    void setStatus(const std::string& status);
    std::string getStatus() const;

    // 获取任务的ID、名字、描述、类型和奖励
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getType() const;
    int getReward() const;

private:
    int _id; // 任务的唯一ID
    std::string _name; // 任务的名字
    std::string _description; // 任务的描述
    std::string _type; // 任务的类型（如收集、修复等）
    int _reward; // 任务的奖励
    std::string _status; // 任务的状态（未接受、进行中、已完成）
};

#endif // NPCTASK_H
