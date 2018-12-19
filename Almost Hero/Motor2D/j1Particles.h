#ifndef j1Particles_H
#define j1Particles_H

#include "j1Module.h"
#include "Animation.h"
#include "p2Defs.h"
#include "p2Point.h"
#include "j1Collisions.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

#define MAX_ACTIVE_PARTICLES 700


struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle {

	Particle();
	Particle(const Particle &p);
	~Particle();
	bool Update();


	Collider* collider = nullptr;
	SDL_Texture *Sprites = nullptr;
	Animation Anim;

	uint fx = 0;
	bool fx_played = false;

	iPoint Position;
	iPoint Speed;
	float scale;

	Uint32 Born = 0;
	Uint32 Life = 0;

	//TYPE Particle_Type = NO_PARTICLE;
	uint TimesCollided = 0;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;

};

class j1Particles : public j1Module
{
public:

	j1Particles();
	~j1Particles();

public:

	bool Start();
	bool Update(float ds);
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, fPoint speed = fPoint(0, 0), float scale = 1.0f, SDL_RendererFlip Flip = SDL_FLIP_NONE, Uint32 delay = 0);

private:

	Particle * active[MAX_ACTIVE_PARTICLES];

public:

	Particle Note_press_Succes;

	void LoadPushbacks(pugi::xml_node node, Animation &animation);

	SDL_Texture *Particle_1;
	SDL_Texture *particle0 = nullptr;

	Mix_Chunk *ImpactExplosionSound;
	Mix_Chunk *ImpactExplosionSound2;

	//this  function is to store info to destroy particles when it is necessary.
	uint Destroy1 = 999999;
	uint Destroy2 = 999999;
	uint Destroy3 = 999999;

private:
	pugi::xml_document	ParticleDocument;
	pugi::xml_node		Animation_node;

};

#endif