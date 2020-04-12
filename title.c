#include "common.h"

static void logic(void);
static void draw(void);
static void drawLogo(void);

static int backgroundX;
static SDL_Texture* background;
static SDL_Texture* backgroundTexture;
static SDL_Texture* mineplexTexture;
static SDL_Texture* mazeTexture;
static int reveal = 0;
static int timeout;

void initTitle(void)
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

	if (app.keyboard[SDL_SCANCODE_P])
	{
		initStage();
	}

	if (app.keyboard[SDL_SCANCODE_ESCAPE])
	{
		exit(1);
	}
}

static void draw(void)
{
	drawBackground();

	drawMap();

	drawLogo();

	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 500, 0, 0, 0, TEXT_CENTER, "PRESS P TO PLAY!");
		drawText(SCREEN_WIDTH / 2, 550, 0, 0, 0, TEXT_CENTER, "CONTROLS:");
		drawText(SCREEN_WIDTH / 2, 580, 0, 0, 0, TEXT_CENTER, "LEFT - LEFT KEY | RIGHT - RIGHT KEY");
		drawText(SCREEN_WIDTH / 2, 610, 0, 0, 0, TEXT_CENTER, "JUMP - UP KEY");
		drawText(SCREEN_WIDTH / 2, 640, 0, 0, 0, TEXT_CENTER, "RESET - SPACE");
		drawText(SCREEN_WIDTH / 2, 670, 0, 0, 0, TEXT_CENTER, "QUIT - ESCAPE");
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

	blitRect(mazeTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 250);
}

void initBackground(void)
{
	//background = loadTexture("gfx/mplx.png");

	backgroundX = 0;
}

void doBackground(void)
{
	if (--backgroundX < -SCREEN_WIDTH)
	{
		backgroundX = 0;
	}
}

void drawBackground(void)
{
	SDL_Rect dest;
	int x;

	for (x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;

		SDL_RenderCopy(app.renderer, background, NULL, &dest);
	}
}
