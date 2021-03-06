#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Timer.h"

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;
	void ResetCamera() {
		camera.x = 0;
		camera.y = 0;
	}

	//Camera Shake
	void CameraShake(float power);
	bool DoCameraShake = false;
	float power = 0;
	float Time_Doing_Shake;
	j1Timer CameraShake_Time;

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float scale = 1.0f, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX, SDL_RendererFlip Flip=SDL_FLIP_NONE,bool center=false) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, float scale_= 1.0f, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;
};

#endif // __j1RENDER_H__