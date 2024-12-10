int dice_value;
int cur_pos;

/**
 *  Draw board
 */
void draw_board (SDL_Renderer *renderer, int screen_x, int screen_y)
{
    IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs

    // Init all ladders (SDL_Surface)
    SDL_Surface *ladder = IMG_Load("grids/images/ladder.png");   // Load your PNG image
    SDL_Surface *ladder2 = IMG_Load("grids/images/ladder2.png"); // Load your PNG image
    SDL_Surface *ladder3 = IMG_Load("grids/images/ladder3.png"); // Load your PNG image

    SDL_Surface *snake = IMG_Load("grids/images/snake1.png");  // Load your PNG image
    SDL_Surface *snake2 = IMG_Load("grids/images/snake4.png"); // Load your PNG image
    SDL_Surface *snake3 = IMG_Load("grids/images/snake8.png"); // Load your PNG image

    SDL_Surface *character = IMG_Load("grids/images/character.png"); // Load your PNG image

    if (ladder == NULL || ladder2 == NULL || ladder3 == NULL)
    {
        printf("Failed to load ladder image: %s\n", IMG_GetError());
        return;
    }

    if (snake == NULL || snake2 == NULL || snake3 == NULL)
    {
        printf("Failed to load snake image: %s\n", IMG_GetError());
        return;
    }

    if (character == NULL)
    {
        printf("Failed to load character image: %s\n", IMG_GetError());
        return;
    }

    // Init all ladders (SDL_Texture)
    SDL_Texture *ladder_texture = SDL_CreateTextureFromSurface(renderer, ladder);
    SDL_Texture *ladder_texture2 = SDL_CreateTextureFromSurface(renderer, ladder2);
    SDL_Texture *ladder_texture3 = SDL_CreateTextureFromSurface(renderer, ladder3);

    // Init all snakes (SDL_Texture)
    SDL_Texture *snake_texture = SDL_CreateTextureFromSurface(renderer, snake);
    SDL_Texture *snake_texture2 = SDL_CreateTextureFromSurface(renderer, snake2);
    SDL_Texture *snake_texture3 = SDL_CreateTextureFromSurface(renderer, snake3);

    // Init character (SDL_Texture)
    SDL_Texture *character_texture = SDL_CreateTextureFromSurface(renderer, character);

    // Free all ladder Surface
    SDL_FreeSurface(ladder); // Free the surface after creating texture
    SDL_FreeSurface(ladder2);
    SDL_FreeSurface(ladder3);

    // Free all the snakes
    SDL_FreeSurface(snake);
    SDL_FreeSurface(snake2);
    SDL_FreeSurface(snake3);

    // Free character
    SDL_FreeSurface(character);

    if (ladder_texture == NULL || ladder_texture2 == NULL || ladder_texture3 == NULL) // failure check
    {
        printf("Failed to create ladder texture: %s\n", SDL_GetError());
        return;
    }

    if (snake_texture == NULL || snake_texture2 == NULL || snake_texture3 == NULL) // failure check
    {
        printf("Failed to create snake texture: %s\n", SDL_GetError());
        return;
    }
    if (character_texture == NULL)
    { // failure check
        printf("Failed to create character texture: %s\n", SDL_GetError());
    }

    // place ladder
    draw_img(renderer, ladder_texture, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 3, 1, 5, 3, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, ladder_texture2, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 18, 2, 20, 4, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture3, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 10, 1, 12, 3, screen_x, screen_y, 1, 1, 0);

    // place snakes
    draw_img(renderer, snake_texture, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 13, 0, 15, 2, screen_x, screen_y, 1, 1, 270);
    draw_img(renderer, snake_texture2, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 18, -1, 23, 2, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture3, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 1, -1, 6, 2, screen_x, screen_y, 1, 1, 90);

    int char_start_x = 23;
    int char_start_y = -1;
    int char_end_x = 25;
    int char_end_y = 0;

    draw_img(renderer, character_texture, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, char_start_x, char_start_y, char_end_x, char_end_y, screen_x, screen_y, 1, 1, 0);

    SDL_DestroyTexture(ladder_texture);
    SDL_DestroyTexture(ladder_texture2);
    SDL_DestroyTexture(ladder_texture3);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snake_texture2);
    SDL_DestroyTexture(snake_texture3);
    SDL_DestroyTexture(character_texture);
}

void roll_die() {
    dice_value = rand() % 6;
}


void move_player(int cur_pos)
{
    if (snake_or_ladder(cur_pos))
    {
        snake_ladder_pos(cur_pos);
    }
    else
    {
        cur_pos += dice_value;
    }
}

void end_game() {
    printf("end game");
    exit();
}





