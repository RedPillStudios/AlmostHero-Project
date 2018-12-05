#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1Timer.h"
#include "j1Collisions.h"
#include "Note.h"
#include "Vector4D.h"


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

	void HandleInput();

	bool Save(pugi::xml_node& data_) const;

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

	void LoadSongArray();

	p2DynArray<iPoint4d> notes_positions;

	j1Timer read_next_array_pos;
	int counter = 0;

	SDL_Rect scoreRect = { 0, 0, 20, 20 };
	char score_text[100];

public:

	p2List<Note*> notes;

private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

	pugi::xml_document Notes_Array_Document;
	pugi::xml_node Notes_Position_node;
};

#endif
