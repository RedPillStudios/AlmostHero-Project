#include "j1App.h"
#include "j1Collisions.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Scene.h"


j1Collisions::j1Collisions()
{

	for (int i = 0; i < MAX_COLLIDERS; i++)
		colliders[i] = nullptr;
	

	for (int i = 0; i < COLLIDER_MAX; i++) {
		for (int j = 0; j < COLLIDER_MAX; j++)
			matrix[i][j] = false;
	}

	//Set all matrix positions to false
	for (int i = 0; i < COLLIDER_MAX; i++) {
		for (int j = 0; j < COLLIDER_MAX; j++)
			matrix[i][j] = false;
	}

	//Set all matrix positions that must be true to true (the others remain false)
	matrix[COLLIDER_STATIC][COLLIDER_NOTE] = true;
	matrix[COLLIDER_NOTE][COLLIDER_STATIC] = true;

	matrix[COLLIDER_SMASHER_BLUE][COLLIDER_NOTE] = true;
	matrix[COLLIDER_NOTE][COLLIDER_SMASHER_BLUE] = true;

	matrix[COLLIDER_SMASHER_YELLOW][COLLIDER_NOTE] = true;
	matrix[COLLIDER_NOTE][COLLIDER_SMASHER_YELLOW] = true;

	matrix[COLLIDER_SMASHER_VIOLET][COLLIDER_NOTE] = true;
	matrix[COLLIDER_NOTE][COLLIDER_SMASHER_VIOLET] = true;

	matrix[COLLIDER_SMASHER_PINK][COLLIDER_NOTE] = true;
	matrix[COLLIDER_NOTE][COLLIDER_SMASHER_PINK] = true;

}


j1Collisions::~j1Collisions()
{
}

bool j1Collisions::Awake() {

	LOG("Collisions Module Loading");
	bool ret = true;
	return ret;
}

bool j1Collisions::Start() {

	return true;
}


bool j1Collisions::PreUpdate() {

	bool ret = true;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		
		if (colliders[i] != nullptr) {

		//	LOG("Iteration: %i \n", i);
			if (colliders[i]->to_delete == true) {
				
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}
	}

	return ret;
}


bool j1Collisions::Update(float dt) {

	Collider *c1;
	Collider *c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {

		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		for (uint j = 0; j < MAX_COLLIDERS; ++j) {

			if (colliders[j] == nullptr)
				continue;

			c2 = colliders[j];

			if (c1->CheckCollision(c2->rect)) {

				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);
				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}
	return true;
}

bool j1Collisions::PostUpdate() {

	DebugDraw();
	return true;
}

void j1Collisions::DebugDraw() {

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return;

	for (uint i = 0; i < MAX_COLLIDERS; i++) {

		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type) {

		case COLLIDER_NONE:
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, 40);
			break;
		case COLLIDER_STATIC:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, 255);
			break;
		case COLLIDER_SMASHER_BLUE:
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, 200);
			break;
		case COLLIDER_SMASHER_YELLOW:
			App->render->DrawQuad(colliders[i]->rect, 255, 211, 0, 200);
			break;
		case COLLIDER_SMASHER_VIOLET:
			App->render->DrawQuad(colliders[i]->rect, 75, 0, 130, 200);
			break;
		case COLLIDER_SMASHER_PINK:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, 200);
			break;
		case COLLIDER_NOTE:
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 150, 100);
			break;
		default:
			break;

		}
	}
}

bool j1Collisions::CleanUp() {

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {

		if (colliders[i] != nullptr) {

			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}


Collider* j1Collisions::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module *callback) {

	Collider *ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i) {

		if (colliders[i] == nullptr) {

			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}
	return ret;
}

bool Collider::CheckCollision(const SDL_Rect &r) const {

	if ((r.x + r.w) < rect.x || (r.y + r.h) < rect.y || r.x > (rect.x + rect.w) || r.y > (rect.y + rect.h)) { return false; }
	return true;
}