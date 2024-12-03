#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

char *dice_paths[] = {"grids/dice-imgs/one.png", "grids/dice-imgs/two.png", "grids/dice-imgs/three.png", "grids/dice-imgs/four.png", "grids/dice-imgs/five.png", "grids/dice-imgs/six.png"};

void draw_dice(SDL_Renderer *renderer, SDL_Texture *dice_texture)
{
    if (dice_texture == NULL)
    {
        return; // Do nothing if there is no dice texture
    }

    // Create the rectangle for the dice image
    SDL_Rect dice_rect = {25, 25, 175, 175};
    SDL_RenderCopy(renderer, dice_texture, NULL, &dice_rect);
}

// void draw_dice(SDL_Renderer *renderer, int *did_roll)
// {
//     if (!*did_roll) {
//         return; // nothing if dice not rolled
//     }

//     // Create the rectangle for the dice image
//     SDL_Rect dice_rect = {25, 25, 175, 175};
//     // SDL_SetRenderDrawColor(renderer, 154, 248, 0, 1); // Set color to not pink
//     // SDL_RenderFillRect(renderer, &dice_rect); // Fill the rectangle
//     IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs

//     int dice_value = rand() % 6;
//     char *dice_choice = dice_paths[dice_value];

//     // init dice
//     SDL_Surface *dice = IMG_Load(dice_choice); // Load your PNG image

//     // failure check
//     if (dice == NULL)
//     {
//         printf("Failed to load dice: %s\n", IMG_GetError());
//         return;
//     }

//     // Init dice
//     SDL_Texture *dice_texture = SDL_CreateTextureFromSurface(renderer, dice);

//     SDL_FreeSurface(dice); // Free the surface after creating texture

//     if (dice_texture == NULL) // failure check
//     {
//         printf("Failed to create dice texture: %s\n", SDL_GetError());
//         return;
//     }

//     SDL_RenderCopy(renderer, dice_texture, NULL, &dice_rect);

//     SDL_DestroyTexture(dice_texture);
//     *did_roll = 0; // reset to stop rolling
// }
