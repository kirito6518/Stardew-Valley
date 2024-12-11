#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    initializeResources();
}

void ResourceManager::initializeResources() {
    resources["Water"] = 100;
    resources["Seeds"] = 10;
    resources["Fertilizer"] = 10;
    resources["Feed"] = 100;
}

int ResourceManager::getResource(const std::string& resourceName) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

bool ResourceManager::useResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end() && it->second >= amount) {
        it->second -= amount;
        return true;
    }
    return false;
}

void ResourceManager::addResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        it->second += amount;
    }
    else {
        resources[resourceName] = amount;
    }
}

bool ResourceManager::hasEnoughResource(const std::string& resourceName, int amount) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second >= amount;
    }
    return false;
}