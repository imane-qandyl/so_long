#include "so_long.h"
//the top and bottom rows)
static  horizontalwall(t_complete *game)
{
    int	i;
	int	j;
    i = game->widthmap;
    j = 0;
    while(j < i)
    {
        if(game->map[0][i] == '1' && game->map[game->heightmap - 1][j] == '1')
            return(0); //wall enclosed
        j++;
    }
    return(1);//wall fail
}

static  int verticalwall(t_complete *game)
{
    int height;
    int width;

    height = 0;
    width = game->widthmap;
    while(height < game->heightmap)
    {
        if(!(game->map[height][0] == '1' && game->map[height][width - 1] == '1'))
            return(0);
        height++;
    }
    return(1);
}
//map is properly enclosed.
static void	if_walls(t_complete *game)
{
	int	verticalwalls;
	int	horizontalwalls;

	verticalwalls = verticalwall(game);
	horizontalwalls = horizontalwall(game);
	if (!verticalwalls || !horizontalwalls)
	{
		printf("\nThis map is missing the walls\n");
		exit_point(game);
	}
}
// checks individual cells in the map for valid characters
static void	count_checker(t_complete *game, int height, int width)
{
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'P' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'C' &&
		game->map[height][width] != '\n')
	{
		printf("\nError Here!%c\n", game->map[height][width]);
		exit_point(game);
	}
	if (game->map[height][width] == 'C')
			game->columncount++;
	if (game->map[height][width] == 'P')
			game->playercount++;
	if (game->map[height][width] == 'E')
			game->exitcount++;
}
//contains exactly one player start position, at least one collectible, and exactly one exit.
void	character_valid(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->heightmap - 1)
	{
		width = 0;
		while (width <= game->widthmap)
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
	}
	if (!(game->playercount == 1 && game->columncount > 1
			&& game->exitcount == 1))
	{
		printf("\nError\nSomething is wrong!\n");
		printf("either player, exit or collectable issue\n");
		exit_point(game);
	}
}

void	check_errors(t_complete *game)
{
	if_walls(game);
	character_valid(game);
}
