#include "Player.h"
#include "chipmunk.h"
#include "cocos2d.h"
#include "Cave.h"
#include "BringMine.h"
#include "MainMap.h"

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
    // ��ʼ�������ϵͳ
    srand((unsigned)(time(0)));

    gem = 0;

    // ��ʼ��Layer
    chooseMineLayer = ChooseMineLayer::getInstance();

    // ��� chooseMineLayer �Ƿ�Ϊ nullptr
    if (chooseMineLayer == nullptr) {
        CCLOG("Failed to create ChooseMineLayer instance!");
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
    // physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // ���ص�ͼ
    caveSprite = Sprite::create("maps/Cave.png");// 1152 * 1248��
    caveSprite->setAnchorPoint(Vec2(0.5, 0.5));
    caveSprite->setPosition(visibleSize / 2);
    this->addChild(caveSprite, 0);

    // ���ر�ʯ
    gemSprite1 = Sprite::create("mineral/GemA.png");
    gemSprite1->retain();
    gemSprite2 = Sprite::create("mineral/GemB.png");
    gemSprite2->retain();
    gemSprite3 = Sprite::create("mineral/GemC.png");
    gemSprite3->retain();
    gemSprite4 = Sprite::create("mineral/GemD.png");
    gemSprite4->retain();
    gemSprite5 = Sprite::create("mineral/GemE.png");
    gemSprite5->retain();

    // �����ͼ���������ײ��

    // �ϱ߽�
    caveUpBoundary = Sprite::create("maps/caveUpBoundary.png");// 1152 * 168��
    caveUpBoundary->setAnchorPoint(Vec2(0.5, 1.0));
    caveUpBoundary->setPosition(visibleSize / 2 + Size(0, 1248 / 2));
    caveUpBoundaryBox = PhysicsBody::createBox(caveUpBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveUpBoundaryBox->setDynamic(false);
    caveUpBoundary->setPhysicsBody(caveUpBoundaryBox);
    this->addChild(caveUpBoundary, 0);

    // �ұ߽�
    caveRightBoundary = Sprite::create("maps/caveRightBoundary.png");// 120 * 1248��
    caveRightBoundary->setAnchorPoint(Vec2(1.0, 0.5));
    caveRightBoundary->setPosition(visibleSize / 2 + Size(1152 / 2, 0));
    caveRightBoundaryBox = PhysicsBody::createBox(caveRightBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveRightBoundaryBox->setDynamic(false);
    caveRightBoundary->setPhysicsBody(caveRightBoundaryBox);
    this->addChild(caveRightBoundary, 0);

    // ��߽�
    caveLeftBoundary = Sprite::create("maps/caveLeftBoundary.png");// 72 * 1248��
    caveLeftBoundary->setAnchorPoint(Vec2(0.0, 0.5));
    caveLeftBoundary->setPosition(visibleSize / 2 + Size(-1152 / 2, 0));
    caveLeftBoundaryBox = PhysicsBody::createBox(caveLeftBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveLeftBoundaryBox->setDynamic(false);
    caveLeftBoundary->setPhysicsBody(caveLeftBoundaryBox);
    this->addChild(caveLeftBoundary, 0);

    // �±߽�
    caveDownBoundary = Sprite::create("maps/caveDownBoundary.png");// 1152 * 48��
    caveDownBoundary->setAnchorPoint(Vec2(0.5, 0.0));
    caveDownBoundary->setPosition(visibleSize / 2 + Size(0, -1248 / 2));
    caveDownBoundaryBox = PhysicsBody::createBox(caveDownBoundary->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    caveDownBoundaryBox->setDynamic(false);
    caveDownBoundary->setPhysicsBody(caveDownBoundaryBox);
    this->addChild(caveDownBoundary, 0);

    // ��������
    ladder = Sprite::create("maps/ladder.png"); // 24 * 120��
    ladder->setAnchorPoint(Vec2(0.0f,1.0f)); // ���Ͻ�
    ladder->setPosition(visibleSize / 2 + Size(24, 552)); // ��ʼλ������Ļ�Ϸ�
    ladderBox = PhysicsBody::createBox(ladder->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.0f));// �ܶ� ���� Ħ����
    ladderBox->setDynamic(false); // ����Ϊ��̬������
    ladderBox->setCollisionBitmask(0x01);
    ladderBox->setContactTestBitmask(0x01);
    ladder->setPhysicsBody(ladderBox);// ����������
    this->addChild(ladder, 1);

    // �������Ǿ���
    player.playerSprite->setPosition(visibleSize / 2 + Size(24 + 12, 384)); // ��ʼλ������Ļ�Ϸ�

    // Ϊ������������
    playerBox = PhysicsBody::createBox(player.playerSprite->getContentSize() / 4, PhysicsMaterial(0.1f, 0.0f, 0.0f));// �ܶ� ���� Ħ����
    playerBox->setDynamic(true); // ����Ϊ��̬������
    playerBox->setCollisionBitmask(0x01);
    playerBox->setContactTestBitmask(0x01);
    player.playerSprite->setPhysicsBody(playerBox);// ����������
    this->addChild(player.playerSprite, 1);

    ladder->setName("ladder");

    // �����ڰ�����
    black = Sprite::create("black.png"); // 4000 * 2000��
    black->setAnchorPoint(Vec2(0.5f, 0.5f)); // ����
    black->setPosition(visibleSize / 2); // ��ʼλ������Ļ�Ϸ�
    this->addChild(black, 2);

    // ���ɿ���
    CreateMine();

    // ע������¼�
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, &player);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, &player);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ÿ����s��������ͷ�Ͱ�ťλ��
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::update), 0);

    return true;
}

