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

	RELEASE(guitar_tex);

	return true;
}

// Called before the first frame
bool j1Scene::Start()
{			
	//Guitar texture
	guitar_tex = App->tex->Load("maps/Guitar_Sequence.png");

	for (int i = 0; i < 43; ++i) {
		Guitar.PushBack({ countGuitar.x, countGuitar.y, 480, 425 });
		countGuitar.x += 480;
		if (countGuitar.x >= 480 * 7) {
			countGuitar.y += 425;
			countGuitar.x = 0;
		}
	}
	Guitar.speed = 0.20f;
	Guitar.loop = true;
	current_anim = &Guitar;
	//Notes deleter
	Bottom_Limit.x = 400;
	Bottom_Limit.y = 400;
	Bottom_Limit.w = 500;
	Bottom_Limit.h = 35;

	Bottom_coll = App->collisions->AddCollider(Bottom_Limit, COLLIDER_STATIC, this);

	//Notes Smasher
	Notes_smasher.x = 400;
	Notes_smasher.y = 300;
	Notes_smasher.w = 500;
	Notes_smasher.h = 2;

	nSmasher_coll = App->collisions->AddCollider(Notes_smasher, COLLIDER_SMASHER, this);

	//Red Note
	red_note = CreateNote(fPoint(820.0f, 200.0f), fPoint(1.0f, 1.0f), NOTE_RED);
	
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

	App->render->Blit(guitar_tex,1280/2-480/2 , 720-425, &current_anim->GetCurrentFrame());

	App->render->DrawQuad(red_note->note_rect, 255, 0, 0, 255, red_note->scale);
	red_note->nPosition.x -= red_note->nVelocity.x;
	red_note->nPosition.y += red_note->nVelocity.y;
	red_note->note_rect = { (int)red_note->nPosition.x, (int)red_note->nPosition.y, 35, 35 };

	App->render->DrawQuad(Bottom_Limit, 255, 0, 255, 255);
	App->render->DrawQuad(Notes_smasher, 0, 0, 255, 255);

	red_note->note_collider->SetPos(red_note->nPosition.x, red_note->nPosition.y);
	Bottom_coll->SetPos(Bottom_Limit.x, Bottom_Limit.y);
	nSmasher_coll->SetPos(Notes_smasher.x, Notes_smasher.y);

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

	if (/*(c1->type == COLLIDER_STATIC && c2->type == COLLIDER_NOTE) ||*/ (c1->type == COLLIDER_NOTE && c2->type == COLLIDER_STATIC)) {

		
		NOTE_COLOR aux_col = red_note->nColor;
		red_note->note_collider->to_delete = true;
		RELEASE(red_note);

		if (red_note == nullptr)
			red_note = CreateNote(fPoint(820.0f, 200.0f), fPoint(1.0f, 1.0f), aux_col);
		
	}
	
	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = red_note->nColor;
			red_note->note_collider->to_delete = true;
			RELEASE(red_note);

			if (red_note == nullptr)
				red_note = CreateNote(fPoint(820.0f, 200.0f), fPoint(1.0f, 1.0f), aux_col);

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