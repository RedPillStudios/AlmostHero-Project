#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

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

	iPoint nPosition;
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

	SDL_Texture* debug_tex;
	SDL_Texture* guitar_tex;

	SDL_Rect Bottom_Limit;

	Note red_note;

};

#endif