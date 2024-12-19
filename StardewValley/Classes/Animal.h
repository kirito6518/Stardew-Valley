#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <string>

USING_NS_CC;

// ������
class Animal : public Node {
public:

    // ���캯��
    Animal(const std::string& name, const std::string& productType, Sprite* sprite, int numOfChild, int numOfAdult, int numOfOld, Animation* animations);
 
    std::string name; // ��������
    std::string productType; // ��Ʒ����
    Sprite* sprite; // ������ʾ����ľ���
    int numOfChild; // �ö������͵�����������Ŀ
    int numOfAdult; // �ö������͵ĳ���������Ŀ
    int numOfOld; // �ö������͵�����������Ŀ

    // ��̬��Ա�������洢����Ĳ���
    Animation* animations; // ����Ķ���
};

#endif // ANIMAL_H