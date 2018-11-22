#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2DynArray.h"
#include "Animation.h"

#define MAX_RED_NOTES_ON_SCREEN 10


struct SDL_Texture;

enum NOTE_COLOR {

	NOTE_NON = -1,
	NOTE_BLUE,
	NOTE_RED,
	NOTE_GREEN,
	NOTE_VIOLET

};

struct Note {

	SDL_Texture *note_tex = nullptr;
	SDL_Rect note_rect;

	float scale = 1.0f;

	fPoint nPosition;
	fPoint nVelocity;

	Collider *note_collider = nullptr;

	NOTE_COLOR nColor = NOTE_NON;

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

	SDL_Texture* guitar_tex;
	Animation* current_anim;
	Animation Guitar;

	iPoint countGuitar;

	SDL_Rect Bottom_Limit;
	Collider* Bottom_coll;

	SDL_Rect Notes_smasher;
	Collider *nSmasher_coll = nullptr;

	Note *red_note;

	void OnCollision(Collider *c1, Collider *c2);
	Note* CreateNote(fPoint pos, fPoint vel, NOTE_COLOR color);

};

#endif