#ifndef _J1COLLISIONS_H
#define _J1COLLISIONS_H

#include "p2Defs.h"
#include "p2Log.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1App.h"

#define MAX_COLLIDERS 700

struct SDL_Rect;

enum COLLIDER_TYPE {

	COLLIDER_NONE = -1,
	COLLIDER_STATIC,
	COLLIDER_NOTE,
	COLLIDER_SMASHER_BLUE,
	COLLIDER_SMASHER_YELLOW,
	COLLIDER_SMASHER_PINK,
	COLLIDER_SMASHER_VIOLET,
	COLLIDER_MAX = 8

};

struct Collider {

	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type = COLLIDER_NONE;
	j1Module *callback = nullptr;
	//j1Entity *callback2 = nullptr;

	Collider(SDL_Rect rect, COLLIDER_TYPE type, j1Module *callback = nullptr) :
		rect(rect), type(type), callback(callback) {}

	//Collider(SDL_Rect rect, COLLIDER_TYPE type, j1Entity *callback = nullptr) :
		//rect(rect), type(type), callback2(callback) {}
	
	void SetPos(int x, int y) { rect.x = x; rect.y = y; }
	bool CheckCollision(const SDL_Rect &r) const;
	void ChangeCollider(COLLIDER_TYPE type_) { type = type_; }

};

class j1Collisions : public j1Module {

public:

	j1Collisions();
	~j1Collisions();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	bool PostUpdate();

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

public:

	void DebugDraw();
	Collider* AddCollider(SDL_Rect r, COLLIDER_TYPE type, j1Module*callback = nullptr);
	//Collider* AddColliderEntity(SDL_Rect r, COLLIDER_TYPE type, j1Entity*callback = nullptr);

private:

	Collider* colliders[MAX_COLLIDERS];
	bool debug = false;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	
};

#endif