#ifndef _J1_BUTTONENTITY_
#define _J1_BUTTONENTITY_

#include "j1Entity.h"
#include "p2DynArray.h"
#include "p2List.h"

struct SDL_Rect;

enum BUTTON_TYPE {

	NON = -1,
	RED_BUTTON,
	GREEN_BUTTON,
	BLUE_BUTTON,
	VIOLET_BUTTON,
	UNKNOWN = 4
};

class j1ButtonEntity : public j1Entity
{

public:

	j1ButtonEntity(iPoint pos, BUTTON_TYPE type_);
	~j1ButtonEntity() {}

	void j1ButtonEntity::OnCollision(Collider *c1, Collider *c2) override;

public:

	//Create/Destroy a Button
	j1ButtonEntity* CreateButton(iPoint pos, BUTTON_TYPE buttonType, const char* path, pugi::xml_document &ButtonDocument);
	void j1ButtonEntity::DestroyButton(j1ButtonEntity *Button);

	//Load Enemy
	bool LoadButton(const char*file_name, pugi::xml_document &ButtonDocument);
	//Pushbacks loading
	void LoadPushbacks(pugi::xml_node node, Animation &animation);

public:

	bool falling = false;;


	pugi::xml_node		EnemySettings;
	pugi::xml_node		Animation_node;

	BUTTON_TYPE type;


	iPoint position;
	fPoint velocity;
	iPoint initial_velocity;

	SDL_Texture *Enemy_tex = nullptr;
	SDL_Rect button_rect;
	SDL_Rect button_Collider_rect;

};

#endif