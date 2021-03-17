// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "model.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MONKEY "monkey.png"
#define WATER "water.png"
#define COCO "coconutTree.png"
#define SAND "sand.png"
#define BACKGROUND "background.png"
#define TABLE "table.png"

/* **************************************************************** */

struct Env_t {
  SDL_Texture* monkey;
  SDL_Texture* sand;
  SDL_Texture* water;
  SDL_Texture* coco;
  SDL_Texture* background;
  SDL_Texture* table;
};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));

  /* init background texture from PNG image */
  env->monkey = IMG_LoadTexture(ren, MONKEY);
  if (!env->monkey) ERROR("IMG_LoadTexture: %s\n", MONKEY);

  /* init background texture from PNG image */
  env->sand = IMG_LoadTexture(ren, SAND);
  if (!env->sand) ERROR("IMG_LoadTexture: %s\n", SAND);

  /* init background texture from PNG image */
  env->coco = IMG_LoadTexture(ren, COCO);
  if (!env->coco) ERROR("IMG_LoadTexture: %s\n", COCO);

  /* init background texture from PNG image */
  env->water = IMG_LoadTexture(ren, WATER);
  if (!env->water) ERROR("IMG_LoadTexture: %s\n", WATER);

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if (!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init background texture from PNG image */
  env->table = IMG_LoadTexture(ren, TABLE);
  if (!env->table) ERROR("IMG_LoadTexture: %s\n", TABLE);

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { 
  SDL_Rect rect_monkey;
  SDL_Rect rect_sand;
  SDL_Rect rect_water;
  SDL_Rect rect_coco;
  SDL_Rect rect_table;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  /* render table texture */
  SDL_QueryTexture(env->table, NULL, NULL, &rect_table.w, &rect_table.h);
  rect_table.x = w / 2 - rect_table.w / 2;
  rect_table.y = h / 2 - rect_table.h / 2;
  SDL_RenderCopy(ren, env->table, NULL, &rect_table);

  /* render monkey texture */
  SDL_QueryTexture(env->monkey, NULL, NULL, &rect_monkey.w, &rect_monkey.h);
  rect_monkey.x = 100;
  rect_monkey.y = 300;
  SDL_RenderCopy(ren, env->monkey, NULL, &rect_monkey);

  /* render sand texture */
  SDL_QueryTexture(env->sand, NULL, NULL, &rect_sand.w, &rect_sand.h);
  rect_sand.x = 10;
  rect_sand.y = 10;
  SDL_RenderCopy(ren, env->sand, NULL, &rect_sand);

  /* render coconut texture */
  SDL_QueryTexture(env->coco, NULL, NULL, &rect_coco.w, &rect_coco.h);
  rect_coco.x = 120;
  rect_coco.y = 120;
  SDL_RenderCopy(ren, env->coco, NULL, &rect_coco);

  /* render water texture */
  SDL_QueryTexture(env->water, NULL, NULL, &rect_water.w, &rect_water.h);
  rect_water.x = 300;
  rect_water.y = 300;
  SDL_RenderCopy(ren, env->water, NULL, &rect_water);
}

/* **************************************************************** */

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e) {
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  SDL_Rect rect_monkey;

  SDL_Point mouse;
  SDL_GetMouseState(&mouse.x, &mouse.y);

  /* generic events */
  if (e->type == SDL_QUIT) {
    return true;
  }
  
  else 
  {
    switch(e->type)
    {
      //case SDL_MOUSEMOTION:
      //  printf("%d / %d\n", e->motion.x, e->motion.y);
      //  break;

      case SDL_MOUSEBUTTONDOWN:
        printf("Click in %d / %d\n", e->motion.x, e->motion.y);

        SDL_QueryTexture(env->monkey, NULL, NULL, &rect_monkey.w, &rect_monkey.h);
        rect_monkey.x = e->motion.x;
        rect_monkey.y = e->motion.y;
        SDL_RenderCopy(ren, env->monkey, NULL, &rect_monkey);
        

        break;

      
      default:
        break;
    }
  
    

  
 }

  return false; /* don't quit */
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */

  if (win == NULL || ren == NULL || env == NULL)
  {
    exit(0);
  }

    SDL_DestroyTexture(env->monkey);
    SDL_DestroyTexture(env->sand);
    SDL_DestroyTexture(env->water);
    SDL_DestroyTexture(env->coco);
    SDL_DestroyTexture(env->background);
    SDL_DestroyTexture(env->table);

    free(env);
}

/* **************************************************************** */
