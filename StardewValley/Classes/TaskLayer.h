#ifndef __TASK_LAYER_H__
#define __TASK_LAYER_H__

#include "cocos2d.h"
#include "NPCTask.h"

USING_NS_CC;

/**
 * @class TaskLayer
 * @brief �����б���࣬������ʾ�͹��������б��е�����
 *
 * TaskLayer ��һ�� Cocos2d-x �� Layer��������ʾ�����б���档�������� NPC ���ơ��������顢
 * ����������Ʒ����������Ϣ���û�����ͨ���ò��������б���н���������鿴�������顢�������ȡ�
 */
class TaskLayer : public cocos2d::Layer
{
public:
    // ����һ�� TaskLayer ����
    static TaskLayer* create();

    // ��ʼ�� TaskLayer
    bool init();

    //��������б�layer��
    bool addList(Sprite* taskList);

    // �Ƴ��б�
    void removeItem(Sprite* taskList);

    //������Ʒλ��
    void renewPosition();

    //�ر��������
    void closeTaskUI(Ref* sender);

    // ��ȡ�������������
    const Vector<NPCTask*>& getTasks() const { return tasks; }


    // ��������¼�������
    void setupMouseListener();

private:

    cocos2d::Vector<Sprite*> lists;//���������б���
    Vector <NPCTask*> tasks;//��������

    cocos2d::Sprite* taskUI; ///< �������
    cocos2d::Sprite* taskDetailsUi;//��������UI
    cocos2d::MenuItemImage* closeButton; ///< �ر��������鰴ť

    cocos2d::Label* nowGoodwill;//��ǰ�øж�
    cocos2d::Label* rewardGoodwill;//�����øж�

    cocos2d::Sprite* needItem;//������Ʒͼ�꾫��
    cocos2d::Label* needItemCount;//������Ʒ����

};

#endif // __TASK_LAYER_H__