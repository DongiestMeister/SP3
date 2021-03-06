#ifndef GAMEPLAY_CAM_H
#define GAMEPLAY_CAM_H

#include "Camera3.h"


class GameplayCam : public Camera3
{
public:

	GameplayCam();
	~GameplayCam();

	/*cameratype
		0 = locked camera
		1 = Pan Camera
		2 = Auto turn camera (display new towers / enemies)
	*/
	virtual void Init(const Vector3& pos, const Vector3& target, Vector3& up, int cameratype);
	virtual void Update(double dt);
	virtual void Reset();

	//turntable camera
	void TurnTable(float cam_spd, double dt, Vector3& targetpos);

	//Gameplay panning camera
	void PanCamera(float cam_spd, double dt);

	//void ZoomInCam()
	bool showcase_intro;
	//void ShowcaseIntro();

private:
	int cameratype_no;
	
	
	bool leftright;	// false = left,  true = right
	float turnSpeed_Mod;

	bool started;


};





#endif




