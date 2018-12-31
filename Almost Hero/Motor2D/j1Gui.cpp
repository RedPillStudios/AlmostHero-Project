#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Scene.h"

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

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}


// Called before the first frame
bool j1Gui::Start()
{
	
	//onTopSFX = App->audio->LoadFx("audio/fx/button_hover_sfx.wav");
	clickSFX = App->audio->LoadFx("audio/fx/Click_Buttons.wav");
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}


// Update all guis
bool j1Gui::PreUpdate()
{

	
	return true;
}


bool j1Gui::Update() {


	
	return true;
}


// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<UI_Element*>* Item = UI_Elements_List.start;
	for (; Item != nullptr; Item = Item->next) {

		Item->data->Update();
		if (Item->data->isActive) {
			Item->data->onTop();
			if (Item->data->Clicked() == false) {

			}
			if (Item->data->onTop() == false) {
				int a = 1;
				Item->data->sound = true;
				Item->data->isClicked = false;
			}
			Item->data->Draw();
		}
	}

	return true;
}


// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}


// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}


UI_Element* j1Gui::Add_UIElement(UI_Type type, iPoint position, SDL_Rect Image_Rect,
	Button_Logic logic, SDL_Rect Image_Rect_Active, SDL_Rect ButtonPush, float scale, SDL_Color Color,
	UI_Element* Parent, const char* Text) {

	UI_Element* ret = nullptr;

	if (type == BUTTON || type==BAR) {
		ret = new UI_Element(type, position, Image_Rect, logic, Parent);
		ret->texture = GetAtlas();
		UI_Elements_List.add(ret);
		ret->UI_Rect_Active = Image_Rect_Active;
		if (Parent != nullptr) {
			ret->Parent = Parent;
			Parent->Child_List.add(ret);
		}
	}
	if (type == NON_INTERACTIVE) {

		ret = new UI_Element(type, position, Image_Rect, logic, Parent);
		ret->texture = GetAtlas();
		UI_Elements_List.add(ret);

		if (Parent != nullptr) {
			ret->Parent = Parent;
			Parent->Child_List.add(ret);
		}
	}
	else if (type == LABEL) {

		ret = new UI_Element(type, position, logic, Text, Parent);
		ret->texture = App->font->Print(Text, Color);

		ret->UI_Rect.x = 0;
		ret->UI_Rect.y = 0;
		App->font->CalcSize(Text, ret->UI_Rect.w, ret->UI_Rect.h);
		UI_Elements_List.add(ret);
		ret->CurrentRect = &ret->UI_Rect;
		if (Parent != nullptr) {
			ret->Parent = Parent;
			Parent->Child_List.add(ret);
		}
	}
	ret->scale = scale;
	ret->isActive = true;
	return ret;

}


void UI_Element::Draw() {

	if(Logic!=BLITTING)
	App->render->Blit(texture, Position.x, Position.y, CurrentRect, scale, angle, 0, 0,0, SDL_FLIP_NONE );
	else
		App->render->Blit(Current_Texture, Position.x, Position.y, CurrentRect, scale, angle, 0, 0, 0, SDL_FLIP_NONE);

	if (App->gui->Debug == true)
		App->render->DrawQuad({ Position.x,Position.y,UI_Rect.w,UI_Rect.h }, 255, 0, 0, 255, false, false, scale);

}


bool UI_Element::onTop() {

	int y;
	int x;

	App->input->GetMousePosition(x, y);

	if (x >= Position.x&&x < Position.x + UI_Rect.w*scale&&y >= Position.y&&y <= Position.y + UI_Rect.h*scale) {
		if (sound) {
			if (type == BUTTON||type==BAR) {
				if(isActive)
					App->audio->PlayFx(App->scene->On_top_buttons_SFX,0);
			}
			sound = false;
		}
		return true;
	}
	else
		return false;

}


