#include "j1ButtonEntity.h"
#include "j1Collisions.h"
#include "j1EntityManager.h"


j1ButtonEntity::j1ButtonEntity(iPoint pos, BUTTON_TYPE type_) : j1Entity(ENTITY_TYPE::ENEMY_ENT), position(pos)
{
}

j1ButtonEntity* j1ButtonEntity::CreateEnemy(iPoint pos, BUTTON_TYPE enemyType, const char* path, pugi::xml_document &EnemiesDocument) {

	static_assert(BUTTON_TYPE::UNKNOWN == BUTTON_TYPE(2), "UPDATE ENEMY TYPES");
	j1ButtonEntity* Button = nullptr;
	switch (enemyType) {

	case BUTTON_TYPE::FLYER:
		Button = new j1ButtonEntity(pos, path, EnemiesDocument);
		break;
	case BUTTON_TYPE::WALKER:
		Button = new j1ButtonEntity(pos, path, EnemiesDocument);
		break;
	default:
		break;
	}

	App->entity_manager->entities_list.add(Button);

	return Enemy;
}

bool j1Enemy::LoadEnemy(const char*file_name, pugi::xml_document &EnemiesDocument) {

	EnemySettings = EnemiesDocument.child("config");

	//Starting Position & Velocity
	initial_velocity.x = EnemySettings.child("EnemySettings").child("Velocity").attribute("velocity.x").as_int();
	initial_velocity.y = EnemySettings.child("EnemySettings").child("Velocity").attribute("velocity.y").as_int();

	enemy_rect.x = 0;
	enemy_rect.y = 0;
	enemy_rect.w = EnemySettings.child("image").attribute("w").as_int();
	enemy_rect.h = EnemySettings.child("image").attribute("h").as_int();

	enemy_Collider_rect.w = EnemySettings.child("EnemySettings").child("Collider").attribute("w").as_int();
	enemy_Collider_rect.h = EnemySettings.child("EnemySettings").child("Collider").attribute("h").as_int();

	entity_collider = App->collisions->AddColliderEntity({ enemy_Collider_rect.x, enemy_rect.y,enemy_Collider_rect.w ,enemy_Collider_rect.h }, COLLIDER_ENEMY, this);

	Enemy_tex = App->tex->Load(file_name);

	return true;
}

void j1Enemy::LoadPushbacks(pugi::xml_node node, Animation &animation) {

	animation.loop = node.attribute("loop").as_bool();
	animation.speed = node.attribute("speed").as_float();
	SDL_Rect rect;

	for (node = node.child("Pushback"); node; node = node.next_sibling("Pushback")) {

		rect.x = node.attribute("x").as_int();
		rect.y = node.attribute("y").as_int();
		rect.w = node.attribute("w").as_int();
		rect.h = node.attribute("h").as_int();
		animation.PushBack({ rect });
	}
}

void j1Enemy::OnCollision(Collider *c1, Collider *c2) {

	p2List_item<j1Entity*>* item = App->entity_manager->entities_list.start;

	for (; item != nullptr; item = item->next) {

		if (item->data->type == ENTITY_TYPE::ENEMY_ENT && c1 == item->data->entity_collider) {

			if (c2->type == COLLIDER_STATIC || (c2->type == COLLIDER_BLINKING && App->map->TriggerActive == true)) {

				//Calculating an error margin of collision to avoid problems with colliders corners
				int error_margin = 0;

				if (Direction == EN_RIGHT)
					error_margin = (c1->rect.x + c1->rect.w) - c2->rect.x;
				else if (Direction == EN_LEFT)
					error_margin = (c2->rect.x + c2->rect.w) - c1->rect.x;

				//If the enemy falls less than a pixel over a collider, it falls (and it looks ok)
				if (error_margin > 1) {

					//Checking Y Axis Collisions
					if (c1->rect.y <= c2->rect.y + c2->rect.h && c1->rect.y >= c2->rect.y + c2->rect.h - velocity.y) {

						velocity.y = 0;
						position.y = c1->rect.y + c2->rect.h - (c1->rect.y - c2->rect.y) + 3;
					}
					else if (c1->rect.y + c1->rect.h >= c2->rect.y && c1->rect.y + c1->rect.h <= c2->rect.y + velocity.y) {
						falling = false;
						velocity.y = 0;
						position.y = c1->rect.y - ((c1->rect.y + c1->rect.h) - c2->rect.y);
					}
				}

				//Checking X Axis Collisions
				if (c1->rect.x + c1->rect.w >= c2->rect.x && c1->rect.x + c1->rect.w <= c2->rect.x + velocity.x) { //Colliding Left (going right)

					velocity.x = 0;
					position.x -= (c1->rect.x + c1->rect.w) - c2->rect.x + 4;

				}
				else if (c1->rect.x <= c2->rect.x + c2->rect.w && c1->rect.x >= c2->rect.x + c2->rect.w - velocity.x) { //Colliding Right (going left)

					velocity.x = 0;
					position.x += (c2->rect.x + c2->rect.w) - c1->rect.x + 4;

				}
			}
		}
	}
}

void j1Enemy::DestroyEnemy(j1Enemy *Enemy) {

	p2List_item<j1Entity*>*item = App->entity_manager->entities_list.start;

	while (item != nullptr) {

		if (item->data == Enemy) {

			App->entity_manager->entities_list.del(item);
			RELEASE(item->data);
			break;
		}

		item = item->next;
	}
}