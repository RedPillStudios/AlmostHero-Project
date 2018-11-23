#ifndef _NOTE_H_
#define _NOTE_H_

#include "j1Module.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "j1Timer.h"
#include "j1Collisions.h"
#include "j1Timer.h"

#define MAX_NOTES_ON_SCREEN 10


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

private:

	void OnCollision(Collider *c1, Collider *c2);
	
public:

	//Notes
	Note *violet_note;
	//Note *yellow_note;
	//Note *pink_note;


	//Notes attributes
	fPoint velocity = fPoint(-0.8f, 2.5f);
	fPoint initial_pos = fPoint(615.0f, 250.0f);
	fPoint position;


	Collider *note_collider = nullptr;
	NOTE_COLOR nColor = NOTE_NON;
	SDL_Texture *note_tex = nullptr;

	Note* CreateNote(NOTE_COLOR color);


private:

	SDL_Rect note_rect;
	float scale = 0.2f;

};

#endif