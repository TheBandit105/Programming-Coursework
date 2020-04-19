#include "common.h"

static void logic(void);
static void draw(void);
static void drawLogo(void);

static int backgroundX;
static SDL_Texture* background;
static SDL_Texture* mineplexTexture;
static SDL_Texture* mazeTexture;
static int reveal = 0;
static int timeout;

void initObjective(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	mineplexTexture = loadTexture("gfx/mineplex.png");
	mazeTexture = loadTexture("gfx/maze.png");
}

static void logic(void)
{
	doBackground();

	drawMap();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
		background = loadTexture("gfx/mplx.png");
	}

	if (app.keyboard[SDL_SCANCODE_R])
	{
		initTitle();
	}

}

static void draw(void)
{
	drawBackground();

	drawMap();

	drawLogo();

	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 300, 0, 0, 0, TEXT_CENTER, "OBJECTIVE:");
		drawText(SCREEN_WIDTH / 2, 340, 0, 0, 0, TEXT_CENTER, "NAVIGATE AS SAM THROUGH THE CAVE SYSTEM");
		drawText(SCREEN_WIDTH / 2, 380, 0, 0, 0, TEXT_CENTER, "AND COLLECT 11 DIAMONDS TO");
		drawText(SCREEN_WIDTH / 2, 420, 0, 0, 0, TEXT_CENTER, "COMPLETE THE GAME. PLAY AND TIME WITH YOUR FRIENDS");
		drawText(SCREEN_WIDTH / 2, 460, 0, 0, 0, TEXT_CENTER, "AND SEE WHO GETS ALL THE DIAMONDS");
		drawText(SCREEN_WIDTH / 2, 500, 0, 0, 0, TEXT_CENTER, "WITHIN THE SHORTEST AMOUNT OF TIME.");
		
		drawText(SCREEN_WIDTH / 2, 650, 0, 0, 0, TEXT_CENTER, "PRESS R TO RETURN TO MENU");
	}
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