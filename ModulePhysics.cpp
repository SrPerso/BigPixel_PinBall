#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	/*b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	/*b2Body* big_ball = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;
	
	b2FixtureDef fixture;
	fixture.shape = &shape;
	big_ball->CreateFixture(&fixture);*/
	//CIRCLE FOR JOINT
	b2Body *circle;
	b2BodyDef circledef;
	circledef.type = b2_staticBody;
	circledef.position.Set(3.8f, 19.4f);
	circle = world->CreateBody(&circledef);
	
	b2CircleShape circleshape;
	circleshape.m_radius = PIXEL_TO_METERS(5);
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleshape;
	myFixtureDef.density = 1;

	circle->CreateFixture(&myFixtureDef);
	
	//CLICKER FOR JOINT:
	
	b2Vec2 obstacles[8];

	
	obstacles[0].Set(0.0, 0.0);
	obstacles[1].Set(0.344, 0.927);
	obstacles[2].Set(0.360, 0.927);
	obstacles[3].Set(0.438, 0.967);
	obstacles[4].Set(0.436, 0.978);
	obstacles[5].Set(0.420, 0.982);
	obstacles[6].Set(0.326, 0.953);
	obstacles[7].Set(0.322, 0.941);

	/*0.900362f, 0.573913f,
		0.884058f, 0.575845f,
		0.860507f, 0.616425f,
		0.867754f, 0.623188f,
		0.882246f, 0.622222f,
		0.920290f, 0.582609f,
		0.911232f, 0.575845f
};*/
	
	/*0.329710f, 0.933333f,
		0.344203f, 0.927536f,
		0.360507f, 0.927536f,
		0.438406f, 0.967150f,
		0.436594f, 0.978744f,
		0.420290f, 0.982609f,
		0.326087f, 0.953623f,
		0.322464f, 0.941063f*/


	App->physics->CreatePolygons(obstacles,8, b2_dynamicBody, 150, 500, 0.05);
	
	/*
	b2BodyDef clickerdef;
	clickerdef.type = b2_dynamicBody;
	clickerdef.position.Set(3.8f, 19.4f);
	b2Body *clicker = world->CreateBody(&clickerdef);
	
	b2PolygonShape clickershape;
	clickershape.Set(obstacles, 8);
	b2FixtureDef myFixtureDef22;
	myFixtureDef22.shape = &clickershape;
	//myFixtureDef22.density = 1;
	clicker->CreateFixture(&myFixtureDef22);


	//revolution joint

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = circle;
	revoluteJointDef.bodyB = clicker;
	revoluteJointDef.localAnchorA = clicker->GetLocalCenter();
	revoluteJointDef.localAnchorB = circle->GetLocalCenter();
	revoluteJointDef.collideConnected = true;

	world->CreateJoint(&revoluteJointDef);*/
	
	
	//TRIANGLES-----------------------------------------------------------------
	//LEFT
	int triangle1[14] = {
		110, 777,
		128, 770,
		178, 859,
		181, 863,
		169, 875,
		114, 846,
		108, 782
	};
	
	CreateChain(0, 0, triangle1, 14, b2_staticBody);
	//RIGHT
	int triangle2[12] = {
		406, 773,
		424, 778,
		417, 849,
		367, 875,
		353, 863,
		401, 777
	};
	
	CreateChain(0, 0, triangle2, 12, b2_staticBody);
	
	
	//"EYEBROW"
	//LEFT
	int eyebrow1[24] = {
		78, 871,
		86, 893,
		97, 901,
		110, 909,
		186, 950,
		189, 954,
		176, 978,
		169, 979,
		84, 932,
		69, 917,
		65, 897,
		70, 873
	};
	
	CreateChain(0, 0, eyebrow1, 24, b2_staticBody);

	//RIGHT
	int eyebrow2[44] = {
		347, 951,
		441, 898,
		446, 891,
		450, 881,
		454, 873,
		461, 872,
		465, 878,
		466, 886,
		466, 894,
		465, 905,
		462, 913,
		457, 922,
		452, 928,
		445, 935,
		436, 941,
		428, 945,
		418, 950,
		366, 978,
		361, 980,
		356, 978,
		352, 972,
		344, 957
	};
	
	CreateChain(0, 0, eyebrow2, 44, b2_staticBody);
	//PRUEBA:
	int line[6] = {
		530, 900,
		501, 900,
		500,900,
	};	
	CreateChain(0, 0, line, 6, b2_staticBody);
	//--------------------
	

	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, float Rest)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.restitution = Rest;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}
PhysBody* ModulePhysics::CreateSensorBall(int x, int y, int* points, int size, bool sensor) {
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.isSensor = sensor;
	

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

PhysBody* ModulePhysics::CreateChainSensor(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}


PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			
			if(App->input->GetMouseButton(SDL_BUTTON_LEFT)==KEY_DOWN && mousein==false){
				b2Vec2 mouse(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));
				if (f->TestPoint(mouse)) {
					mousein = true;
					mousebody = b;
				}
			}
		}
	}

	
	if (mousein == true && mouse_joint==nullptr) {
		b2Vec2 mousepos(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = mousebody;
		def.target = mousepos;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * mousebody->GetMass();
		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}


	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mousein==true) {
		b2Vec2 mousepos(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		mouse_joint->SetTarget(mousepos);

		App->renderer->DrawLine(METERS_TO_PIXELS(mousepos.x), METERS_TO_PIXELS(mousepos.y), METERS_TO_PIXELS(mousebody->GetPosition().x), METERS_TO_PIXELS(mousebody->GetPosition().y), 255, 0, 0);

	}
	
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && mousein == true) {
		world->DestroyJoint(mouse_joint);
		mouse_joint = nullptr;
		mousein = false;
	}
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}

void ModulePhysics::DestroyBody(b2Body* body) {
	world->DestroyBody(body);
}
PhysBody* ModulePhysics::CreatePolygons(b2Vec2* vertices1, int count1, b2BodyType type, int x, int y, float rest)
{
	b2BodyDef polygonbody;
	polygonbody.type = type;
	polygonbody.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&polygonbody);

	b2PolygonShape polygon1shape;
	polygon1shape.Set(vertices1, count1);
	b2FixtureDef polygon1fix;
	polygon1fix.density = 1.0f;
	polygon1fix.restitution = rest;
	polygon1fix.shape = &polygon1shape;
	b->CreateFixture(&polygon1fix);

	

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);

	return pbody;
}