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
  SDL_Rect rect;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  /* render table texture */
  SDL_QueryTexture(env->table, NULL, NULL, &rect.w, &rect.h);
  rect.x = w / 2 - rect.w / 2;
  rect.y = h / 2 - rect.h / 2;
  SDL_RenderCopy(ren, env->table, NULL, &rect);

  /* render monkey texture */
  SDL_QueryTexture(env->monkey, NULL, NULL, &rect.w, &rect.h);
  rect.x = 100;
  rect.y = 100;
  SDL_RenderCopy(ren, env->monkey, NULL, &rect);

  /* render sand texture */
  SDL_QueryTexture(env->sand, NULL, NULL, &rect.w, &rect.h);
  rect.x = 10;
  rect.y = 10;
  SDL_RenderCopy(ren, env->sand, NULL, &rect);

  /* render coconut texture */
  SDL_QueryTexture(env->coco, NULL, NULL, &rect.w, &rect.h);
  rect.x = 120;
  rect.y = 120;
  SDL_RenderCopy(ren, env->coco, NULL, &rect);

  /* render water texture */
  SDL_QueryTexture(env->water, NULL, NULL, &rect.w, &rect.h);
  rect.x = 300;
  rect.y = 300;
  SDL_RenderCopy(ren, env->water, NULL, &rect);
}

/* **************************************************************** */

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e) {
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* generic events */
  if (e->type == SDL_QUIT) {
    return true;
  }
  /* Android events */
#ifdef __ANDROID__
  else if (e->type == SDL_FINGERDOWN) {
    env->mario_x = e->tfinger.x * w; /* tfinger.x, normalized in [0..1] */
    env->mario_y = e->tfinger.y * h; /* tfinger.y, normalized in [0..1] */
  }
  /* other events */
#else
  
  
else if (e->type == SDL_MOUSEBUTTONDOWN)
  {

  SDL_Point mouse;
  SDL_GetMouseState(&mouse.x, &mouse.y);
  
  SDL_Rect monkey;
  monkey.x = 200;
  monkey.y = 200;
  SDL_QueryTexture(env->monkey, NULL, NULL, &monkey.w, &monkey.h);
  SDL_RenderCopy(ren, env->monkey, NULL, &monkey);

  
}

#endif

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
