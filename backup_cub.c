/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:20:00 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/14 15:43:24 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 ! Creates a small debug map for testing purposes
 ! This function allocates and initializes a simple 5x5 test map
*/
void create_debug_map(t_cub *cub)
{
	int i;

	// Set map dimensions
	cub->map.map_w = 5;
	cub->map.map_h = 5;

	// Allocate memory for the map
	cub->map.map = ft_calloc(cub->map.map_h + 1, sizeof(char *));
	if (!cub->map.map)
	{
		printf("Error: Failed to allocate memory for debug map\n");
		return;
	}

	// Create each row of the map
	for (i = 0; i < cub->map.map_h; i++)
	{
		cub->map.map[i] = ft_calloc(cub->map.map_w + 1, sizeof(char));
		if (!cub->map.map[i])
		{
			printf("Error: Failed to allocate memory for map row %d\n", i);
			return;
		}
	}

	// Initialize the debug map layout
	// Simple 5x5 map with walls around the border and open space in the middle
	ft_strcpy(cub->map.map[0], "11111");
	ft_strcpy(cub->map.map[1], "1N001"); // N = North facing player spawn
	ft_strcpy(cub->map.map[2], "10001");
	ft_strcpy(cub->map.map[3], "10001");
	ft_strcpy(cub->map.map[4], "11111");

	// Set player starting position and direction
	cub->player.pos_x = 1.5; // Middle of the spawn cell
	cub->player.pos_y = 1.5;
	cub->player.spawn_dir = 'N';

	// Set player direction vectors for North facing
	cub->player.dir_x = 0.0;
	cub->player.dir_y = -1.0;	// North is negative Y
	cub->player.plane_x = 0.66; // Camera plane perpendicular to direction
	cub->player.plane_y = 0.0;

	// Initialize basic texture colors (you can modify these)
	cub->texture.floor_hex = 0x404040; // Dark gray floor
	cub->texture.ceil_hex = 0x87CEEB;  // Sky blue ceiling

	// Initialize texture paths with debug textures
	cub->texture.no_path = ft_strdup("./assets/textures/validTextures/north.xpm");
	cub->texture.so_path = ft_strdup("./assets/textures/validTextures/south.xpm");
	cub->texture.we_path = ft_strdup("./assets/textures/validTextures/west.xpm");
	cub->texture.ea_path = ft_strdup("./assets/textures/validTextures/east.xpm");

	// Check if texture path allocation succeeded
	if (!cub->texture.no_path || !cub->texture.so_path ||
		!cub->texture.we_path || !cub->texture.ea_path)
	{
		printf("Error: Failed to allocate texture paths\n");
		return;
	}

	// Set texture flags to indicate they are loaded
	cub->texture.has_no = true;
	cub->texture.has_so = true;
	cub->texture.has_we = true;
	cub->texture.has_ea = true;
	cub->texture.has_floor = true;
	cub->texture.has_ceil = true;

	// Initialize RGB values for floor and ceiling
	cub->texture.floor_rgb[0] = 64; // R component of 0x404040
	cub->texture.floor_rgb[1] = 64; // G component of 0x404040
	cub->texture.floor_rgb[2] = 64; // B component of 0x404040

	cub->texture.ceil_rgb[0] = 135; // R component of 0x87CEEB
	cub->texture.ceil_rgb[1] = 206; // G component of 0x87CEEB
	cub->texture.ceil_rgb[2] = 235; // B component of 0x87CEEB

	printf("Debug map created successfully!\n");
	printf("Map dimensions: %dx%d\n", cub->map.map_w, cub->map.map_h);
	printf("Player position: (%.1f, %.1f)\n", cub->player.pos_x, cub->player.pos_y);
	printf("Textures loaded:\n");
	printf("  North: %s\n", cub->texture.no_path);
	printf("  South: %s\n", cub->texture.so_path);
	printf("  West:  %s\n", cub->texture.we_path);
	printf("  East:  %s\n", cub->texture.ea_path);
	printf("Floor color: RGB(%d, %d, %d) = 0x%06X\n",
			cub->texture.floor_rgb[0], cub->texture.floor_rgb[1],
			cub->texture.floor_rgb[2], cub->texture.floor_hex);
	printf("Ceiling color: RGB(%d, %d, %d) = 0x%06X\n",
			cub->texture.ceil_rgb[0], cub->texture.ceil_rgb[1],
			cub->texture.ceil_rgb[2], cub->texture.ceil_hex);
}

