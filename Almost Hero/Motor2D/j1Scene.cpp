#define _CRT_SECURE_NO_WARNINGS

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
#include "j1Fonts.h"
#include "Video.h"


/*--------------------------------------------------------------------

HANDLEINPUT()  -----> 1234 + ENTER
HANDLEINPUT2() -----> 1234

--------------------------------------------------------------------*/

//GENERAL METHODS
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
	if (current_screen == GAME) {

		p2List_item<Note*> *notes_item = notes.start;
		for (; notes_item != nullptr; notes_item = notes_item->next)
			notes_item->data->DestroyNote(notes_item->data);

		if (notes.count() > 0)
			notes.clear();

		if (notes_positions.Count() > 0)
			notes_positions.Clear();

	}

	return true;
}

// Called before the first frame
bool j1Scene::Start()
{

	current_screen = MAIN_MENU;

	smViolet.Current_anim = &smViolet.Standard_anim;
	smBlue.Current_anim = &smBlue.Standard_anim;
	smYellow.Current_anim = &smYellow.Standard_anim;
	smPink.Current_anim = &smPink.Standard_anim;

	//Guitar & Buttons texture
	Multiplier_tex = App->tex->Load("textures/Multiplliers.png");
	PowerUp_Light_tex = App->tex->Load("textures/Power_Up_Effects.png");
	guitar_tex = App->tex->Load("textures/Guitar_Sequence.png");
	Buttons_Texture = App->tex->Load("textures/Buttons_and_Notes.png");

	//Main Menu & Game Over Screen
	Main_Menu_txtr = App->tex->Load("textures/Start_Image.png");
	Game_Over_txtr = App->tex->Load("textures/GameOver_Image.png");

	//Pushbacks
	LoadPushbacks();

	//Notes deleter (at bottom of buttons, when notes cannot longer be pressed)
	Bottom_Limit.x = 401;
	Bottom_Limit.y = 719;
	Bottom_Limit.w = 480;
	Bottom_Limit.h = 50;

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

	if (current_screen == GAME) 
		HandleGameScreen(dt);

	else if (current_screen == MAIN_MENU) {

		SDL_Rect img_rect = { 0, 0, 1920, 1080 };
		App->render->Blit(Main_Menu_txtr, 0, 0, &img_rect);

		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

			change_input = false;
			ChangeScreen(GAME);
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

			change_input = true;
			ChangeScreen(GAME);
		}

	}

	else if (current_screen == GAME_OVER) {

		SDL_Rect img_rect = { 0, 0, 1920, 1080 };
		App->render->Blit(Game_Over_txtr, 0, 0, &img_rect);

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			ChangeScreen(MAIN_MENU);

	}
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



//SCENE METHODS
void j1Scene::HandleGeneralInput() {

	if (App->input->GetKey(SDL_SCANCODE_S) || App->input->GetKey(SDL_SCANCODE_ESCAPE))
		App->SaveGame("saved_data.xml");

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y++;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y--;
}


void j1Scene::HandleGameScreen(float dt) {

	//Notes deleter blit & colider
	App->render->DrawQuad(Bottom_Limit, 255, 255, 255, 255);
	Bottom_coll->SetPos(Bottom_Limit.x, Bottom_Limit.y);

	HandleGeneralInput();

	if (!change_input)
		HandleInput();
	else
		HandleInput2();

	int y = 650;
	int x = 400;

	//Blitting Guitar texture
	App->render->Blit(guitar_tex, x, 720 - 425, &Guitar.GetCurrentFrame());

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

	//Blitting Light PowerUps
	App->render->Blit(PowerUp_Light_tex, x + 60, 720 - 430, &Left_Light.GetCurrentFrame(), 1, 1, 22, 60, 0);
	App->render->Blit(PowerUp_Light_tex, x + 225, 720 - 370, &Right_Light.GetCurrentFrame(), 1, 1, -19, 0, 0);

	if (App->note->numNotes > 10 && App->note->numNotes <= 20) {
		Multipliers_current_anim = &x2;
		multiplier = 2;
	}
	else if (App->note->numNotes > 20 && App->note->numNotes <= 30) {
		Multipliers_current_anim = &x3;
		multiplier = 3;
	}
	else if (App->note->numNotes > 30) {
		Multipliers_current_anim = &x4;
		multiplier = 4;
	}
	else {
		Multipliers_current_anim = &x1;
		multiplier = 1;
	}

	//Blitting Multiplier
	App->render->Blit(Multiplier_tex, -25, 300, &Multipliers_current_anim->GetCurrentFrame());
	sprintf(score_text, "%d", score);
	App->font->CalcSize(score_text, scoreRect.w, scoreRect.h, App->font->fonts.end->data);
	App->render->Blit(App->font->Print(score_text, { 30,119,255,255 }, App->font->fonts.end->data), 900, 400, &scoreRect, 1, false);

	p2List_item<Note*> *notes_item = notes.start;
	for (; notes_item != nullptr; notes_item = notes_item->next)
		notes_item->data->Update(dt);

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		ChangeScreen(GAME_OVER);
}


