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

void initCredits(void)
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
		drawText(SCREEN_WIDTH / 2, 300, 0, 0, 0, TEXT_CENTER, "CREDITS:");
		drawText(SCREEN_WIDTH / 2, 340, 0, 0, 0, TEXT_CENTER, "CREATED BY PARALLEL REALITIES");
		drawText(SCREEN_WIDTH / 2, 370, 0, 0, 0, TEXT_CENTER, "TITLE SCREEN - SHAVIN CROOS");
		drawText(SCREEN_WIDTH / 2, 400, 0, 0, 0, TEXT_CENTER, "GAME GRAPHICS - SHAVIN CROOS");
		drawText(SCREEN_WIDTH / 2, 430, 0, 0, 0, TEXT_CENTER, "GAME DEVELOPMENT - SHAVIN CROOS");
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

