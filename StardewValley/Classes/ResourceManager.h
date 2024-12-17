#pragma once
#include <string>
#include <unordered_map>

// 资源管理器类
class ResourceManager {
public:
    // 构造函数
    ResourceManager();

    // 获取资源数量
    int getResource(const std::string& resourceName) const;

    // 使用资源
    bool useResource(const std::string& resourceName, int amount);

    // 添加资源
    void addResource(const std::string& resourceName, int amount);

    // 判断是否有足够的资源
    bool hasEnoughResource(const std::string& resourceName, int amount) const;

private:
    std::unordered_map<std::string, int> resources; // 资源存储
    void initializeResources(); // 初始化资源
};