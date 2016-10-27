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

	
	b2BodyDef bd;
	ground = world->CreateBody(&bd);


	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	
	
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

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, float Rest, bool _bullet, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.bullet = _bullet;
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
	//AVoid Memory Leaks:
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		delete b->GetUserData();
	}

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

void PhysBody::Clickers_force(int degrees) {
	body->ApplyAngularImpulse(DEGTORAD*degrees, true);
}
void ModulePhysics::DestroyBody(b2Body* body) {
	world->DestroyBody(body);
}
PhysBody* ModulePhysics::CreatePolygon(b2Vec2* vertices1, int count1, b2BodyType type, int x, int y, float rest)
{
	b2BodyDef polygonbody;
	polygonbody.type = type;
	polygonbody.bullet = true;
	polygonbody.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* body = world->CreateBody(&polygonbody);

	b2PolygonShape polygonshape;
	polygonshape.Set(vertices1, count1);
	b2FixtureDef polygonfix;
	polygonfix.density = 1.0f;
	polygonfix.restitution = rest;
	polygonfix.shape = &polygonshape;
	body->CreateFixture(&polygonfix);

	

	PhysBody* p_body = new PhysBody();
	p_body->body = body;
	body->SetUserData(p_body);

	return p_body;
}
void ModulePhysics::CreateRevoluteJoint(b2Body* bodyA, b2Body* bodyB, int upperangle, int lowerangle, int pivot_x, int pivot_y) {

	b2RevoluteJointDef definition;
	definition.bodyA = bodyA;
	definition.bodyB = bodyB;
	b2Vec2 localanchor(PIXEL_TO_METERS(pivot_x), PIXEL_TO_METERS(pivot_y));
	definition.localAnchorA = localanchor;
	definition.localAnchorB = bodyB->GetLocalCenter();
	definition.enableLimit = true;
	definition.upperAngle = DEGTORAD * upperangle;
	definition.lowerAngle = DEGTORAD * lowerangle;
	world->CreateJoint(&definition);
}
double PhysBody::getAngle() const {
	return body->GetAngle();
}

void ModulePhysics::CreateUpJoint(PhysBody* bodyA, PhysBody* bodyB, b2Vec2 ancorA, b2Vec2 ancorB, int max, int min, int maxMotor, int motorSpeed)
{
	b2PrismaticJointDef definition;
	definition.bodyA = bodyA->body;
	definition.bodyB = bodyB->body;
	definition.collideConnected = false;
	definition.localAxisA.Set(0, 1);
	definition.localAnchorA.Set(PIXEL_TO_METERS(ancorA.x), PIXEL_TO_METERS(ancorA.y));
	definition.localAnchorB.Set(PIXEL_TO_METERS(ancorB.x), PIXEL_TO_METERS(ancorB.y));

	definition.enableLimit = true;
	definition.lowerTranslation = PIXEL_TO_METERS(min);
	definition.upperTranslation = PIXEL_TO_METERS(max);
	definition.type = e_prismaticJoint;

	definition.enableMotor = true;
	definition.motorSpeed = motorSpeed * DEGTORAD;
	definition.maxMotorForce = maxMotor;

	joint = (b2PrismaticJoint*)world->CreateJoint(&definition);

	//return joint;
}