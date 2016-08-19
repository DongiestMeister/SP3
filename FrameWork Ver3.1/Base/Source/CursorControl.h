#ifndef CURSORCONTROL_H
#define CURSORCONTROL_H

#include "OrthoCamera.h"
#include "TileMap.h"
#include "Tower.h"
#include "MatrixStack.h"
#include "RenderManager.h"
#include "GUI.h"

class CursorControl
{
public:
	CursorControl();
	~CursorControl();
	void Init(vector<Tower*> *towerList, vector<Enemy*> *enemyList);
	void Update(OrthoCamera &camera, const TileMap &tileMap, const double &dt);
	int checkPositionX, checkPositionY;
	Vector3 worldCoords;
	bool SpawnTower(string name);
	Tower* FindTower(int x,int y);
	

	GUI* spawnTower[4];

	vector<Tower*> *towerList;
	vector<Enemy*> *enemyList;
private:
	void TowerButtons(float worldX,float worldY);
	void EdgePanning(const double &dt, OrthoCamera &camera, float worldX, float worldY);
};

#endif