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

	//RELEASE(violet_note->note_tex);
	//RELEASE(violet_note);
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
	/*violet_note = CreateNote(nIpos, 0, NOTE_VIOLET);
	blue_note = CreateNote(nIpos, 1, NOTE_BLUE);
	yellow_note = CreateNote(nIpos, 2, NOTE_YELLOW);
	pink_note = CreateNote(nIpos, 3, NOTE_PINK);*/


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

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
		Violet_Current_anim = &Violet_Pushed;
	else
		Violet_Current_anim = &Violet_Standard;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		Violet_Current_anim = &Violet_Enter;


	 if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)
		 Blue_Current_anim = &Blue_Pushed;
	 else
		 Blue_Current_anim = &Blue_Standard;

	 if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		 Blue_Current_anim = &Blue_Enter;


	 if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
		 Yellow_Current_anim = &Yellow_Pushed;
	 else
		 Yellow_Current_anim = &Yellow_Standard;

	 if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		 Yellow_Current_anim = &Yellow_Enter;


	 if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		 Pink_Current_anim = &Pink_Pushed;
	 else
		 Pink_Current_anim = &Pink_Standard;

	 if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		 Pink_Current_anim = &Pink_Enter;


//Blitting Guitar texture
	App->render->Blit(guitar_tex,1280/2-480/2 , 720-425, &current_anim->GetCurrentFrame());

//Blitting Buttons textures
	App->render->Blit(Buttons_Texture, 100, 100, &violet_Button);
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2+25, 720-70, &Violet_Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2 + 135, 720 - 70, &Blue_Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2 + 245, 720 - 70, &Yellow_Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, 1280 / 2 - 480 / 2 + 350, 720 - 70, &Pink_Current_anim->GetCurrentFrame());


	//Smashers blit and collider
	App->render->DrawQuad(smBlue.smasher_rect, 0, 0, 255, 255);
	smBlue.smasher_collider->SetPos(smBlue.smasher_rect.x, smBlue.smasher_rect.y);

	App->render->DrawQuad(smViolet.smasher_rect, 150, 0, 255, 255);
	smViolet.smasher_collider->SetPos(smViolet.smasher_rect.x, smViolet.smasher_rect.y);

	App->render->DrawQuad(smPink.smasher_rect, 255, 0, 255, 255);
	smPink.smasher_collider->SetPos(smPink.smasher_rect.x, smPink.smasher_rect.y);

	App->render->DrawQuad(smYellow.smasher_rect, 255, 200, 0, 255);
	smYellow.smasher_collider->SetPos(smYellow.smasher_rect.x, smYellow.smasher_rect.y);

	//Notes drawing & moving
	//MoveNote(violet_note);
	//MoveNote(blue_note);
	//MoveNote(yellow_note);
	//MoveNote(pink_note);

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

	//if (c1->type == COLLIDER_NOTE && c2->type == COLLIDER_STATIC) { //If for some reason collision fails, try to check both c1/c2 and c2/c1 instead of only c1/c2

	//
	//	NOTE_COLOR aux_col = violet_note->nColor;
	//	violet_note->note_collider->to_delete = true;
	//	RELEASE(violet_note);

	//	if (violet_note == nullptr)
	//		violet_note = CreateNote(nIpos, 0, aux_col);
	//
	//}
	//
	//if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_VIOLET)) {

	//	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

	//		NOTE_COLOR aux_col = violet_note->nColor;
	//		violet_note->note_collider->to_delete = true;
	//		RELEASE(violet_note);

	//		if (violet_note == nullptr)
	//			violet_note = CreateNote(nIpos, 0, aux_col);


	//	}
	//}

	//if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_BLUE)) {

	//	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

	//		NOTE_COLOR aux_col = blue_note->nColor;
	//		blue_note->note_collider->to_delete = true;
	//		RELEASE(blue_note);

	//		if (blue_note == nullptr)
	//			blue_note = CreateNote(nIpos, 1, aux_col);


	//	}
	//}

	//if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_YELLOW)) {

	//	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

	//		NOTE_COLOR aux_col = yellow_note->nColor;
	//		yellow_note->note_collider->to_delete = true;
	//		RELEASE(yellow_note);

	//		if (yellow_note == nullptr)
	//			yellow_note = CreateNote(nIpos, 2, aux_col);


	//	}
	//}

	//if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_PINK)) {

	//	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

	//		NOTE_COLOR aux_col = pink_note->nColor;
	//		pink_note->note_collider->to_delete = true;
	//		RELEASE(pink_note);

	//		if (pink_note == nullptr)
	//			pink_note = CreateNote(nIpos, 3, aux_col);


	//	}
	//}
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

void j1Scene::MoveNote(Note* note) {

	note->scale += 0.002f;
	App->render->DrawQuad(note->note_rect, 0, 150, 0, 150, note->scale);

	//note->nPosition = fPoint(note->note_rect.x, note->note_rect.y);

	note->nPosition.x -= nVelocity.x;
	note->nPosition.y += nVelocity.y;

	note->note_rect = { (int)note->nPosition.x, (int)note->nPosition.y, 35, 35 };

	note->note_collider->SetPos(note->nPosition.x, note->nPosition.y);

}
