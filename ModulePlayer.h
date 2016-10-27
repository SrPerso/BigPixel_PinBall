#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ImproveScore(const int& score) {this->Score += score;}
	int GetScore() { return Score; }
	void RestBalls() { this->Balls-=1; }
	int GetBalls() { return Balls; }
	void ResetBalls() { this->Balls = 3; };

	int GetPreviousScore() { return this->PreviousScore; }
	void SetPreviousScore() { this->PreviousScore = this->Score; }
	void ResetScore() { this->Score = 0; }



private:
	int Score;
	int PreviousScore=0;
	int Balls = 3;

};