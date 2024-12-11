#include "ResourceManager.h"

// 构造函数
ResourceManager::ResourceManager() {
    initializeResources();
}

// 初始化资源
void ResourceManager::initializeResources() {
    // 初始化水资源、种子和肥料
    resources["Water"] = 100;
    resources["Seeds"] = 10;
    resources["Fertilizer"] = 10;
}

// 获取资源数量
int ResourceManager::getResource(const std::string& resourceName) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second;
    }
    return 0; // 如果资源不存在，返回 0
}

// 使用资源（消耗资源）
bool ResourceManager::useResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end() && it->second >= amount) {
        it->second -= amount;
        return true;
    }
    return false; // 资源不足
}

// 添加资源（收集资源）
void ResourceManager::addResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        it->second += amount;
    }
    else {
        resources[resourceName] = amount; // 如果资源不存在，新增资源
    }
}

// 检查资源是否足够
bool ResourceManager::hasEnoughResource(const std::string& resourceName, int amount) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second >= amount;
    }
    return false; // 资源不存在
}