#include "Item.h"

void Item::bindSprite(Sprite* pSprite)
{
    m_pSprite = pSprite;
    this->addChild(m_pSprite);
}

Sprite* Item::getSprite()
{
    return m_pSprite;
}

ui::Scale9Sprite* Item::showInformation(const std::string& message)
{
	auto board = ui::Scale9Sprite::create("interface/voidboard.png");
	board->retain();
	board->setContentSize(Size(message.size() * 5.0f, 40.0f));

	auto setInformation = Label::createWithTTF(message, "Font/IRANYekanBold.ttf", 20.);
	const Vec2 informationPosition = { message.size() * 2.5f,25.0f };

	setInformation->setPosition(informationPosition);
	board->addChild(setInformation, 3);

	return board;
}

void Item::remove()
{
	m_pSprite->removeFromParentAndCleanup(true);
}

void Item::changeSprite(Sprite* _sprite)
{
	m_pSprite = _sprite;
}

void Item::setInformationUnvisible()
{
	m_pInformation->setVisible(false);
}
