#include "ResourceManager.h"

// ���캯������ʼ����Դ
ResourceManager::ResourceManager() {
    initializeResources();
}

// ��ʼ����Դ
void ResourceManager::initializeResources() {
    resources["Water"] = 100;
    resources["Seeds"] = 10;
    resources["Fertilizer"] = 10;
    resources["Feed"] = 100;
}

// ��ȡ��Դ����
int ResourceManager::getResource(const std::string& resourceName) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

// ʹ����Դ
bool ResourceManager::useResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end() && it->second >= amount) {
        it->second -= amount;
        return true;
    }
    return false;
}

// �����Դ
void ResourceManager::addResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        it->second += amount;
    }
    else {
        resources[resourceName] = amount;
    }
}

// �ж��Ƿ����㹻����Դ
bool ResourceManager::hasEnoughResource(const std::string& resourceName, int amount) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second >= amount;
    }
    return false;
}