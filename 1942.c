
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

struct Player {
    int x;
    int y;
};

Player player;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_GetTicks();

    int width = 800;
    int height = 600;

    if (!SDL_CreateWindowAndRenderer("Hello World", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Surface *spriteSheetSurface = IMG_Load("images/JAP_Ki45.png");
    if (!spriteSheetSurface) {
        SDL_Log("Failed to load sprite sheet: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
    SDL_DestroySurface(spriteSheetSurface);

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if( (event->type == SDL_EVENT_KEY_DOWN && event->key.scancode == SDL_SCANCODE_ESCAPE) ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    else if(event->type == SDL_EVENT_KEY_DOWN) {
        SDL_Log("keypressed %i", event->key.scancode);
    }
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate)
{
    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 64, 64, 128, 255);
    SDL_RenderClear(renderer);

    SDL_FRect src = {0, 0, 100, 100};
    SDL_FRect dst = {player.x, player.y, 100, 100};
    SDL_RenderTexture(renderer, texture, &src, &dst);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}
