#include "ResourceManager.h"

// 构造函数，初始化资源
ResourceManager::ResourceManager() {
    initializeResources();
}

// 初始化资源
void ResourceManager::initializeResources() {
    resources["Water"] = 100;
    resources["Seeds"] = 10;
    resources["Fertilizer"] = 10;
    resources["Feed"] = 100;
}

// 获取资源数量
int ResourceManager::getResource(const std::string& resourceName) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

// 使用资源
bool ResourceManager::useResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end() && it->second >= amount) {
        it->second -= amount;
        return true;
    }
    return false;
}

// 添加资源
void ResourceManager::addResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        it->second += amount;
    }
    else {
        resources[resourceName] = amount;
    }
}

// 判断是否有足够的资源
bool ResourceManager::hasEnoughResource(const std::string& resourceName, int amount) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second >= amount;
    }
    return false;
}