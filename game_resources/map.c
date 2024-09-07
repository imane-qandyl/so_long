#include "so_long.h"
//These functions are used to read a map from a file and store it in a data

static int width_of_map(char *str)
{
    int width;

    width = 0;
    while(str[width])
        width++;
    if(str[width - 1] == '\n') // subtracts \n
        width--;
    return(width);
}
static int	add_line(t_complete *game, char *line)
{
    char **temp;
    int i;
    if(!line)
        return(0);
    i = 0;
    game->heightmap++; //number of lines 
	temp = (char **)malloc(sizeof(char *) * (game->heightmap + 1));
	temp[game->heightmap] = NULL;
	while (i < game->heightmap - 1)
	{
		temp[i] = game->map[i];
		i++;
	}
	temp[i] = line; //\n
	if (game->map)
		free(game->map);
	game->map = temp;
	return (1);
}
int	map_reading(t_complete *game, char **argv)
{
	char	*readmap;

	game->fd = open(argv[1], O_RDONLY);
	if (game->fd < 0)
		return (0);
	while (1)
	{
		readmap = get_next_line(game->fd); //Each line read is added to the map 
		if (!add_line(game, readmap))
			break ;
	}
	close (game->fd);
	game->widthmap = width_of_map(game->map[0]);
	return (1);
}
