#pragma once
#include <string>
#include <unordered_map>

// ��Դ��������
class ResourceManager {
public:
    // ���캯��
    ResourceManager();

    // ��ȡ��Դ����
    int getResource(const std::string& resourceName) const;

    // ʹ����Դ
    bool useResource(const std::string& resourceName, int amount);

    // �����Դ
    void addResource(const std::string& resourceName, int amount);

    // �ж��Ƿ����㹻����Դ
    bool hasEnoughResource(const std::string& resourceName, int amount) const;

private:
    std::unordered_map<std::string, int> resources; // ��Դ�洢
    void initializeResources(); // ��ʼ����Դ
};