bool UI_Element::Clicked() {

	if (onTop()) {
		if (App->input->GetMouseButtonDown(KEY_DOWN) && isClicked == false) {
			if (Logic != DRAGVOLUME && Logic != BACKVOLUME) {
				App->audio->PlayFx(App->gui->clickSFX);
				isClicked = true;
			}
				
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void UI_Element::Blitter() {

	if (counter <= 100)
		counter++;
	else
		counter = 0;
	
	int randNum = rand() % 89+1;
	if ( type == NON_INTERACTIVE) {
		if (Current_Texture == texture&&counter % randNum == 0) {
			Current_Texture = texture_Off;
			blittingCounter = randNum;
			blitting_duration = rand() % 10 + 1;
		}
		else if (Current_Texture == texture_Off&&counter % (blittingCounter + blitting_duration) == 0) {
			Current_Texture = texture;
		}
	}
	else {
		if (CurrentRect==&UI_Rect_Active&&counter % randNum == 0) {
			CurrentRect = &UI_Rect;
			blittingCounter = randNum;
			blitting_duration = rand() % 10 + 1;
		}
		else if (blittingCounter + blitting_duration == 0) {
			blittingCounter = 1;
		}
		else if (CurrentRect == &UI_Rect&&counter%(blittingCounter + blitting_duration) == 0) {
			CurrentRect = &UI_Rect_Active;
		}
	}

}


bool UI_Element::isParent() {

	if (Parent == nullptr)
		return false;
	else
		return true;
}


void UI_Element::Score(int score) {

	char score_Text[10];
	sprintf_s(score_Text, "%d", score); //warning: deprecated
	App->font->CalcSize(score_Text, UI_Rect.w, UI_Rect.h);
	texture = App->font->Print(score_Text);
}


void UI_Element::Time(int time) {

	char score_Text[10];
	sprintf_s(score_Text, "%02i", time); //warning: deprecated
	App->font->CalcSize(score_Text, UI_Rect.w, UI_Rect.h);
	texture = App->font->Print(score_Text);
}


void UI_Element::Drag() {

	if (Clicked()) {
		int x = 0;
		int y = 0;
		App->input->GetMouseMotion(x, y);
		if (isParent()) {
			initialPosition.x += x;
			initialPosition.y += y;
		}
		else
		{
			Position.x += x;
			Position.y += y;
		}
	}
}


void UI_Element::Update() {

	if (isParent()) {
		Position.x = Parent->Position.x + initialPosition.x;
		Position.y = Parent->Position.y + initialPosition.y;
	}
	if (type == BUTTON) {
		if (onTop()) {
			if (Clicked() == false) {
				CurrentRect = &UI_Rect_Active;
			}
			else
				CurrentRect = &UI_Rect;
		}
		else {
			CurrentRect = &UI_Rect;
		}
	}
	if (Child_List.count() > 0) {
		p2List_item<UI_Element*>* Item = Child_List.start;
		for (; Item != nullptr; Item = Item->next) {
			if (isActive)
				Item->data->isActive = true;
			else
				Item->data->isActive = false;
		}
	}
}


void UI_Element::Alert(SDL_Texture* texture, int& alpha) {

	if (alpha <= 255 && alphaReach) {
		alpha -= 7;
	}
	else if (alpha >= 90) {
		alphaReach = false;
		alpha += 2;
		if (alpha >= 255) {
			alphaReach = true;
		}
	}
	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, alpha);
}


void UI_Element::Active(UI_Element* toActive) {

	toActive->isActive = true;
}


void UI_Element::Deactive(UI_Element* toDeactive) {

	toDeactive->isActive = false;
}


void UI_Element::goWeb(const char* web) {

	ShellExecuteA(NULL, "open", web, NULL, NULL, SW_SHOWNORMAL);
}


void UI_Element::VolumeControl(iPoint newMousePos, iPoint lastMousePos,int &volume) {
	
	int barPosition = newMousePos.x - Position.x;
	UI_Rect.w = barPosition;
	
	//if (Position.x >= Parent->Position.x&&Position.x + UI_Rect.w*scale < (Parent->Position.x + Parent->UI_Rect.w*scale))
	//	initialPosition.x += newMousePos.x - lastMousePos.x;
	if (barPosition < 0)
		barPosition = 0;
	else if ( barPosition>=UI_Rect_Active.w)
		barPosition = UI_Rect_Active.w - 1;

	volume = (barPosition*200)/UI_Rect_Active.w;

}