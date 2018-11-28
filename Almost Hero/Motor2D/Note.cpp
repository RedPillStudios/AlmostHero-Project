//#include "Note.h"
//#include "j1Render.h"
//#include "j1Textures.h"
//#include "j1Collisions.h"
//#include "j1Input.h"
//#include "j1Scene.h"
//
//Note::Note()
//{
//	name.create("Note");
//}
//
//
//Note::~Note()
//{
//}
//
//
//// Called before the first frame
//bool Note::Start() {
//
//	note_tex = App->tex->Load("textures/Buttons_and_Notes.png");
//	return true;
//
//
//
//}
//
//// Called before quitting
//bool Note::CleanUp() {
//
//	LOG("Cleaning Up Notes");
//	return true;
//}
//
//// Called each loop iteration
//bool Note::Update(float dt) {
//
//
//		if (scale <= 0.65f)
//			scale += 0.0020f;
//
//		position += velocity;
//		if (velocity.y <= maxVelocity.y) {
//			velocity.y += Acceleration.y;
//		}
//
//		if (maxVelocity.x <= 0) {
//			if (velocity.x >= maxVelocity.x) {
//				velocity.x -= Acceleration.x;
//			}
//		}
//		else if (maxVelocity.x >=0) {
//			if (velocity.x <= maxVelocity.x) {
//				velocity.x += Acceleration.x;
//			}
//		}
//
//		if (note_collider != nullptr) {
//
//			note_collider->SetPos(position.x - note_rect.w * 0.25f, position.y - note_rect.h * 0.25f);
//			App->render->Blit(note_tex, position.x, position.y, &note_rect, scale, 1.0f, 0.0f, 53, 32);
//		}
//
//	return true;
//}
//
//
//Note* Note::CreateNote(NOTE_COLOR color) {
//
//	Note *note = new Note();
//	note->scale = 0.2f;
//
//	switch (color) {
//
//	case NOTE_COLOR::NOTE_VIOLET:
//
//		note->note_tex = note_tex;
//		note->position = initial_pos;
//		note->nColor = color;
//		note->note_rect = { 0, 0, 107, 64 };
//		note->Acceleration = fPoint(0.0060f, 0.017f);
//		note->maxVelocity = fPoint{ -0.79f,5.00f };
//		break;
//
//	case NOTE_COLOR::NOTE_BLUE:
//
//		note->note_tex = note_tex;
//		note->position = initial_pos + fPoint(30.0f , 0.0f);
//		note->velocity = fPoint(0.0f, 0.2f);
//		note->nColor = color;
//		note->note_rect = { 107, 0, 107, 64 };
//		note->Acceleration = fPoint(0.0040f, 0.017f);
//		note->maxVelocity = fPoint(-0.15, 5.00f);
//		break;
//
//	case NOTE_COLOR::NOTE_YELLOW:
//
//		note->note_tex = note_tex;
//		note->position = initial_pos + fPoint(60.0f, 0.0f);
//		note->nColor = color;
//		note->velocity =  fPoint(0.0f, 0.2f);
//		note->note_rect = { 214, 0, 107, 64 };
//		note->Acceleration = fPoint(0.0060f,0.017f);
//		note->maxVelocity = fPoint( 0.2f,5.00f );
//		break;
//
//	case NOTE_COLOR::NOTE_PINK:
//
//		note->note_tex = note_tex;
//		note->position = initial_pos + fPoint(90.0f, 0.0f);
//		note->nColor = color;
//		note->velocity = fPoint(0.0f, 0.2f);
//		note->note_rect = { 321, 0, 107, 64 };
//		note->Acceleration = fPoint(0.0080f, 0.017f);
//		note->maxVelocity = fPoint(0.79f, 5.00f);
//		break;
//
//	case NOTE_COLOR::NOTE_NON:
//		LOG("NOTE NON!");
//		break;
//
//	default:
//		break;
//	}
//
//	SDL_Rect collider_rect = { note->note_rect.x * 0.5f, note->note_rect.y * 0.5f, note->note_rect.w * 0.5f, note->note_rect.h * 0.5f };
//	note->note_collider = App->collisions->AddCollider(collider_rect, COLLIDER_NOTE, this);
//
//	App->scene->notes.add(note);
//	return note;
//}
//
//void Note::DestroyNote(Note* note) {
//
//	p2List_item<Note*> *item = App->scene->notes.start;
//	for (; item; item = item->next) {
//
//		if (item->data == note) {
// 			if (item->data->note_collider != nullptr)
//				item->data->note_collider->to_delete = true;
//			App->scene->notes.del(item);
//			break;
//
//		}
//	}
//}
//
//void Note::OnCollision(Collider *c1, Collider *c2) {
//
//	colliding = true;
//
//	if (c1->type == COLLIDER_NOTE && c2->type == COLLIDER_STATIC || c1->type == COLLIDER_STATIC && c2->type == COLLIDER_NOTE) { //If for some reason collision fails, try to check both c1/c2 and c2/c1 instead of only c1/c2
//		if (General_collided_timer.Read() >= 100) {
//
//			DestroyNote(App->scene->notes.start->data);
//			PERF_START(General_collided_timer);
//			numNotes = 0;
//
//			if (App->render->DoCameraShake == false) {
//				App->render->DoCameraShake = true;
//				App->render->power = 2.0f;
//				App->render->Time_Doing_Shake = 0.2f;
//				PERF_START(App->render->CameraShake_Time);
//			}
//			colliding = false;
//		}
//	}
//
//	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_VIOLET)) {
//
//		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {
//			if (Violet_collided_timer.Read() >= 100){
//
//				p2List_item<Note*> *item = App->scene->notes.start;
//				for (; item; item = item->next) {
//					if (item->data->nColor == NOTE_VIOLET) {
//
//						DestroyNote(item->data);
//						PERF_START(Violet_collided_timer);
//						numNotes++;
//
//						break;
//					}
//				}
//		  }
//		}
//	}
//
//	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_BLUE)) {
//		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {
//
//			if (Blue_collided_timer.Read() >= 100) {
//
//				p2List_item<Note*> *item = App->scene->notes.start;
//				for (; item; item = item->next) {
//					if (item->data->nColor == NOTE_BLUE) {
//
//						DestroyNote(item->data);
//						PERF_START(Blue_collided_timer);
//						numNotes++;
//			
//						break;
//					}
//				}
//			}
//		}
//	}
//
//	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_YELLOW)) {
//		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
//
//			if (Yellow_collided_timer.Read() >= 100) {
//
//				p2List_item<Note*> *item = App->scene->notes.start;
//				for (; item; item = item->next) {
//					if (item->data->nColor == NOTE_YELLOW) {
//
//						DestroyNote(item->data);
//						PERF_START(Yellow_collided_timer);
//						numNotes++;
//				
//						break;
//					}
//				}
//			}
//		}
//	}
//
//	if ((c1->type == COLLIDER_NOTE && c2->type == COLLIDER_SMASHER_PINK)) {
//		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT) {
//
//			if (Pink_collided_timer.Read() >= 100) {
//
//				p2List_item<Note*> *item = App->scene->notes.start;
//				for (; item; item = item->next) {
//					if (item->data->nColor == NOTE_PINK) {
//
//						DestroyNote(item->data);
//						PERF_START(Pink_collided_timer);
//						numNotes++;
//						break;
//					}
//				}
//			}
//		}
//	}
//}
