#pragma once
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    ResourceManager();

    int getResource(const std::string& resourceName) const;
    bool useResource(const std::string& resourceName, int amount);
    void addResource(const std::string& resourceName, int amount);
    bool hasEnoughResource(const std::string& resourceName, int amount) const;

private:
    std::unordered_map<std::string, int> resources;
    void initializeResources();
};