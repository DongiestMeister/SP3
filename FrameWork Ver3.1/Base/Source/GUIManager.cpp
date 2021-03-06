#include "GUIManager.h"
#include "GUI.h"

GUIManager* GUIManager::instance = nullptr;

GUIManager::GUIManager()
{
	m_currentSceneID = 1;
	list<GUI*> temp;
	GUIList.push_back(temp);
}

GUIManager::~GUIManager()
{

}

GUIManager* GUIManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GUIManager();
	}
	return instance;
}

void GUIManager::AddGUI(GUI* gui)
{
	gui->m_sceneID = this->m_currentSceneID;

	if (m_currentSceneID >= GUIList.size())
	{
		list<GUI*> temp;
		GUIList.push_back(temp);
		AddGUI(gui);
		return;
	}
	this->GUIList[m_currentSceneID].push_back(gui);
}

void GUIManager::RemoveGUI(GUI* gui)
{
	this->GUIList[gui->m_sceneID].remove(gui);
}

void GUIManager::RenderAllGUI(int sceneID)
{
	if (sceneID >= GUIList.size())
	{
		return;
	}

	// Render twice because mesh will be behind text ( render order issues )

	for (list<GUI*>::iterator it = GUIList[sceneID].begin(); it != GUIList[sceneID].end(); ++it)
	{
		GUI* gui = *it;
		if (gui->b_isActive)
		{
			Vector3 offset(0, 0, 0);
			if (gui->GetParent() != nullptr)
			{
				offset = gui->GetParent()->position;
			}
			if (gui->meshID != GEO_NULL)
			{
				RenderManager::GetInstance()->RenderMeshOnScreen(gui->meshID, gui->b_lightEnabled, Vector3(gui->position.x + gui->meshOffset.x, gui->position.y + gui->meshOffset.y, gui->position.z + gui->meshOffset.z) + offset, gui->scale, gui->rotation);
			}
		}
	}

	for (list<GUI*>::iterator it = GUIList[sceneID].begin(); it != GUIList[sceneID].end(); ++it)
	{
		GUI* gui = *it;
		if (gui->b_isActive)
		{
			Vector3 offset(0,0,0);
			if (gui->GetParent() != nullptr)
			{
				offset = gui->GetParent()->position;
			}
			if (gui->b_textActive)
			{
				RenderManager::GetInstance()->RenderTextOnScreen(gui->GetText(), Color(gui->textColor.x, gui->textColor.y, gui->textColor.z), gui->GetTextSize(), gui->position.x + gui->textOffset.x + offset.x, gui->position.y + gui->textOffset.y + offset.y,gui->position.z + gui->textOffset.z + offset.z);
			}
		}
	}
}

GUI* GUIManager::FindGUI(float screenX, float screenY)
{
	for (list<GUI*>::iterator it = GUIList[m_currentSceneID].begin(); it != GUIList[m_currentSceneID].end(); ++it)
	{
		GUI* gui = *it;
		if (gui->b_buttonActive && gui->b_isActive)
		{
			float guiPosX = gui->position.x / 80 - 0.5f;
			float guiPosY = gui->position.y / 60 - 0.5f;
			float guiButtonSizeX = gui->buttonSize.x / 80;
			float guiButtonSizeY = gui->buttonSize.y / 60;

			if (screenX >= guiPosX && screenX <= guiPosX + guiButtonSizeX
				&& screenY >= guiPosY && screenY <= guiPosY + guiButtonSizeY)
			{
				return gui;
			}
		}
	}
	return nullptr;
}