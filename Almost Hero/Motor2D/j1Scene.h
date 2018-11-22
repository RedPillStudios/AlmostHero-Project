#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1Timer.h"
#include "j1Collisions.h"

#define MAX_NOTES_ON_SCREEN 10


struct SDL_Texture;

enum NOTE_COLOR {

	NOTE_NON = -1,
	NOTE_BLUE,
	NOTE_YELLOW,
	NOTE_PINK,
	NOTE_VIOLET

};

struct Note {

	SDL_Texture *note_tex = nullptr;
	SDL_Rect note_rect = { 0, 0, 35, 35 };

	float scale = 0.1f;

	fPoint nPosition;

	Collider *note_collider = nullptr;

	NOTE_COLOR nColor = NOTE_NON;

};

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

public:

	void OnCollision(Collider *c1, Collider *c2);
	Note* CreateNote(fPoint pos, int note_num, NOTE_COLOR color);
	Smasher CreateSmasher(COLLIDER_TYPE smasher_collider, pugi::xml_node &node, const char *color);
	void MoveNote(Note* note);

	SDL_Rect LoadButtons(pugi::xml_node &node, const char* color);
	SDL_Rect SetNotesPushbacks(pugi::xml_node &node, const char* color, const char* anim_name);

private:

	//Buttons & guitar texture
	SDL_Texture * Buttons_Texture;
	SDL_Texture* guitar_tex;


private:

	iPoint countGuitar;

	//Notes deleter
	SDL_Rect Bottom_Limit;
	Collider* Bottom_coll;

	//Notes
	//Note *violet_note;
	//Note *blue_note;
	//Note *yellow_note;
	//Note *pink_note;

	//Note Smashers
	Smasher smBlue;
	Smasher smPink;
	Smasher smViolet;
	Smasher smYellow;

	//Notes attributes
	fPoint nVelocity = fPoint(0.27f, 1.0f);
	fPoint nIpos = fPoint(825.0f, 82.0f);


private:

	//Guitar animation
	Animation Guitar;

private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

};

#endif
