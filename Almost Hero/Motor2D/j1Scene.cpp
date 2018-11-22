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

	pugi::xml_parse_result result = Buttons_Document.load_file("Butons_Settings.xml");
	if (result == NULL)
		LOG("pugi error : %s", result.description());

	Buttons_node = Buttons_Document.child("config");
	violet_Button = { Buttons_node.child("Notes").child("Violet").attribute("x").as_int(),Buttons_node.child("Notes").child("Violet").attribute("y").as_int(),Buttons_node.child("Notes").child("Violet").attribute("w").as_int(),Buttons_node.child("Notes").child("Violet").attribute("h").as_int() };
	blue_Button = { Buttons_node.child("Notes").child("Blue").attribute("x").as_int(),Buttons_node.child("Notes").child("Blue").attribute("y").as_int(),Buttons_node.child("Notes").child("Blue").attribute("w").as_int(),Buttons_node.child("Notes").child("Blue").attribute("h").as_int() };
	yellow_Button = { Buttons_node.child("Notes").child("Yellow").attribute("x").as_int(),Buttons_node.child("Notes").child("Yellow").attribute("y").as_int(),Buttons_node.child("Notes").child("Yellow").attribute("w").as_int(),Buttons_node.child("Notes").child("Yellow").attribute("h").as_int() };
	pink_Button = { Buttons_node.child("Notes").child("Pink").attribute("x").as_int(),Buttons_node.child("Notes").child("Pink").attribute("y").as_int(),Buttons_node.child("Notes").child("Pink").attribute("w").as_int(),Buttons_node.child("Notes").child("Pink").attribute("h").as_int() };
	
	Violet_Standard.PushBack({ Buttons_node.child("Buttons").child("Violet").child("Normal").attribute("x").as_int(),Buttons_node.child("Buttons").child("Violet").child("Normal").attribute("y").as_int(),Buttons_node.child("Buttons").child("Violet").child("Normal").attribute("w").as_int(),Buttons_node.child("Buttons").child("Violet").child("Normal").attribute("h").as_int() });
	Violet_Pushed.PushBack({ Buttons_node.child("Buttons").child("Violet").child("Pushed").attribute("x").as_int(),Buttons_node.child("Buttons").child("Violet").child("Pushed").attribute("y").as_int(),Buttons_node.child("Buttons").child("Violet").child("Pushed").attribute("w").as_int(),Buttons_node.child("Buttons").child("Violet").child("Pushed").attribute("h").as_int() });
	Violet_Enter.PushBack({ Buttons_node.child("Buttons").child("Violet").child("Enter").attribute("x").as_int(),Buttons_node.child("Buttons").child("Violet").child("Enter").attribute("y").as_int(),Buttons_node.child("Buttons").child("Violet").child("Enter").attribute("w").as_int(),Buttons_node.child("Buttons").child("Violet").child("Enter").attribute("h").as_int() });

	Blue_Standard.PushBack({ Buttons_node.child("Buttons").child("Blue").child("Normal").attribute("x").as_int(),Buttons_node.child("Buttons").child("Blue").child("Normal").attribute("y").as_int(),Buttons_node.child("Buttons").child("Blue").child("Normal").attribute("w").as_int(),Buttons_node.child("Buttons").child("Blue").child("Normal").attribute("h").as_int() });
	Blue_Pushed.PushBack({ Buttons_node.child("Buttons").child("Blue").child("Pushed").attribute("x").as_int(),Buttons_node.child("Buttons").child("Blue").child("Pushed").attribute("y").as_int(),Buttons_node.child("Buttons").child("Blue").child("Pushed").attribute("w").as_int(),Buttons_node.child("Buttons").child("Blue").child("Pushed").attribute("h").as_int() });
	Blue_Enter.PushBack({ Buttons_node.child("Buttons").child("Blue").child("Enter").attribute("x").as_int(),Buttons_node.child("Buttons").child("Blue").child("Enter").attribute("y").as_int(),Buttons_node.child("Buttons").child("Blue").child("Enter").attribute("w").as_int(),Buttons_node.child("Buttons").child("Blue").child("Enter").attribute("h").as_int() });

	Yellow_Standard.PushBack({ Buttons_node.child("Buttons").child("Yellow").child("Normal").attribute("x").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Normal").attribute("y").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Normal").attribute("w").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Normal").attribute("h").as_int() });
	Yellow_Pushed.PushBack({ Buttons_node.child("Buttons").child("Yellow").child("Pushed").attribute("x").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Pushed").attribute("y").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Pushed").attribute("w").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Pushed").attribute("h").as_int() });
	Yellow_Enter.PushBack({ Buttons_node.child("Buttons").child("Yellow").child("Enter").attribute("x").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Enter").attribute("y").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Enter").attribute("w").as_int(),Buttons_node.child("Buttons").child("Yellow").child("Enter").attribute("h").as_int() });

	Pink_Standard.PushBack({ Buttons_node.child("Buttons").child("Pink").child("Normal").attribute("x").as_int(),Buttons_node.child("Buttons").child("Pink").child("Normal").attribute("y").as_int(),Buttons_node.child("Buttons").child("Pink").child("Normal").attribute("w").as_int(),Buttons_node.child("Buttons").child("Pink").child("Normal").attribute("h").as_int() });
	Pink_Pushed.PushBack({ Buttons_node.child("Buttons").child("Pink").child("Pushed").attribute("x").as_int(),Buttons_node.child("Buttons").child("Pink").child("Pushed").attribute("y").as_int(),Buttons_node.child("Buttons").child("Pink").child("Pushed").attribute("w").as_int(),Buttons_node.child("Buttons").child("Pink").child("Pushed").attribute("h").as_int() });
	Pink_Enter.PushBack({ Buttons_node.child("Buttons").child("Pink").child("Enter").attribute("x").as_int(),Buttons_node.child("Buttons").child("Pink").child("Enter").attribute("y").as_int(),Buttons_node.child("Buttons").child("Pink").child("Enter").attribute("w").as_int(),Buttons_node.child("Buttons").child("Pink").child("Enter").attribute("h").as_int() });


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
	Violet_Current_anim = &Violet_Standard;
	//Guitar texture
	guitar_tex = App->tex->Load("maps/Guitar_Sequence.png");
	Buttons_Texture = App->tex->Load("maps/Buttons_and_Notes.png");

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

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {
		Violet_Current_anim = &Violet_Pushed;
	}
	else
		Violet_Current_anim = &Violet_Standard;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
		Violet_Current_anim = &Violet_Enter;
	}

	 if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {
		 Blue_Current_anim = &Blue_Pushed;
	 }
	 else
		 Blue_Current_anim = &Blue_Standard;

	 if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
		 Blue_Current_anim = &Blue_Enter;
	 }

	 if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
		 Yellow_Current_anim = &Yellow_Pushed;
	 }
	 else
		 Yellow_Current_anim = &Yellow_Standard;

	 if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
		 Yellow_Current_anim = &Yellow_Enter;
	 }

	 if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT) {
		 Pink_Current_anim = &Pink_Pushed;
	 }
	 else
		 Pink_Current_anim = &Pink_Standard;

	 if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
		 Pink_Current_anim = &Pink_Enter;
	 }

	



	App->render->Blit(Buttons_Texture, 100, 100, &violet_Button);

	App->render->Blit(guitar_tex,1280/2-480/2 , 720-425, &current_anim->GetCurrentFrame());


	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2+25, 720-70, &Violet_Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2 + 135, 720 - 70, &Blue_Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2 + 245, 720 - 70, &Yellow_Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2 + 350, 720 - 70, &Pink_Current_anim->GetCurrentFrame());

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