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

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	ModulePlayer* Player;
	

	PhysBody* sensor;
	PhysBody* sensor_ball;


	PhysBody* ball;
	PhysBody* ball2;
	PhysBody* ball3;


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

	PhysBody* __background;
	PhysBody*  __tubetop;
	PhysBody*  __tubebottom;

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
	
	
	

	bool sensed;
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
	SDL_Texture* ball_texture;
	
	SDL_Texture* spritesheet;
	SDL_Texture* background2;
	SDL_Texture* background;
	SDL_Texture* _red_shadow;
	SDL_Texture* fliper_down_left;


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
	int clicker1x;
	int clicker1y;

	//
	Object ball_obj;

	Object leftkicker1;
	PhysBody* leftwheel1;

	Object rightkicker1;
	PhysBody* rightwheel1;

	Object leftkicker2;
	PhysBody* leftwhee21;

	Object rightkicker2;
	PhysBody* rightwheel2;


	/*SDL_Rect GetSpriteCood(PhysBody* object);
	SDL_Rect GetSpritefxCood(PhysBody* object);*/

};


/*


int _1_grey[22] = {
	261, 136,
	255, 141,
	253, 149,
	255, 155,
	260, 160,
	267, 162,
	275, 159,
	279, 153,
	279, 145,
	274, 138,
	267, 135
};



//--
int _2_orange[26] = {
	361, 68,
	352, 77,
	349, 87,
	350, 99,
	358, 109,
	368, 113,
	380, 113,
	389, 107,
	395, 98,
	396, 86,
	391, 76,
	383, 68,
	373, 66
};


//--

int _3_grey[24] = {
	412, 82,
	416, 88,
	421, 91,
	428, 91,
	434, 88,
	438, 81,
	438, 75,
	435, 69,
	429, 65,
	420, 65,
	414, 69,
	411, 75
};


//
int _4_orange[24] = {
	454, 94,
	460, 106,
	469, 113,
	482, 114,
	494, 107,
	500, 96,
	500, 85,
	493, 73,
	483, 67,
	470, 67,
	460, 73,
	454, 83
};

//

int _5_grey[24] = {
	338, 136,
	336, 142,
	336, 150,
	339, 155,
	344, 158,
	352, 158,
	358, 154,
	361, 149,
	361, 142,
	357, 135,
	351, 132,
	343, 132
};

//
int _6_black[24] = {
	398, 133,
	398, 158,
	401, 163,
	406, 167,
	428, 167,
	435, 163,
	453, 163,
	454, 150,
	447, 149,
	447, 124,
	442, 117,
	416, 116
};


//

int _7_grey[24] = {
	471, 151,
	475, 156,
	480, 158,
	486, 158,
	492, 155,
	495, 150,
	496, 144,
	494, 137,
	489, 133,
	480, 132,
	473, 136,
	470, 143
};

//
int _8_grey[24] = {
	504, 256,
	509, 261,
	516, 263,
	522, 261,
	527, 257,
	529, 252,
	529, 245,
	524, 239,
	518, 236,
	510, 237,
	505, 241,
	503, 248
};

//

int _9_orange[28] = {
	121, 243,
	119, 250,
	120, 261,
	126, 270,
	135, 277,
	146, 278,
	154, 275,
	162, 269,
	166, 259,
	165, 246,
	159, 237,
	151, 231,
	140, 230,
	130, 234
};

//

int _10_grey[24] = {
	128, 288,
	122, 290,
	119, 295,
	118, 302,
	121, 309,
	126, 313,
	134, 313,
	141, 310,
	144, 304,
	144, 297,
	141, 291,
	135, 288
};

//
int _11_orange[32] = {
	470, 292,
	470, 301,
	472, 309,
	478, 315,
	486, 320,
	497, 321,
	506, 317,
	513, 311,
	516, 303,
	517, 293,
	513, 284,
	506, 278,
	499, 274,
	488, 274,
	479, 278,
	474, 283
};

//
int _12_black[26] = {
	272, 320,
	272, 344,
	275, 349,
	280, 353,
	304, 353,
	310, 350,
	327, 350,
	327, 335,
	321, 335,
	321, 311,
	319, 306,
	314, 304,
	290, 304
};


//
int _13_orange[26] = {
	121, 370,
	132, 370,
	142, 367,
	149, 359,
	151, 349,
	149, 336,
	141, 327,
	131, 324,
	118, 325,
	109, 332,
	104, 345,
	107, 358,
	113, 364
};

//
int _14_orange[26] = {
	104, 389,
	105, 403,
	111, 412,
	121, 418,
	133, 419,
	142, 413,
	150, 405,
	151, 393,
	148, 383,
	140, 375,
	130, 372,
	120, 373,
	110, 380
};

//
int _15_green[30] = {
	461, 413,
	476, 413,
	490, 407,
	502, 394,
	505, 379,
	504, 365,
	495, 352,
	483, 345,
	471, 342,
	457, 344,
	445, 352,
	437, 362,
	435, 376,
	436, 392,
	445, 405
};

//
int _16_green[34] = {
	324, 537,
	337, 536,
	347, 531,
	357, 520,
	360, 507,
	360, 494,
	355, 481,
	343, 471,
	329, 467,
	315, 468,
	303, 474,
	294, 484,
	290, 498,
	292, 514,
	296, 523,
	305, 532,
	313, 536
};

//
int _17_orange[22] = {
	487, 526,
	499, 526,
	509, 520,
	516, 510,
	516, 496,
	509, 486,
	495, 480,
	480, 484,
	472, 495,
	472, 509,
	477, 519
};

//
int _18_orange[26] = {
	137, 604,
	147, 604,
	157, 599,
	164, 590,
	166, 580,
	162, 569,
	153, 560,
	140, 557,
	128, 561,
	121, 569,
	118, 581,
	122, 594,
	128, 600
};

//
int _19_pink[32] = {
	258, 646,
	288, 646,
	296, 641,
	312, 640,
	313, 625,
	307, 625,
	306, 597,
	300, 588,
	268, 587,
	250, 602,
	251, 611,
	245, 615,
	246, 622,
	251, 625,
	250, 636,
	252, 642
};



int _20_yellow[32] = {
	129, 650,
	128, 662,
	131, 668,
	137, 670,
	168, 671,
	174, 666,
	192, 666,
	193, 651,
	186, 649,
	186, 622,
	179, 613,
	147, 613,
	130, 627,
	130, 638,
	126, 640,
	126, 646
};


//

int _21_red[30] = {
	383, 675,
	415, 676,
	422, 671,
	438, 670,
	439, 656,
	432, 655,
	433, 626,
	427, 619,
	395, 619,
	377, 634,
	376, 644,
	373, 646,
	373, 651,
	378, 655,
	378, 668
};




//
int _22_boy[50] = {
	64, 847,
	79, 845,
	93, 844,
	95, 839,
	107, 835,
	105, 824,
	105, 816,
	99, 811,
	101, 805,
	96, 791,
	89, 792,
	79, 780,
	58, 783,
	55, 791,
	51, 796,
	54, 805,
	50, 810,
	51, 816,
	47, 821,
	46, 827,
	49, 831,
	55, 833,
	59, 829,
	59, 839,
	64, 839
};


//
int _23_blue[32] = {
	190, 835,
	221, 836,
	228, 830,
	244, 829,
	245, 814,
	239, 813,
	239, 786,
	232, 779,
	199, 779,
	183, 794,
	183, 803,
	179, 805,
	178, 812,
	183, 816,
	183, 826,
	185, 833
};

int _24_green_xp[32] = {
	308, 835,
	340, 835,
	346, 830,
	363, 828,
	364, 813,
	357, 812,
	357, 785,
	352, 777,
	317, 776,
	300, 793,
	300, 801,
	295, 805,
	295, 811,
	300, 815,
	300, 825,
	301, 831
};



int _25_grey[18] = {
	473, 778,
	481, 778,
	489, 771,
	489, 761,
	484, 754,
	476, 752,
	467, 756,
	464, 763,
	466, 772
};

//

int _26_girl[42] = {
453, 844,
454, 851,
463, 851,
468, 846,
482, 847,
486, 827,
481, 817,
483, 798,
476, 783,
464, 778,
449, 779,
436, 793,
434, 810,
428, 812,
426, 821,
435, 829,
439, 837,
438, 845,
442, 849,
448, 848,
453, 844
};

int _27_yellow[32] = {
	250, 945,
	281, 946,
	287, 940,
	304, 940,
	305, 924,
	298, 923,
	297, 893,
	291, 887,
	258, 886,
	241, 903,
	242, 910,
	237, 913,
	236, 920,
	242, 924,
	241, 936,
	244, 943
};*/