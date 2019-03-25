#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>


void SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius);
void SDL_RenderDrawCircunference(SDL_Renderer *renderer,int center_x, int center_y,  int radius);
int SDL_CollisionCheck(SDL_Rect *obj1, SDL_Rect *obj2);
void SDL_DrawCircunference(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);

struct Vect2 {
    int x;
    int y;
};

int main(int argc, char *argv[])
{
    // Creating Initializing sdl video module and
    // initializing video variables.

    SDL_InitSubSystem(SDL_INIT_VIDEO);


    SDL_Window *window = SDL_CreateWindow(
            "Pong",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        printf("cannot get a window, error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    if (renderer == NULL)
    {
        printf("cannot get accelerated renderer.");
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == NULL)
        {
            printf("cannot get renderer, aborting.");
            return 1;
        }
    }

    SDL_Event event;

    // Defining game variables
    unsigned int P1_score = 0;
    unsigned int P2_score = 0;
    int pause = 1;

    // Defining Player 1 vars
    SDL_Rect P1;
    P1.x = 32;
    P1.y = 160;
    P1.w = 16;
    P1.h = 100;
    char P1_strscore[3] =  "00";
    // Initializing TTF to render the score labels
    TTF_Init();
    TTF_Font *DOSfont = TTF_OpenFont("ModernDOS8x16.ttf", 64);
    SDL_Color white = {255, 255, 255};

    // P1 score label
    SDL_Surface *S1_label_surface = TTF_RenderText_Solid(DOSfont, P1_strscore, white);
    SDL_Texture *S1_label = SDL_CreateTextureFromSurface(renderer, S1_label_surface);
    SDL_Rect S1_label_properties;
    S1_label_properties.x = 224;
    S1_label_properties.y = 32;
    S1_label_properties.w = S1_label_surface->w;
    S1_label_properties.h = S1_label_surface->h;

    // Defining Player 2 vars
    SDL_Rect P2;
    P2.x = 576;
    P2.y = 160;
    P2.w = 16;
    P2.h = 100;
    char P2_strscore[3] =  "00";

    // P2 score label
    SDL_Surface *S2_label_surface = TTF_RenderText_Solid(DOSfont, P2_strscore, white);
    SDL_Texture *S2_label = SDL_CreateTextureFromSurface(renderer, S2_label_surface);
    SDL_Rect S2_label_properties;
    S2_label_properties.x = 360;
    S2_label_properties.y = 32;
    S2_label_properties.w = S2_label_surface->w;
    S2_label_properties.h = S2_label_surface->h;

    // Creating Ball vars
    SDL_Rect ball;
    ball.w = 4; // Ball Radius, not diameter
    ball.h = ball.w;
    // Centralizing the ball
    ball.x = 320 - ball.w;
    ball.y = 240 - ball.h;
    struct Vect2 ball_speed;
    srand(time(NULL));
    ball_speed.x = rand() % 100 <= 50 ? 1 : -1;
    ball_speed.y = 0;

    // misc vars
    int quit = 0;
    int mouse_pressed = 0;

    // Main game loop
    while (!quit)
    {
        // Handling events
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouse_pressed = 1;
                        if (pause)
                        {
                            pause = 0;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouse_pressed = 0;
                    }
                case SDL_MOUSEMOTION:
                    if (mouse_pressed)
                    {
                        if (event.button.x < 320)
                        {
                            P1.y = event.button.y - P1.h / 2;
                        }
                        else
                        {
                            P2.y = event.button.y - P2.h / 2;
                        }
                    }
                    break;
            }
        }

        // Physics process
        if (!pause)
        {
            // Making ball move
            ball.x += ball_speed.x;
            ball.y += ball_speed.y;

            if (SDL_CollisionCheck(&ball, &P1))
            {
                if (ball_speed.x < 0)
                {
                    ball_speed.x = -ball_speed.x + 1;
                    ball_speed.y = ((ball.y + ball.h / 2)  - (P1.y + P1.h / 2)) / 10;
                }
            }
            else if (SDL_CollisionCheck(&ball, &P2))
            {
                if (ball_speed.x > 0)
                {
                    ball_speed.x = -ball_speed.x - 1;
                    ball_speed.y = ((ball.y + ball.h / 2)  - (P2.y + P2.h / 2)) / 10;
                }
            }

            // Making ball bounce at the top and bottom of window.
            if (ball.y <= 0 | ball.y >= 480 - ball.h)
            {
                ball_speed.y = -ball_speed.y;
            }

            // Checking if ball is out of screen, and computing the score of P2
            if (ball.x < -ball.w)
            {
                pause = 1;
                P2_score += 1;
                P2_strscore[0] = P2_score / 10 + '0';
                P2_strscore[1] = P2_score % 10 + '0';
                ball.x = 320 - ball.w;
                ball.y = 240 - ball.h;
                srand(time(NULL));
                ball_speed.x = rand() % 100 <= 50 ? 1 : -1;
                ball_speed.y = 0;
                S2_label_surface = TTF_RenderText_Solid(DOSfont, P2_strscore, white);
                S2_label = SDL_CreateTextureFromSurface(renderer, S2_label_surface);
                S2_label_properties.w = S2_label_surface->w;
            }

            // Checking if ball is out of screen, and computing the score of P1
            if (ball.x > 640)
            {
                pause = 1;
                P1_score += 1;
                P1_strscore[0] = P1_score / 10 + '0';
                P1_strscore[1] = P1_score % 10 + '0';
                ball.x = 320 - ball.w;
                ball.y = 240 - ball.h;
                srand(time(NULL));
                ball_speed.x = rand() % 100 <= 50 ? 1 : -1;
                ball_speed.y = 0;
                S1_label_surface = TTF_RenderText_Solid(DOSfont, P1_strscore, white);
                S1_label = SDL_CreateTextureFromSurface(renderer, S1_label_surface);
                S1_label_properties.w = S1_label_surface->w;
            }
        }

        // Clearing the screen to draw new frame
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Rendering Field
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 320, 0, 320, 480);

        // Rendering Ball
        SDL_RenderDrawCircle(renderer, ball.x, ball.y, ball.w);

        // Rendering Players
        SDL_SetRenderDrawColor(renderer, 75, 255, 75, 255);
        SDL_RenderFillRect(renderer, &P1);
        SDL_RenderFillRect(renderer, &P2);

        // Rendering Score Labels
        SDL_RenderCopy(renderer, S1_label, NULL, &S1_label_properties);
        SDL_RenderCopy(renderer, S2_label, NULL, &S2_label_properties);

        // Updating Screen
        SDL_RenderPresent(renderer);

        // Limitting game to aproximately 60 fps
        SDL_Delay(16);
    }

    // Discarting video variables
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}




int SDL_CollisionCheck(SDL_Rect *obj1, SDL_Rect *obj2)
{
    if (obj1->x + obj1->w < obj2->x)
    {
        return 0;
    }
    if (obj1->y + obj1->h < obj2->y)
    {
        return 0;
    }
    if (obj2->x + obj2->w < obj1->x)
    {
        return 0;
    }
    if (obj2->y + obj2->h < obj1->y)
    {
        return 0;
    }
    return 1;
}



void SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    x += radius;
    y += radius;

    for (int i = 0; i < radius; ++i)
    {
        SDL_RenderDrawCircunference(renderer, x, y, radius - i);
    }
}


void SDL_RenderDrawCircunference(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
