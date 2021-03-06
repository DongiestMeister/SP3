#ifndef GUI_H
#define GUI_H

#include "Vector2.h"
#include <string>
#include "GUIManager.h"

using std::string;

class GUI
{
public:
	GUI(string s = "");
	~GUI();

	GEOMETRY_TYPE meshID;

	Vector3 meshOffset;
	Vector3 rotation;
	Vector3 scale;

	bool b_isActive;

	Vector3 position; // Position of GUI on screen (x : 0 to 80, y :0 to 60)
	Vector2 buttonSize; // Button size
	Vector3 textOffset;

	void SetText(string s);
	string GetText();

	Vector3 textColor;

	void SetTextSize(float size);
	float GetTextSize();

	bool b_buttonActive; // Can it be clicked
	bool b_textActive; // Display text

	int m_sceneID;

	int functionID; // To check what function will run on click

	bool b_lightEnabled;
	void SetParent(GUI* parent);
	GUI* GetParent();
private:
	GUI* parent;
	string Text;
	float f_textSize;
};

#endif