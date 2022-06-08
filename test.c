# include "solong.h"
# include "./libft/libft.h"

static void	get_map(t_map *map, int fd)
{
	char	*line;
	char	*lines;
	char	*temp;

	line = NULL;
	lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = lines;
		lines = ft_strjoin(lines, line);
		free(line);
		free(temp);
	}
	map->map = ft_split(lines, '\n');
	free(lines);
	map->column = ft_strlen(map->map[0]); //check map으로
}

int main()
{
	t_map	*map = ft_calloc(1, sizeof(t_map));
	int fd = open("./map/map.ber", O_RDONLY);
	get_map(map, fd);
	int i = 0;
	while ((map->map)[i])
	{
		printf("%s\n", (map->map)[i]);
		i++;
	}
}