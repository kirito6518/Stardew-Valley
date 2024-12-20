#include "cocos2d.h"
#include "NPC.h"
#include <random>

USING_NS_CC;

// ���캯������ʼ��NPC��ID�����ֺ;���ͼ��
NPC::NPC(int id, const std::string& name, const std::string& spritePath)
    : _id(id), _name(name), _relationship(0) {
    // ���ؾ���ͼ��
    this->initWithFile(spritePath);
}

NPC::~NPC() {}

// ����NPC�ĶԻ�����
void NPC::setDialogue(const std::vector<std::string>& dialogues) {
    _dialogues = dialogues;
}

// ��ȡNPC������Ի�����
std::string NPC::getRandomDialogue() const {
    if (_dialogues.empty()) return "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _dialogues.size() - 1);
    return _dialogues[dis(gen)];
}

// ����NPC����ҵĹ�ϵ�ȼ�
void NPC::setRelationship(int level) {
    _relationship.increaseLevel(level);
}

// ��ȡNPC����ҵĹ�ϵ�ȼ�
int NPC::getRelationship() const {
    return _relationship.getLevel();
}

// �������NPC�������б�
void NPC::addTask(const std::string& task) {
    _tasks.push_back(task);
}

// ��ȡNPC�������б�
std::vector<std::string> NPC::getTasks() const {
    return _tasks;
}

// ����NPC��λ��
void NPC::setLocation(const cocos2d::Vec2& location) {
    _location = location;
    this->setPosition(location); // ���þ����λ��
}

// ��ȡNPC��λ��
cocos2d::Vec2 NPC::getLocation() const {
    return _location;
}

void NPC::interactWithPlayer() {
    if (_isDialogueVisible) return; // ����Ի����Ѿ���ʾ��ֱ�ӷ���

    // ��ȡ NPC ������Ի�����
    std::string dialogue = getRandomDialogue();

    // �����Ի��� Label��ʹ�� TTF ����
    auto dialogueBox = Label::createWithTTF(dialogue, "fonts/Marker Felt.ttf", 24);

    // ���öԻ����λ��
    dialogueBox->setPosition(Vec2(getPosition().x, getPosition().y + getContentSize().height / 2 + 20));
    dialogueBox->setAnchorPoint(Vec2(0.5, 0.5));

    // ���Ի�����ӵ�������
    this->getParent()->addChild(dialogueBox, 3); // ȷ���Ի�����ʾ�����ϲ�

    // ���öԻ�����������ڣ����� 3 ����Ƴ�
    this->scheduleOnce([this, dialogueBox](float dt) {
        dialogueBox->removeFromParent();
        _isDialogueVisible = false; // �Ի����Ƴ������ñ�־λ
        }, 2.0f, "remove_dialogue_box"); // �����������Ƕ�ʱ���ı�ǩ����ѡ

    _isDialogueVisible = true; // ��ǶԻ�������ʾ
}

void NPC::removeDialogue() {
    if (!_isDialogueVisible) return; // ����Ի���δ��ʾ��ֱ�ӷ���

    // �Ƴ��Ի���
    auto dialogueBox = this->getChildByName("dialogue_box");
    if (dialogueBox) {
        dialogueBox->removeFromParent();
    }

    _isDialogueVisible = false; // ���ñ�־λ
}