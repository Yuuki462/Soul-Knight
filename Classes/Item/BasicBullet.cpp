#include "BasicBullet.h"

bool BasicBullet::init()
{
	Sprite* pSprite = Sprite::create("item/gunbullet.png");
	if (pSprite == nullptr)
	{
		log("gunbullet.png not found");
	}
	bindSprite(pSprite);
	m_isArrive = false;
	return true;
}

void BasicBullet::attack(Point heroPoint, int curFacing, Vec2 monsterPos)
{
	heroPoint.x += 25.0;
	heroPoint.y += 20.0;
	m_pBulletSprite->setPosition(heroPoint);

	auto v = Vec2(monsterPos.x - heroPoint.x + 100, monsterPos.y - heroPoint.y + 100);
	if (monsterPos.x == 1)
		v = Vec2(-1, 0.26);
	if (monsterPos.x == -1)
		v = Vec2(1, 0.26);
	v.normalize();
	v *= 2000;
	auto actionMove = MoveTo::create(2.5f, v);
	auto actionRemove = RemoveSelf::create();
	/*m_pBulletSprite->runAction(Sequence::create(actionMove, actionRemove, nullptr));*/
	m_pBulletSprite->runAction(Sequence::create(actionMove, nullptr));
}

//Vec2 curPos = this->getPosition();
//Vec2 target;
//if (this->atBattleRoom != nullptr) {
//	Boss* boss = this->atBattleRoom->getBoss();
//	if (boss != nullptr && boss->getIsKilled() == false) {
//		target = boss->getPosition() - curPos;
//		target.set(target.x / target.length(), target.y / target.length());
//		fireSpeed = target * this->weapon->getFireSpeed();
//	}
//	else {
//		Vector<Enemy*>& vecEnemy = atBattleRoom->getVecEnemy();
//		Enemy* nearNeast = nullptr;
//		float distance = 99999;
//		for (auto e : vecEnemy) {
//			if (e->getParent() != nullptr && e->getIsKilled() == false) {
//				Vec2 enemyPos = e->getPosition();
//				if (enemyPos.distance(curPos) < distance) {
//					nearNeast = e;
//					distance = enemyPos.distance(curPos);
//				}
//			}
//		}
//		if (nearNeast != nullptr) {
//			target = nearNeast->getPosition() - curPos;
//			target.set(target.x / target.length(), target.y / target.length());
//			fireSpeed = target * this->weapon->getFireSpeed();
//		}
//	}
//}