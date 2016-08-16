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


Assignment::Assignment(int sceneID) :Scene(sceneID)
{
}

Assignment::~Assignment()
{
}

void Assignment::Init()
{
	testMap.LoadMap(std::fstream("Image//MapDesign.csv"));
	//this->m_sceneID = 1;
	
	testEnemy.nxtTile = testMap.root;
	testEnemy.pos.Set(testMap.root->coords.x, testMap.root->coords.y, 0);
	testEnemy.meshID = GEO_CONE;

	Node* currentNode = testMap.root;
	while (currentNode != nullptr)
	{
		std::cout << currentNode->coords.x << "," << currentNode->coords.y << std::endl;
		currentNode = currentNode->next;

	}
	
	//testball.meshID = GEO_SPHERE;
	testball.pos.Set(0, 10, 0);
	testball.scale.Set(1, 1, 1);

	
	camera.Init(Vector3(testMap.i_columns / 2, testMap.i_rows / 2 - 5, 10), Vector3(testMap.i_columns / 2, testMap.i_rows / 2, 0), Vector3(0, 1, 0));

	//camera.Init(Vector3(0,-5,10), Vector3(0,0,0), Vector3(0, 1, 0));
	camera.b_ortho = true;
	camera.orthoSize = (testMap.i_rows/2) + 1;
	camera.aspectRatio.Set(4 , 3);
	RenderManager::GetInstance()->SetCamera(&camera);

	grass.meshID = GEO_GRASS_DARKGREEN;
	grass.pos.Set(testMap.i_columns / 2, testMap.i_rows / 2, 0);
	grass.scale.Set(camera.orthoSize * (camera.aspectRatio.x / camera.aspectRatio.y) * 2, camera.orthoSize * 2.5, 1);
	grass.rotation.Set(0, 0, 0);
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
	

	if (Application::IsKeyPressed('N'))
	{
		//glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		SceneManager::GetInstance()->ChangeScene(2, true);
	}

	
	fps = (float)(1.f / dt);


	camera.Update(dt);
	RenderManager::GetInstance()->SetCamera(&camera);
}

void Assignment::Render()
{
	//RenderManager::GetInstance()->RenderMesh(GEO_CONE, Vector3(2,2,0), Vector3(0.1, 0.1, 0.1), Vector3(90, 0, 0), false, false);

	Node* currentNode = testMap.root;
	while (currentNode != nullptr)
	{
		RenderManager::GetInstance()->RenderMesh(GEO_SPHERE, Vector3(currentNode->coords.x * testMap.i_tileSize, currentNode->coords.y  * testMap.i_tileSize, 0), Vector3(0.5, 0.5, 0.5), Vector3(0, 0, 0), false, false);
		currentNode = currentNode->next;
		
	}

	double x, y;
	Application::GetCursorPos(&x, &y);
	float w = Application::GetWindowWidth();
	float h = Application::GetWindowHeight();

	float worldX = x / w * 100;
	float worldY = (h - y) / h * 100 * (camera.aspectRatio.y / camera.aspectRatio.x); // 0.05 = 1 unit

	int selectedUnitX = Math::Clamp((worldX - 15.f) / 5.35f,0.f,(float)testMap.i_columns - 1);
	int selectedUnitY = Math::Clamp((worldY - 2.75f) / 5.25f, 0.f, (float)testMap.i_rows - 1);

	std::cout << worldX << "," << worldY << std::endl;

	RenderManager::GetInstance()->RenderMesh(GEO_CONE, Vector3(selectedUnitX, selectedUnitY, 0), Vector3(0.1, 0.1, 0.1), Vector3(90, 0, 0), false, false);

	for (int i = 0; i < testMap.i_rows; ++i) // y - axis
	{
		for (int j = 0; j < testMap.i_columns; ++j) // x - axis
		{
			if (testMap.screenMap[j][i] == 0)
			{
				RenderManager::GetInstance()->RenderMesh(GEO_CUBE, Vector3(j * testMap.i_tileSize, i  * testMap.i_tileSize, 0), Vector3(1, 1, 1), Vector3(0, 0, 0), true, false);
			}
		}
	}
}

void Assignment::Exit()
{
	//clean Up scene Variables
	
}
