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

	//LOAD BALLS
	ball = App->physics->CreateCircle(520, 900, 10, 0.5f);
	//Plusball = App->physics->CreateCircle(104, 125, 10, 0.5f);
	ball->listener = this;

	 
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
		97,117,
		130, 108
	};

	//CAMERA
	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	//LOAD TEXTURES
	background = App->textures->Load("pinball/Images/Ground/background.png");
	background2 = App->textures->Load("pinball/Images/Ground/frontground.png");
	ball_texture== App->textures->Load("pinball/Images/1.png");

	//LOAD AUDIOS
	hitWall_fx = App->audio->LoadFx("pinball/Audio/HitBallWall.wav");
	bird_fx = App->audio->LoadFx("pinball/Audio/bird_fx.wav");
	dead_fx = App->audio->LoadFx("pinball/Audio/dead_fx.wav");
	game_bso = App->audio->LoadFx("pinball/Audio/game_bso.wav");
	gg_fx = App->audio->LoadFx("pinball/Audio/gg_circles_fx.wav");
	combo_balls = App->audio->LoadFx("pinball/Audio/Combo_Balls.wav");

	//LOST CONDITION	
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	sensor_ball = App->physics->CreateChainSensor(0, 0, sensor_balls, 6);
	
	//OBJECTS
	
	__1_grey = App->physics->CreateChain(0, 0, _1_grey, 22, b2_staticBody);
	//__2_orange = App->physics->CreateChain(0, 0, _2_orange, 26, b2_staticBody);
	__3_grey = App->physics->CreateChain(0, 0, _3_grey, 24, b2_staticBody);
	//__4_orange = App->physics->CreateChain(0, 0, _4_orange, 24, b2_staticBody);
	__5_grey = App->physics->CreateChain(0, 0, _5_grey, 24, b2_staticBody);
	__6_black = App->physics->CreateChainSensor(0, 0, _6_black, 24);
	__7_grey = App->physics->CreateChain(0, 0, _7_grey, 24, b2_staticBody);
	__8_grey = App->physics->CreateChain(0, 0, _8_grey, 24, b2_staticBody);
	//__9_orange = App->physics->CreateChain(0, 0, _9_orange, 28, b2_staticBody);
	__10_grey = App->physics->CreateChain(0, 0, _10_grey, 24, b2_staticBody);
	//__11_orange = App->physics->CreateChain(0, 0, _11_orange, 32, b2_staticBody);
	__12_black = App->physics->CreateChainSensor(0, 0, _12_black, 26);
	//__13_orange = App->physics->CreateChain(0, 0, _13_orange, 26, b2_staticBody);
	//__14_orange = App->physics->CreateChain(0, 0, _14_orange, 26, b2_staticBody);
	__15_green = App->physics->CreateChain(0, 0, _15_green, 30, b2_staticBody);
	__16_green = App->physics->CreateChain(0, 0, _16_green, 34, b2_staticBody);
	//__17_orange = App->physics->CreateChain(0, 0, _17_orange, 22, b2_staticBody);
	//__18_orange = App->physics->CreateChain(0, 0, _18_orange, 26, b2_staticBody);
	__19_pink = App->physics->CreateChainSensor(0, 0, _19_pink, 32);
	__20_yellow = App->physics->CreateChainSensor(0, 0, _20_yellow, 32);
	__21_red = App->physics->CreateChainSensor(0, 0, _21_red, 30);
	__22_boy = App->physics->CreateChainSensor(0, 0, _22_boy, 50);
	__23_blue = App->physics->CreateChainSensor(0, 0, _23_blue, 32);
	__24_green_xp = App->physics->CreateChainSensor(0, 0, _24_green_xp, 32);
	__25_grey = App->physics->CreateChain(0, 0, _25_grey, 18, b2_staticBody);
	//__26_girl= App->physics->CreateChainSensor(0, 0, _26_girl, 42);
	__27_yellow = App->physics->CreateChainSensor(0, 0, _27_yellow, 32);
	
	
	/*__21_red->listener->Start();
	__21_red->listener->App->audio->PlayFx(bonus_fx,0);*/

	//BACKGROUND
	__tubebottom = App->physics->CreateChain(0, 0, _tubebottom, 66, b2_staticBody);
	__tubetop = App->physics->CreateChain(0, 0, _tubetop, 98, b2_staticBody);
	__background = App->physics->CreateChain(0, 0, _background, 150, b2_staticBody);


	


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
	App->renderer->Blit(background, 0, 0);
	App->renderer->Blit(background2, 0, 0);
	App->renderer->Blit(ball_texture,ballx,bally);


	//DESTROY BALLS
	

	if ( bally >= 1010) {
		App->physics->DestroyBody(ball->body);
		ball = nullptr;
		ball = App->physics->CreateCircle(520, 900, 10, 0.5f);
		ball->listener = this;//
		App->audio->PlayFx(dead_fx);
	/*	forced = false;*/
	
	}
	/*if (bally == 120 && ballx == 100) {
		uint balls_combo = 1;
		App->audio->PlayFx(combo_balls, 0);
		App->physics->DestroyBody(ball->body);
		ball = nullptr;
		ball = App->physics->CreateCircle(97, 117, 10, 0.5f);
		ball->listener = this;//
		uint LastTime = 0, CurrentTime;
		CurrentTime = SDL_GetTicks();
		if (CurrentTime > LastTime + 1000 && balls_combo<3) {
			ball = App->physics->CreateCircle(97, 117, 10, 0.5f);
			ball->listener = this;//
			balls_combo++;
		}
	}*/

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11,0.5f));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN /*&& forced == false*/) {
		b2Vec2 vec(0, -200);
		ball->body->ApplyForceToCenter(vec, true);
		/*forced = true;		*/
			
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
		ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, 0.5f);
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
		bodyA == __23_blue || bodyA == __24_green_xp || bodyA == __27_yellow ||/*bodyA == __26_girl ||*/bodyA == __27_yellow) {
		
		App->audio->PlayFx(bird_fx,0);//play the bonus 
		//a�adir 100 puntos
		if (__6_black->IsTrodden == true){}

	}
	if (bodyA == __1_grey || bodyA == __3_grey || bodyA == __5_grey ||
		bodyA == __7_grey || bodyA == __8_grey || bodyA == __10_grey ||
		bodyA == __25_grey || bodyA == __15_green || bodyA == __16_green) {

		App->audio->PlayFx(gg_fx);//play the bonus 							

	}
	if (bodyA == sensor_ball) {
		//primero hacer blit de el trozo de textura
		uint balls_combo = 1;
		if (destroyed == false) {
			App->physics->DestroyBody(ball->body);
			ball = nullptr;
			destroyed == true;
			while (balls_combo < 3) {
				App->audio->PlayFx(combo_balls, 0);
				ball = App->physics->CreateCircle(100, 120, 10, 0.5f);
				ball->listener = this;//
				uint LastTime = 0, CurrentTime;
				CurrentTime = SDL_GetTicks();
				if (CurrentTime > LastTime + 1000) {
					ball = App->physics->CreateCircle(100, 120, 10, 0.5f);
					ball->listener = this;//
					balls_combo++;
				}
			}
		}
		
	}



	}

	//if (bodyA == __2_orange || bodyA == __4_orange || bodyA == __9_orange ||
	//	bodyA == __11_orange || bodyA == __13_orange || bodyA == __14_orange ||
	//	bodyA == __17_orange || bodyA == __18_orange) {

	//	//App->audio->PlayFx(orange_fx);//play the bonus 							

	//}

	//if (bodyA == sensor) {
	//	App->audio->PlayFx(dead_fx);
	//}


	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
