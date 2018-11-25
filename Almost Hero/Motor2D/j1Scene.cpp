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

	p2List_item<Note*> *notes_item = notes.start;
	for (; notes_item != nullptr; notes_item = notes_item->next)
		notes_item->data->DestroyNote(notes_item->data);

	notes.clear();
	notes_positions.Clear();

	return true;
}

// Called before the first frame
bool j1Scene::Start()
{

	pugi::xml_parse_result result = Buttons_Document.load_file("Butons_Settings.xml");
	if (result == NULL)
		LOG("pugi error : %s", result.description());

	Buttons_node = Buttons_Document.child("config");

	//Notes Smashers
	smViolet = CreateSmasher(COLLIDER_SMASHER_VIOLET, Buttons_node, "Violet");
	smBlue = CreateSmasher(COLLIDER_SMASHER_BLUE, Buttons_node, "Blue");
	smYellow = CreateSmasher(COLLIDER_SMASHER_YELLOW, Buttons_node, "Yellow");
	smPink = CreateSmasher(COLLIDER_SMASHER_PINK, Buttons_node, "Pink");

	smViolet.Current_anim = &smViolet.Standard_anim;
	smBlue.Current_anim = &smBlue.Standard_anim;
	smYellow.Current_anim = &smYellow.Standard_anim;
	smPink.Current_anim = &smPink.Standard_anim;

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
	Bottom_Limit.x = 401;
	Bottom_Limit.y = 719;
	Bottom_Limit.w = 480;
	Bottom_Limit.h = 50;

	Bottom_coll = App->collisions->AddCollider(Bottom_Limit, COLLIDER_STATIC, this);

	notes_positions.PushBack(pos1);
	notes_positions.PushBack(pos2);
	notes_positions.PushBack(pos3);
	notes_positions.PushBack(pos4);
	notes_positions.PushBack(pos5);
	notes_positions.PushBack(pos6);
	notes_positions.PushBack(pos7); 
	notes_positions.PushBack(pos9);
	notes_positions.PushBack(pos10);
	notes_positions.PushBack(pos11);
	notes_positions.PushBack(pos12);
	notes_positions.PushBack(pos13);
	notes_positions.PushBack(pos14);
	notes_positions.PushBack(pos15);
	notes_positions.PushBack(pos16);
	notes_positions.PushBack(pos17);
	notes_positions.PushBack(pos18);
	notes_positions.PushBack(pos19);
	notes_positions.PushBack(pos20);
	notes_positions.PushBack(pos21);
	notes_positions.PushBack(pos22);
	notes_positions.PushBack(pos23);

	//notes_positions.PushBack(pos4);
	//notes_positions.PushBack(pos5);

	PERF_START(read_next_array_pos);
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

	HandleInput();
	
	 int y = 650;
	 int x = 400;

	//Blitting Guitar texture
	App->render->Blit(guitar_tex, x , 720 - 425, &Guitar.GetCurrentFrame());
	

	//Blitting Buttons textures
	App->render->Blit(Buttons_Texture, x + 25, y, &smViolet.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 135, y, &smBlue.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 245, y, &smYellow.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 350, y, &smPink.Current_anim->GetCurrentFrame());


	//Smashers colliders

	smViolet.smasher_collider->SetPos(x + smViolet.smasher_rect.w * 0.33f + 25, y + smViolet.smasher_rect.h * 0.48f);
	smBlue.smasher_collider->SetPos(x + smBlue.smasher_rect.w * 0.33f + 135, y + smBlue.smasher_rect.h * 0.48f);

	smYellow.smasher_collider->SetPos(x + smYellow.smasher_rect.w * 0.33f + 245, y + smYellow.smasher_rect.h * 0.48f);
	smPink.smasher_collider->SetPos(x + smPink.smasher_rect.w * 0.33f + 350, y + smPink.smasher_rect.h * 0.48f);


	if (read_next_array_pos.Read() >= 350) {

		ReadArray(notes_positions[counter]);
		read_next_array_pos.Start();
		counter++;

		if (counter == notes_positions.Count())
			counter = 0;
	}

	p2List_item<Note*> *notes_item = notes.start;
	for (; notes_item != nullptr; notes_item = notes_item->next) 
		notes_item->data->Update(dt);

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


Smasher j1Scene::CreateSmasher(COLLIDER_TYPE smasher_collider, pugi::xml_node &node, const char *color) {

	Smasher aux;
	aux.smasher_rect = LoadButtons(node, color);

	aux.Standard_anim.PushBack(SetNotesPushbacks(node, color, "Normal"));
	aux.Pushed_anim.PushBack(SetNotesPushbacks(node, color, "Pushed"));
	aux.Enter_anim.PushBack(SetNotesPushbacks(node, color, "Enter"));

	SDL_Rect button_collider_rect = { aux.smasher_rect.x + aux.smasher_rect.w * 0.4f, aux.smasher_rect.y - aux.smasher_rect.w * 0.4f, aux.smasher_rect.w * 0.4f, aux.smasher_rect.h * 0.15f };
	aux.smasher_collider = App->collisions->AddCollider(button_collider_rect, smasher_collider, this);

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

void j1Scene::HandleInput() {

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


	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y++;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y--;
}


void j1Scene::ReadArray(iPoint4d vec) {

	if (vec.x == 1)
		App->note->CreateNote(NOTE_VIOLET);

	if (vec.y == 1)
		App->note->CreateNote(NOTE_BLUE);

	if (vec.z == 1)
		App->note->CreateNote(NOTE_YELLOW);

	if (vec.k == 1)
		App->note->CreateNote(NOTE_PINK);

}