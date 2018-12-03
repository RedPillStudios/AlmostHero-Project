#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1Textures.h"

#define CURSOR_WIDTH 2


class UI_Element {

public:

	SDL_Rect element_rect;
	SDL_Texture *element_tex = nullptr;
	iPoint pos;
	iPoint initial_pos;

};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UI_Element* CreateUIElement(SDL_Rect rect, iPoint pos, SDL_Texture* tex = nullptr);

	const SDL_Texture* GetAtlas() const;

private:

	//SDL_Texture * atlas;
	//p2SString atlas_file_name;
	p2List<UI_Element*> ui_elements_list;

};

#endif // __j1GUI_H__