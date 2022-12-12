/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:08:48 by qlentz            #+#    #+#             */
/*   Updated: 2022/12/11 18:18:56 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_player *player)
{
	for(int x = 0; x < SCREENW; x++)
    {
		double rayDirX;
		double rayDirY;
		double cameraX;
      	//calculate ray position and direction
    	cameraX = 2 * x / (double)SCREENW - 1; //x-coordinate in camera space
	  	rayDirX = player->dir.x + player->plane.x * cameraX;
      	rayDirY = player->dir.y + player->plane.y * cameraX;

		//which box of the map are we in
		int mapX = (int)player->pos.x;
      	int mapY = (int)player->pos.y;

		//length of ray from current position to next x or y-side
      	double sideDistX;
      	double sideDistY;

      	//length of ray from one x or y-side to next x or y-side
      	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      	double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
      	int stepX;
		int stepY;
    	int hit = 0; //was there a wall hit?
    	int side; //was a NS or a EW wall hit?

      	//calculate step and initial sideDist
      	if(rayDirX < 0)
      	{
        	stepX = -1;
        	sideDistX = (player->pos.x - mapX) * deltaDistX;
      	}
      	else
      	{
        	stepX = 1;
        	sideDistX = (mapX + 1.0 - player->pos.x) * deltaDistX;
      	}
      	if(rayDirY < 0)
      	{
        	stepY = -1;
        	sideDistY = (player->pos.y - mapY) * deltaDistY;
      	}
      	else
      	{
        	stepY = 1;
        	sideDistY = (mapY + 1.0 - player->pos.y) * deltaDistY;
      	}
      	//perform DDA
      	while (hit == 0)
      	{
        	//jump to next map square, either in x-direction, or in y-direction
        	if(sideDistX < sideDistY)
        	{
          		sideDistX += deltaDistX;
          		mapX += stepX;
          		side = 0;
        	}
        	else
        	{
          		sideDistY += deltaDistY;
          		mapY += stepY;
          		side = 1;
        	}
        	//Check if ray has hit a wall
        	if(player->worldMap[mapX][mapY] > 0) hit = 1;
      	}

      	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      	else          perpWallDist = (sideDistY - deltaDistY);

      	//Calculate height of line to draw on screen
      	int lineHeight = (int)(SCREENH / perpWallDist);

      	//calculate lowest and highest pixel to fill in current stripe
      	int drawStart = -lineHeight / 2 + SCREENH / 2;
      	if(drawStart < 0) drawStart = 0;
      		int drawEnd = lineHeight / 2 + SCREENH / 2;
      	if(drawEnd >= SCREENH)
			drawEnd = SCREENH - 1;
		     
		//choose wall color
    	int color;
      	switch(player->worldMap[mapX][mapY])
      	{
        	case 1:  color = encode_rgb(255, 0, 0);  break; //red
        	case 2:  color = encode_rgb(0, 255, 0);  break; //green
        	case 3:  color = encode_rgb(0, 0, 255);   break; //blue
        	case 4:  color = encode_rgb(120, 120, 0);  break; //white
        	default: color = encode_rgb(255, 255, 255); break; //yellow
      	}

      	//give x and y sides different brightness
      	if (side == 1) {color = color / 2;}

      	//draw the pixels of the stripe as a vertical line
      	verLine(player->mlx, x, drawStart, drawEnd, color);
    }
}