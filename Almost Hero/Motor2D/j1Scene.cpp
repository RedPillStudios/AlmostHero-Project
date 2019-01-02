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
	float scale = 1.0f;

	volume = 90;

	Main_MenuScene = App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(0, 0), { 0,0,1280,720 }, BLITTING, { 0,0,1280,720 });
	Main_MenuScene->texture = App->tex->Load("gui/Main_Menu_LIGHT_ON.png");
	Main_MenuScene->texture_Off = App->tex->Load("gui/Main_Menu_LIGHT_OFF.png");
	Main_MenuScene->Current_Texture = Main_MenuScene->texture;

	GameOverScene = App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(0, 0), { 0,0,1280,720 }, BLITTING, { 0,0,1280,720 });
	GameOverScene->isActive = false;
	GameOverScene->texture = App->tex->Load("gui/GAME_OVER_ON.png");
	GameOverScene->texture_Off = App->tex->Load("gui/GAME_OVER_OFF.png");
	GameOverScene->Current_Texture = GameOverScene->texture;

	BoostersPosition = App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(120, 480), { 838,6,425,123 }, NONE_LOGIC, {838,6,425,123 },NULL_RECT,0.9f);
	BoostersPosition->isActive = false;
	PowerUPActive = App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(680, 480), { 697, 133, 411, 104 }, NONE_LOGIC, { 697, 133, 411, 104 },NULL_RECT,0.89f);;
	PowerUPActive->isActive = false;
	Boosters_Position_button = App->gui->Add_UIElement(BAR, iPoint(510, 500), { 1104, 436, 75, 75 }, PUSH, { 1029, 436, 75, 75 });
	Boosters_Position_button->isActive = false;
	PowerUpActive_button = App->gui->Add_UIElement(BAR, iPoint(1080, 500), { 1104, 436, 75, 75 }, PUSH, { 1029, 436, 75, 75 });
	PowerUpActive_button->isActive = false;


	Play = App->gui->Add_UIElement(BUTTON, iPoint(514, 380), { 252, 5, 252, 143 }, ACTIVEWIN, { 0, 5, 252, 143 });
	Settings = App->gui->Add_UIElement(BUTTON, iPoint(475, 500), { 330, 148, 330, 131 }, ACTIVEWIN, { 0, 148, 330, 131 });
	Mode1 = App->gui->Add_UIElement(BUTTON, iPoint(280, 360), { 689, 283, 252, 124 }, PLAY, { 437, 283, 252, 124 });
	Mode1->isActive = false;
	Mode2 = App->gui->Add_UIElement(BUTTON, iPoint(750, 360), { 269, 414, 264, 132 }, PLAY, { 5, 414, 264, 132 });
	Mode2->isActive = false;
	LogoCitm= App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(10, 10), { 0, 0, 462, 141 }, NONE_LOGIC, { 0, 0, 462, 141 },NULL_RECT,0.55);
	LogoCitm->texture = App->tex->Load("gui/logocitm.png");

	versionLabel= App->gui->Add_UIElement(LABEL, iPoint(800, 690), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 0.8f, SDL_Color{ 255,255,255,255 }, nullptr, "Version 0.5 Prototype. Licensed under MIT");

	Volumen = App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(200, 380), { 507, 5, 303, 130 }, NONE_LOGIC, { 507, 5, 303, 130 });
	Volumen->isActive = false;

	Volume_Background = App->gui->Add_UIElement(NON_INTERACTIVE, iPoint(558, 395), { 579, 579,409, 57 }, BACKVOLUME, { 579, 579,409, 57 });
	Volume_Background->isActive = false;

	Volume_Bar = App->gui->Add_UIElement(BAR, iPoint(540, 360), { 561, 417, 250, 127 }, DRAGVOLUME, { 561, 417, 461, 127 });
	Volume_Bar->isActive = false;
	Quit = App->gui->Add_UIElement(BUTTON, iPoint(550, 620), { 188, 304, 188, 77 }, QUIT, { 0, 304, 188, 77 });

	Credits = App->gui->Add_UIElement(BAR, iPoint(920, 610), { 969, 336, 328, 96 }, BLITTING, { 969, 240, 328, 96 }, NULL_RECT, 0.9f);
	Credits->CurrentRect = &Credits->UI_Rect_Active;
	Credits->Current_Texture = Credits->texture;

	Tip1 = App->gui->Add_UIElement(LABEL, iPoint(220, 660), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.2f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: Really guys, don't forget the README!!!");
	Tip1->isActive = false;
	Tip2 = App->gui->Add_UIElement(LABEL, iPoint(20, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: Pay attention to the icon and approach the keyboard... Use it as a Guitar! FEEL THE POWER");
	Tip2->isActive = false;
	Tip3 = App->gui->Add_UIElement(LABEL, iPoint(110, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: If your experience with mode 1 was very disgusting, try the mode2 LOSER");
	Tip3->isActive = false;
	Tip4 = App->gui->Add_UIElement(LABEL, iPoint(40, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: Remember to do the Questionaire and send us the Data, unless you want us to FAIL");
	Tip4->isActive = false;
	Tip5 = App->gui->Add_UIElement(LABEL, iPoint(20, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: We supose that work on this until 6am everyday will make us work with rockstar... Don't?");
	Tip5->isActive = false;
	Tip6 = App->gui->Add_UIElement(LABEL, iPoint(35, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: Hope that Rick is happy with this and put us on King or something... We are ready right?");
	Tip6->isActive = false;
	Tip7 = App->gui->Add_UIElement(LABEL, iPoint(35, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: This game is unbreakable... Just as Spain");
	Tip7->isActive = false;
	Tip8 = App->gui->Add_UIElement(LABEL, iPoint(35, 640), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.0f, SDL_Color{ 255,255,255,255 }, nullptr, "Tip: If you don't fail any note you'll fly high like Carrero");
	Tip8->isActive = false;
	TipPause = App->gui->Add_UIElement(LABEL, iPoint(400, 175), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.3f, SDL_Color{ 255,255,255,255 }, nullptr, "PRess Esc to resume the game");
	TipPause->isActive = false;

	Pause_WarnOnVideo = App->gui->Add_UIElement(LABEL, iPoint(145, 50), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.2f, SDL_Color{ 255,255,255,255 }, nullptr, "They Video will not keep playing. Sorry for the inconveniance");
	Pause_WarnOnVideo->isActive = false;
	Pause_WarnOnVideo2 = App->gui->Add_UIElement(LABEL, iPoint(80, 85), NULL_RECT, NONE_LOGIC, NULL_RECT, NULL_RECT, 1.2f, SDL_Color{ 255,255,255,255 }, nullptr, "this is a prototype under construction if you play again, video will too");
	Pause_WarnOnVideo2->isActive = false;

	Pause = App->gui->Add_UIElement(BAR, iPoint(400, 180), { 5, 548, 553, 224 }, BLITTING, { 5, 772, 553, 224 });
	Pause->isActive = false;
	Pause->CurrentRect = &Pause->UI_Rect_Active;
	Pause->Current_Texture = Pause->texture;

	Feedback = App->gui->Add_UIElement(BAR, iPoint(15, 550), { 579, 820, 384, 162 }, BLITTING, { 579, 658, 384, 162 });
	Feedback->CurrentRect = &Feedback->UI_Rect_Active;
	Feedback->Current_Texture = Feedback->texture;

	UI_Elements_List.add(Main_MenuScene);
	UI_Elements_List.add(LogoCitm);
	UI_Elements_List.add(Play);
	UI_Elements_List.add(Settings);
	UI_Elements_List.add(Credits);
	UI_Elements_List.add(Mode1);
	UI_Elements_List.add(Mode2);
	UI_Elements_List.add(Quit);
	UI_Elements_List.add(Volumen);
	UI_Elements_List.add(Volume_Background);
	UI_Elements_List.add(Volume_Bar);
	UI_Elements_List.add(BoostersPosition);
	UI_Elements_List.add(Boosters_Position_button);
	UI_Elements_List.add(PowerUPActive);
	UI_Elements_List.add(PowerUpActive_button);
	UI_Elements_List.add(versionLabel);
	UI_Elements_List.add(Feedback);
	UI_Elements_List.add(Pause);
	/*UI_Elements_List.add(Pause_WarnOnVideo);
	UI_Elements_List.add(Pause_WarnOnVideo2);*/

	smViolet.Current_anim = &smViolet.Standard_anim;
	smBlue.Current_anim = &smBlue.Standard_anim;
	smYellow.Current_anim = &smYellow.Standard_anim;
	smPink.Current_anim = &smPink.Standard_anim;

	//Guitar & Buttons texture
	Multiplier_tex = App->tex->Load("textures/Multiplliers.png");
	PowerUp_Light_tex = App->tex->Load("textures/Power_Up_Effects.png");
	guitar_tex = App->tex->Load("textures/Guitar_Sequence.png");
	Buttons_Texture = App->tex->Load("textures/Buttons_and_Notes.png");
	KeyboardAnimation_Text = App->tex->Load("textures/Keyboard_Rotate.png");
	keyboardText = App->tex->Load("textures/Keyboard_Alone.png");
	multiplier_Head_tex = App->tex->Load("textures/Multiplier_Head.png");
	PowerUP_counter_tex = App->tex->Load("textures/PowerUP_Counter.png");
	Boosters_tex = App->tex->Load("textures/Boosters_In_Screen.png");
	Credits_tex = App->tex->Load("textures/Credits.png");
	Under_Notes_tex = App->tex->Load("textures/UnderNotes.png");

	current_screen = MAIN_MENU;
	App->audio->ControlMUSVolume(volume);
	App->audio->PlayMusic("audio/music/MainMenu_Sound.ogg", 1);
	On_top_buttons_SFX = App->audio->LoadFx("audio/fx/On_Top_Buttons.wav");

	//Game Over Screen
	Game_Over_txtr = App->tex->Load("textures/GameOver_Image.png");

	Failnote_SFX = App->audio->LoadFx("audio/fx/fail_notes_effects.wav");
	gameOver_FX = App->audio->LoadFx("audio/fx/Guitarra_chunga_para_Lucho__Co.wav");

	//Pushbacks
	LoadPushbacks();

	PowerUP_counter = {0, 0, 160, 292 };

	//Notes deleter (at bottom of buttons, when notes cannot longer be pressed)
	Bottom_Limit.x = 401;
	Bottom_Limit.y = 719;
	Bottom_Limit.w = 480;
	Bottom_Limit.h = 50;

	Credits_Rect = { 0,0,700,300};

	App->audio->ControlSFXVolume(90);
	PauseGame = false;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	if (current_screen == GAME) {

		if (read_next_array_pos.ReadMs() >= 97 && keep_reading == true) {

			ReadArray(notes_positions[counter]);
			read_next_array_pos.Start();
			counter++;

			if (counter == notes_positions.Count()) {
				keep_reading = false;
				App->audio->PauseMusic();
				App->video->StopVideo();
				end_timer.Start();
			}
		}

		if (keep_reading == false && end_timer.ReadSec() > 5) {

			if (App->audio->MusicPaused() == true)
				App->audio->ResumeMusic();
			Pause->isActive = false;
			TipPause->isActive = false;
			GameOverScene->isActive = true;
			App->SaveGame("saved_data.xml");
			ChangeScreen(GAME_OVER);
			Quit->isActive = !Quit->isActive;

			
		}
	}

	if (current_screen == GAME && App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {

		Pause->isActive = !Pause->isActive;
		TipPause->isActive = !TipPause->isActive;
		Quit->isActive =!Quit->isActive;
		PauseGame = !PauseGame;
		Pause_WarnOnVideo->isActive = !Pause_WarnOnVideo->isActive;
		Pause_WarnOnVideo2->isActive = !Pause_WarnOnVideo2->isActive;
	}

	lastMousePos = newMousePos;
	App->input->GetMousePosition(newMousePos.x, newMousePos.y);
	p2List_item<UI_Element*>*UI_Item = UI_Elements_List.end;
	for (; UI_Item != nullptr; UI_Item = UI_Item->prev) {
		if (UI_Item->data->isActive) {
			if (UI_Item->data->Logic == BLITTING) {
				UI_Item->data->Blitter();
				if (UI_Item->data == Feedback) {
					if (UI_Item->data->onTop()) {
						UI_Item->data->CurrentRect = &UI_Item->data->UI_Rect_Active;
						if (UI_Item->data->Clicked()) {
							UI_Item->data->goWeb("https://docs.google.com/forms/d/e/1FAIpQLSct2409cHzdKPBmRW8pXSJ8cxh3uVCViAKXwFkYCZn7wYRe0w/viewform");
						}
					}
				}
				else if (UI_Item->data == Credits) {
					if (UI_Item->data->onTop()) {
						UI_Item->data->CurrentRect = &UI_Item->data->UI_Rect_Active;
						if (UI_Item->data->Clicked()) {
							for (p2List_item<UI_Element*>*UI_Item2 = UI_Elements_List.start; UI_Item2 != nullptr; UI_Item2 = UI_Item2->next) {
								if (UI_Item2->data != Main_MenuScene&&UI_Item2->data != Quit)
									UI_Item2->data->isActive = false;
							}
							creditsisActive = true;
						}
					}
				}
			}
			if (UI_Item->data->Logic == PUSH) {
				if (UI_Item->data == Boosters_Position_button) {
					if (ActivatePlaytestBoosterCentered==true) {
						UI_Item->data->CurrentRect = &UI_Item->data->UI_Rect_Active;
					}else
						UI_Item->data->CurrentRect = &UI_Item->data->UI_Rect;
					if (UI_Item->data->Clicked()) {
						ActivatePlaytestBoosterCentered = !ActivatePlaytestBoosterCentered;
					}
				}
				if (UI_Item->data == PowerUpActive_button) {
					if (ActivatePlaytestPowerUp==true) {
						UI_Item->data->CurrentRect = &UI_Item->data->UI_Rect_Active;
					}
					else
						UI_Item->data->CurrentRect = &UI_Item->data->UI_Rect;
					if (UI_Item->data->Clicked()) {
						ActivatePlaytestPowerUp = !ActivatePlaytestPowerUp;
					}
				}
			}
			if (UI_Item->data->Logic == ACTIVEWIN) {
				if (UI_Item->data->Clicked()) {
					if (UI_Item->data == Play) {
						UI_Item->data->Deactive(Settings);
						UI_Item->data->Deactive(Play);
						UI_Item->data->Active(Mode1);
						UI_Item->data->Active(Mode2);
					}
					else if (UI_Item->data == Settings) {
						UI_Item->data->Deactive(Play);
						UI_Item->data->Deactive(Settings);
						UI_Item->data->Deactive(LogoCitm);
						UI_Item->data->Deactive(Feedback);
						UI_Item->data->Deactive(Credits);
						UI_Item->data->Active(Volumen);
						UI_Item->data->Active(Volume_Background);
						UI_Item->data->Active(Volume_Bar);
						UI_Item->data->Active(BoostersPosition);
						UI_Item->data->Active(PowerUPActive);
						UI_Item->data->Active(PowerUpActive_button);
						UI_Item->data->Active(Boosters_Position_button);
					}
				}
			}
			if (UI_Item->data->Logic == DRAGVOLUME) {
				if (Volume_Background->Clicked()) {
					UI_Item->data->VolumeControl(newMousePos, lastMousePos,volume);
					App->audio->ControlMUSVolume(volume);
				}
			}
			if (UI_Item->data->Logic == PLAY) {
				if (UI_Item->data->Clicked()) {
					if (UI_Item->data == Mode1) {
						current_screen=TIP;
						change_input = false;
						PERF_START(TipScreen);
						for (p2List_item<UI_Element*>*UI_Item2 = UI_Elements_List.start; UI_Item2 != nullptr; UI_Item2 = UI_Item2->next) {
							if (UI_Item2->data != Main_MenuScene)
								UI_Item2->data->isActive = false;
						}

						}
					else if (UI_Item->data == Mode2) {
						current_screen = TIP;
						change_input = true;
						PERF_START(TipScreen);
						for (p2List_item<UI_Element*>*UI_Item2 = UI_Elements_List.start; UI_Item2 != nullptr; UI_Item2 = UI_Item2->next) {
							if (UI_Item2->data != Main_MenuScene)
								UI_Item2->data->isActive = false;
						}
					}
					int a = rand() % 8;
					switch (a)
					{
					case 0:
						Tip1->isActive = true;
						break;
					case 1:
						Tip2->isActive = true;
						break;
					case 2:
						Tip3->isActive = true;
						break;
					case 3:
						Tip4->isActive = true;
						break;
					case 4:
						Tip5->isActive = true;
						break;
					case 5:
						Tip6->isActive = true;
						break;
					case 6:
						Tip7->isActive = true;
						break;
					case 7:
						Tip8->isActive = true;
						break;
					}
				}
			}
			if ((UI_Item->data->Logic == QUIT)) {

				if (UI_Item->data->Clicked()) {

					if (Play->isActive == false && current_screen==MAIN_MENU) {
						for (p2List_item<UI_Element*>*UI_Item2 = UI_Elements_List.start; UI_Item2 != nullptr; UI_Item2 = UI_Item2->next) {

							if( UI_Item2->data != Main_MenuScene)
								UI_Item2->data->isActive = false;
						}

						Quit->isActive = true;
						Play->isActive = true;
						LogoCitm->isActive = true;
						Settings->isActive = true;
						Feedback->isActive = true;
						Credits->isActive = true;
						versionLabel->isActive = true;
						Credits->isActive = true;
						creditsisActive = false;//this makes the credits appear or not
						Credits_Rect.y = 0;
					}
					else if (Play->isActive == true && current_screen == MAIN_MENU)
						return false;

					else if (current_screen == GAME) {

						if(App->audio->MusicPaused() == true)
							App->audio->ResumeMusic();
						Pause->isActive = false;
						Pause_WarnOnVideo->isActive = false;
						Pause_WarnOnVideo2->isActive = false;
						TipPause->isActive = false;
						Pause_WarnOnVideo->isActive = false;
						Pause_WarnOnVideo2->isActive = false;
						GameOverScene->isActive=true;
						App->SaveGame("saved_data.xml");
						ChangeScreen(GAME_OVER);
					}

					else if (current_screen == GAME_OVER) {

						Quit->isActive = false;
						GameOverScene->isActive = false;
						Main_MenuScene->isActive = true;
						current_screen = TIP;
						PERF_START(TipScreen);
						PauseGame = false;
						int a = rand() % 8;
						switch (a)
						{
						case 0:
							Tip1->isActive = true;
							break;
						case 1:
							Tip2->isActive = true;
							break;
						case 2:
							Tip3->isActive = true;
							break;
						case 3:
							Tip4->isActive = true;
							break;
						case 4:
							Tip5->isActive = true;
							break;
						case 5:
							Tip6->isActive = true;
							break;
						case 6:
							Tip7->isActive = true;
							break;
						case 7:
							Tip8->isActive = true;
							break;
						}
					}
				}
			}
		}
	}
	return true;
}


void j1Scene::BoosterAnim(Animation Booster) {

	if (ScaleBooster <= 0.7) {

		ScaleBooster += 0.04;
		PERF_START(BoosterStatic);
	}
	else
		boosterSizeReached = true;

	if (boosterSizeReached&&BoosterStatic.ReadSec()>=1.5) {

			boosterSizeReached = false;
			boosterActivated = false;
			ScaleBooster = 0;
	}
}


// Called each loop iteration
bool j1Scene::Update(float dt)
{

	if (current_screen == GAME)
		HandleGameScreen(dt);

	else if (current_screen == TIP) {

		if (Aux_Screen == MAIN_MENU && TipScreen.ReadSec() >= 7) {

			Main_MenuScene->Deactive(Main_MenuScene);
			Tip1->isActive = false;
			Tip2->isActive = false;
			Tip3->isActive = false;
			Tip4->isActive = false;
			Tip5->isActive = false;
			Tip6->isActive = false;
			Tip7->isActive = false;
			Tip8->isActive = false;
			PERF_START(match_time);
			ChangeScreen(GAME);
		}

		else if(Aux_Screen == GAME_OVER && TipScreen.ReadSec() >= 4) {

			Tip1->isActive = false;
			Tip2->isActive = false;
			Tip3->isActive = false;
			Tip4->isActive = false;
			Tip5->isActive = false;
			Tip6->isActive = false;
			Tip7->isActive = false;
			Tip8->isActive = false;
			Settings->isActive = true;
			Play->isActive = true;
			Quit->isActive = true;
			Credits->isActive = true;
			Feedback->isActive = true;
			LogoCitm->isActive = true;
			versionLabel->isActive = true;
			ChangeScreen(MAIN_MENU);
			}

		PERF_START(videostart);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{

	bool ret = true;
	if (current_screen == GAME_OVER) {

		SDL_Color white_col = { 255, 255, 255, 255 };
		
		float hit_percentage = ((float)App->note->total_smashed_notes / (float)App->note->deleted_notes) * 100.0f;
		if (App->note->deleted_notes == 0)
			hit_percentage = 0;
		if (hit_percentage > 100.0f)
			hit_percentage = 100.0f;

		sprintf(hit_percentage_text, "%.2f", hit_percentage);
		App->font->CalcSize(hit_percentage_text, scoreRect.w, scoreRect.h, App->font->fonts.end->data);
		App->render->Blit(App->font->Print(hit_percentage_text, white_col, App->font->fonts.end->data), 900, 365, &scoreRect, 0.7, false);

		sprintf(score_text, "%d", score);
		App->font->CalcSize(score_text, scoreRect.w, scoreRect.h, App->font->fonts.end->data);
		App->render->Blit(App->font->Print(score_text, white_col, App->font->fonts.end->data), 900, 447, &scoreRect, 0.7, false);

		sprintf(total_smashed_notes_text, "%d", App->note->total_smashed_notes);
		App->font->CalcSize(total_smashed_notes_text, scoreRect.w, scoreRect.h, App->font->fonts.end->data);
		App->render->Blit(App->font->Print(total_smashed_notes_text, white_col, App->font->fonts.end->data), 900, 534, &scoreRect, 0.7, false);

		sprintf(total_created_notes_text, "%d", App->note->total_song_notes);
		App->font->CalcSize(total_created_notes_text, scoreRect.w, scoreRect.h, App->font->fonts.end->data);
		App->render->Blit(App->font->Print(total_created_notes_text, white_col, App->font->fonts.end->data), 900, 589, &scoreRect, 0.7, false);

		SDL_Rect img_rect = { 0, 0, 1280, 720 };
		App->render->Blit(Game_Over_txtr, 0, 70, &img_rect);
	}

	if(current_screen==TIP)
		App->render->Blit(KeyboardAnimation_Text, 490, 350, &KeyboardAnimation.GetCurrentFrame());


	if (current_screen == MAIN_MENU) {

		if (creditsisActive) {
			App->render->Blit(Credits_tex, 315, 345, &Credits_Rect,0.9);
			Credits_Rect.y++;
		}

		if (Mode1->isActive&&Mode1->onTop()) {
			App->render->Blit(keyboardText, 510, 530, &Enter.GetCurrentFrame(), 0.7f, 1.0f, 0, 0, 0, SDL_FLIP_NONE, true);
			App->render->Blit(keyboardText, 300, 530, &Numbers.GetCurrentFrame(), 0.7f, 1.0f, 0, 0, 0, SDL_FLIP_NONE, true);
		}
		else if (Mode1->isActive) {
			App->render->Blit(keyboardText, 510, 530, &Enter.frames[0], 0.7f, 1.0f, 0, 0, 0, SDL_FLIP_NONE, true);
			App->render->Blit(keyboardText, 300, 530, &Numbers.frames[5], 0.7f, 1.0f, 0, 0, 0, SDL_FLIP_NONE, true);
		}
		if (Mode2->isActive&&Mode2->onTop())
			App->render->Blit(keyboardText, 900, 530, &Numbers.GetCurrentFrame(), 0.7f, 1.0f, 0, 0, 0, SDL_FLIP_NONE, true);
		else if (Mode2->isActive)
			App->render->Blit(keyboardText, 900, 530, &Numbers.frames[5], 0.7f, 1.0f, 0, 0, 0, SDL_FLIP_NONE, true);
	}
	if (current_screen == GAME) {
		if (boosterActivated == true) {
			int positionx = 0;
			int positiony = 0;
			if (ActivatePlaytestBoosterCentered) {
				positionx = 600;
				positiony = 300;
			}
			else {
				positionx = 950;
				positiony = 150;
			}

			if (multiplier == 2) {
				BoosterAnim(boosterx2);
				App->render->Blit(Boosters_tex, positionx, positiony, &boosterx2.GetCurrentFrame(), ScaleBooster, 1.0, 0, 0, 0, SDL_FLIP_NONE, true);
			}

			else if (multiplier == 3) {
				BoosterAnim(boosterx3);
				App->render->Blit(Boosters_tex, positionx, positiony, &boosterx3.GetCurrentFrame(), ScaleBooster, 1.0, 0, 0, 0, SDL_FLIP_NONE, true);

			}

			else if (multiplier == 4) {
				BoosterAnim(boosterx4);
				App->render->Blit(Boosters_tex, positionx, positiony, &boosterx4.GetCurrentFrame(), ScaleBooster, 1.0, 0, 0, 0, SDL_FLIP_NONE, true);
			}
		}
		SDL_Rect a = { 0,0,266,143 };
		App->render->Blit(Under_Notes_tex, 880, 450, &a, 1.1f,false);
	}

	if (current_screen == MAIN_MENU && App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}



//SCENE METHODS
void j1Scene::HandleGeneralInput() {

	/*if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y++;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y--;*/
}


void j1Scene::HandleGameScreen(float dt) {

	if ((videostart.ReadMs()) >= 3600 && play_video) {

		play_video = false;
		App->audio->PlayMusic("audio/music/GodDamn_Song3.ogg",0);
		App->video->PlayVideo("video/GodDamn_NoAudio2.ogv", { 0,-50,1280,850 });
	}

	//Notes deleter blit & colider
	App->render->DrawQuad(Bottom_Limit, 255, 255, 255, 255);
	Bottom_coll->SetPos(Bottom_Limit.x, Bottom_Limit.y);

	if (PauseGame == true) {

		App->video->StopVideo();
		App->audio->PauseMusic();
	}
	HandleGeneralInput();


	int y = 650;
	int x = 400;


	if (PauseGame == false) {

		if (App->audio->MusicPaused() == true)
			App->audio->ResumeMusic();

		if (!change_input)
			HandleInput();
		else
			HandleInput2();

		//Blitting Guitar texture
		App->render->Blit(guitar_tex, x, 720 - 425, &Guitar.GetCurrentFrame());
		lastframe = Guitar.getCurrentFrame();
	}
	else
		App->render->Blit(guitar_tex, x, 720 - 425, &Guitar.frames[lastframe]);


	//Blitting Buttons textures
	App->render->Blit(Buttons_Texture, x + 25, y, &smViolet.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 135, y, &smBlue.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 245, y, &smYellow.Current_anim->GetCurrentFrame());
	App->render->Blit(Buttons_Texture, x + 350, y, &smPink.Current_anim->GetCurrentFrame());


	//Smashers colliders
	int y_corr = 5;
	smViolet.smasher_collider->SetPos(x + smViolet.smasher_rect.w * 0.33f + 25, y + smViolet.smasher_rect.h * 0.48f - y_corr);
	smBlue.smasher_collider->SetPos(x + smBlue.smasher_rect.w * 0.33f + 135, y + smBlue.smasher_rect.h * 0.48f - y_corr);

	smYellow.smasher_collider->SetPos(x + smYellow.smasher_rect.w * 0.33f + 245, y + smYellow.smasher_rect.h * 0.48f - y_corr);
	smPink.smasher_collider->SetPos(x + smPink.smasher_rect.w * 0.33f + 350, y + smPink.smasher_rect.h * 0.48f - y_corr);


	//Blitting Light PowerUps
	if (PowerUpActivated) {

		App->render->Blit(PowerUp_Light_tex, x + 60, 720 - 430, &Left_Light.GetCurrentFrame(), 1, 1, 22, 60, 0);
		App->render->Blit(PowerUp_Light_tex, x + 225, 720 - 370, &Right_Light.GetCurrentFrame(), 1, 1, -19, 0, 0);
	}


	//counter to Activate PowerUps
	SDL_Rect PowerUp_counterback = { 160, 0, 160, 290 };

	if (PowerUp_notes_counter >= 40) {

		PowerUp_notes_counter = 40;

		if (App->input->GetKey(SDL_SCANCODE_RCTRL)) {
			PowerUpActivated = true;
			times_PU_used++;
		}
	}

	if (PowerUpActivated) {

		if(match_time.Read()%4==0)
			PowerUp_notes_counter--;

		if (PowerUp_notes_counter <= 0)
			PowerUpActivated = false;

	}

	//x+40,530
	PowerUP_counter.h= (PowerUp_notes_counter*292)/40;
	App->render->Blit(PowerUP_counter_tex,x-50, 430, &PowerUp_counterback, 1,1,180);
	App->render->Blit(PowerUP_counter_tex,x-50, 430+292-PowerUP_counter.h, &PowerUP_counter, 1,1,180);


	//MUltipliers Logic
	if (App->note->numNotes > 15 && App->note->numNotes <= 30) {
		if (multiplier != 2) {
			boosterActivated = true;
		}
		Multipliers_current_anim = &x2;
		multiplier = 2;
	}
	if (App->note->numNotes > 30 && App->note->numNotes <= 45) {
		if (multiplier != 3) {
			boosterActivated = true;
		}

		Multipliers_current_anim = &x3;
		multiplier = 3;
	}
	if (App->note->numNotes > 45) {
		if (multiplier != 4) {
			boosterActivated = true;
		}
		Multipliers_current_anim = &x4;
		multiplier = 4;
	}
	if(App->note->numNotes <= 15){
		Multipliers_current_anim = &x1;
		multiplier = 1;
	}

	//Blitting Multiplier
	App->render->Blit(Multiplier_tex, -25, 300, &Multipliers_current_anim->GetCurrentFrame());

	if (Multipliers_current_anim != &x1) {
		SDL_Rect aux = { 0, 0, 235, 248 };
		App->render->Blit(multiplier_Head_tex, 185,497 , &aux,1.12f,1.0f,0,0,0,SDL_FLIP_NONE,true);
	}

	sprintf(score_text, "%d", score);
	App->font->CalcSize(score_text, scoreRect.w, scoreRect.h, App->font->fonts.end->data);
	App->render->Blit(App->font->Print(score_text, { 255,255,255,255 }, App->font->fonts.end->data), 900, 400, &scoreRect, 1, false);

	p2List_item<Note*> *notes_item = notes.end;

	for (; notes_item != nullptr; notes_item = notes_item->prev)
		notes_item->data->Update(dt);
}


void j1Scene::HandleInput() {

	//INPUTS
	if (PushFailure2() == true && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {

		App->audio->PlayFx(Failnote_SFX);
		App->note->numNotes = 0;
		
		if(ActivatePlaytestPowerUp == true)
			PowerUp_notes_counter--;

		if (App->render->DoCameraShake == false) {
			App->render->DoCameraShake = true;
			App->render->power = 2.0f;
			App->render->Time_Doing_Shake = 0.2f;
			PERF_START(App->render->CameraShake_Time);
		}
	}


	//Anims
	//1 (Violet)
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
		smViolet.Current_anim = &smViolet.Pushed_anim;
	else
		smViolet.Current_anim = &smViolet.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		smViolet.Current_anim = &smViolet.Enter_anim;

	//2
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)
		smBlue.Current_anim = &smBlue.Pushed_anim;
	else
		smBlue.Current_anim = &smBlue.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		smBlue.Current_anim = &smBlue.Enter_anim;

	//3
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
		smYellow.Current_anim = &smYellow.Pushed_anim;
	else
		smYellow.Current_anim = &smYellow.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		smYellow.Current_anim = &smYellow.Enter_anim;

	//4
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		smPink.Current_anim = &smPink.Pushed_anim;
	else
		smPink.Current_anim = &smPink.Standard_anim;

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
		smPink.Current_anim = &smPink.Enter_anim;


	//Failing Notes
	//if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {

	//	smViolet.Current_anim = &smViolet.Enter_anim;

	//	p2List_item<Note*>* nItem = notes.start;
	//	int counter = 0;
	//	for (; nItem; nItem = nItem->next)
	//		if (nItem->data->nColor == NOTE_COLOR::NOTE_VIOLET)
	//			counter++;
	//
	//	if (counter == 0) {

	//		App->audio->PlayFx(Failnote_SFX);
	//		App->note->numNotes = 0;
	//		PowerUp_notes_counter--;
	//	}

	//	nItem = notes.start;
	//	for (; nItem; nItem = nItem->next) {

	//		if (nItem->data->nColor == NOTE_COLOR::NOTE_VIOLET) {

	//			if (nItem->data->vColliding == false) {

	//				App->audio->PlayFx(Failnote_SFX);
	//				App->note->numNotes = 0;
	//				PowerUp_notes_counter--;

	//				if (App->render->DoCameraShake == false) {
	//					App->render->DoCameraShake = true;
	//					App->render->power = 2.0f;
	//					App->render->Time_Doing_Shake = 0.2f;
	//					PERF_START(App->render->CameraShake_Time);
	//				}
	//			}

	//			break;
	//		}
	//	}
	//}

	/*if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {

		smBlue.Current_anim = &smBlue.Enter_anim;

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_BLUE)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_BLUE) {

				if (nItem->data->bColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {

		smYellow.Current_anim = &smYellow.Enter_anim;

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_YELLOW)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_YELLOW) {

				if (nItem->data->yeColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {

		smPink.Current_anim = &smPink.Enter_anim;

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_PINK)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_PINK) {

				if (nItem->data->piColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}*/
}


void j1Scene::HandleInput2() {

	if (PushFailure() == true) {

		App->audio->PlayFx(Failnote_SFX);
		App->note->numNotes = 0;

		if(ActivatePlaytestPowerUp == true)
			PowerUp_notes_counter--;

		if (App->render->DoCameraShake == false) {
			App->render->DoCameraShake = true;
			App->render->power = 2.0f;
			App->render->Time_Doing_Shake = 0.2f;
			PERF_START(App->render->CameraShake_Time);
		}
	}


	//INPUTS
	//1 (Violet)
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
		smViolet.Current_anim = &smViolet.Enter_anim;

	else
		smViolet.Current_anim = &smViolet.Standard_anim;

	/*if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_VIOLET)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_VIOLET) {

				if (nItem->data->vColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}*/

	//2 (Blue)
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)
		smBlue.Current_anim = &smBlue.Enter_anim;

	else
		smBlue.Current_anim = &smBlue.Standard_anim;

	/*if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_BLUE)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_BLUE) {

				if (nItem->data->bColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}*/

	//3 (Yellow)
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
		smYellow.Current_anim = &smYellow.Enter_anim;
	else
		smYellow.Current_anim = &smYellow.Standard_anim;

	/*if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_YELLOW)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_YELLOW) {

				if (nItem->data->yeColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}*/

	//4 (Pink)
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		smPink.Current_anim = &smPink.Enter_anim;
	else
		smPink.Current_anim = &smPink.Standard_anim;

	/*if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

		p2List_item<Note*>* nItem = notes.start;
		int counter = 0;
		for (; nItem; nItem = nItem->next)
			if (nItem->data->nColor == NOTE_COLOR::NOTE_PINK)
				counter++;

		if (counter == 0) {

			App->audio->PlayFx(Failnote_SFX);
			App->note->numNotes = 0;
			PowerUp_notes_counter--;
		}

		nItem = notes.start;
		for (; nItem; nItem = nItem->next) {

			if (nItem->data->nColor == NOTE_COLOR::NOTE_PINK) {

				if (nItem->data->piColliding == false) {

					App->audio->PlayFx(Failnote_SFX);
					App->note->numNotes = 0;
					PowerUp_notes_counter--;

					if (App->render->DoCameraShake == false) {
						App->render->DoCameraShake = true;
						App->render->power = 2.0f;
						App->render->Time_Doing_Shake = 0.2f;
						PERF_START(App->render->CameraShake_Time);
					}
				}

				break;
			}
		}
	}*/
}


bool j1Scene::PushFailure() {

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			return true;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			return true;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
			return true;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			return true;

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			return true;

	return false;

}


bool j1Scene::PushFailure2() {

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		return true;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		return true;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
		return true;

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		return true;

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
		return true;

	return false;
}


bool j1Scene::Save(pugi::xml_node& data) const
{

	data.append_child("END_DATA");
	data.append_child("TIMER");

	int lost_notes_from_created = App->note->total_song_notes - App->note->total_smashed_notes;
	int lost_notes = App->note->deleted_notes - App->note->total_smashed_notes;
	float hit_percentage = ((float)App->note->total_smashed_notes / (float)App->note->deleted_notes) * 100.0f;
	float hit_percentage_created = ((float)App->note->total_smashed_notes / (float)App->note->total_song_notes) * 100.0f;

	if (App->note->deleted_notes == 0)
		hit_percentage = 0;

	if (hit_percentage > 100.0f)
		hit_percentage = 100.0f;

	if (App->note->total_song_notes == 0)
		hit_percentage_created = 0;

	data.child("END_DATA").append_attribute("score") = score;
	data.child("END_DATA").append_attribute("total_smashed_notes") = App->note->total_smashed_notes;
	data.child("END_DATA").append_attribute("total_song_notes_before_quiting_or_ending") = App->note->total_song_notes;
	data.child("END_DATA").append_attribute("total_song_notes_deleted") = App->note->deleted_notes;
	data.child("END_DATA").append_attribute("total_song_notes_lost") = lost_notes_from_created;

	data.child("END_DATA").append_attribute("lost_notes") = lost_notes;
	data.child("END_DATA").append_attribute("hit_percentage") = hit_percentage;
	data.child("END_DATA").append_attribute("hit_percentage_referral_notes_created") = hit_percentage_created;
	data.child("END_DATA").append_attribute("times_powerUP_used") = times_PU_used;

	int game_mode = 0;
	if (change_input == false)
		game_mode = 1;
	else
		game_mode = 2;

	data.child("END_DATA").append_attribute("game_mode") = game_mode;
	data.child("END_DATA").append_attribute("boost_centered") = ActivatePlaytestBoosterCentered;
	data.child("END_DATA").append_attribute("powerUp_substract_notes") = ActivatePlaytestPowerUp;


	int sec = (int)match_time.ReadSec() % 60;
	int min = match_time.ReadSec() / 60;
	data.child("TIMER").append_attribute("time_min") = min;
	data.child("TIMER").append_attribute("time_s") = sec;

	return true;
}


void j1Scene::ChangeScreen(int screen) {

	if (current_screen == GAME) {

		Aux_Screen = GAME;
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
		App->audio->PlayMusic("audio/music/Initial_Effect_Sound.ogg");
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
		PowerUp_notes_counter = 0;
		PowerUpActivated = false;
		score = 0;

		play_video = true;
		keep_reading = true;
		counter = 0;
		times_PU_used = 0;

	}
	else if (screen == MAIN_MENU) {

		Aux_Screen = MAIN_MENU;
		App->note->deleted_notes = 0;
		current_screen = MAIN_MENU;

	}

	else if (screen == GAME_OVER) {

		App->audio->PlayFx(gameOver_FX);
		App->audio->PlayMusic("audio/music/MainMenu_Sound.ogg", 1);
		Aux_Screen = GAME_OVER;
		current_screen = GAME_OVER;
	}
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

	Notes_Position_node = Notes_Array_Document.child("notes");

	pugi::xml_node node = Notes_Position_node;
	for (node = node.child("PushBack"); node; node = node.next_sibling("PushBack")) {

		int x = node.attribute("q").as_int();
		int y = node.attribute("w").as_int();
		int z = node.attribute("e").as_int();
		int k = node.attribute("r").as_int();

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
	//setting animation for boosters;
	countGuitar.x = 0;
	countGuitar.y = 0;
	for (int i = 0; i < 8; ++i) {
		boosterx2.PushBack({ countGuitar.x,countGuitar.y,669,483 });
		countGuitar.x += 669;
		if (countGuitar.x >= 669*4) {
			countGuitar.y += 483;
			countGuitar.x = 0;
		}
	}
	boosterx2.speed = 0.4f;
	boosterx2.loop = true;
	for (int i = 8; i < 16; ++i) {
		boosterx3.PushBack({ countGuitar.x,countGuitar.y,669,483 });
		countGuitar.x += 669;
		if (countGuitar.x >= 669 * 4) {
			countGuitar.y += 483;
			countGuitar.x = 0;
		}
	}
	boosterx3.speed = 0.3f;

	for (int i = 16; i < 24; ++i) {
		boosterx4.PushBack({ countGuitar.x,countGuitar.y,669,483 });
		countGuitar.x += 669;
		if (countGuitar.x >= 669 * 4) {
			countGuitar.y += 483;
			countGuitar.x = 0;
		}
	}
	boosterx4.speed = 0.3f;
	//settting animation for keyboard icon
	countGuitar.x = 1;
	countGuitar.y = 1;
	for (int i = 0; i < 28; ++i) {
		KeyboardAnimation.PushBack({ countGuitar.x,countGuitar.y,269,269 });
		countGuitar.x += 270;
		if (countGuitar.x >= 1620) {
			countGuitar.y += 270;
			countGuitar.x = 1;
		}
	}
	KeyboardAnimation.PushBack({ countGuitar.x,countGuitar.y,269,269 });
	KeyboardAnimation.PushBack({ countGuitar.x,countGuitar.y,269,269 });
	KeyboardAnimation.PushBack({ countGuitar.x,countGuitar.y,269,269 });

	KeyboardAnimation.speed = 0.3f;

	//setting animation for Enter icon
	Enter.PushBack({ 0,0,179,179 });
	Enter.PushBack({ 179,0,179,179 });
	Enter.PushBack({ 358,0,179,179 });
	Enter.PushBack({ 537,0,179,179 });
	Enter.PushBack({ 716,0,179,179 });
	Enter.PushBack({ 0,179,179,179 });
	Enter.PushBack({ 179,179,179,179 });
	Enter.PushBack({ 358,179,179,179 });
	Enter.PushBack({ 537,179,179,179 });

	Enter.speed = 0.3f;
	//setting animation for numpad icons

	Numbers.PushBack({0,358,294,200});
	Numbers.PushBack({ 294,358,294,200 });
	Numbers.PushBack({ 588,358,294,200 });
	Numbers.PushBack({ 0,558,294,200 });
	Numbers.PushBack({ 294,558,294,200 });
	Numbers.PushBack({ 294,558,294,200 });


	Numbers.speed = 0.1f;
}
