#include "../../includes/cub3d.h"

static int is_element(char *line)
{
	if (ft_strnstr(line, "NO ",  ft_strlen(line)) != NULL\
	 || ft_strnstr(line, "SO ", ft_strlen(line)) != NULL\
	|| ft_strnstr(line, "WE ", ft_strlen(line)) != NULL\
	 || ft_strnstr(line, "EA ", ft_strlen(line)) != NULL\
	|| ft_strnstr(line, "F ", ft_strlen(line)) != NULL\
	 || ft_strnstr(line, "C ", ft_strlen(line)) != NULL)
	{
		return (1);
	}
	return (0);
}

int get_map(t_map *map)
{
	int i;
	int flag;
	int j;

	i = 0;
	flag = 0;
	while(map->file_read[i])
	{
		if (is_element(map->file_read[i]))
			flag++;
		i++;
		if (flag == 6)
		{
			while (map->file_read[i][0] == '\0' && map->file_read[i] != NULL)
				i++;
			break;
		}
	}
	map->map_height = map->file_lines - i;
	map->map = (char **)ft_calloc(sizeof(char *), (map->map_height + 1));
	j = 0;
	while (j < map->map_height)
		map->map[j++] = ft_strdup(map->file_read[i++]);
	map->map[j] = NULL;
	return (0);
}