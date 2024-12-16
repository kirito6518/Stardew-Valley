#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>

// NPC��̳���cocos2d::Sprite����ʾһ��NPC����
class NPC : public cocos2d::Sprite {
public:
    // ���캯������ʼ��NPC��ID�����ֺ;���ͼ��
    NPC(int id, const std::string& name, const std::string& spritePath);
    ~NPC(); // ��������

    // ���úͻ�ȡNPC�ĶԻ�����
    void setDialogue(const std::string& dialogue);
    std::string getDialogue() const;

    // ���úͻ�ȡNPC����ҵĹ�ϵ�ȼ�
    void setRelationship(int level);
    int getRelationship() const;

    // �������NPC�������б�
    void addTask(const std::string& task);
    std::vector<std::string> getTasks() const;

    // ���úͻ�ȡNPC��λ��
    void setLocation(const cocos2d::Vec2& location);
    cocos2d::Vec2 getLocation() const;

    // �����NPC����ʱ�����ĺ���
    void interactWithPlayer();

    // �Ƴ��Ի���
    void removeDialogue();

    bool _isDialogueVisible = false; // �Ի����Ƿ�ɼ�

private:
    int _id; // NPC��ΨһID
    std::string _name; // NPC������
    std::string _dialogue; // NPC�ĶԻ�����
    int _relationship; // ����ҵĹ�ϵ�ȼ���0:İ����, 1:����, 2:������
    std::vector<std::string> _tasks; // NPC�����������б�
    cocos2d::Vec2 _location; // NPC��λ��
};

#endif // NPC_H