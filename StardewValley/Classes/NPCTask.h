#ifndef NPCTASK_H
#define NPCTASK_H

#include <string>

// �����ࣺ��ʾһ������
class NPCTask {
public:
    // ���캯������ʼ�������ID�����֡����������ͺͽ���
    NPCTask(int id, const std::string& name, const std::string& description, const std::string& type, int reward);
    ~NPCTask(); // ��������

    // ���úͻ�ȡ�����״̬
    void setStatus(const std::string& status);
    std::string getStatus() const;

    // ��ȡ�����ID�����֡����������ͺͽ���
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getType() const;
    int getReward() const;

private:
    int _id; // �����ΨһID
    std::string _name; // ���������
    std::string _description; // ���������
    std::string _type; // ��������ͣ����ռ����޸��ȣ�
    int _reward; // ����Ľ���
    std::string _status; // �����״̬��δ���ܡ������С�����ɣ�
};

#endif // NPCTASK_H
