#include "AnimalManager.h"
#include <string>
#include "cocos2d.h"

USING_NS_CC;

// 静态成员变量初始化
AnimalManager* AnimalManager::_instance = nullptr;

// 获取单例实例
AnimalManager* AnimalManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) AnimalManager();
        if (_instance && _instance->init())
        {
            _instance->autorelease();
            _instance->retain(); // 增加引用计数，防止被释放
        }
        else
        {
            CC_SAFE_DELETE(_instance);
            _instance = nullptr;
        }
    }
    return _instance;
}

// 私有构造函数
AnimalManager::AnimalManager()
{
    // 私有构造函数，防止外部直接实例化
}

// 初始化
bool AnimalManager::init() {

    if (!Layer::init())
    {
        return false;
    }

  
    return true;
}
