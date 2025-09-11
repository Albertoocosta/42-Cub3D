
#include "cub3D.h"


//FUNcAO APENAS pARa dEbuG
void	addMapToStruct(t_cub *cub)
{
	int i = 0;

	cub->map = ft_calloc(sizeof(char *), 5);
	cub->map[0] = ft_strdup("11111");
	cub->map[1] = ft_strdup("10001");
	cub->map[2] = ft_strdup("100N1");
	cub->map[3] = ft_strdup("11111");
	while (cub->map[i])
	{
		printf("Linha [%d] = %s\n", i, cub->map[i]);
		i++;
	}
}