/*
 ! Prints the debug map to console for verification
*/
void print_debug_map(t_cub *cub)
{
	int i;

	if (!cub->map.map)
	{
		printf("Error: No map to display\n");
		return;
	}

	printf("\n=== DEBUG MAP ===\n");
	for (i = 0; i < cub->map.map_h; i++)
	{
		printf("%s\n", cub->map.map[i]);
	}
	printf("==================\n\n");
}


Funcao set MLX
int set_mlx(t_cub *cub)
{
	cub->mlx.mlx_ptr = mlx_init();
	if (cub->mlx.mlx_ptr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr, WIDTH, HEIGHT,
									WIN_TITLE);
	if (cub->mlx.win_ptr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	cub->mlx.img_ptr = mlx_new_image(cub->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (cub->mlx.img_ptr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);
	cub->mlx.img_addr = (int *)mlx_get_data_addr(cub->mlx.img_ptr,
												&cub->mlx.bits_per_pixel, &cub->mlx.size_line, &cub->mlx.endian);
	if (cub->mlx.img_addr == NULL)
		return (ft_putstr_fd("Mlx error\n", 2), 1);

	// ! Added to fix ESC and X closing window (Maight be for debug)
	mlx_hook(cub->mlx.win_ptr, KeyPress, KeyPressMask, key_press_handler, cub);
	mlx_hook(cub->mlx.win_ptr, KeyRelease, KeyReleaseMask, key_release_handler, cub);
	mlx_hook(cub->mlx.win_ptr, DestroyNotify, StructureNotifyMask, exit_cub3d, cub);

	return (0);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:30:00 by rde-fari          #+#    #+#             */
/*   Updated: 2025/10/14 16:27:40 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int load_single_texture(t_cub *cub, char *path, int index)
{
	void *img;
	int *data;
	int width;
	int height;
	int i;

	img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, path, &width, &height);
	if (!img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (1);
	}

	cub->texture.size = width; // Assume square textures
	data = (int *)mlx_get_data_addr(img, &cub->mlx.bits_per_pixel,
									&cub->mlx.size_line, &cub->mlx.endian);

	if (!data)
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, img);
		printf("Error: Failed to get texture data: %s\n", path);
		return (1);
	}

	// Allocate memory for texture data
	cub->texture.texture_grid[index] = malloc(sizeof(int) * width * height);
	if (!cub->texture.texture_grid[index])
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, img);
		printf("Error: Failed to allocate memory for texture data\n");
		return (1);
	}

	// Copy texture data
	i = 0;
	while (i < width * height)
	{
		cub->texture.texture_grid[index][i] = data[i];
		i++;
	}

	mlx_destroy_image(cub->mlx.mlx_ptr, img);
	return (0);
}

int load_textures(t_cub *cub)
{
	// Allocate memory for texture grid array
	cub->texture.texture_grid = malloc(sizeof(int *) * 4);
	if (!cub->texture.texture_grid)
	{
		printf("Error: Failed to allocate memory for texture grid\n");
		return (1);
	}

	// Initialize all pointers to NULL
	cub->texture.texture_grid[NO] = NULL;
	cub->texture.texture_grid[SO] = NULL;
	cub->texture.texture_grid[WE] = NULL;
	cub->texture.texture_grid[EA] = NULL;

	// Load all four textures
	if (load_single_texture(cub, cub->texture.no_path, NO) ||
		load_single_texture(cub, cub->texture.so_path, SO) ||
		load_single_texture(cub, cub->texture.we_path, WE) ||
		load_single_texture(cub, cub->texture.ea_path, EA))
	{
		printf("Error: Failed to load one or more textures\n");
		return (1);
	}

	printf("All textures loaded successfully! Texture size: %d\n", cub->texture.size);
	return (0);
}



