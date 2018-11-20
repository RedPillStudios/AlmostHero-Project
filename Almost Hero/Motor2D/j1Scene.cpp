#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Collisions.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	red_note.nPosition = iPoint(820, 200);
	red_note.nVelocity = fPoint(1.0f, 1.0f);

	red_note.note_rect = { red_note.nPosition.x, red_note.nPosition.y, 35, 35 };
	//red_note.note_tex = App->tex->Load("maps/path2.png");
	red_note.nColor = NOTE_RED;
	red_note.note_collider = App->collisions->AddCollider(red_note.note_rect, COLLIDER_NOTE, this);
	
	guitar_tex = App->tex->Load("maps/Neck_Guitar.png");


	Bottom_Limit.x = 400;
	Bottom_Limit.y = 400;
	Bottom_Limit.w = 500;
	Bottom_Limit.h = 35;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	dt *= 200;
	float camera_speed = dt;

	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	// TODO 6: Make the camera movement independent of framerate
	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += camera_speed;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= camera_speed;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += camera_speed;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= camera_speed;

	//int x, y;
	//App->input->GetMousePosition(x, y);
	//iPoint p = App->render->ScreenToWorld(x, y);
	//App->render->Blit(red_note.note_tex, p.x, p.y);

	App->render->Blit(guitar_tex, 640, 50);

	App->render->DrawQuad(red_note.note_rect, 255, 0, 0, 255);
	red_note.note_rect.y += red_note.nVelocity.x;
	red_note.note_rect.x -= red_note.nVelocity.y;

	App->render->DrawQuad(Bottom_Limit, 255, 0, 255, 255);
	red_note.note_collider->SetPos(red_note.nPosition.x, red_note.nPosition.y);

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}