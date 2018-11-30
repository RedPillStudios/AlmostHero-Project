#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	//atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	//atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{

	p2List_item<UI_Element*>*elements_item = ui_elements_list.start;
	for (; elements_item; elements_item = elements_item->next)
		App->render->Blit(elements_item->data->element_tex, elements_item->data->pos.x, elements_item->data->pos.y, &elements_item->data->element_rect, 0.0f);


	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<UI_Element*>*elements_item = ui_elements_list.start;
	for (; elements_item; elements_item = elements_item->next)
		ui_elements_list.del(elements_item);

	ui_elements_list.clear();

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	//return atlas;
}

// class Gui ---------------------------------------------------
UI_Element* j1Gui::CreateUIElement(SDL_Rect rect, iPoint pos, SDL_Texture* tex) {

	UI_Element* element = new UI_Element();

	//if (tex == nullptr)
		//element->element_tex = atlas;
	//else
	if(tex != nullptr)
		element->element_tex = tex;

	element->element_rect = rect;
	element->pos = pos;

	ui_elements_list.add(element);
	return element;

}

