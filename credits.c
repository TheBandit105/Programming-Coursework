#include "common.h"

static void logic(void);				  /*credits.c works in the same way as title.c, but it shows the credits of the game for the user to see
							                and it only	gives you the option to return to the title screen after you finished reading the credits.*/
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

	if (app.keyboard[SDL_SCANCODE_R])  /* Presing R allows for user to return to the title screen */
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
		drawText(SCREEN_WIDTH / 2, 380, 0, 0, 0, TEXT_CENTER, "TITLE SCREEN - SHAVIN CROOS");
		drawText(SCREEN_WIDTH / 2, 420, 0, 0, 0, TEXT_CENTER, "GAME GRAPHICS - SHAVIN CROOS");
		drawText(SCREEN_WIDTH / 2, 460, 0, 0, 0, TEXT_CENTER, "GAME DEVELOPMENT - SHAVIN CROOS");
		drawText(SCREEN_WIDTH / 2, 500, 0, 0, 0, TEXT_CENTER, "MUSIC - NOVA BY AHRIX ");
		drawText(SCREEN_WIDTH / 2, 540, 0, 0, 0, TEXT_CENTER, "SOUND EFFECTS FROM FREESOUND");
		drawText(SCREEN_WIDTH / 2, 580, 0, 0, 0, TEXT_CENTER, "LAST UPDATED: 19 APRIL 2020 AT 12:21 PM");
		drawText(SCREEN_WIDTH / 2, 650, 0, 0, 0, TEXT_CENTER, "PRESS R TO RETURN TO MENU");
	}
}													/* Tells the credits to the user and gives them the option to return to the title screen by pressing R.*/

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

