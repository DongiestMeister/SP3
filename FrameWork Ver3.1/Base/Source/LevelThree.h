#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "TurntableCam.h"
#include "TileMap.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include <vector>
#include "Terrain.h"
#include "OrthoCamera.h"
#include "WaveManager.h"
#include "CursorControl.h"
#include "ArrowTower.h"
#include "CannonTower.h"

using std::vector;

class LevelThree : public Scene
{

public:
	LevelThree();
	~LevelThree();

	virtual void Init();
	virtual void Init2();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();



private:
	//Camera3 camera;
	//TurntableCam turntab;
	OrthoCamera camera;

	Renderable grass;
	Renderable testball;

	TileMap testMap;
	CursorControl cursor;

	bool bLightEnabled;
	Vector3 distance;
	float angle;
	float fps;

	Terrain terrain;

	vector<Tower*> towerList;
};

#endif