// ÿ֡��������ͷ�Ͱ�ťλ�ã�������ײ��
void Cave::update(float dt) {

    // ������ҵ�λ�úͶ���
    player.update(dt);

    // ��ȡ��ҵ�λ��
    const Vec2 playerPosition = player.playerSprite->getPosition();// ê�������½ǵ�һ��λ��
    black->setPosition(playerPosition); // ͬ���ڰ�

    //��ȡ��Ļ��С�͵�ͼ��С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = caveSprite->getContentSize();

    // ������λ��
    // CCLOG("player position: (%f,%f)", playerPosition.x, playerPosition.y);

    // ������������½ǵ�Ŀ��λ�ã�ʹ��ұ�������Ļ����
    Vec2 targetCameraPosition = playerPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // ������������ƶ���Χ
    float maxX = 0;
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

    // ���±�ʯλ��
    Gem(targetCameraPosition);

    chooseMineLayer->chooseLayer->setPosition(targetCameraPosition + visibleSize / 2);
    chooseMineLayer->yesButton->setPosition(targetCameraPosition + visibleSize / 2 + Vec2(-240, -136));
    chooseMineLayer->noButton->setPosition(targetCameraPosition + visibleSize / 2 + Vec2(+240, -136));

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
    if (nodeB->getName() == "ladder" || nodeA->getName() == "ladder") {
        // CCLOG("Player collided with ladder area!");
        Director::getInstance()->popScene(); // ������һ������
        dynamic_cast<MainMap*>(mainMap)->BackFromCave();
    }
    else if (nodeB->getName() == "ShardE" || nodeA->getName() == "ShardE") {
        OpenLayer();
        chooseMineLayer->chooseMine = 5;
    }
    else if (nodeB->getName() == "ShardD" || nodeA->getName() == "ShardD") {
        OpenLayer();
        chooseMineLayer->chooseMine = 4;
    }
    else if (nodeB->getName() == "ShardC" || nodeA->getName() == "ShardC") {
        OpenLayer();
        chooseMineLayer->chooseMine = 3;
    }
    else if (nodeB->getName() == "ShardB" || nodeA->getName() == "ShardB") {
        OpenLayer();
        chooseMineLayer->chooseMine = 2;
    }
    else if (nodeB->getName() == "ShardA" || nodeA->getName() == "ShardA") {
        OpenLayer();
        chooseMineLayer->chooseMine = 1;
    }
    return true;
}

