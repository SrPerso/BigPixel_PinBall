#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
struct Object {

	SDL_Rect section;
	PhysBody* body;
	uint fx;

	Object() : body(NULL) {}
};
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

	void MasterCreator();
	void AnimationsCreator();
	void LosCondition();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;	

	PhysBody* sensor;
	PhysBody* sensor_ball;	

	PhysBody*_puller;
	PhysBody*_pullerB;

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
	PhysBody* __26_girl;//sensor
	PhysBody* __27_yellow;//sensor
	PhysBody* ball_sensor_stop;

	//SENSOR BALLAS
	//PhysBody* sensor_ball;

	//

	PhysBody* __background;
	PhysBody*  __tubetop;
	PhysBody*  __tubebottom;

	bool Game_over=false;
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
	SDL_Texture* spritesheet;
	SDL_Texture* background;
	SDL_Texture* background2;
	SDL_Texture* ball_texture;
	SDL_Texture* _red_shadow;
	SDL_Texture* fliper_down_left;
	SDL_Texture* fliper_down_right;
	SDL_Texture* fliper_down_left2;
	SDL_Texture* fliper_down_right2;
	SDL_Texture* puller_txt;
	SDL_Texture* Game_Over;
	
	int angle;
	//
	//AUDIO----
	uint hitWall_fx;
	uint bird_fx;
	uint game_bso;
	uint dead_fx;
	uint gg_fx;
	uint bird_fx2;
	uint combo_balls;
	uint combo_balls_release;
	uint pull_fx;
	uint throw_pull_fx;
	uint black_fx;
	uint kicker_left;
	uint kicker_right;
	//--------


	p2Point<int> ray;
	bool ray_on;
	bool destroyed = false;
	bool combodone = false;

	ModulePhysics* pointer = nullptr;

	int ballx;
	int bally;
	int ball2x;
	int ball2y;
	int ball3x;
	int ball3y;
	int clicker1x;
	int clicker1y;

	//
	Object ball_obj;

	Object leftkicker1;
	PhysBody* leftwheel1;

	Object rightkicker1;
	PhysBody* rightwheel1;

	Object leftkicker2;
	PhysBody* leftwheel2;

	Object rightkicker2;
	PhysBody* rightwheel2;

	Object leftkicker3;
	PhysBody* leftwheel3;

	Object rightkicker3;
	PhysBody* rightwheel3;


	
};





