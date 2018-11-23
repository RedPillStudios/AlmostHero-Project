#ifndef _NOTE_H_
#define _NOTE_H_

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Animation.h"
#include "p2DynArray.h"


struct SDL_Texture;


enum NOTE_COLOR {

	NOTE_NON = -1,
	NOTE_BLUE,
	NOTE_YELLOW,
	NOTE_PINK,
	NOTE_VIOLET

};

class Note : public j1Module {

public:

	//Constructor
	Note();

	// Destructor
	virtual ~Note();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

public:

	Note* CreateNote(NOTE_COLOR color);
	void DestroyNote(Note* note);
	void OnCollision(Collider* c1, Collider* c2);

public:


	//Notes attributes
	fPoint velocity = fPoint(-0.73f, 2.5f);
	fPoint initial_pos = fPoint(598.0f, 280.0f);
	fPoint position;

	Collider *note_collider = nullptr;
	NOTE_COLOR nColor = NOTE_NON;

private:

	float scale = 0.2f;
	SDL_Rect note_rect;
	SDL_Texture *note_tex = nullptr;

};

#endif