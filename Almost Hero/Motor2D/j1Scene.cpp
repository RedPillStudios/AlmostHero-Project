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

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	RELEASE(red_note->note_tex);
	RELEASE(red_note);

	//RELEASE(guitar_tex);

	return true;
}

// Called before the first frame
bool j1Scene::Start()
{			

	//Guitar texture
	guitar_tex = App->tex->Load("maps/Neck_Guitar.png");

	//Notes deleter
	Bottom_Limit.x = 643;
	Bottom_Limit.y = 617;
	Bottom_Limit.w = 480;
	Bottom_Limit.h = 50;

	Bottom_coll = App->collisions->AddCollider(Bottom_Limit, COLLIDER_STATIC, this);

	//Notes Smashers
	int iX = 705, iY = 520, sW = 50, sH = 2, sSpace = 50;

	smBlue.smasher_rect.x = iX;
	smBlue.smasher_rect.y = iY;
	smBlue.smasher_rect.w = sW;
	smBlue.smasher_rect.h = sH;
	
	smBlue.smasher_collider = App->collisions->AddCollider(smBlue.smasher_rect, COLLIDER_SMASHER_BLUE, this);


	smYellow.smasher_rect.x = iX + sW + sSpace;
	smYellow.smasher_rect.y = 520;
	smYellow.smasher_rect.w = sW;
	smYellow.smasher_rect.h = sH;

	smYellow.smasher_collider = App->collisions->AddCollider(smYellow.smasher_rect, COLLIDER_SMASHER_YELLOW, this);


	smViolet.smasher_rect.x = iX + 2*(sW + sSpace);
	smViolet.smasher_rect.y = iY;
	smViolet.smasher_rect.w = sW;
	smViolet.smasher_rect.h = sH;

	smViolet.smasher_collider = App->collisions->AddCollider(smViolet.smasher_rect, COLLIDER_SMASHER_VIOLET, this);


	smPink.smasher_rect.x = iX + 3*(sW + sSpace);
	smPink.smasher_rect.y = iY;
	smPink.smasher_rect.w = sW;
	smPink.smasher_rect.h = sH;

	smPink.smasher_collider = App->collisions->AddCollider(smPink.smasher_rect, COLLIDER_SMASHER_PINK, this);


	//Red Note
	red_note = CreateNote(fPoint(806.0f, 82.0f), fPoint(0.27f, 1.0f), NOTE_BLUE);
	timer_long.Start();
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
	red_note->scale += 0.01f;

	float camera_speed = dt * 200;

	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	//camera movement independent of framerate
	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += camera_speed;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= camera_speed;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += camera_speed;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= camera_speed;

	App->render->Blit(guitar_tex, 640, 50, NULL);

	App->render->DrawQuad(red_note->note_rect, 0, 150, 0, 150, red_note->scale);
	red_note->nPosition.x -= red_note->nVelocity.x;
	red_note->nPosition.y += red_note->nVelocity.y;
	red_note->note_rect = { (int)red_note->nPosition.x, (int)red_note->nPosition.y, 35, 35 };

	//Notes deleter blit & colider
	App->render->DrawQuad(Bottom_Limit, 255, 0, 255, 255);
	Bottom_coll->SetPos(Bottom_Limit.x, Bottom_Limit.y);

	//Smashers blit and collider
	App->render->DrawQuad(smBlue.smasher_rect, 0, 0, 255, 255);
	smBlue.smasher_collider->SetPos(smBlue.smasher_rect.x, smBlue.smasher_rect.y);

	App->render->DrawQuad(smViolet.smasher_rect, 150, 0, 255, 255);
	smViolet.smasher_collider->SetPos(smViolet.smasher_rect.x, smViolet.smasher_rect.y);

	App->render->DrawQuad(smPink.smasher_rect, 255, 0, 255, 255);
	smPink.smasher_collider->SetPos(smPink.smasher_rect.x, smPink.smasher_rect.y);

	App->render->DrawQuad(smYellow.smasher_rect, 255, 200, 0, 255);
	smYellow.smasher_collider->SetPos(smYellow.smasher_rect.x, smYellow.smasher_rect.y);

	//red_note Collider
	red_note->note_collider->SetPos(red_note->nPosition.x, red_note->nPosition.y);
	
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

void j1Scene::OnCollision(Collider *c1, Collider *c2) {

	if (c1->type == COLLIDER_NOTE && c2->type == COLLIDER_STATIC) { //If for some reason collision fails, try to check both c1/c2 and c2/c1 instead of only c1/c2

		
		NOTE_COLOR aux_col = red_note->nColor;
		red_note->note_collider->to_delete = true;
		RELEASE(red_note);

		if (red_note == nullptr)
			red_note = CreateNote(fPoint(806.0f, 82.0f), fPoint(0.27f, 1.0f), aux_col);
		
	}
	
	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_BLUE)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = red_note->nColor;
			red_note->note_collider->to_delete = true;
			RELEASE(red_note);

			if (red_note == nullptr)
				red_note = CreateNote(fPoint(806.0f, 82.0f), fPoint(0.27f, 1.0f), aux_col);

			LOG("TIME TO REACH: %f", timer_long.ReadSec());
			bool a = true;
		}
	}
}

Note* j1Scene::CreateNote(fPoint pos, fPoint vel, NOTE_COLOR color) {

	Note *note = new Note();

	note->nPosition = pos;
	note->nVelocity = vel;

	note->note_rect = { (int)note->nPosition.x, (int)note->nPosition.y, 35, 35 };

	note->nColor = color;
	note->note_collider = App->collisions->AddCollider(note->note_rect, COLLIDER_NOTE, this);

	return note;
}