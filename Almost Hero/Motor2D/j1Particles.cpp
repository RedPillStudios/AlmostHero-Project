#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Particles.h"
#include "j1Scene.h"
#include "SDL/include/SDL_timer.h"



j1Particles::j1Particles() {

	name.create("Particles");
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

j1Particles::~j1Particles() {}

bool j1Particles::Start() {


	pugi::xml_parse_result result = ParticleDocument.load_file("Particle_Settings.xml");
	if (result == NULL)
		LOG("The xml file containing the player tileset fails. Pugi error: %s", result.description());


	Particle_1 = App->tex->Load("textures/Particles.png");

	Animation_node = ParticleDocument.child("config").child("Particle_Pushbacks").child("Note_Press_Succes");
	LoadPushbacks(Animation_node, Note_press_Succes.Anim);
	Note_press_Succes.Sprites = Particle_1;
	//Animation_node = ParticleDocument.child("config").child("Particle_Pushbacks").child("Player_Shoot");
	//App->scene->Player->LoadPushbacks(Animation_node, Player_Shoot.Anim);
	//Animation_node = ParticleDocument.child("config").child("Particle_Pushbacks").child("Enemy_Shoot");
	//App->scene->Player->LoadPushbacks(Animation_node, Enemy_Shoot.Anim);
	//Animation_node = ParticleDocument.child("config").child("Particle_Pushbacks").child("Player_Shot_Beam");
	//App->scene->Player->LoadPushbacks(Animation_node, Player_Shoot_Beam.Anim);
	//Animation_node = ParticleDocument.child("config").child("Particle_Pushbacks").child("Plasma_explosion");
	//App->scene->Player->LoadPushbacks(Animation_node, Plasma_Explosion.Anim);

	//Particle_1 = App->tex->Load("maps/Particles.png");
	////LOG("Loading Particles");
	////particle0 = App->textures->Load("Images/Player/Ship&Ball_Sprite.png");

	//Player_Shoot.Sprites = Blood.Sprites = Enemy_Shoot.Sprites = Plasma_Explosion.Sprites = Player_Shoot_Beam.Sprites = Particle_1;
	//Enemy_Shoot.Life = 600;
	//Player_Shoot.Life = 1200;
	//Player_Shoot.collider = App->collisions->AddCollider({ 0,0,80,10 }, COLLIDER_PLAYER_BULLET, this);
	return true;

}

void j1Particles::LoadPushbacks(pugi::xml_node node, Animation &animation) {

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

bool j1Particles::CleanUp() {

	LOG("Unloading Particles");

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		if (active[i] != nullptr) {
			App->tex->UnLoad(active[i]->Sprites);
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

bool j1Particles::Update(float dt) {



	bool ret = true;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {

		Particle *p = active[i];

		if (p == nullptr)
			continue;


		if (p->Update() == false) {

			delete p;
			active[i] = nullptr;
		}

		else if (SDL_GetTicks() >= p->Born) {

			App->render->Blit(p->Sprites, p->Position.x, p->Position.y, &(p->Anim.GetCurrentFrame()), p->scale, 1, 0, 0, 0,p->Flip,true);

			if (!p->fx_played)
				p->fx_played = true;

		}
	}

	return ret;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, fPoint speed, float scale, SDL_RendererFlip Flip, Uint32 delay) {
	int a = rand() % 2;
	if (a == 0)
		Flip = SDL_FLIP_NONE;
	else if (a == 1)
		Flip = SDL_FLIP_HORIZONTAL;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		if (active[i] == nullptr) {

			Particle* p = new Particle(particle);
			p->Born = SDL_GetTicks() + delay;
			p->Position.x = x;
			p->Position.y = y;
			p->Sprites = particle.Sprites;
			p->Speed.x = speed.x;
			p->Speed.y = speed.y;
			p->Flip = Flip;
			p->scale = scale;
		
			active[i] = p;
			break;

		}
	}
}

void j1Particles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1) {

			if (c2->type == COLLIDER_STATIC /*|| c2->type == COLLIDER_WALL*/) {

				delete active[i];
				active[i] = nullptr;

				break;
			}
		}
	}
}

Particle::Particle() {

	Position.SetToZero();
	Speed.SetToZero();
}

Particle::Particle(const Particle &p) :
	Anim(p.Anim), Position(p.Position), Speed(p.Speed),
	fx(p.fx), Born(p.Born), Life(p.Life) {}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update() {

	bool ret = true;

	if (Life > 0) {

		if (((int)SDL_GetTicks() - (int)Born) > (int)Life)
			return false;
	}
	else
		if (Anim.Finished())
			ret = false;

	if (collider != nullptr)
		ret = true;

	if (SDL_GetTicks() >= Born) {

		Position.x += Speed.x;
		Position.y += Speed.y;

		if (collider != nullptr)
			collider->SetPos(Position.x, Position.y);
	}

	return ret;

}
