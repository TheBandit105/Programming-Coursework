/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"

static SDL_Texture *sam[2];

void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;

	player->health = 1;

	sam[0] = loadTexture("gfx/sam01.png");
	sam[1] = loadTexture("gfx/sam02.png");

	player->texture = sam[0];

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void)
{
	player->dx = 0;

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_MOVE_SPEED;

		player->texture = sam[1];

	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_MOVE_SPEED;

		player->texture = sam[0];
		
	}

	if (app.keyboard[SDL_SCANCODE_UP] && player->isOnGround)
	{
		player->riding = NULL;

		player->dy = -20;

		playSound(SND_JUMP, CH_PLAYER);
	}

	if (app.keyboard[SDL_SCANCODE_SPACE])
	{
		player->x = player->y = 0;

		app.keyboard[SDL_SCANCODE_SPACE] = 0;
	}
}
