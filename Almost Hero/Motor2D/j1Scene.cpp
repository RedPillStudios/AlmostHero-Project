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
	smViolet = CreateSmasher(0, COLLIDER_SMASHER_VIOLET);
	smBlue = CreateSmasher(1, COLLIDER_SMASHER_BLUE);
	smYellow = CreateSmasher(2, COLLIDER_SMASHER_YELLOW);
	smPink = CreateSmasher(3, COLLIDER_SMASHER_PINK);


	//Notes
	red_note = CreateNote(nIpos, 0, NOTE_BLUE);
	red_note->nPosition = nIpos;

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

	App->render->Blit(guitar_tex, 640, 50, NULL);

	//Notes deleter blit & colider
	App->render->DrawQuad(Bottom_Limit, 255, 255, 255, 255);
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

	//Notes drawing
	red_note->scale += 0.01f;
	App->render->DrawQuad(red_note->note_rect, 0, 150, 0, 150, red_note->scale);

	red_note->nPosition.x -= nVelocity.x;
	red_note->nPosition.y += nVelocity.y;

	red_note->note_rect = { (int)red_note->nPosition.x, (int)red_note->nPosition.y, 35, 35 };

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
			red_note = CreateNote(nIpos, 0, aux_col);
		
	}
	
	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_VIOLET)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = red_note->nColor;
			red_note->note_collider->to_delete = true;
			RELEASE(red_note);

			if (red_note == nullptr)
				red_note = CreateNote(nIpos, 0, aux_col);


		}
	}
}

Note* j1Scene::CreateNote(fPoint pos, int note_num, NOTE_COLOR color) {

	Note *note = new Note();

	int iX = nIpos.x, sW = 35, sSpace = 50;

	note->nPosition = pos;

	int Xf = iX + note_num * (sW + sSpace);

	note->note_rect.x = Xf;
	note->note_rect.y = nIpos.y;

	note->nColor = color;
	note->note_collider = App->collisions->AddCollider(note->note_rect, COLLIDER_NOTE, this);

	return note;
}


Smasher j1Scene::CreateSmasher(int smasher_num, COLLIDER_TYPE  smasher_collider) {

	int iX = 705, iY = 520, sW = 50, sH = 2, sSpace = 50;

	Smasher aux;
	aux.smasher_rect.x = iX + smasher_num * (sW + sSpace);
	aux.smasher_rect.y = iY;
	aux.smasher_rect.w = sW;
	aux.smasher_rect.h = sH;

	aux.smasher_collider = App->collisions->AddCollider(aux.smasher_rect, smasher_collider, this);

	return aux;
}