void j1Scene::HandleInput() {

	//INPUTS
	//1 (Violet)
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
		smViolet.Current_anim = &smViolet.Pushed_anim;
	else
		smViolet.Current_anim = &smViolet.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {

		smViolet.Current_anim = &smViolet.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}


	//2 (Blue)
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)
		smBlue.Current_anim = &smBlue.Pushed_anim;
	else
		smBlue.Current_anim = &smBlue.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {

		smBlue.Current_anim = &smBlue.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}

	}


	//3 (Yellow)
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
		smYellow.Current_anim = &smYellow.Pushed_anim;
	else
		smYellow.Current_anim = &smYellow.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
		
		smYellow.Current_anim = &smYellow.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}


	//4 (Pink)
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		smPink.Current_anim = &smPink.Pushed_anim;
	else
		smPink.Current_anim = &smPink.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT) {
	
		smPink.Current_anim = &smPink.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}

}


void j1Scene::HandleInput2() {

	//INPUTS
	//1 (Violet)
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {

		smViolet.Current_anim = &smViolet.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}
	else
		smViolet.Current_anim = &smViolet.Standard_anim;


	//2 (Blue)
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {

		smBlue.Current_anim = &smBlue.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}
	else
		smBlue.Current_anim = &smBlue.Standard_anim;


	//3 (Yellow)
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
	
		smYellow.Current_anim = &smYellow.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}
	else
		smYellow.Current_anim = &smYellow.Standard_anim;


	//4 (Pink)
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT) {
	
		smPink.Current_anim = &smPink.Enter_anim;
		if (App->note->colliding == false) {

			if (App->render->DoCameraShake == false) {
				App->render->DoCameraShake = true;
				App->render->power = 2.0f;
				App->render->Time_Doing_Shake = 0.2f;
				PERF_START(App->render->CameraShake_Time);
			}
		}
	}
	else
		smPink.Current_anim = &smPink.Standard_anim;

}


bool j1Scene::Save(pugi::xml_node& data) const
{
	pugi::xml_node scen = data.append_child("scene");

	scen.append_attribute("score") = score;
	scen.append_attribute("total_smashed_notes") = App->note->total_smashed_notes;
	scen.append_attribute("total_song_notes_before_quiting_or_ending") = App->note->total_song_notes;

	return true;
}


void j1Scene::ChangeScreen(int screen) {

	if (current_screen == GAME) {

		App->collisions->CleanUp();

		p2List_item<Note*> *notes_item = notes.start;
		for (; notes_item != nullptr; notes_item = notes_item->next)
			notes_item->data->DestroyNote(notes_item->data);

		if (notes.count() > 0)
			notes.clear();

		if (notes_positions.Count() > 0)
			notes_positions.Clear();

		if (App->video->IsPlaying())
			App->video->StopVideo();

	}

	if (screen == GAME) {

		current_screen = GAME;

		pugi::xml_parse_result result = Buttons_Document.load_file("Butons_Settings.xml");
		if (result == NULL)
			LOG("pugi error : %s", result.description());

		Buttons_node = Buttons_Document.child("config");
		App->font->Load("fonts/ShonenPunk custom.ttf", 60);

		//Notes Smashers
		smViolet = CreateSmasher(COLLIDER_SMASHER_VIOLET, Buttons_node, "Violet");
		smBlue = CreateSmasher(COLLIDER_SMASHER_BLUE, Buttons_node, "Blue");
		smYellow = CreateSmasher(COLLIDER_SMASHER_YELLOW, Buttons_node, "Yellow");
		smPink = CreateSmasher(COLLIDER_SMASHER_PINK, Buttons_node, "Pink");

		Bottom_coll = App->collisions->AddCollider(Bottom_Limit, COLLIDER_STATIC, this);

		PERF_START(read_next_array_pos);

		PERF_START(App->note->Violet_collided_timer);
		PERF_START(App->note->Blue_collided_timer);
		PERF_START(App->note->Yellow_collided_timer);
		PERF_START(App->note->Pink_collided_timer);

		PERF_START(App->note->General_collided_timer);

		LoadSongArray();
		multiplier = 1;
		score = 0;

		App->video->PlayVideo("video/GodDamn_NoAudio2.ogv", { 0,-50,1280,850 });

	}
	else if (screen == MAIN_MENU)
		current_screen = MAIN_MENU;

	else if (screen == GAME_OVER)
		current_screen = GAME_OVER;

}



