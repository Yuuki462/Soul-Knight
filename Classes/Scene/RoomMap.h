#ifndef _ROOMMAP_H_
#define _ROOMMAP_H_

#include "cocos2d.h"
#include "Player/Hero.h"
#include <iostream>
USING_NS_CC;
class RoomMap :public Scene
{
public:
	RoomMap(TMXTiledMap* map) : m_pMap(map) { };

	static Scene* createScene(TMXTiledMap* map);

	bool init() override;

	static RoomMap* create(TMXTiledMap* map);


	

	static TMXTiledMap* createTiled(int mapNumber);

	static int m_mapNumber;

protected:
	TMXTiledMap* m_pMap;
	bool ifDoor;

};
#endif