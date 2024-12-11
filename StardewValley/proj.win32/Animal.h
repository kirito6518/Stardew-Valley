#pragma once
#include <string>
#include <vector>

class Animal {
public:
    Animal(std::string name, int productTime, std::string productType, std::string breedSeason);

    // 检查是否可以生产产品
    bool canProduce() const;

    // 更新动物状态
    void update(int days);

    // 收集产品（包括肥料）
    void collectProduct();

    // 检查是否可以繁殖
    bool canBreed(const std::string& currentSeason) const;

    // 繁殖行为
    Animal* breed() const;

    // 获取动物名称
    std::string getName() const { return name; }

    // 获取产品类型
    std::string getProductType() const { return productType; }

    // 获取肥料数量
    int getFertilizerCount() const { return fertilizerCount; }

private:
    std::string name;               // 动物名称
    int productTime;                // 生产产品的时间（以游戏天数为单位）
    std::string productType;        // 产品类型（如牛奶、鸡蛋等）
    int daysSinceLastProduct;       // 上次生产产品后的天数
    int fertilizerCount;            // 肥料数量（每次生产产品时生成）
    std::string breedSeason;        // 繁殖季节
};