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

	//Notes Smashers
	smViolet = CreateSmasher(COLLIDER_SMASHER_VIOLET, Buttons_node, "Violet");
	smBlue = CreateSmasher(COLLIDER_SMASHER_BLUE, Buttons_node, "Blue");
	smYellow = CreateSmasher(COLLIDER_SMASHER_YELLOW, Buttons_node, "Yellow");
	smPink = CreateSmasher(COLLIDER_SMASHER_PINK, Buttons_node, "Pink");

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

	smViolet.Current_anim = &smViolet.Standard_anim;
	smBlue.Current_anim = &smBlue.Standard_anim;
	smYellow.Current_anim = &smYellow.Standard_anim;
	smPink.Current_anim = &smPink.Standard_anim;

	smViolet.smasher_collider = App->collisions->AddCollider(smViolet.smasher_rect, COLLIDER_SMASHER_VIOLET, this);
	smBlue.smasher_collider = App->collisions->AddCollider(smBlue.smasher_rect, COLLIDER_SMASHER_BLUE, this);
	smYellow.smasher_collider = App->collisions->AddCollider(smYellow.smasher_rect, COLLIDER_SMASHER_YELLOW, this);
	smPink.smasher_collider = App->collisions->AddCollider(smPink.smasher_rect, COLLIDER_SMASHER_PINK, this);


	//Notes
	/*violet_note = CreateNote(nIpos, 0, NOTE_VIOLET);
	blue_note = CreateNote(nIpos, 1, NOTE_BLUE);
	yellow_note = CreateNote(nIpos, 2, NOTE_YELLOW);
	pink_note = CreateNote(nIpos, 3, NOTE_PINK);*/

	//Guitar & Buttons texture
	guitar_tex = App->tex->Load("textures/Guitar_Sequence.png");
	Buttons_Texture = App->tex->Load("textures/Buttons_and_Notes.png");

	//Guitar animation Pushbacks
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

	//Notes deleter (at bottom of buttons, when notes cannot longer be pressed)
	Bottom_Limit.x = 643;
	Bottom_Limit.y = 617;
	Bottom_Limit.w = 480;
	Bottom_Limit.h = 50;

	Bottom_coll = App->collisions->AddCollider(Bottom_Limit, COLLIDER_STATIC, this);

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

	//Notes deleter blit & colider
	App->render->DrawQuad(Bottom_Limit, 255, 255, 255, 255);
	Bottom_coll->SetPos(Bottom_Limit.x, Bottom_Limit.y);

	//INPUTS
	//1 (Violet)
	 if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
		 smViolet.Current_anim = &smViolet.Pushed_anim;
	 else
		 smViolet.Current_anim = &smViolet.Standard_anim;

	 if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		 smViolet.Current_anim = &smViolet.Enter_anim;


	 //2 (Blue)
	 if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)
		 smBlue.Current_anim = &smBlue.Pushed_anim;
	 else
		 smBlue.Current_anim = &smBlue.Standard_anim;

	 if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		 smBlue.Current_anim = &smBlue.Enter_anim;


	 //3 (Yellow)
	 if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
		 smYellow.Current_anim = &smYellow.Pushed_anim;
	 else
		 smYellow.Current_anim = &smYellow.Standard_anim;

	 if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		 smYellow.Current_anim = &smYellow.Enter_anim;


	 //4 (Pink)
	 if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		 smPink.Current_anim = &smPink.Pushed_anim;
	 else
		 smPink.Current_anim = &smPink.Standard_anim;

	 if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		 smPink.Current_anim = &smPink.Enter_anim;


	 int y = 650;
	 int x = 400;

	//Blitting Guitar texture
	App->render->Blit(guitar_tex, x , 720 - 425, &Guitar.GetCurrentFrame());

	//Blitting Buttons textures
	App->render->Blit(Buttons_Texture, 100, 100, &smViolet.smasher_rect);
	App->render->Blit(Buttons_Texture, x + 25, y, &smViolet.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 135, y, &smBlue.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 245, y, &smYellow.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 350, y, &smPink.Current_anim->GetCurrentFrame());


	//Smashers colliders
	smBlue.smasher_collider->SetPos(x + 25, y);
	smViolet.smasher_collider->SetPos(x + 135, y);
	smPink.smasher_collider->SetPos(x + 245, y);
	smYellow.smasher_collider->SetPos(x + 350, y);

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

void j1Scene::MoveNote(Note* note) {

	note->scale += 0.002f;
	App->render->DrawQuad(note->note_rect, 0, 150, 0, 150, note->scale);

	//note->nPosition = fPoint(note->note_rect.x, note->note_rect.y);

	note->nPosition.x -= nVelocity.x;
	note->nPosition.y += nVelocity.y;

	note->note_rect = { (int)note->nPosition.x, (int)note->nPosition.y, 35, 35 };

	note->note_collider->SetPos(note->nPosition.x, note->nPosition.y);

}

Smasher j1Scene::CreateSmasher(COLLIDER_TYPE smasher_collider, pugi::xml_node &node, const char *color) {

	Smasher aux;
	aux.smasher_rect = LoadButtons(node, color);

	aux.Standard_anim.PushBack(SetNotesPushbacks(node, color, "Normal"));
	aux.Pushed_anim.PushBack(SetNotesPushbacks(node, color, "Pushed"));
	aux.Enter_anim.PushBack(SetNotesPushbacks(node, color, "Enter"));

	return aux;
}


SDL_Rect j1Scene::LoadButtons(pugi::xml_node &node, const char* color) {

	int x = node.child("Notes").child(color).attribute("x").as_int();
	int y = node.child("Notes").child(color).attribute("y").as_int();
	int w = node.child("Notes").child(color).attribute("w").as_int();
	int h = node.child("Notes").child(color).attribute("h").as_int();

	return { x, y, w, h };
}

SDL_Rect j1Scene::SetNotesPushbacks(pugi::xml_node &node, const char* color, const char* anim_name) {


	int x = node.child("Anims").child(color).child(anim_name).attribute("x").as_int();
	int y = node.child("Anims").child(color).child(anim_name).attribute("y").as_int();
	int w = node.child("Anims").child(color).child(anim_name).attribute("w").as_int();
	int h = node.child("Anims").child(color).child(anim_name).attribute("h").as_int();

	return { x, y, w, h };

}
