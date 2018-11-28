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

	void UpdateMultiplier() {
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

	void ReadArray(iPoint4d vec);

	void HandleInput();

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

	int multiplier = 1;

private:

	p2DynArray<iPoint4d> notes_positions;

	iPoint4d pos1 = iPoint4d(1, 1, 1, 1);
	iPoint4d pos2 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos3 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos4 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos5 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos6 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos7 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos8 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos9 = iPoint4d(1, 0,0, 0);
	iPoint4d pos10 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos11 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos12 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos13 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos14 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos15 = iPoint4d(1, 0, 0, 0);
	iPoint4d pos16 = iPoint4d(0, 0, 0, 0);

	iPoint4d pos17 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos18 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos19 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos20 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos21 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos22 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos23 = iPoint4d(0, 0, 0, 0);
	iPoint4d pos24 = iPoint4d(0, 0, 0, 0);
	//iPoint4d pos5 = iPoint4d(1, 1, 1, 1);

	j1Timer read_next_array_pos;
	int counter = 0;

public:

	//p2List<Note*> notes;

private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

};

#endif
