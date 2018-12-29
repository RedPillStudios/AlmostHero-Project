#ifndef __j1GUI_H__
#define __j1GUI_H__
#define _CRT_SECURE_NO_WARNINGS


#include "j1Module.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Fonts.h"
#include "j1Audio.h"


#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

enum UI_Type {

	BUTTON,
	LABEL,
	NON_INTERACTIVE,
	BAR,
	NONE_TYPE
};
enum Button_Logic {
	QUIT,
	RETURN_MAIN_MENU,
	RESUME_GAME,
	LIFE_ALERT,
	TIME,
	PLAY,
	SCORE,
	BLITTING,
	CONTINUE,
	DRAG,
	ACTIVEWIN,
	CLOSEWIN,
	PUSH,
	WEB,
	CLICKTOWRITE,
	DRAGVOLUME,
	BACKVOLUME,
	NONE_LOGIC
};

class UI_Element {

public:

	UI_Element() {};
	UI_Element(UI_Type type, iPoint position, SDL_Rect Image_Rect, Button_Logic logic, UI_Element* Parent = nullptr)
		:type(type), UI_Rect(Image_Rect), Position(position), initialPosition(position), Logic(logic), Parent(Parent) {
		if (this->isParent()) {
			position.x = Parent->Position.x + initialPosition.x;
			position.y = Parent->Position.y + initialPosition.y;
		}
		CurrentRect = &UI_Rect;
		counter = 0;
	};


	UI_Element(UI_Type type, iPoint position, Button_Logic logic, const char* Text = nullptr, UI_Element* Parent = nullptr)
		:type(type), Position(position), initialPosition(position), Logic(logic), Parent(Parent) {
		if (this->isParent()) {
			Position.x = Parent->Position.x + initialPosition.x;
			Position.y = Parent->Position.y + initialPosition.y;
		}
	};

public:

	bool isParent();
	bool onTop();
	bool Clicked();

	void Score(int score);
	void Time(int time);
	void Alert(SDL_Texture* texture, int& alpha);
	void VolumeControl(iPoint newMousePos, iPoint lastMousePos,int &volume);
	void Blitter();


	void Active(UI_Element* toActive);
	void Deactive(UI_Element* toDeactive);
	void goWeb(const char* web);

	void Update();
	void Draw();
	void Drag();


public:


	iPoint initialPosition;
	iPoint Position;

	UI_Type type;
	Button_Logic Logic;

	const char* text = nullptr;
	SDL_Rect UI_Rect;
	SDL_Rect UI_Rect_Active;
	SDL_Rect* CurrentRect;
	SDL_Texture* texture;
	SDL_Texture* texture_Off;
	SDL_Texture* Current_Texture;

	p2List<UI_Element*> Child_List;
	UI_Element* Parent = nullptr;
	float scale = 1.0f;
	float angle = 0.0f;
	bool isClicked = false;;
	bool isActive = true;
	bool toDesactive = false;
	bool toActive = false;
	bool sound = true;

	int blitting_duration;
	int blittingCounter;
	int counter=0;
	bool alphaReach = true;
	int alpha = 255;


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

	bool Update();
	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	SDL_Texture* GetAtlas() const;


	iPoint lastMousePos = { 0,0 };
	iPoint newMousePos = { 0,0 };

	UI_Element* Add_UIElement(UI_Type type, iPoint position, SDL_Rect Image_Rect, Button_Logic = NONE_LOGIC, SDL_Rect Image_Rect_Active = NULL_RECT, SDL_Rect ButtonPush = NULL_RECT, float scale = 1.0f, SDL_Color Color = { 255,255,255,255 }, UI_Element* Parent = nullptr, const char* Text = nullptr);

	//UI_Element* Add_UIElement(UI_Type type, iPoint position, const char* Text = nullptr, UI_Element* Parent = nullptr);

	p2List<UI_Element*> UI_Elements_List;
	UI_Element*last;

	uint32 onTopSFX;
	uint32 clickSFX;

	bool Debug = false;
private:

	SDL_Rect a = { 0, 0, 219, 57 };

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__
