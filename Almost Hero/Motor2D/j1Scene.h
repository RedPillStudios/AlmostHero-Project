#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1Timer.h"
#include "j1Collisions.h"
#include "Note.h"
#include "Vector4D.h"


enum SCREEN_TYPE {

		MAIN_MENU = 0,
		TIP,
		GAME,
		GAME_OVER,
		NON

};


struct SDL_Texture;

struct Smasher {

	Collider* smasher_collider = nullptr;
	SDL_Rect smasher_rect;

	Animation* Current_anim = nullptr;
	Animation Standard_anim;
	Animation Pushed_anim;
	Animation Enter_anim;

};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	int multiplier = 1;
	int LastMultiplier = 0;
	int score = 0;
	int PowerUp_notes_counter=0;
	bool PowerUpActivated = false;
	int volume;
	int Failnote_SFX;
	int On_top_buttons_SFX;
	bool failnote = false;
	bool ActivatePlaytestPowerUp = true;
	bool ActivatePlaytestBoosterCentered = true;
	
	uint gameOver_FX;
	int times_PU_used = 0;

private:
	
	Smasher CreateSmasher(COLLIDER_TYPE smasher_collider, pugi::xml_node &node, const char *color);
	SDL_Rect LoadButtons(pugi::xml_node &node, const char* color);
	SDL_Rect SetNotesPushbacks(pugi::xml_node &node, const char* color, const char* anim_name);


	void UpdateMultiplier();
	void ReadArray(iPoint4d vec);
	void LoadSongArray();

	bool Save(pugi::xml_node& data) const;
	void ChangeScreen(int screen);

	void BoosterAnim(Animation Booster);

	void HandleInput();
	void HandleInput2();
	void HandleGeneralInput();
	void HandleGameScreen(float dt);
	
	void LoadPushbacks();
	bool PushFailure2();
	bool PushFailure();

private:

	//Buttons & guitar texture
	SDL_Texture* Multiplier_tex;
	SDL_Texture* Buttons_Texture;
	SDL_Texture* guitar_tex;
	SDL_Texture* PowerUp_Light_tex;
	SDL_Texture* keyboardText;
	SDL_Texture* KeyboardAnimation_Text;
	SDL_Texture* multiplier_Head_tex;
	SDL_Texture* PowerUP_counter_tex;
	SDL_Texture* Boosters_tex;
	SDL_Texture* Credits_tex;
	SDL_Texture* Under_Notes_tex;

	SDL_Rect PowerUP_counter;


	iPoint countGuitar;

	//Notes deleter
	SDL_Rect Bottom_Limit;
	Collider* Bottom_coll;
	
	//Guitar animation
	Animation Guitar;
	Animation KeyboardAnimation;
	Animation Numbers;
	Animation Enter;


	//Lights PowerUp animation
	Animation Left_Light;
	Animation Right_Light;

	//Multiplier animation
	Animation* Multipliers_current_anim = nullptr;
	Animation x1;
	Animation x2;
	Animation x3;
	Animation x4;

	Animation boosterx4;
	Animation boosterx3;
	Animation boosterx2;

	UI_Element* Main_MenuScene;

	UI_Element* GameOverScene;

	UI_Element* Play;
	UI_Element* Settings;
	UI_Element* Pause;
	UI_Element* Mode1;
	UI_Element* Mode2;
	UI_Element* Volumen;
	UI_Element* Volume_Bar;
	UI_Element* Volume_Background;
	UI_Element* LogoCitm;
	UI_Element* Credits;
	UI_Element* BoostersPosition;
	UI_Element* PowerUPActive;
	UI_Element* Boosters_Position_button;
	UI_Element* PowerUpActive_button;

	UI_Element* Pause_WarnOnVideo;
	UI_Element* Pause_WarnOnVideo2;

	UI_Element* versionLabel;
	
	UI_Element* Tip1;
	UI_Element* Tip2;
	UI_Element* Tip3;
	UI_Element* Tip4;
	UI_Element* Tip5;
	UI_Element* Tip6;
	UI_Element* Tip7;
	UI_Element* Tip8;
	UI_Element* TipPause;
	UI_Element* Feedback;

	UI_Element* Quit;

	iPoint lastMousePos = { 0,0 };
	iPoint newMousePos = { 0,0 };

	p2List<UI_Element*> UI_Elements_List;
	p2List<UI_Element*> UI_Elements_List_Playing;
	
private:

	p2DynArray<iPoint4d> notes_positions;

	j1PerfTimer videostart;
	j1PerfTimer read_next_array_pos;
	j1Timer end_timer;
	j1PerfTimer pauseTimer;
	int itP = 0;

	int counter = 0;
	int lastframe = 0;
	bool keep_reading = true;

	SDL_Rect scoreRect = { 0, 0, 20, 20 };
	char score_text[100];
	char hit_percentage_text[100];

	SCREEN_TYPE current_screen;
	SCREEN_TYPE Aux_Screen;

	SDL_Texture* Game_Over_txtr = nullptr;

	j1Timer match_time;
	char match_time_min_text[2];
	char match_time_sec_text[2];

	char total_smashed_notes_text[4];
	char total_created_notes_text[4];

	bool play_video = false;

	j1Timer TipScreen;

	int Time_During_TipScreen = 14;

	bool boosterActivated = false;
	bool boosterSizeReached = false;
	float ScaleBooster = 0;
	j1Timer BoosterStatic;


public:

	p2List<Note*> notes;
	bool change_input = false;

	SDL_Rect Credits_Rect;
	bool creditsisActive;
	bool PauseGame;

	//Note Smashers
	Smasher smBlue;
	Smasher smPink;
	Smasher smViolet;
	Smasher smYellow;


private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

	pugi::xml_document Notes_Array_Document;
	pugi::xml_node Notes_Position_node;
};

#endif
