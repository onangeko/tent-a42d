// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "model.h"
#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MONKEY "monkey.png"
#define WATER "water.png"
#define COCO "coconutTree.png"
#define SAND "sand.png"

/* **************************************************************** */

struct Env_t {
  SDL_Texture* monkey;
  SDL_Texture* sand;
  SDL_Texture* water;
  SDL_Texture* coco;
};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));

  /* init background texture from PNG image */
  env->monkey = IMG_LoadTexture(ren, MONKEY)
  if (!env->monkey) ERROR("IMG_LoadTexture: %s\n", MONKEY);

  /* init background texture from PNG image */
  env->sand = IMG_LoadTexture(ren, SAND)
  if (!env->sand) ERROR("IMG_LoadTexture: %s\n", SAND);

  /* init background texture from PNG image */
  env->coco = IMG_LoadTexture(ren, COCO)
  if (!env->coco) ERROR("IMG_LoadTexture: %s\n", COCO);

  /* init background texture from PNG image */
  env->water = IMG_LoadTexture(ren, WATER)
  if (!env->water) ERROR("IMG_LoadTexture: %s\n", WATER);

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { 

}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */

  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */

  free(env);
}

/* **************************************************************** */