// ���һ������
void Cave::AddMine(Sprite* mine, PhysicsBody* mineBox, Vec2 position) {

    auto num = rand() % 25 + 1;
    
    if (num == 1) { // ���ˮ��E
        mine = Sprite::create("mineral/ShardE.png"); // 60 * 60��
        mine->setName("ShardE");
    }
    else if (num >= 2 && num <= 4) { // ���ˮ��D
        mine = Sprite::create("mineral/ShardD.png"); // 60 * 60��
        mine->setName("ShardD");
    }
    else if (num >= 5 && num <= 9) { // ���ˮ��C
        mine = Sprite::create("mineral/ShardC.png"); // 60 * 60��
        mine->setName("ShardC");
    }
    else if (num >= 10 && num <= 16) { // ���ˮ��B
        mine = Sprite::create("mineral/ShardB.png"); // 60 * 60��
        mine->setName("ShardB");
    }
    else if (num >= 17 && num <= 25) { // ���ˮ��A
        mine = Sprite::create("mineral/ShardA.png"); // 60 * 60��
        mine->setName("ShardA");
    }
    mine->setAnchorPoint(Vec2(0.5f, 0.5f)); // �м�
    mine->setPosition(position); // ��ʼλ��
    mineBox = PhysicsBody::createBox(mine->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));// �ܶ� ���� Ħ����
    mineBox->setDynamic(false); // ����Ϊ��̬������
    mineBox->setCollisionBitmask(0x01);
    mineBox->setContactTestBitmask(0x01);
    mine->setPhysicsBody(mineBox);// ����������
    this->addChild(mine, 1);
}

// ������ɿ���
void Cave::CreateMine() {
    // �����Ļ�ߴ�͵�ͼ�ߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto mapSize = caveSprite->getContentSize();

    // ���ɷ�Χ
    int minX = 144 + 60;
    int maxX = 1080 - 60;
    int minY = 192 + 60;
    int maxY = 816 - 60 - 72;

    for (int i = minX; i <= maxX; i = i + 168) {
        for (int j = minY; j <= maxY; j = j + 120) {
            auto num = rand() % 5 + 1;
            if (num == 5 && mines.size() <= 10) { // ���֮һ�ĸ������ɿ���
                Sprite* mine = Sprite::create();
                PhysicsBody* mineBox = PhysicsBody::create();
                // ���ɿ���
                AddMine(mine, mineBox, Vec2(i, j));
                // ����
                mines.push_back(mine);
                minesBox.push_back(mineBox);
            }
        }
    }
}

// ��ѡ��
void Cave::OpenLayer() {

    // ��� chooseMineLayer �Ƿ��Ѿ��и��ڵ�
    if (chooseMineLayer->getParent() == nullptr) {
        chooseMineLayer->cave = this;
        this->addChild(chooseMineLayer, 3);
    }
    // ���� Cave ������ʱ�����
    this->unschedule(CC_SCHEDULE_SELECTOR(Cave::update));
}

//����ѡ��
void Cave::HideLayer(Ref* sender){

    // �������� cave ������ʱ�����
    this->schedule(CC_SCHEDULE_SELECTOR(Cave::update), 0);
    // �Ƴ� chooseMineLayer
    if (chooseMineLayer->getParent()) {
        this->removeChild(chooseMineLayer);
    }
}

// ����Ļ�·���ʾ���Դ��ߵı�ʯ
void Cave::Gem(Vec2 targetCameraPosition) {
    // �Ƴ��Ѿ���ӵı�ʯ����
    if (gemSprite1->getParent()) {
        this->removeChild(gemSprite1);
    }
    if (gemSprite2->getParent()) {
        this->removeChild(gemSprite2);
    }
    if (gemSprite3->getParent()) {
        this->removeChild(gemSprite3);
    }
    if (gemSprite4->getParent()) {
        this->removeChild(gemSprite4);
    }
    if (gemSprite5->getParent()) {
        this->removeChild(gemSprite5);
    }

    // ���� gem �����Ӷ�Ӧ�ı�ʯ����
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    switch (gem) {
        case 1:
            gemSprite1->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite1->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite1, 3);
            break;
        case 2:
            gemSprite2->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite2->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite2, 3);
            break;
        case 3:
            gemSprite3->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite3->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite3, 3);
            break;
        case 4:
            gemSprite4->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite4->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite4, 3);
            break;
        case 5:
            gemSprite5->setAnchorPoint(Vec2(0.5, 0.0));
            gemSprite5->setPosition(targetCameraPosition + Vec2(visibleSize.width / 2, 0));
            this->addChild(gemSprite5, 3);
            break;
        default:
            // ��� gem Ϊ 0��������κα�ʯ
            break;
    }
}
