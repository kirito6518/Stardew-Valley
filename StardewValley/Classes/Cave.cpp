#include "Player.h"
#include "chipmunk.h"
#include "cocos2d.h"
#include "Cave.h"

USING_NS_CC;

Scene* Cave::createScene()
{
    return Cave::create();
}

bool Cave::init()
{
    // ������ش���
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    // ԭ���Ǵ������½�
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    // ��ȡ��������
    auto physicsWorld = this->getPhysicsWorld();
    physicsWorld->setGravity(Vec2(0, 0));// ������������

    // ������ײ������
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Cave::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // ���õ��Ի���
    physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // ���ص�ͼ
    caveSprite = Sprite::create("maps/Cave.png");// 1152 * 1248��
    caveSprite->setAnchorPoint(Vec2(0.5, 0.5));
    caveSprite->setPosition(visibleSize / 2);
    this->addChild(caveSprite, 0);

    // �������Ǿ���
    player.playerSprite->setPosition(visibleSize / 2); // ��ʼλ������Ļ�Ϸ�

    // Ϊ������������
    playerBox = PhysicsBody::createBox(player.playerSprite->getContentSize() / 4, PhysicsMaterial(0.1f, 0.0f, 0.0f));// �ܶ� ���� Ħ����
    playerBox->setDynamic(true); // ����Ϊ��̬������
    playerBox->setCollisionBitmask(0x01);
    playerBox->setContactTestBitmask(0x01);
    player.playerSprite->setPhysicsBody(playerBox);// ����������
    this->addChild(player.playerSprite, 1);

    // ע������¼�
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ÿ����s��������λ��
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::updatePlayerPosition), 0.2f);
    // ÿ����s��������ͷ�Ͱ�ťλ��
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::updateCameraPosition), 0);

    return true;
}

// ÿ0.2s�������λ�úͶ���
void Cave::updatePlayerPosition(float delta)
{
    // ������ҵ�λ�úͶ���
    player.update(delta);

}

// ÿ֡��������ͷ�Ͱ�ťλ�ã�������ײ��
void Cave::updateCameraPosition(float dt) {

    // ��ȡ��ҵ�λ��
    const Vec2 playerPosition = player.playerSprite->getPosition();// ê�������½ǵ�һ��λ��

    //��ȡ��Ļ��С�͵�ͼ��С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = caveSprite->getContentSize();

    // ������λ��
    // CCLOG("player position: (%f,%f)", playerPosition.x, playerPosition.y);

    // ������������½ǵ�Ŀ��λ�ã�ʹ��ұ�������Ļ����
    Vec2 targetCameraPosition = playerPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // ������������ƶ���Χ
    float maxX = mapSize.width - visibleSize.width;
    float maxY = mapSize.height - visibleSize.height;

    // ȷ��������� x �����ڷ�Χ��
    if (targetCameraPosition.x < -maxX / 2) {
        targetCameraPosition.x = -maxX / 2;
    }
    else if (targetCameraPosition.x > maxX / 2) {
        targetCameraPosition.x = maxX / 2;
    }

    // ȷ��������� y �����ڷ�Χ��
    if (targetCameraPosition.y < -maxY / 2) {
        targetCameraPosition.y = -maxY / 2;
    }
    else if (targetCameraPosition.y > maxY / 2) {
        targetCameraPosition.y = maxY / 2;
    }

    // ��������λ��
    // CCLOG("camera position: (%f,%f)", targetCameraPosition.x, targetCameraPosition.y);

    // �����������λ��
    this->setPosition(-targetCameraPosition);

}

// ��ײ��ʼ������
bool Cave::onContactBegin(PhysicsContact& contact) {
    // ��ȡ��ײ������������
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    // ��ȡ�������Ӧ�Ľڵ�
    auto nodeA = bodyA->getNode();
    auto nodeB = bodyB->getNode();

    // �����ײ��Ϣ
    // CCLOG("Collision between: %s and %s", nodeA->getName().c_str(), nodeB->getName().c_str());

    // �����������ײ����߼�
   
    return true;
}