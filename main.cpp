#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <set>

#define WIDTH 1080
#define HEIGHT 720

#define SIZE 200
#define SPEED 1000
#define GRAVITY 100
#define FPS 144
#define JUMP -3000

int main(int argc, char *argv[])
{
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *wind = SDL_CreateWindow("Example SDL2!",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 0);

    if (!wind)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, render_flags);
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }

    bool running = true;
    bool can_jump = true;
    std::set<uint32_t> pressed_keys;

    float x_pos = (WIDTH - SIZE) / 2, y_pos = (HEIGHT - SIZE) / 2, x_vel = 0, y_vel = 0;
    SDL_Rect rect = {(int)x_pos, (int)y_pos, SIZE, SIZE};
    SDL_Event event;
    while (running)
    {
        /* Process events */
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                pressed_keys.insert(event.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                pressed_keys.erase(event.key.keysym.scancode);
                break;
            default:
                break;
            }
        }
        /* Clear screen */
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);
        x_vel = ((pressed_keys.find(SDL_Scancode::SDL_SCANCODE_D) != pressed_keys.end()) - (pressed_keys.find(SDL_Scancode::SDL_SCANCODE_A) != pressed_keys.end())) * SPEED;
        y_vel += GRAVITY;
        if ((pressed_keys.find(SDL_Scancode::SDL_SCANCODE_SPACE) != pressed_keys.end()) && can_jump)
        {
            can_jump = false;
            y_vel = JUMP;
        }

        x_pos += x_vel / FPS;
        y_pos += y_vel / FPS;

        if (x_pos <= 0)
        {
            x_pos = 0;
        }

        if (x_pos >= WIDTH - rect.w)
        {
            x_pos = WIDTH - rect.w;
        }

        if (y_pos <= 0)
        {
            y_pos = 0;
        }

        if (y_pos >= HEIGHT - rect.h)
        {
            y_vel = 0;
            y_pos = HEIGHT - rect.h;
            if (pressed_keys.find(SDL_Scancode::SDL_SCANCODE_SPACE) == pressed_keys.end())
            {
                can_jump = true;
            }
        }

        /* Update rectangle position */
        rect.x = (int)x_pos;
        rect.y = (int)y_pos;

        /* Draw the rectangle */
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
        SDL_RenderFillRect(rend, &rect);

        /* Draw to window and loop */
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / FPS);
    }

    /* Release resources */
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
}
