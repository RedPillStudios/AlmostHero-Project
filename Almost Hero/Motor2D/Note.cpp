#include "Note.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collisions.h"
#include "j1Input.h"
#include "j1Scene.h"

Note::Note()
{
}


Note::~Note()
{
}


// Called before the first frame
bool Note::Start() {

	note_tex = App->tex->Load("textures/Buttons_and_Notes.png");	
	return true;

}

// Called before quitting
bool Note::CleanUp() {

	LOG("Cleaning Up Notes");
	return true;
}

// Called each loop iteration
bool Note::Update(float dt) {

	if(scale <= 0.65f)
		scale += 0.0027f;
	
	position += velocity;

	if (this->note_collider != nullptr) {

		note_collider->SetPos(position.x - note_rect.w * 0.25f, position.y - note_rect.h * 0.25f);
		App->render->Blit(note_tex, position.x, position.y, &note_rect, scale, 1.0f, 0.0f, 53, 32);
	}


	return true;
}


Note* Note::CreateNote(NOTE_COLOR color) {

	Note *note = new Note();
	note->scale = 0.2f;
	
	switch (color) {

	case NOTE_COLOR::NOTE_VIOLET: 

		note->note_tex = note_tex;
		note->position = initial_pos;
		note->nColor = color;
		note->note_rect = { 0, 0, 107, 64 };
		break;

	case NOTE_COLOR::NOTE_BLUE:

		note->note_tex = note_tex;
		note->position = initial_pos + fPoint(30.0f , 0.0f);
		note->velocity = velocity + fPoint(0.5f, 0.0f);
		note->nColor = color;
		note->note_rect = { 107, 0, 107, 64 };
		break;

		case NOTE_COLOR::NOTE_YELLOW:

		note->note_tex = note_tex;
		note->position = initial_pos + fPoint(60.0f, 0.0f);
		note->nColor = color;
		note->velocity = velocity + fPoint(1.0f, 0.0f);
		note->note_rect = { 214, 0, 107, 64 };
		break;

		case NOTE_COLOR::NOTE_PINK:

		note->note_tex = note_tex;
		note->position = initial_pos + fPoint(90.0f, 0.0f);
		note->nColor = color;
		note->velocity = velocity + fPoint(1.47f, 0.0f);
		note->note_rect = { 321, 0, 107, 64 };
		break;

	case NOTE_COLOR::NOTE_NON:
		LOG("NOTE NON!");
		break;

	default:
		break;
	}
	
	SDL_Rect collider_rect = { note->note_rect.x * 0.5f, note->note_rect.y * 0.5f, note->note_rect.w * 0.5f, note->note_rect.h * 0.5f };
	note->note_collider = App->collisions->AddCollider(collider_rect, COLLIDER_NOTE, this);

	App->scene->notes.add(note);
	return note;
}

void Note::DestroyNote(Note* note) {

	p2List_item<Note*> *item = App->scene->notes.start;
	for (; item; item = item->next) {

		if (item->data == note) {

			if (note->note_collider != nullptr)
				note->note_collider->to_delete = true;

			App->scene->notes.del(item);
			break;

		}
	}
}

void Note::OnCollision(Collider *c1, Collider *c2) {

	if (c1->type == COLLIDER_NOTE && c2->type == COLLIDER_STATIC || c1->type == COLLIDER_STATIC && c2->type == COLLIDER_NOTE) //If for some reason collision fails, try to check both c1/c2 and c2/c1 instead of only c1/c2
		DestroyNote(this);

	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_VIOLET)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
			DestroyNote(this);
		
	}

	/*if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_BLUE)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = blue_note->nColor;
			blue_note->note_collider->to_delete = true;
			RELEASE(blue_note);

			if (blue_note == nullptr)
				blue_note = CreateNote(nIpos, 1, aux_col);


		}
	}

	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_YELLOW)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = yellow_note->nColor;
			yellow_note->note_collider->to_delete = true;
			RELEASE(yellow_note);

			if (yellow_note == nullptr)
				yellow_note = CreateNote(nIpos, 2, aux_col);


		}
	}

	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_PINK)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = pink_note->nColor;
			pink_note->note_collider->to_delete = true;
			RELEASE(pink_note);

			if (pink_note == nullptr)
				pink_note = CreateNote(nIpos, 3, aux_col);


		}
	}*/


}