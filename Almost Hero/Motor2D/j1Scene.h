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

private:
	
	Smasher CreateSmasher(COLLIDER_TYPE smasher_collider, pugi::xml_node &node, const char *color);

	SDL_Rect LoadButtons(pugi::xml_node &node, const char* color);
	SDL_Rect SetNotesPushbacks(pugi::xml_node &node, const char* color, const char* anim_name);
	void ReadArray(iPoint4d vec);

	void HandleInput();

private:

	//Buttons & guitar texture
	SDL_Texture* Buttons_Texture;
	SDL_Texture* guitar_tex;

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

private:

	p2DynArray<iPoint4d> notes_positions;

	iPoint4d pos1 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos2 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos3 = iPoint4d(0, 1, 0, 0);
	iPoint4d pos4 = iPoint4d(0, 0, 0, 0);
	//iPoint4d pos5 = iPoint4d(1, 1, 1, 1);

	j1Timer read_next_array_pos;
	int counter = 0;

public:

	p2List<Note*> notes;

private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

};

#endif
