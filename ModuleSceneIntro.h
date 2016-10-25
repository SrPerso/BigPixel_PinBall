#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	

	PhysBody* sensor;
	PhysBody* sensor_ball;
	// objects

	p2List<PhysBody*> Objects;
	PhysBody* __1_grey;
	PhysBody* __2_orange;
	PhysBody* __3_grey;
	PhysBody* __4_orange;
	PhysBody* __5_grey;
	PhysBody* __6_black;//sensor
	PhysBody* __7_grey;
	PhysBody* __8_grey;
	PhysBody* __9_orange;
	PhysBody* __10_grey;
	PhysBody* __11_orange;
	PhysBody* __12_black;//sensor
	PhysBody* __13_orange;
	PhysBody* __14_orange;
	PhysBody* __15_green;
	PhysBody* __16_green;
	PhysBody* __17_orange;
	PhysBody* __18_orange;
	PhysBody* __19_pink;//sensor
	PhysBody* __20_yellow;//sensor
	PhysBody* __21_red;//sensor
	PhysBody* __22_boy;//sensor
	PhysBody* __23_blue;//sensor
	PhysBody* __24_green_xp;//sensor
	PhysBody* __25_grey;
	//PhysBody* __26_girl;//sensor
	PhysBody* __27_yellow;//sensor
	PhysBody* ball_sensor_stop;
	//sensor balls
	//PhysBody* sensor_ball;
	int sensor_balls_stop[16] = {
		88, 133,
		105, 127,
		118, 154,
		120, 159,
		148, 144,
		154, 156,
		104, 179,
		90, 139
	};
	//
	
	
	PhysBody* __background;
	PhysBody*  __tubetop;
	PhysBody*  __tubebottom;

	bool sensed;
	PhysBody *ball;
	PhysBody *ball2;
	PhysBody *ball3;
	bool isball1=false;
	bool isball2=false;
	bool collisioned = false;
	bool sensored = false;
	bool one = false;
	bool ball_2 = false;
	bool ball_3 = false;
	//bool sensorss = false;

	uint LastTime = 0, CurrentTime;

	//TITLE
	uint score, ball_points;
	char* title;

	bool forced = false;
	
	//back
	SDL_Texture* background;
	SDL_Texture* background2;
	SDL_Texture* ball_texture;
	//
	//audio
	uint hitWall_fx;
	uint bird_fx;
	uint game_bso;
	uint dead_fx;
	uint gg_fx;
	uint combo_balls;
	

	p2Point<int> ray;
	bool ray_on;
	bool destroyed = false;

	ModulePhysics* pointer = nullptr;

	int ballx;
	int bally;
	int ball2x;
	int ball2y;

	int ball3x;
	int ball3y;



	
};





