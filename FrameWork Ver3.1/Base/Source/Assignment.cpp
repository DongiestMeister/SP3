#include "Assignment.h"
#include "GL\glew.h"
#include "LoadHmap.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "SceneManager.h"


Assignment::Assignment():Scene()
{
}

Assignment::~Assignment()
{
}

void Assignment::Init()
{
	testMap.LoadMap(std::fstream("Image//MapDesign.csv"));
	//this->m_sceneID = 1;

	wave.SetRoot(testMap.root);
	wave.AddWave({ MINION }, 0, 1);
	wave.AddWave({ MINION,MINION }, 5, 2);
	wave.AddWave({ MINION }, 100, 4);
	wave.AddWave({ MINION }, 100, 4);
	wave.AddWave({ MINION }, 100, 4);
	wave.AddWave({ MINION }, 100, 4);
	wave.AddWave({ MINION }, 100, 4);
	wave.AddWave({ MINION }, 100, 4);

	wave.player = &(this->player);

	Node* currentNode = testMap.root;
	while (currentNode != nullptr)
	{
		std::cout << currentNode->coords.x << "," << currentNode->coords.y << std::endl;
		currentNode = currentNode->next;

	}


	camera.Init(Vector3((float)testMap.i_columns / 2.f, (float)testMap.i_rows / 2.f, 10.f), Vector3((float)testMap.i_columns / 2.f, (float)testMap.i_rows / 2.f, 0.f), Vector3(0, 1, 0), 30.f);

	//camera.Init(Vector3(0,-5,10), Vector3(0,0,0), Vector3(0, 1, 0));
	camera.b_ortho = true;
	camera.orthoSize = (testMap.i_rows / 2) + 1;
	camera.aspectRatio.Set(4, 3);
	RenderManager::GetInstance()->SetCamera(&camera);

	grass.meshID = GEO_GRASS_DARKGREEN;
	grass.pos.Set(testMap.i_columns / 2, testMap.i_rows / 2, 0);
	grass.scale.Set(camera.orthoSize * (camera.aspectRatio.x / camera.aspectRatio.y) * 2, camera.orthoSize * 2.5, 1);
	grass.rotation.Set(0, 0, 0);

	cursor.Init(&towerList,wave.GetEnemyList());
}

void Assignment::Update(double dt)
{
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//if (Application::IsKeyPressed('9'))
	//{
	//	ATower.upgrade = true;
	//}

	if (Application::IsKeyPressed('N'))
	{
		//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		SceneManager::GetInstance()->ChangeScene(3, true);
	}

	wave.Update(dt);
	fps = (float)(1.f / dt);

	cursor.Update(camera, testMap);
	camera.Update(dt);
	RenderManager::GetInstance()->SetCamera(&camera);

	
}

void Assignment::Render()
{


	RenderManager::GetInstance()->RenderMesh(GEO_CONE, Vector3(cursor.checkPositionX, cursor.checkPositionY, 0), Vector3(1.5f, 1.5f, 1.5f), Vector3(90, 0, 0), false, false);

	for (int i = 0; i < testMap.i_rows; ++i) // y - axis
	{
		for (int j = 0; j < testMap.i_columns; ++j) // x - axis
		{
			if (testMap.screenMap[j][i] == -2)
			{
				RenderManager::GetInstance()->RenderMesh(GEO_CUBE2, Vector3(j * testMap.i_tileSize, i  * testMap.i_tileSize, 0), Vector3(1, 1, 1), Vector3(0, -90, 0), true, false);
			}
			else if (testMap.screenMap[j][i] == -1)
			{
				RenderManager::GetInstance()->RenderMesh(GEO_PATH, Vector3(j * testMap.i_tileSize, i  * testMap.i_tileSize, 0.1), Vector3(1, 1, 1), Vector3(0, 0, 0), true, false);
			}
		}
	}

	Tower* tower = cursor.FindTower(cursor.checkPositionX, cursor.checkPositionY);

	if (tower != nullptr)
	{
		RenderManager::GetInstance()->RenderTextOnScreen(tower->s_name, Color(1, 1, 1), 3, 40 - tower->s_name.size()/2.f, 55);
	}


	

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderManager::GetInstance()->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 3, 0, 9);
	
	ss.str("");
	ss.precision(5);
	ss << "Health left: " << player.i_health;
	RenderManager::GetInstance()->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 3, 0, 3);

	ss.str("");
	ss.precision(5);
	ss << "Currency: " << player.i_currency;
	RenderManager::GetInstance()->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 3, 0, 6);
}

void Assignment::Exit()
{
	//clean Up scene Variables
	for (vector<Tower*>::iterator it = towerList.begin(); it != towerList.end(); ++it)
	{
		if (*it != nullptr)
		{
			delete *it;
		}
	}
	towerList.clear();
}