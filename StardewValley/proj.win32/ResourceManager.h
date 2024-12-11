#pragma once
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    // 构造函数
    ResourceManager();

    // 获取资源数量
    int getResource(const std::string& resourceName) const;

    // 使用资源（消耗资源）
    bool useResource(const std::string& resourceName, int amount);

    // 添加资源（收集资源）
    void addResource(const std::string& resourceName, int amount);

    // 检查资源是否足够
    bool hasEnoughResource(const std::string& resourceName, int amount) const;

private:
    // 资源存储（使用 unordered_map 存储多种资源）
    std::unordered_map<std::string, int> resources;

    // 初始化资源
    void initializeResources();
};