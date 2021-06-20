#include "SpearBullet.h"

bool SpearBullet::init()
{
	int actionStep = 5;
	SpriteFrame* frame_r = nullptr;
	SpriteFrame* frame_l = nullptr;
	for (int i = 1; i <= actionStep; i++)
	{
		frame_r = SpriteFrame::create(StringUtils::format("item/bullets/spear_action%d.png", i),
			Rect(0, 0, 60, 15));
		frame_l = SpriteFrame::create(StringUtils::format("item/bullets/spear_action%d.png", i),
			Rect(0, 0, 60, 15));

		frame_r->setAnchorPoint(Vec2(0.5f, 0.5f));
		m_rightActionVec.pushBack(frame_r);
		frame_l->setAnchorPoint(Vec2(0.5f, 0.5f));
		m_leftActionVec.pushBack(frame_l);

	}
	m_pBulletSprite = Sprite::create("item/spear1.png");
	bindSprite(m_pBulletSprite);
	return true;
}
void SpearBullet::attack(Point heroPoint, int curFacing, Vec2 monsterPos)
{
    if (curFacing == 1)
    {
        m_pBulletSprite->setFlippedX(true);
    }
    auto point = heroPoint + Vec2((curFacing == 0 ? 35.f : -35.f), 20.f);
    m_pBulletSprite->setPosition(point);
    Animation* animation = nullptr;
    if (curFacing == 1)
    {
        animation = Animation::createWithSpriteFrames(m_rightActionVec);
    }
    else
    {
        animation = Animation::createWithSpriteFrames(m_leftActionVec);
    }
    animation->setLoops(1);
    animation->setDelayPerUnit(0.1f);
    Animate* actionOne = Animate::create(animation);
    auto end = CallFunc::create([&]() {
        this->removeFromParentAndCleanup(true);
        });
    actionOne->retain();
    auto seq = Sequence::create(actionOne, end, nullptr);
    m_pBulletSprite->runAction(seq);
}
