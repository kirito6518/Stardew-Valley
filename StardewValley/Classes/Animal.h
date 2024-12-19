#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <string>
#include <vector>

USING_NS_CC;

// ������
class Animal : public Node {
public:

    // ���캯��
    Animal(const std::string& name, const std::string& productType, int numOfChild, int numOfAdult, int numOfOld);
 
    std::string name; // ��������
    std::string productType; // ��Ʒ����
    std::vector<Sprite*> sprites; // ������ʾ����ľ���
    int numOfChild; // �ö������͵�����������Ŀ
    int numOfAdult; // �ö������͵ĳ���������Ŀ
    int numOfOld; // �ö������͵�����������Ŀ

    // ��̬��Ա�������洢����Ĳ���
    Animation* animations; // ����Ķ���
};

#endif // ANIMAL_H