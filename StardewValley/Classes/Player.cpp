#include "Player.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

// ��ʼ������
bool Player::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // ��ʼ������
    isWPressed = isAPressed = isSPressed = isDPressed = false; // ��ʼ������״̬

    // ��������
    createWalkAnimations();
    createIdleAnimations();



    // ע��ÿ֡����
    this->scheduleUpdate();

    return true;
}

// ����������������߶���
void Player::createWalkAnimations()
{
    // ���� walk.png ͼƬ
    auto texture = Director::getInstance()->getTextureCache()->addImage("walk.png");

    // walk.png ��һ�� 6 �����ͼƬ��ÿ֡�Ŀ��Ϊ 72 ���أ��߶�Ϊ 96 ����
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // ÿ�������� 8 ֡

    // ����ÿ�������֡��Χ
    // ����˳���¡������ϡ��ϡ����ϡ���
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 �������ƫ����

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // ���ݷ���ƫ��������֡������
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // ��������
        walkAnimations[i] = Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡��� 0.1 ��
        walkAnimations[i]->retain(); // ������������ֹ���ͷ�
    }
}

// ������������Ĵ�������
void Player::createIdleAnimations()
{
    // ���� idle.png ͼƬ
    auto texture = Director::getInstance()->getTextureCache()->addImage("idle.png");

    // idle.png ��һ�� 6 �����ͼƬ��ÿ֡�Ŀ��Ϊ 72 ���أ��߶�Ϊ 96 ����
    const int frameWidth = 72;
    const int frameHeight = 96;
    const int framesPerDirection = 8; // ÿ�������� 8 ֡

    // ����ÿ�������֡��Χ
    // ����˳���¡������ϡ��ϡ����ϡ���
    const int directionOffsets[6] = { 0, 1, 2, 3, 4, 5 }; // 6 �������ƫ����

    for (int i = 0; i < 6; ++i)
    {
        Vector<SpriteFrame*> frames;
        for (int j = 0; j < framesPerDirection; ++j)
        {
            // ���ݷ���ƫ��������֡������
            auto frame = SpriteFrame::createWithTexture(texture, Rect(j * frameWidth, directionOffsets[i] * frameHeight, frameWidth, frameHeight));
            frames.pushBack(frame);
        }

        // ��������
        idleAnimations[i] = Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡��� 0.1 ��
        idleAnimations[i]->retain(); // ������������ֹ���ͷ�
    }
}

// ���ݷ���ѡ�񶯻�
int Player::getDirectionIndex(const cocos2d::Vec2& from, const cocos2d::Vec2& to)
{
    Vec2 direction = to - from;
    float angle = CC_RADIANS_TO_DEGREES(atan2(direction.y, direction.x));

    // ���ݽǶ�ȷ������
    if (angle >= -22.5f && angle < 22.5f) return 5; // ��
    if (angle >= 22.5f && angle < 67.5f) return 4;  // ����
    if (angle >= 67.5f && angle < 112.5f) return 3; // ��
    if (angle >= 112.5f && angle < 157.5f) return 2; // ����
    if (angle >= 157.5f || angle < -157.5f) return 1; // ��
    if (angle >= -157.5f && angle < -112.5f) return 1; // ����
    if (angle >= -112.5f && angle < -67.5f) return 0; // ��
    if (angle >= -67.5f && angle < -22.5f) return 5; // ����

    return 5; // Ĭ����
}

// ���̰����¼�����
void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key pressed: %d", keyCode); // �����������
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            isWPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            isAPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isSPressed = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            isDPressed = true;
            break;
        default:
            break;
    }
}

// �����ͷ��¼�����
void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    CCLOG("Key released: %d", keyCode); // �����������
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            isWPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            isAPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isSPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            isDPressed = false;
            break;
        default:
            break;
    }
}

// ��������λ��
void Player::updatePlayerPosition(float dt)
{
    Vec2 direction = Vec2::ZERO;

    if (isWPressed) direction.y += 1;
    if (isAPressed) direction.x -= 1;
    if (isSPressed) direction.y -= 1;
    if (isDPressed) direction.x += 1;

    if (direction != Vec2::ZERO)
    {
        //�ƶ�����
        Vec2 moveDistance = direction * 100 * dt;
        //�ƶ�
        auto moveAction = MoveBy::create(dt, moveDistance);
        //�жϷ��򶯻�
        int directionIndex = getDirectionIndex(this->getPosition(), this->getPosition() + moveDistance);
        //�������ߵĶ���
        auto animateAction = Animate::create(walkAnimations[directionIndex]);
        //���߶������ƶ�һ�𲥷�
        auto spawn = Spawn::create(moveAction, animateAction, NULL);
        //����
        playerSprite->runAction(spawn);

        lastDirectionIndex = directionIndex;
    }
    else
    {
        // ���Ŵ�������
        playerSprite->runAction(RepeatForever::create(Animate::create(idleAnimations[lastDirectionIndex])));
    }
}

// ÿ֡����
void Player::update(float dt)
{
    updatePlayerPosition(dt);
}