//CREATORS & LOADERS
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


void j1Scene::UpdateMultiplier() {

	multiplier++;
	if (multiplier > 4) {
		multiplier = 1;
	}
	switch (multiplier)
	{
	case 1:
		Multipliers_current_anim = &x1;
		break;
	case 2:
		Multipliers_current_anim = &x2;
		break;
	case 3:
		Multipliers_current_anim = &x3;
		break;
	case 4:
		Multipliers_current_anim = &x4;
		break;
	default:
		break;
	}
}


void j1Scene::LoadSongArray() {

	pugi::xml_parse_result result = Notes_Array_Document.load_file("Notes_Settings.xml");
	if (result == NULL)
		LOG("pugi error : %s", result.description());

	Notes_Position_node = Notes_Array_Document.child("array");

	pugi::xml_node node = Notes_Position_node;
	for (node = node.child("pos"); node; node = node.next_sibling("pos")) {

		int x = node.attribute("x").as_int();
		int y = node.attribute("y").as_int();
		int z = node.attribute("z").as_int();
		int k = node.attribute("k").as_int();

		iPoint4d pos = iPoint4d(x, y, z, k);
		notes_positions.PushBack(pos);

	}
}


void j1Scene::LoadPushbacks() {

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

	countGuitar = { 0,0 };

	//Left Light animation Pushbacks
	for (int i = 0; i < 12; ++i) {
		Left_Light.PushBack({ countGuitar.x, countGuitar.y, 230, 450 });
		countGuitar.x += 230;
		if (countGuitar.x >= 230 * 5) {
			countGuitar.y += 450;
			countGuitar.x = 0;
		}
	}
	Left_Light.speed = 0.30f;
	Left_Light.loop = true;

	//Right Light animation Pushbacks
	for (int i = 12; i < 24; ++i) {
		Right_Light.PushBack({ countGuitar.x, countGuitar.y, 230, 450 });
		countGuitar.x += 230;
		if (countGuitar.x >= 230 * 5) {
			countGuitar.y += 450;
			countGuitar.x = 0;
		}
	}
	Right_Light.speed = 0.30f;
	Right_Light.loop = true;

	//Setting animation multiplier
	countGuitar = { 0,0 };
	for (int i = 0; i < 9; ++i) {
		x1.PushBack({ countGuitar.x, countGuitar.y, 400, 400 });
		countGuitar.x += 400;
		if (countGuitar.x >= 400 * 6) {
			countGuitar.y += 400;
			countGuitar.x = 0;
		}
	}
	for (int i = 9; i < 18; ++i) {
		x2.PushBack({ countGuitar.x, countGuitar.y, 400, 400 });
		countGuitar.x += 400;
		if (countGuitar.x >= 400 * 6) {
			countGuitar.y += 400;
			countGuitar.x = 0;
		}
	}
	for (int i = 18; i < 27; ++i) {
		x3.PushBack({ countGuitar.x, countGuitar.y, 400, 400 });
		countGuitar.x += 400;
		if (countGuitar.x >= 400 * 6) {
			countGuitar.y += 400;
			countGuitar.x = 0;
		}
	}
	for (int i = 27; i < 36; ++i) {
		x4.PushBack({ countGuitar.x, countGuitar.y, 400, 400 });
		countGuitar.x += 400;
		if (countGuitar.x >= 400 * 6) {
			countGuitar.y += 400;
			countGuitar.x = 0;
		}
	}

	x1.speed = x2.speed = x3.speed = x4.speed = 0.25f;
	Multipliers_current_anim = &x1;

}