#include "Sword.h"
#include"cocos2d.h"

void Sword::bindsprite(Sprite* sprite)
{
	mysword = sprite;
}
bool Sword::init()
{
	log("Trying to create sword");
	Sprite* pSprite = Sprite::create("item/sword.png");
	bindsprite(pSprite);
	pSprite->setRotation(-60.f);
	return true;
}
void Sword::attack(bool face)
{
	int actionStep = 4;
	SpriteFrame* frame_r = nullptr;
	SpriteFrame* frame_l = nullptr;

	for (int i = 1; i <= actionStep; i++)
	{
		frame_r = SpriteFrame::create(StringUtils::format("item/bullets/sword_action%d.png", i),
			Rect(0, 0, 60, 60));
		frame_l = SpriteFrame::create(StringUtils::format("item/bullets/sword_action%d.png", i),
			Rect(0, 0, 60, 60));
		if (frame_l == nullptr || frame_r == nullptr)
		{
			log("animate sword_action%d.png lost", i);
		}
		else
		{
			frame_r->setAnchorPoint(Vec2(0.f, 0.5f));
			m_rightActionVec.pushBack(frame_r);
			frame_l->setAnchorPoint(Vec2(1.f, 0.5f));
			m_leftActionVec.pushBack(frame_l);
		}
	}
	auto fig = "item/sword1.png";
	mysword = Sprite::create(fig);
	bindsprite(mysword);
	if (face == false)
	{
		mysword->setFlippedX(true);
	}
	Animation* animation = nullptr;
	if (face == true)
		animation = Animation::createWithSpriteFrames(m_rightActionVec);
	else
		animation = Animation::createWithSpriteFrames(m_leftActionVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	Animate* actionOne = Animate::create(animation);
	auto end = CallFunc::create([&]() {
		this->removeFromParentAndCleanup(true);
		});
	actionOne->retain();
	auto seq = Sequence::create(actionOne, end, nullptr);
	mysword->runAction(seq);
	log("sword attack!");
}