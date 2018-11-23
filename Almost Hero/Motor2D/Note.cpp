#include "Note.h"
#include "j1Render.h"
#include "j1Textures.h"

Note::Note()
{
}


Note::~Note()
{
}


// Called before the first frame
bool Note::Start() {

	note_tex = App->tex->Load("textures/Buttons_and_Notes.png");

	//Notes
	violet_note = CreateNote(NOTE_VIOLET);
	/*violet_note = CreateNote(nIpos, 0, NOTE_VIOLET);
	blue_note = CreateNote(nIpos, 1, NOTE_BLUE);
	yellow_note = CreateNote(nIpos, 2, NOTE_YELLOW);
	pink_note = CreateNote(nIpos, 3, NOTE_PINK);*/

	return true;

}

// Called before quitting
bool Note::CleanUp() {

	LOG("Cleaning Up Notes");
	RELEASE(violet_note);
	return true;
}

// Called each loop iteration
bool Note::Update(float dt) {

	if(scale <= 0.65f)
		scale += 0.0027f;
	
	/*violet_note->position += violet_note->velocity;

	violet_note->note_collider->SetPos(violet_note->position.x - violet_note->note_rect.w * 0.25f, violet_note->position.y - violet_note->note_rect.h * 0.25f);
	App->render->Blit(note_tex, violet_note->position.x, violet_note->position.y, &violet_note->note_rect, scale, 1.0f, 0.0f, 53, 32);
*/

	position += velocity;

	if (this->note_collider != nullptr) {
		note_collider->SetPos(this->position.x - this->note_rect.w * 0.25f, this->position.y - this->note_rect.h * 0.25f);
		App->render->Blit(note_tex, this->position.x, this->position.y, &this->note_rect, scale, 1.0f, 0.0f, 53, 32);
	}


	return true;
}


Note* Note::CreateNote(NOTE_COLOR color) {

	Note *note = new Note();
	scale = 0.2f;
	
	switch (color) {

	case NOTE_COLOR::NOTE_VIOLET: 

		note->note_tex = note_tex;
		note->position = initial_pos;
		note->nColor = color;
		note->note_rect = { 0, 0, 107, 64 };
		break;

	case NOTE_COLOR::NOTE_NON:
		LOG("NOTE NON!");
		break;

	default:
		break;
	}
	

	SDL_Rect collider_rect = { note->note_rect.x * 0.5f, note->note_rect.y * 0.5f, note->note_rect.w * 0.5f, note->note_rect.h * 0.5f };
	note->note_collider = App->collisions->AddCollider(collider_rect, COLLIDER_NOTE, this);

	return note;
}


void Note::OnCollision(Collider *c1, Collider *c2) {

	if (c1->type == COLLIDER_NOTE && c2->type == COLLIDER_STATIC) { //If for some reason collision fails, try to check both c1/c2 and c2/c1 instead of only c1/c2


		NOTE_COLOR aux_col = violet_note->nColor;
		violet_note->note_collider->to_delete = true;
		RELEASE(violet_note);
		
		if (violet_note == nullptr)
			violet_note = CreateNote(aux_col);

	}

	/*if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_VIOLET)) {

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {

			NOTE_COLOR aux_col = violet_note->nColor;
			violet_note->note_collider->to_delete = true;
			RELEASE(violet_note);

			if (violet_note == nullptr)
				violet_note = CreateNote(nIpos, 0, aux_col);


		}
	}

	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_BLUE)) {

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


//void j1Scene::MoveNote(Note* note) {
//
//	note->scale += 0.002f;
//	App->render->DrawQuad(note->note_rect, 0, 150, 0, 150, note->scale);
//
//	//note->nPosition = fPoint(note->note_rect.x, note->note_rect.y);
//
//	note->nPosition.x -= nVelocity.x;
//	note->nPosition.y += nVelocity.y;
//
//	note->note_rect = { (int)note->nPosition.x, (int)note->nPosition.y, 35, 35 };
//
//	note->note_collider->SetPos(note->nPosition.x, note->nPosition.y);
//
//}
