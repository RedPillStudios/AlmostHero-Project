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
	int score = 0;

private:
	
	Smasher CreateSmasher(COLLIDER_TYPE smasher_collider, pugi::xml_node &node, const char *color);
	SDL_Rect LoadButtons(pugi::xml_node &node, const char* color);
	SDL_Rect SetNotesPushbacks(pugi::xml_node &node, const char* color, const char* anim_name);


	void UpdateMultiplier();
	void ReadArray(iPoint4d vec);
	void LoadSongArray();

	bool Save(pugi::xml_node& data_) const;
	void ChangeScreen(int screen);

	void HandleInput();
	void HandleInput2();
	void HandleGeneralInput();
	void HandleGameScreen(float dt);

	void LoadPushbacks();

private:

	//Buttons & guitar texture
	SDL_Texture* Multiplier_tex;
	SDL_Texture* Buttons_Texture;
	SDL_Texture* guitar_tex;
	SDL_Texture* PowerUp_Light_tex;

	iPoint countGuitar;

	//Notes deleter
	SDL_Rect Bottom_Limit;
	Collider* Bottom_coll;

	//Note Smashers
	Smasher smBlue;
	Smasher smPink;
	Smasher smViolet;
	Smasher smYellow;

	//Guitar animation
	Animation Guitar;

	//Lights PowerUp animation
	Animation Left_Light;
	Animation Right_Light;

	//Multiplier animation
	Animation* Multipliers_current_anim = nullptr;
	Animation x1;
	Animation x2;
	Animation x3;
	Animation x4;


private:

	p2DynArray<iPoint4d> notes_positions;

	j1PerfTimer videostart;

	j1Timer read_next_array_pos;
	int counter = 0;

	SDL_Rect scoreRect = { 0, 0, 20, 20 };
	char score_text[100];


	SCREEN_TYPE current_screen;

	SDL_Texture* Main_Menu_txtr = nullptr;
	SDL_Texture* Game_Over_txtr = nullptr;

	j1Timer match_time;
	char match_time_min_text[2];
	char match_time_sec_text[2];

	char total_smashed_notes_text[4];
	char total_created_notes_text[4];

	bool play_video = false;

public:

	p2List<Note*> notes;
	bool change_input = false;

private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

	pugi::xml_document Notes_Array_Document;
	pugi::xml_node Notes_Position_node;
};

#endif
