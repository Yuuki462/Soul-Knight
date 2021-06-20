/**
*@file   HeroUI.h
*@author Ф��
*@date   6/14/2020
*/
#ifndef _HERO_UI_H_
#define _HERO_UI_H_

#include "Player/Hero.h"

/**
*@brief Ӣ������UI
*@author Ф��
*/
class HeroUI :public Node
{
public:
	CREATE_FUNC(HeroUI)

		/**
		*@brief ����ui�������
		*@author Ф��
		*/
	void present(Hero*_hero);


	void bindhero(Hero* _hero);
	/**
	*@brief 0.1s����״̬
	*@author Ф��
	*/
	void scheduleUI(float dt);

protected:
	Sprite* m_pSprite;
	ProgressTimer* m_pHealth;
	ProgressTimer* m_pArmor;

	Label* m_pHealthMessage;
	Label* m_pArmorMessage;
	Label* m_pCoinMessage;

	Hero* m_pHero;
	int m_presentHP;
	int m_presentArmor;
	int m_presntCoin;
};

#endif // !_HERO_UI_H_

