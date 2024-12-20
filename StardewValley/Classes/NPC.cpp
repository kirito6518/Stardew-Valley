#include "cocos2d.h"
#include "NPC.h"
#include <random>

USING_NS_CC;

// 构造函数：初始化NPC的ID、名字和精灵图像
NPC::NPC(int id, const std::string& name, const std::string& spritePath)
    : _id(id), _name(name), _relationship(0) {
    // 加载精灵图像
    this->initWithFile(spritePath);
}

NPC::~NPC() {}

// 设置NPC的对话内容
void NPC::setDialogue(const std::vector<std::string>& dialogues) {
    _dialogues = dialogues;
}

// 获取NPC的随机对话内容
std::string NPC::getRandomDialogue() const {
    if (_dialogues.empty()) return "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _dialogues.size() - 1);
    return _dialogues[dis(gen)];
}

// 设置NPC与玩家的关系等级
void NPC::setRelationship(int level) {
    _relationship.increaseLevel(level);
}

// 获取NPC与玩家的关系等级
int NPC::getRelationship() const {
    return _relationship.getLevel();
}

// 添加任务到NPC的任务列表
void NPC::addTask(const std::string& task) {
    _tasks.push_back(task);
}

// 获取NPC的任务列表
std::vector<std::string> NPC::getTasks() const {
    return _tasks;
}

// 设置NPC的位置
void NPC::setLocation(const cocos2d::Vec2& location) {
    _location = location;
    this->setPosition(location); // 设置精灵的位置
}

// 获取NPC的位置
cocos2d::Vec2 NPC::getLocation() const {
    return _location;
}

void NPC::interactWithPlayer() {
    if (_isDialogueVisible) return; // 如果对话框已经显示，直接返回

    // 获取 NPC 的随机对话内容
    std::string dialogue = getRandomDialogue();

    // 创建对话框 Label，使用 TTF 字体
    auto dialogueBox = Label::createWithTTF(dialogue, "fonts/Marker Felt.ttf", 24);

    // 设置对话框的位置
    dialogueBox->setPosition(Vec2(getPosition().x, getPosition().y + getContentSize().height / 2 + 20));
    dialogueBox->setAnchorPoint(Vec2(0.5, 0.5));

    // 将对话框添加到场景中
    this->getParent()->addChild(dialogueBox, 3); // 确保对话框显示在最上层

    // 设置对话框的生命周期，例如 3 秒后移除
    this->scheduleOnce([this, dialogueBox](float dt) {
        dialogueBox->removeFromParent();
        _isDialogueVisible = false; // 对话框被移除后，重置标志位
        }, 2.0f, "remove_dialogue_box"); // 第三个参数是定时器的标签，可选

    _isDialogueVisible = true; // 标记对话框已显示
}

void NPC::removeDialogue() {
    if (!_isDialogueVisible) return; // 如果对话框未显示，直接返回

    // 移除对话框
    auto dialogueBox = this->getChildByName("dialogue_box");
    if (dialogueBox) {
        dialogueBox->removeFromParent();
    }

    _isDialogueVisible = false; // 重置标志位
}