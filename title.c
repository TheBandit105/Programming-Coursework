#include "common.h"

static void logic(void);
static void draw(void);
static void drawLogo(void);

static int backgroundX;
static SDL_Texture* background;												/*These SDL_Texture pointers allow for the textures to be generated onto the title screen in the first place.*/
static SDL_Texture* mineplexTexture;
static SDL_Texture* mazeTexture;
static int reveal = 0;
static int timeout;

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);				/* Tells the program what and how the title screen should be set up upon startup.*/

	mineplexTexture = loadTexture("gfx/mineplex.png");
	mazeTexture = loadTexture("gfx/maze.png");
}

static void logic(void)
{
	doBackground();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
		background = loadTexture("gfx/mplx.png");
	}

	if (app.keyboard[SDL_SCANCODE_P])
	{
		initStage();
	}																		  /* Tells the program that if the user selects any one of these keys that the function is carried out.
																			  When P is press, it initialises the stage and it takes the user to play the game. When user presses the escape key, the program terminates.
																			  When K is pressed, the user is shown to the credits and when O is pressed, the user is shown to the objectives.*/

	if (app.keyboard[SDL_SCANCODE_ESCAPE])
	{
		exit(1);
	}

	if (app.keyboard[SDL_SCANCODE_K])
	{
		initCredits();
	}

	if (app.keyboard[SDL_SCANCODE_O])
	{
		initObjective();
	}
}

static void draw(void)
{
	drawBackground();

	drawLogo();

	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 300, 0, 0, 0, TEXT_CENTER, "PRESS P TO PLAY!");
		drawText(SCREEN_WIDTH / 2, 350, 0, 0, 0, TEXT_CENTER, "CONTROLS:");
		drawText(SCREEN_WIDTH / 2, 390, 0, 0, 0, TEXT_CENTER, "LEFT - LEFT KEY | RIGHT - RIGHT KEY");
		drawText(SCREEN_WIDTH / 2, 430, 0, 0, 0, TEXT_CENTER, "JUMP - UP KEY");											   /* drawText allows for text to be written onto the title screen*/
		drawText(SCREEN_WIDTH / 2, 475, 0, 0, 0, TEXT_CENTER, "RESET FROM START (ALSO RESETS TIME) - SPACE");
		drawText(SCREEN_WIDTH / 2, 520, 0, 0, 0, TEXT_CENTER, "CREDITS - K");
		drawText(SCREEN_WIDTH / 2, 565, 0, 0, 0, TEXT_CENTER, "OBJECTIVE (TASK OF THE GAME) - O");
		drawText(SCREEN_WIDTH / 2, 610, 0, 0, 0, TEXT_CENTER, "QUIT - ESCAPE");
	}
}

static void drawLogo(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(mineplexTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);													   /*This allows for the logos to be animated as well as be drawn and displayed on the title screen.*/

	blitRect(mineplexTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);

	SDL_QueryTexture(mazeTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(mazeTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 160);
}

void initBackground(void)
{
	backgroundX = 0;
}
																					   /*This allows for the background to be animated as well as be drawn and displayed on the title screen.*/
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
