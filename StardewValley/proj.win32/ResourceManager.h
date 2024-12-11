#pragma once
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    // ���캯��
    ResourceManager();

    // ��ȡ��Դ����
    int getResource(const std::string& resourceName) const;

    // ʹ����Դ��������Դ��
    bool useResource(const std::string& resourceName, int amount);

    // �����Դ���ռ���Դ��
    void addResource(const std::string& resourceName, int amount);

    // �����Դ�Ƿ��㹻
    bool hasEnoughResource(const std::string& resourceName, int amount) const;

private:
    // ��Դ�洢��ʹ�� unordered_map �洢������Դ��
    std::unordered_map<std::string, int> resources;

    // ��ʼ����Դ
    void initializeResources();
};