#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <string>
#include <vector>
#include "NPCRelationship.h"

class NPC : public cocos2d::Sprite {
public:
    // ���캯������ʼ��NPC��ID�����ֺ;���ͼ��
    NPC(int id, const std::string& name, const std::string& spritePath);
    ~NPC(); // ��������

    // ���úͻ�ȡNPC�ĶԻ�����
    void setDialogue(const std::vector<std::string>& dialogues);
    std::string getRandomDialogue() const;

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

    void setSpecialTaskCompleted(bool completed);
    bool isSpecialTaskCompleted() const;

    //��ȡ��ǰ��ϵ�ȼ�
    int getFavorability()const { return _relationship.getFavorability(); }


    int _id; // NPC��ΨһID
    std::string _name; // NPC������
    std::vector<std::string> _dialogues; // NPC�ĶԻ�����
    NPCRelationship _relationship; // ����ҵĹ�ϵ�ȼ�
    std::vector<std::string> _tasks; // NPC�����������б�
    cocos2d::Vec2 _location; // NPC��λ��
private:
    
};

#endif // NPC_H