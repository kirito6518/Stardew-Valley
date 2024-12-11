#include "Animal.h"

// ���캯��
Animal::Animal(std::string name, int productTime, std::string productType, std::string breedSeason)
    : name(name), productTime(productTime), productType(productType), breedSeason(breedSeason),
    daysSinceLastProduct(0), fertilizerCount(0) {
}

// ����Ƿ����������Ʒ
bool Animal::canProduce() const {
    return daysSinceLastProduct >= productTime;
}

// ���¶���״̬
void Animal::update(int days) {
    daysSinceLastProduct += days;
}

// �ռ���Ʒ���������ϣ�
void Animal::collectProduct() {
    if (canProduce()) {
        // ����������ʱ
        daysSinceLastProduct = 0;
        // ���ɷ���
        fertilizerCount += 1; // ÿ��������Ʒʱ���� 1 ������
    }
}

// ����Ƿ���Է�ֳ
bool Animal::canBreed(const std::string& currentSeason) const {
    return currentSeason == breedSeason;
}

// ��ֳ��Ϊ
Animal* Animal::breed() const {
    // ��ֳʱ����һ���µĶ���ʵ��
    return new Animal(name, productTime, productType, breedSeason);
}