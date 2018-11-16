#include "j1EntityManager.h"
#include "p2Log.h"
#include "j1Entity.h"

j1EntityManager::j1EntityManager()
{
	name.create("entities");
}


j1EntityManager::~j1EntityManager() {}

bool j1EntityManager::Awake() {

	LOG("AWAKING ENTITY MANAGER");
	times_per_sec = TIMES_PER_SEC; //Read this with an XML
	update_ms_cycle = 1.0f / (float)times_per_sec;

	return true;
}

bool j1EntityManager::PreUpdate() {

	do_logic = false;
	return true;
}

bool j1EntityManager::Update(float dt) {

	/*accumulated_time += dt;

	if (accumulated_time >= update_ms_cycle)
		do_logic = true;

	if (do_logic == true) {*/
	p2List_item<j1Entity*>*item = entities_list.start;
	for (; item != nullptr; item = item->next)
		item->data->Update(dt);

	accumulated_time = 0.0f;
	//}

	return true;
}

bool j1EntityManager::CleanUp() {

	LOG("Clean Up Entity Manager");

	p2List_item<j1Entity*>* item;
	item = entities_list.start;

	while (item != nullptr) {

		RELEASE(item->data);
		item = item->next;
	}

	entities_list.clear();

	return true;
}

j1Entity *j1EntityManager::CreateEntity(ENTITY_TYPE eType) {

	static_assert(ENTITY_TYPE::UNKNOWN == ENTITY_TYPE(2), "UPDATE ENTITY TYPES");

	j1Entity* Entity = nullptr;

	switch (eType) {

	case ENTITY_TYPE::ENEMY_ENT:
		Entity = new j1Entity(ENTITY_TYPE::ENEMY_ENT);
		break;
	case ENTITY_TYPE::PLAYER_ENT:
		Entity = new j1Entity(ENTITY_TYPE::PLAYER_ENT);
		break;
	default:
		break;

	}

	entities_list.add(Entity);
	return Entity;
}


void j1EntityManager::DestroyEntity(j1Entity *Entity) {

	p2List_item<j1Entity*>*item = entities_list.start;

	while (item != nullptr) {

		if (item->data == Entity) {

			entities_list.del(item);
			RELEASE(item->data);
			break;
		}

		item = item->next;
	}
}