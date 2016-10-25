#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"


#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	void Clickers_force(int degrees);
public:
	int width, height;
	b2Body* body;
	Module* listener;
	bool IsTrodden = false;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	bool mousein=false;
	b2Body* mousebody= nullptr;

	PhysBody* CreateCircle(int x, int y, int radius, float Rest, bool _bullet, b2BodyType type);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size, b2BodyType type);
	PhysBody* CreateChainSensor(int x, int y, int* points, int size);
	PhysBody* CreateSensorBall(int x, int y, int* points, int size, bool sensor);
	PhysBody* CreatePolygon(b2Vec2* vertices1, int count1, b2BodyType type, int x, int y, float Rest);
	void CreateRevoluteJoint(b2Body* bodyA, b2Body* bodyB, int upperangle, int lowerangle, int pivot_x, int pivot_y);
	void DestroyBody(b2Body* body);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);
	b2Body* ground;
	

	p2List<b2RevoluteJoint*> paddleList;
	
	b2Body* b;
	
	

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	
};