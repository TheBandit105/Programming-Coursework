#include "common.h"

static void logic(void);	  /*endscreen.c works in the same way as title.c, except it doesnt feature the "Mineplex Maze" logo 
							  and it only	gives you the option to terminate the program after you finished playing the game.*/
static void draw(void);			
static void drawHud(void);
static void drawLogo(void);

static SDL_Texture* background;
static SDL_Texture* mineplexTexture;
static SDL_Texture* mazeTexture;
static int backgroundX;
static int reveal = 0;

void initEndscreen(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	mineplexTexture = loadTexture("gfx/mineplex.png");
	mazeTexture = loadTexture("gfx/maze.png");

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();
}

static void logic(void)
{
	doBackground();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
		background = loadTexture("gfx/mplx.png");
	}

	doCamera();

	if (app.keyboard[SDL_SCANCODE_ESCAPE])  // Closes the window after you press the escape button.
	{
		exit(1);
	}
}

static void draw(void)
{
	drawBackground();

    drawLogo();

	drawHud();

	drawText(SCREEN_WIDTH / 2, 475, 0, 0, 0, TEXT_CENTER, "WELL DONE, YOU COLLECTED ALL THE DIAMONDS! PRESS ESC TO QUIT.");	 // Congratulates the user on completing the game and tells them to quit the game by pressing the escape button.
}

static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "DIAMONDS COLLECTED: 11/11");
}

static void drawLogo(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(mineplexTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(mineplexTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);

	SDL_QueryTexture(mazeTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(mazeTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 160);

}

