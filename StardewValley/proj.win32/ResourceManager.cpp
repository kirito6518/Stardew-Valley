#include "ResourceManager.h"

// ���캯��
ResourceManager::ResourceManager() {
    initializeResources();
}

// ��ʼ����Դ
void ResourceManager::initializeResources() {
    // ��ʼ��ˮ��Դ�����Ӻͷ���
    resources["Water"] = 100;
    resources["Seeds"] = 10;
    resources["Fertilizer"] = 10;
}

// ��ȡ��Դ����
int ResourceManager::getResource(const std::string& resourceName) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second;
    }
    return 0; // �����Դ�����ڣ����� 0
}

// ʹ����Դ��������Դ��
bool ResourceManager::useResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end() && it->second >= amount) {
        it->second -= amount;
        return true;
    }
    return false; // ��Դ����
}

// �����Դ���ռ���Դ��
void ResourceManager::addResource(const std::string& resourceName, int amount) {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        it->second += amount;
    }
    else {
        resources[resourceName] = amount; // �����Դ�����ڣ�������Դ
    }
}

// �����Դ�Ƿ��㹻
bool ResourceManager::hasEnoughResource(const std::string& resourceName, int amount) const {
    auto it = resources.find(resourceName);
    if (it != resources.end()) {
        return it->second >= amount;
    }
    return false; // ��Դ������
}