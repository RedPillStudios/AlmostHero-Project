#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1Timer.h"
#include "j1Collisions.h"
#include "Note.h"


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

	void HandleInput();

private:

	//Buttons & guitar texture
	SDL_Texture * Buttons_Texture;
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

	//List of violet notes
	p2List<Note*> vi_notes;
	j1Timer timer_creation;

private:

	pugi::xml_document Buttons_Document;
	pugi::xml_node Buttons_node;

};

#endif
