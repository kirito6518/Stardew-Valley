#pragma once
#include <string>
#include <vector>

class Animal {
public:
    Animal(std::string name, int productTime, std::string productType, std::string breedSeason);

    // ����Ƿ����������Ʒ
    bool canProduce() const;

    // ���¶���״̬
    void update(int days);

    // �ռ���Ʒ���������ϣ�
    void collectProduct();

    // ����Ƿ���Է�ֳ
    bool canBreed(const std::string& currentSeason) const;

    // ��ֳ��Ϊ
    Animal* breed() const;

    // ��ȡ��������
    std::string getName() const { return name; }

    // ��ȡ��Ʒ����
    std::string getProductType() const { return productType; }

    // ��ȡ��������
    int getFertilizerCount() const { return fertilizerCount; }

private:
    std::string name;               // ��������
    int productTime;                // ������Ʒ��ʱ�䣨����Ϸ����Ϊ��λ��
    std::string productType;        // ��Ʒ���ͣ���ţ�̡������ȣ�
    int daysSinceLastProduct;       // �ϴ�������Ʒ�������
    int fertilizerCount;            // ����������ÿ��������Ʒʱ���ɣ�
    std::string breedSeason;        // ��ֳ����
};