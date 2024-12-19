#include "AnimalManager.h"
#include <string>
#include "cocos2d.h"

USING_NS_CC;

// ��̬��Ա������ʼ��
AnimalManager* AnimalManager::_instance = nullptr;

// ��ȡ����ʵ��
AnimalManager* AnimalManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) AnimalManager();
        if (_instance && _instance->init())
        {
            _instance->autorelease();
            _instance->retain(); // �������ü�������ֹ���ͷ�
        }
        else
        {
            CC_SAFE_DELETE(_instance);
            _instance = nullptr;
        }
    }
    return _instance;
}

// ˽�й��캯��
AnimalManager::AnimalManager()
{
    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
}

// ��ʼ��
bool AnimalManager::init() {

    if (!Layer::init())
    {
        return false;
    }

  
    return true;
}
