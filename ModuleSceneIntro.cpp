#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Balls to test
	ball = App->physics->CreateCircle(525, 900, 10, 0.5f, true ,b2_dynamicBody);
	ball->listener = this;
	//LEFT KICKER:
	b2Vec2 left_kicker_cods[8];
	left_kicker_cods[0].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
	left_kicker_cods[1].Set(PIXEL_TO_METERS(6), PIXEL_TO_METERS(-5));//y--
	left_kicker_cods[2].Set(PIXEL_TO_METERS(18), PIXEL_TO_METERS(-5));//y-
	left_kicker_cods[3].Set(PIXEL_TO_METERS(59), PIXEL_TO_METERS(35));
	left_kicker_cods[4].Set(PIXEL_TO_METERS(57), PIXEL_TO_METERS(45));
	left_kicker_cods[5].Set(PIXEL_TO_METERS(44), PIXEL_TO_METERS(44));//y--
	left_kicker_cods[6].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(19));
	left_kicker_cods[7].Set(PIXEL_TO_METERS(-3), PIXEL_TO_METERS(9));

	leftkicker1.body = App->physics->CreatePolygon(left_kicker_cods, 8, b2_dynamicBody, 180,950, 0.5f);
	leftwheel1 = App->physics->CreateCircle(198, 978, 9, 0, false, b2_staticBody);
	App->physics->CreateRevoluteJoint(leftkicker1.body->body, leftwheel1->body, 45, -5, 13, 10);

	//RIGHT KICKER:
	b2Vec2 right_kicker_cods[8];
	right_kicker_cods[0].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
	right_kicker_cods[1].Set(PIXEL_TO_METERS(-6), PIXEL_TO_METERS(-5));//y--
	right_kicker_cods[2].Set(PIXEL_TO_METERS(-18), PIXEL_TO_METERS(-5));//y-
	right_kicker_cods[3].Set(PIXEL_TO_METERS(-59), PIXEL_TO_METERS(35));
	right_kicker_cods[4].Set(PIXEL_TO_METERS(-57), PIXEL_TO_METERS(45));
	right_kicker_cods[5].Set(PIXEL_TO_METERS(-44), PIXEL_TO_METERS(44));//y--
	right_kicker_cods[6].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(19));
	right_kicker_cods[7].Set(PIXEL_TO_METERS(+3), PIXEL_TO_METERS(9));	

	rightkicker1.body = App->physics->CreatePolygon(right_kicker_cods, 8, b2_dynamicBody, 330, 950, 0.5f);
	rightwheel1 = App->physics->CreateCircle(333, 975, 9, 0, false, b2_staticBody);
	App->physics->CreateRevoluteJoint(rightkicker1.body->body, rightwheel1->body, 5,-43, -13, 10);
	
	//MEDIUM KICKER LEFT:
	b2Vec2 left_kicker_cods2[6];
	left_kicker_cods2[0].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
	left_kicker_cods2[1].Set(PIXEL_TO_METERS(7), PIXEL_TO_METERS(-9));//y--
	left_kicker_cods2[2].Set(PIXEL_TO_METERS(51), PIXEL_TO_METERS(-4));//y-
	left_kicker_cods2[3].Set(PIXEL_TO_METERS(53), PIXEL_TO_METERS(1));
	left_kicker_cods2[4].Set(PIXEL_TO_METERS(49), PIXEL_TO_METERS(6));
	left_kicker_cods2[5].Set(PIXEL_TO_METERS(7), PIXEL_TO_METERS(11));//y--

	leftkicker2.body = App->physics->CreatePolygon(left_kicker_cods2, 6, b2_dynamicBody, 116, 482, 0.5f);
	leftwheel2 = App->physics->CreateCircle(120, 492, 5, 0, false, b2_staticBody);
	App->physics->CreateRevoluteJoint(leftkicker2.body->body, leftwheel2->body, 1, -70, 10,3);

	//MEDIUM KICKER RIGHT:
	b2Vec2 right_kicker_cods2[6];
	right_kicker_cods2[0].Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));
	right_kicker_cods2[1].Set(PIXEL_TO_METERS(-7), PIXEL_TO_METERS(-9));//y--
	right_kicker_cods2[2].Set(PIXEL_TO_METERS(-51), PIXEL_TO_METERS(-4));//y-
	right_kicker_cods2[3].Set(PIXEL_TO_METERS(-53), PIXEL_TO_METERS(1));
	right_kicker_cods2[4].Set(PIXEL_TO_METERS(-49), PIXEL_TO_METERS(6));
	right_kicker_cods2[5].Set(PIXEL_TO_METERS(-7), PIXEL_TO_METERS(11));//y--

	rightkicker2.body = App->physics->CreatePolygon(right_kicker_cods2, 6, b2_dynamicBody, 497, 603, 0.5f);
	rightwheel2 = App->physics->CreateCircle(497, 610, 6, 0, false, b2_staticBody);
	App->physics->CreateRevoluteJoint(rightkicker2.body->body, rightwheel2->body,45, -5, -10, 3);
	
	 //Map:
	//OBSTACLES:-----------------------------------------------------------
	
	//--
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
	/*
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
	*/
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
	};

	//BACKGROUND-------------------------------------------------------
	int _background[150] = {
		42, 121,
		44, 580,
		46, 595,
		51, 606,
		64, 627,
		72, 638,
		73, 737,
		69, 741,
		61, 742,
		57, 732,
		53, 737,
		35, 736,
		35, 949,
		92, 978,
		166, 1018,
		182, 1035,
		0, 1035,
		0, 0,
		551, 0,
		552, 1034,
		535, 1034,
		535, 768,
		531, 747,
		523, 725,
		508, 697,
		493, 680,
		473, 664,
		465, 657,
		471, 644,
		486, 644,
		493, 642,
		511, 605,
		498, 598,
		495, 596,
		495, 593,
		536, 517,
		535, 209,
		529, 208,
		498, 229,
		490, 229,
		481, 217,
		483, 211,
		520, 190,
		529, 176,
		536, 173,
		536, 86,
		534, 79,
		529, 83,
		480, 40,
		484, 30,
		375, 30,
		316, 80,
		310, 80,
		308, 163,
		300, 169,
		289, 166,
		286, 159,
		280, 146,
		241, 122,
		237, 118,
		233, 120,
		229, 117,
		228, 101,
		224, 85,
		213, 66,
		198, 53,
		182, 44,
		160, 35,
		141, 32,
		120, 33,
		100, 38,
		82, 48,
		68, 59,
		55, 74,
		44, 106
	};



	//TUBES:
	//TOP:
	int _tubetop[98] = {
		74, 116,
		76, 101,
		85, 86,
		107, 67,
		129, 60,
		150, 63,
		164, 74,
		181, 99,
		187, 118,
		183, 125,
		178, 125,
		172, 136,
		162, 149,
		162, 155,
		166, 163,
		163, 167,
		123, 107,
		90, 117,
		120, 189,
		115, 194,
		112, 197,
		112, 204,
		95, 262,
		90, 265,
		86, 268,
		88, 413,
		118, 469,
		118, 473,
		116, 478,
		102, 485,
		119, 517,
		122, 524,
		119, 530,
		89, 575,
		89, 591,
		101, 606,
		111, 621,
		113, 627,
		115, 737,
		112, 741,
		108, 741,
		105, 738,
		105, 732,
		106, 632,
		103, 623,
		80, 593,
		80, 586,
		78, 396,
		74, 121
	};

	
	//BOTTOM:
	int _tubebottom[66] = {
		440, 696,
		442, 691,
		445, 684,
		448, 678,
		468, 689,
		472, 692,
		478, 697,
		484, 704,
		488, 709,
		493, 717,
		498, 725,
		502, 733,
		505, 741,
		508, 748,
		510, 755,
		511, 764,
		511, 784,
		511, 1034,
		350, 1034,
		366, 1020,
		378, 1012,
		493, 952,
		493, 787,
		493, 774,
		492, 766,
		491, 758,
		488, 748,
		485, 740,
		479, 730,
		473, 722,
		467, 715,
		458, 706,
		448, 702
	};

	//COMBO BALLS SENSOR
	int sensor_balls[6] = {
		87, 127,
		87,126,
		130, 108
	};
		

	//CAMERA
	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	//LOAD TEXTURES
	background = App->textures->Load("pinball/Images/Ground/background.png");
	spritesheet = App->textures->Load("pinball/Images/sprite_sheet.png");
	background2 = App->textures->Load("pinball/Images/Ground/frontground.png");
	ball_texture= App->textures->Load("pinball/Images/Ground/ball.png");
	fliper_down_left= App->textures->Load("pinball/Images/fliper_down_left.png");
	fliper_down_right = App->textures->Load("pinball/Images/fliper_down_rigth.png");
	fliper_down_left2 = App->textures->Load("pinball/Images/fliper_middle_up_left.png");
	fliper_down_right2 = App->textures->Load("pinball/Images/fliper_middle_up_rigth.png");

	//LOAD AUDIOS
	hitWall_fx = App->audio->LoadFx("pinball/Audio/HitBallWall.wav");
	bird_fx = App->audio->LoadFx("pinball/Audio/bird_fx.wav");
	bird_fx2 = App->audio->LoadFx("pinball/Audio/bird_fx2.wav");
	dead_fx = App->audio->LoadFx("pinball/Audio/dead_fx.wav");
	game_bso = App->audio->LoadFx("pinball/Audio/game_bso.wav");
	gg_fx = App->audio->LoadFx("pinball/Audio/gg_circles_fx.wav");
	combo_balls = App->audio->LoadFx("pinball/Audio/Combo.wav");
	combo_balls_release = App->audio->LoadFx("pinball/Audio/Combo_Release.wav");

	//LOST CONDITION	
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	sensor_ball = App->physics->CreateChainSensor(0, 0, sensor_balls, 6);
	
	//OBJECTS
	
	__1_grey = App->physics->CreateChain(0, 0, _1_grey, 22, b2_staticBody);
	__1_grey->SetSprite(184, 176, 27, 27);
	__1_grey->SetSpritefx(25, 149, 83, 83);

	__2_orange = App->physics->CreateChain(0, 0, _2_orange, 22, b2_staticBody);//orange
	__2_orange->SetSprite(811, 94, 68, 47);
	__2_orange->SetSpritefx(902, 94, 68, 47);

	__3_grey = App->physics->CreateChain(0, 0, _3_grey, 24, b2_staticBody);
	__3_grey->SetSprite(184, 176, 27, 27);
	__3_grey->SetSpritefx(25, 149, 83, 83);

	__4_orange = App->physics->CreateChain(0, 0, _4_orange, 22, b2_staticBody);//orange
	__4_orange->SetSprite(811, 94, 68, 47);
	__4_orange->SetSpritefx(902, 94, 68, 47);


	__5_grey = App->physics->CreateChain(0, 0, _5_grey, 24, b2_staticBody);
	__5_grey->SetSprite(184, 176, 27, 27);
	__5_grey->SetSpritefx(25, 149, 83, 83);

	__6_black = App->physics->CreateChainSensor(0, 0, _6_black, 24);
	__6_black->SetSprite(7, 80, 55, 50);
	__6_black->SetSpritefx(82, 80, 57, 50);

	__7_grey = App->physics->CreateChain(0, 0, _7_grey, 24, b2_staticBody);
	__7_grey->SetSprite(184, 176, 27, 27);
	__7_grey->SetSpritefx(25, 149, 83, 83);

	__8_grey = App->physics->CreateChain(0, 0, _8_grey, 24, b2_staticBody);
	__8_grey->SetSprite(184, 176, 27, 27);
	__8_grey->SetSpritefx(25, 149, 83, 83);

	__9_orange = App->physics->CreateChain(0, 0, _9_orange, 22, b2_staticBody);//orange
	__9_orange->SetSprite(811, 94, 68, 47);
	__9_orange->SetSpritefx(902, 94, 68, 47);


	__10_grey = App->physics->CreateChain(0, 0, _10_grey, 24, b2_staticBody);
	__10_grey->SetSprite(184, 176, 27, 27);
	__10_grey->SetSpritefx(25, 149, 83, 83);

	__11_orange = App->physics->CreateChain(0, 0, _11_orange, 22, b2_staticBody);//orange
	__11_orange->SetSprite(811, 94, 68, 47);
	__11_orange->SetSpritefx(902, 94, 68, 47);

	__12_black = App->physics->CreateChainSensor(0, 0, _12_black, 26);
	__12_black->SetSprite(7, 80, 55, 50);
	__12_black->SetSpritefx(82, 80, 57, 50);

	__13_orange = App->physics->CreateChain(0, 0, _13_orange, 22, b2_staticBody);//orange
	__13_orange->SetSprite(811, 94, 68, 47);
	__13_orange->SetSpritefx(902, 94, 68, 47);

	__14_orange = App->physics->CreateChain(0, 0, _14_orange, 22, b2_staticBody);//orange
	__14_orange->SetSprite(811, 94, 68, 47);
	__14_orange->SetSpritefx(902, 94, 68, 47);


	__15_green = App->physics->CreateChain(0, 0, _15_green, 30, b2_staticBody);
	__15_green->SetSprite(556, 218, 71, 71);
	__15_green->SetSpritefx(323, 172, 149, 147);

	__16_green = App->physics->CreateChain(0, 0, _16_green, 34, b2_staticBody);
	__16_green->SetSprite(556, 218, 71, 71);
	__16_green->SetSpritefx(323, 172, 149, 147);

	__17_orange = App->physics->CreateChain(0, 0, _17_orange, 22, b2_staticBody);//orange
	__17_orange->SetSprite(811, 94, 68, 47);
	__17_orange->SetSpritefx(902, 94, 68, 47);

	__18_orange = App->physics->CreateChain(0, 0, _18_orange, 22, b2_staticBody);//orange
	__18_orange->SetSprite(811, 94, 68, 47);
	__18_orange->SetSpritefx(902, 94, 68, 47);

	__19_pink = App->physics->CreateChainSensor(0, 0, _19_pink, 32);
	__19_pink->SetSprite(15, 4, 70, 60);
	__19_pink->SetSpritefx(99, 4, 71, 59);

	__20_yellow = App->physics->CreateChainSensor(0, 0, _20_yellow, 32);
	__20_yellow->SetSprite(347, 3, 70, 61);
	__20_yellow->SetSpritefx(432, 3, 70, 61);

	__21_red = App->physics->CreateChainSensor(0, 0, _21_red, 30);
	__21_red->SetSprite(846, 4, 71, 60);
	__21_red->SetSpritefx(924, 5, 71, 61);

	__22_boy = App->physics->CreateChainSensor(0, 0, _22_boy, 50);
	__22_boy->SetSprite(508, 80, 62, 67);
	__22_boy->SetSpritefx(580, 580, 61, 67);

	__23_blue = App->physics->CreateChainSensor(0, 0, _23_blue, 32);
	__23_blue->SetSprite(685, 5, 71, 61);
	__23_blue->SetSpritefx(767, 6, 70, 61);

	__24_green_xp = App->physics->CreateChainSensor(0, 0, _24_green_xp, 32);
	__24_green_xp->SetSprite(183, 4, 71, 60);
	__24_green_xp->SetSpritefx(267, 4, 71, 60);

	__25_grey = App->physics->CreateChain(0, 0, _25_grey, 18, b2_staticBody);
	__25_grey->SetSprite(184, 176, 27, 27);
	__25_grey->SetSpritefx(25, 149, 83, 83);

	__27_yellow = App->physics->CreateChainSensor(0, 0, _27_yellow, 32);
	__27_yellow->SetSprite(516, 3, 71, 61);
	__27_yellow->SetSpritefx(600, 4, 71, 61);
	
	
	
	//BACKGROUND
	__tubebottom = App->physics->CreateChain(0, 0, _tubebottom, 66, b2_staticBody);
	__tubetop = App->physics->CreateChain(0, 0, _tubetop, 98, b2_staticBody);
	__background = App->physics->CreateChain(0, 0, _background, 150, b2_staticBody);

	//PULLER

	//--------------------------------
	int pos_x = 525; int pos_y = 1037;

	_puller = App->physics->CreateRectangle(pos_x, pos_y, 10, 100);
	_puller->body->SetType(b2_staticBody);

	_pullerB = App->physics->CreateRectangle(pos_x, pos_y+20, 50, 70);
	_puller->body->SetType(b2_staticBody);

	App->physics->CreateUpJoint(_puller, _pullerB, b2Vec2(1, 10), b2Vec2(1, -10), -40, -120, 350, 200);
	_pullerB->SetSprite(255, 160, 27, 163);
	//------------------------------------




	//sensor combo balls
	ball_sensor_stop = App->physics->CreateSensorBall(0, 0, sensor_balls_stop, 16, true);
	App->audio->PlayFx(game_bso,20);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	ball->GetPosition(ballx, bally);
	leftkicker1.body->GetPosition(clicker1x, clicker1y);
	App->renderer->Blit(background, 0, 0);

	//blit puller
	App->renderer->Blit(spritesheet, 500, METERS_TO_PIXELS(App->physics->joint->GetBodyB()->GetPosition().y) - 35, &_puller->GetSprite());



	//BLIT OF ALL TEXTURES:
	if (__1_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 253, 135, &__1_grey->GetSprite());
	else
		App->renderer->Blit(spritesheet, 253, 135, &__1_grey->GetSpritefx());

	//
	if (__3_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 413, 65, &__3_grey->GetSprite());
	else
		App->renderer->Blit(spritesheet, 413, 65, &__3_grey->GetSpritefx());

	//
	if (__5_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 335, 133, &__5_grey->GetSprite());
	else
		App->renderer->Blit(spritesheet, 335, 133, &__5_grey->GetSpritefx());

	//
	if (__6_black->IsTrodden == false)
		App->renderer->Blit(spritesheet, 398, 116, &__6_black->GetSprite());
	else
		App->renderer->Blit(spritesheet, 398, 116, &__6_black->GetSpritefx());

	//
	if (__7_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 470, 133, &__7_grey->GetSprite());
	else
		App->renderer->Blit(spritesheet, 470, 133, &__7_grey->GetSpritefx());

	//
	if (__8_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 503, 236, &__8_grey->GetSprite());
	else
		App->renderer->Blit(spritesheet, 503, 236, &__8_grey->GetSpritefx());

	//
	if (__10_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 118, 288, &__10_grey->GetSprite());
	else {
		App->renderer->Blit(spritesheet, 118, 288, &__10_grey->GetSpritefx());

		//__10_grey->IsTrodden == false;
	}

	if (__12_black->IsTrodden == false)
		App->renderer->Blit(spritesheet, 272, 304, &__12_black->GetSprite());
	else
		App->renderer->Blit(spritesheet, 272, 304, &__12_black->GetSpritefx());
	//
	if (__15_green->IsTrodden == false)
		App->renderer->Blit(spritesheet, 435, 342, &__15_green->GetSprite());

	else
		App->renderer->Blit(spritesheet, 395, 304, &__15_green->GetSpritefx());

	//
	if (__16_green->IsTrodden == false)
		App->renderer->Blit(spritesheet, 290, 468, &__16_green->GetSprite());
	else
		App->renderer->Blit(spritesheet, 250, 430, &__16_green->GetSpritefx());

	//
	if (__19_pink->IsTrodden == false)
		App->renderer->Blit(spritesheet, 245, 588, &__19_pink->GetSprite());
	else
		App->renderer->Blit(spritesheet, 245, 588, &__19_pink->GetSpritefx());

	//
	if (__20_yellow->IsTrodden == false)
		App->renderer->Blit(spritesheet, 126, 613, &__20_yellow->GetSprite());
	else
		App->renderer->Blit(spritesheet, 126, 613, &__20_yellow->GetSpritefx());

	//
	if (__21_red->IsTrodden == false)
		App->renderer->Blit(spritesheet, 373, 619, &__21_red->GetSprite());
	else
		App->renderer->Blit(spritesheet, 373, 619, &__21_red->GetSpritefx());

	//
	if (__22_boy->IsTrodden == false)
		App->renderer->Blit(spritesheet, 46, 780, &__22_boy->GetSprite());
	else
		App->renderer->Blit(spritesheet, 46, 780, &__22_boy->GetSpritefx());

	//
	if (__23_blue->IsTrodden == false)
		App->renderer->Blit(spritesheet, 178, 779, &__23_blue->GetSprite());
	else
		App->renderer->Blit(spritesheet, 178, 779, &__23_blue->GetSpritefx());

	//
	if (__24_green_xp->IsTrodden == false)
		App->renderer->Blit(spritesheet, 295, 776, &__24_green_xp->GetSprite());
	else
		App->renderer->Blit(spritesheet, 295, 776, &__24_green_xp->GetSpritefx());
	//
	if (__25_grey->IsTrodden == false)
		App->renderer->Blit(spritesheet, 466, 752, &__25_grey->GetSprite());
	else
		App->renderer->Blit(spritesheet, 466, 752, &__25_grey->GetSpritefx());


	//App->renderer->Blit(spritesheet, 434, 778, &__26_girl->GetSprite());
	App->renderer->Blit(spritesheet, 236, 886, &__27_yellow->GetSprite());

	App->renderer->Blit(spritesheet, 83, 372, &__14_orange->GetSprite(), NULL, 0);
	App->renderer->Blit(spritesheet, 100, 553, &__18_orange->GetSprite(), NULL, 40);

	int x, y;
	
	App->renderer->Blit(ball_texture, ballx, bally, NULL, 1.0f);
	App->renderer->Blit(background2, 0, 0);
	leftkicker1.body->GetPosition(x, y);
	App->renderer->Blit(fliper_down_left, x-3, y-17, NULL, 1.0f, RADTODEG *leftkicker1.body->getAngle() + 32, 0, 15);
	rightkicker1.body->GetPosition(x, y);
	App->renderer->Blit(fliper_down_right, x-75, y-17, NULL, 1.0f, RADTODEG *rightkicker1.body->getAngle() - 32, 80, 15);
	leftkicker2.body->GetPosition(x, y);
	App->renderer->Blit(fliper_down_left2, x+2, y-13, NULL, 1.0f, RADTODEG *leftkicker2.body->getAngle() -1, 0, 5);
	rightkicker2.body->GetPosition(x, y);
	App->renderer->Blit(fliper_down_right2, x-53, y-10, NULL, 1.0f, RADTODEG *rightkicker2.body->getAngle(),58,10);
	//Blit the texture of the combo balls:
	if(ball2 != nullptr) {
		ball2->GetPosition(ball2x, ball2y);
		App->renderer->Blit(ball_texture, ball2x, ball2y, NULL, 1.0f);
	}
	if(ball3!= nullptr) {
		ball3->GetPosition(ball3x, ball3y);
		App->renderer->Blit(ball_texture, ball3x, ball3y, NULL, 1.0f,20.0f);
	}
	//Change the Sensor into a Chain:
	if (sensored == true) {
		
		ball_sensor_stop->body->GetFixtureList()->SetSensor(false);		
		CurrentTime = SDL_GetTicks();
		if (CurrentTime > LastTime + 1000) {
			ball_sensor_stop->body->GetFixtureList()->SetSensor(true);
			sensored = false;
			App->audio->PlayFx(combo_balls_release, 0);
		}
	}
	//Creating the first ball of combo
	if (isball1 == true) {		
		collisioned = true; 
		CurrentTime = SDL_GetTicks();
		if (CurrentTime > LastTime + 2000) {
			ball2 = App->physics->CreateCircle(130, 160, 10, 0.5f, true, b2_dynamicBody);
			//App->renderer->Blit(background2, 0, 0);
			ball_2 = true;			
			ball2->listener = this;
			isball1 = false;
			isball2 = true;
			LastTime = SDL_GetTicks();
			App->audio->PlayFx(combo_balls_release, 0);
		}
	}
	//Creating the second ball of combo
	if(isball2 == true){
		CurrentTime = SDL_GetTicks();
		if (CurrentTime > LastTime+1000) {
			ball3 = App->physics->CreateCircle(130, 160, 10, 0.5f, true, b2_dynamicBody);
			//App->renderer->Blit(background2, 0, 0);
			ball_3 = true;			
			ball3->listener = this;			
			isball2 = false;
			collisioned = false;
			one = true;
			App->audio->PlayFx(combo_balls_release, 0);
		}
	}
	
	//DESTROY BALLS	
	if (ball2 != nullptr) {
		if (ball2y >= 1010) {
			App->physics->DestroyBody(ball2->body);
			delete ball2;
			ball2 = nullptr;
			App->audio->PlayFx(dead_fx);
			//ball_2 = false;
		}
	}
	if (ball3 != nullptr) {
		if (ball3y >= 1010) {
			App->physics->DestroyBody(ball3->body);
			delete ball3;
			ball3 = nullptr;
			App->audio->PlayFx(dead_fx);
			//ball_3 = false;
		}
	}
	if ( bally >= 1010) {
		
		App->physics->DestroyBody(ball->body);
		delete ball;
		ball = nullptr;
		ball = App->physics->CreateCircle(520, 900, 10, 0.5f, false, b2_dynamicBody);
		ball->listener = this;
		App->audio->PlayFx(dead_fx);	
	
	}
	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		
		leftkicker1.body->Clickers_force(-360);
		leftkicker2.body->Clickers_force(-360);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {

		rightkicker1.body->Clickers_force(360);
		rightkicker2.body->Clickers_force(360);
	}
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11,0.5f, false, b2_dynamicBody));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN /*&& forced == false*/) {
		b2Vec2 vec(0, -200);
		ball->body->ApplyForceToCenter(vec, true);
		/*forced = true;		*/
			
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
		ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, 0.5f, false, b2_dynamicBody);
	}
	
	//PULLER
	if ((App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)) {
		App->audio->PlayFx(pull_fx);
		App->physics->joint->SetMotorSpeed(2);
	}
	else if ((App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT))
		App->physics->joint->SetMotorSpeed(6);

	else if ((App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)) {
		App->audio->PlayFx(trhow_pull_fx);
	}
	else {
		App->physics->joint->SetMotorSpeed(-500);
	}





	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();
	

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

	void ModuleSceneIntro::OnCollision(PhysBody* bodyB, PhysBody* bodyA)
	{
		//App->audio->PlayFx(bonus_fx);

		if (bodyA == __19_pink || bodyA == __20_yellow || bodyA == __21_red || bodyA == __22_boy ||
			bodyA == __23_blue || bodyA == __24_green_xp || bodyA == __27_yellow ||/*bodyA == __26_girl ||*/
			bodyA == __27_yellow) {

			int i = rand() % 20;
			if (bodyA == __19_pink) {
				//App->player->ImproveScore(100);	

				if ((i == 1 || i == 2) && __19_pink->IsTrodden == false)
					App->audio->PlayFx(bird_fx, 0);//play the bonus 

				if (i > 2 && i <= 6)
					App->audio->PlayFx(bird_fx2, 0);//play the bonus 

				__19_pink->IsTrodden = true;
			}
			else if (bodyA == __20_yellow) {
				//App->player->ImproveScore(100);	

				if ((i == 1 || i == 2) && __20_yellow->IsTrodden == false)
					App->audio->PlayFx(bird_fx, 0);//play the bonus 

				if (i > 2 && i <= 6)
					App->audio->PlayFx(bird_fx2, 0);//play the bonus 

				__20_yellow->IsTrodden = true;
			}
			else if (bodyA == __21_red) {
				//App->player->ImproveScore(100);	

				if (__21_red->IsTrodden == false)
					App->audio->PlayFx(bird_fx, 0);//play the bonus 

				if (i > 2 && i <= 6)
					App->audio->PlayFx(bird_fx2, 0);//play the bonus 

				__21_red->IsTrodden = true;

			}
			else if (bodyA == __22_boy) {
				//App->player->ImproveScore(200);
				__22_boy->IsTrodden = true;
			}
			else if (bodyA == __23_blue) {
				//App->player->ImproveScore(100);
				if ((i == 1 || i == 2) && __23_blue->IsTrodden == false)
					App->audio->PlayFx(bird_fx, 0);//play the bonus 

				if (i > 2 && i <= 6)
					App->audio->PlayFx(bird_fx2, 0);//play the bonus 

				__23_blue->IsTrodden = true;
			}
			else if (bodyA == __24_green_xp) {
				//App->player->ImproveScore(100);
				if ((i == 1 || i == 2) && __24_green_xp->IsTrodden == false)
					App->audio->PlayFx(bird_fx, 0);//play the bonus 

				if (i > 2 && i <= 6)
					App->audio->PlayFx(bird_fx2, 0);//play the bonus 

				__24_green_xp->IsTrodden = true;
			}
			else if (bodyA == __27_yellow) {
				//App->player->ImproveScore(100);
				if ((i == 1 || i == 2) && __27_yellow->IsTrodden == false)
					App->audio->PlayFx(bird_fx, 0);//play the bonus 

				if (i > 2 && i <= 6)
					App->audio->PlayFx(bird_fx2, 0);//play the bonus 

				__27_yellow->IsTrodden = true;
			}
		}
			if (bodyA == __15_green || bodyA == __16_green) {



				if (bodyA == __15_green) {
					//App->player->ImproveScore(100);		
					__15_green->IsTrodden = true;
				}
				if (bodyA == __16_green) {
					//App->player->ImproveScore(100);
					;				 __16_green->IsTrodden = true;
				}

				App->audio->PlayFx(gg_fx, 0);//play the bonus 

			}
		if (bodyA == __1_grey || bodyA == __3_grey || bodyA == __5_grey ||
			bodyA == __7_grey || bodyA == __8_grey || bodyA == __10_grey ||
			bodyA == __25_grey || bodyA == __15_green || bodyA == __16_green) {

			App->audio->PlayFx(gg_fx);//play the bonus 							

		}
		if (collisioned == false) {
			if (bodyA == sensor_ball) {
				//primero hacer blit de el trozo de textura
				App->audio->PlayFx(combo_balls);
				LastTime = SDL_GetTicks();				
				sensored = true;				
				isball1 = true;
				LastTime = SDL_GetTicks();
				

			}


		}
		
	}



	
