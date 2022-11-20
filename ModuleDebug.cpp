#include "ModuleDebug.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "Flippers.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleDeath.h"
#include "ModuleTitle.h"

#include <chrono>
using namespace std::chrono;

#include <string>

ModuleDebug::ModuleDebug(Application* app, bool start_enabled) : Module(app, start_enabled) { drawDebug = false; }
ModuleDebug::~ModuleDebug() {}

bool ModuleDebug::Start()
{
	drawDebug = false;
	return true;
}

update_status ModuleDebug::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		drawDebug = !drawDebug;

	// F1: View colliders / logic
		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
			drawPhysics = !drawPhysics;

	if (drawDebug)
	{
		if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
			variables = !variables;

		

		//F2: Lights ON/OFF
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
			lightsON = !lightsON;

		//F3: Change Frames ON/OFF
		if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
			fps = !fps;
	}
	
	 
	if (fps == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && desiredFPS < 120)
			desiredFPS += 1; LOG("%d", desiredFPS);
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && desiredFPS > 10)
			desiredFPS -= 1;
	}

	//F3: Music ON/OFF
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		musicON = !musicON;

	//F4: Sfx ON/OFF
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		sfxON = !sfxON;
	
	//U: Chnage UI
	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
		changeUI = !changeUI;

	return UPDATE_CONTINUE;
}

update_status ModuleDebug::PostUpdate()
{
	if (drawDebug)
		DrawDebug();

	if (drawPhysics)
		DrawPhysics();

	return UPDATE_CONTINUE;
}

void ModuleDebug::DrawDebug()
{
	int fontId = 6;
	int debugX = 600;
	int debugY = 500;


	App->fonts->BlitText(debugX, debugY + 0, fontId, "#DEBUG MODE (TAB)  ON/OFF");

	//Colliders
	if (drawPhysics)
		App->fonts->BlitText(debugX, debugY + 20, fontId, "#COLLIDERS  (F1)   ON");
	else
		App->fonts->BlitText(debugX, debugY + 20, fontId, "#COLLIDERS  (F1)   OFF");

	//Lights
	if (lightsON)
		App->fonts->BlitText(debugX, debugY + 40, fontId, "#LIGHTS     (F2)   ON");
	else
		App->fonts->BlitText(debugX, debugY + 40, fontId, "#LIGHTS     (F2)   OFF");

	//Frames
	if (fps)
		App->fonts->BlitText(debugX, debugY + 60, fontId, "#FRAMES     (F3)   ON");
	else
		App->fonts->BlitText(debugX, debugY + 60, fontId, "#FRAMES     (F3)   OFF");

	//Variables
	if (variables)
		App->fonts->BlitText(debugX, debugY + 80, fontId, "#VARIABLES  (V)    ON");
	else
		App->fonts->BlitText(debugX, debugY + 80, fontId, "#VARIABLES  (V)    OFF");


	if (fps)
	{
		//Frames
		std::string string = std::string("FRAMES = ") + std::to_string(desiredFPS);
		App->fonts->BlitText(debugX, debugY + 120, fontId, string.c_str());
	}

	if (variables)
	{
		//Ball x, y
		std::string string = std::string("BALL.X = ") + std::to_string(App->scene_intro->ball->position.x);
		App->fonts->BlitText(debugX, debugY + 160, fontId, string.c_str());

		string = std::string("BALL.Y = ") + std::to_string(App->scene_intro->ball->position.y);
		App->fonts->BlitText(debugX, debugY + 180, fontId, string.c_str());

		//Spring force
		if (App->scene_intro->springForce == 420)
			string = std::string("SPRING.F = ") + std::to_string(App->scene_intro->springForce) + "  X)";
		else
			string = std::string("SPRING.F = ") + std::to_string(App->scene_intro->springForce);
		App->fonts->BlitText(debugX, debugY + 200, fontId, string.c_str());
	}	
}

void ModuleDebug::DrawPhysics()
{
	
	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = App->physics->world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
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

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
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

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
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

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				// test if the current body contains mouse position
				b2Vec2 p = { PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()) };
				if (f->GetShape()->TestPoint(b->GetTransform(), p) == true)
				{

					// If a body was selected we will attach a mouse joint to it
					// so we can pull it around

					// TODO 2: If a body was selected, create a mouse joint
					// using mouse_joint class property

					// NOTE: you do TODO2 here or also in the original handout's location. 
					// It doesn't matter unless you are triggering several objects at once;
					// I leave it to you to add safety checks to avoid re-defining several mouse joints.

					// The variable "b2Body* mouse_body;" is defined in the header ModulePhysics.h 
					// We need to keep this body throughout several game frames; you cannot define it as a local variable here. 
					App->physics->mouse_body = b;

					// Get current mouse position
					b2Vec2 mousePosition;
					mousePosition.x = p.x;
					mousePosition.y = p.y;

					// Define new mouse joint
					b2MouseJointDef def;
					def.bodyA = App->physics->ground; // First body must be a static ground
					def.bodyB = App->physics->mouse_body; // Second body will be the body to attach to the mouse
					def.target = mousePosition; // The second body will be pulled towards this location
					def.dampingRatio = 0.5f; // Play with this value
					def.frequencyHz = 2.0f; // Play with this value
					def.maxForce = 200.0f * App->physics->mouse_body->GetMass(); // Play with this value

					// Add the new mouse joint into the World
					App->physics->mouse_joint = (b2MouseJoint*)App->physics->world->CreateJoint(&def);
				}
			}
		}
	}



	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (App->physics->mouse_body != nullptr && App->physics->mouse_joint != nullptr)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			// Get new mouse position and re-target mouse_joint there
			b2Vec2 mousePosition;
			mousePosition.x = PIXEL_TO_METERS(App->input->GetMouseX());
			mousePosition.y = PIXEL_TO_METERS(App->input->GetMouseY());
			App->physics->mouse_joint->SetTarget(mousePosition);

			// Draw a red line between both anchor points
			App->renderer->DrawLine(METERS_TO_PIXELS(App->physics->mouse_body->GetPosition().x), METERS_TO_PIXELS(App->physics->mouse_body->GetPosition().y), App->input->GetMouseX(), App->input->GetMouseY(), 255, 0, 0);
		}
	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (App->physics->mouse_body != nullptr && App->physics->mouse_joint != nullptr)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP)
		{
			// Tell Box2D to destroy the mouse_joint
			App->physics->world->DestroyJoint(App->physics->mouse_joint);

			// DO NOT FORGET THIS! We need it for the "if (mouse_body != nullptr && mouse_joint != nullptr)"
			App->physics->mouse_joint = nullptr;
			App->physics->mouse_body = nullptr;
		}
	}
}