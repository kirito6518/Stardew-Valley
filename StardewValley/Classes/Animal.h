#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

// 动物类，继承自cocos2d::Node
class Animal : public cocos2d::Node {
public:
    // 构造函数
    Animal(const std::string& name, const std::string& breedSeason);

    // 判断动物是否可以生产产品
    bool canProduce() const;

    // 更新动物的状态
    void update(int days);

    // 收集动物的产品
    void collectProduct();

    // 判断动物是否可以在当前季节繁殖
    bool canBreed(const std::string& currentSeason) const;

    // 繁殖动物，生成一个新的动物对象
    Animal* breed() const;

    // 喂食动物
    void feed();

    // 判断动物是否饥饿
    bool isHungry() const;

    // 获取动物名称
    std::string get_Name() const { return name; }

    // 获取产品类型
    std::string getProductType() const { return productType; }

    // 获取肥料数量
    int getFertilizerCount() const { return fertilizerCount; }

    // 获取每次喂食量
    int getFeedAmount() const { return feedAmount; }

    // 显示饥饿动画
    void showHungryAnimation();

    // 静态成员函数，用于初始化动物参数
    static void initializeAnimalParameters();

private:
    std::string name;               // 动物名称
    std::string productType;        // 产品类型（如牛奶、鸡蛋等）
    int daysSinceLastProduct;       // 上次生产产品后的天数
    int fertilizerCount;            // 肥料数量（每次生产产品时生成）
    std::string breedSeason;        // 繁殖季节
    int hungerThreshold;            // 饥饿阈值
    int feedAmount;                 // 每次喂食量
    int daysSinceLastFed;           // 上次喂食后的天数
    int lifespan;                   // 寿命
    cocos2d::Sprite* sprite;        // 用于显示动物的精灵

    // 静态成员变量，存储动物的参数
    static std::unordered_map<std::string, int> productTimes;
    static std::unordered_map<std::string, std::string> productTypes;
    static std::unordered_map<std::string, int> hungerThresholds;
    static std::unordered_map<std::string, int> feedAmounts;
    static std::unordered_map<std::string, int> lifespans;
};

#endif // ANIMAL_H