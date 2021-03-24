// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "model.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"

#define MONKEY "monkey.png"
#define WATER "water.png"
#define COCO "coconutTree.png"
#define SAND "sand.png"
#define BACKGROUND "background.png"
#define TABLE "table.png"
#define OFFSETTEXTURE 45

/* **************************************************************** */

typedef struct SDLSquare{
  SDL_Texture* texture;
  SDL_Rect hitBox;
}SDLSquare;

struct Env_t {
  SDLSquare** SDLboard;
  game board;
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

  game board = NULL;
  if(argc < 2)
    board = game_default();
  else
    board = game_load(argv[1]);
  env->board = board;

  env->SDLboard = malloc(game_nb_cols(board) * sizeof(SDLSquare*));
  for(int i = 0; i<game_nb_cols(board);i++){
    env->SDLboard[i] = malloc(game_nb_rows(board) * sizeof(SDLSquare));
    for(int j = 0;j<game_nb_rows(board);j++){
      if(game_get_square(board,i,j) == TREE){
        env->SDLboard[i][j].texture = IMG_LoadTexture(ren,COCO);
        if (!env->SDLboard[i][j].texture) ERROR("IMG_LoadTexture: %s\n", COCO);
      }
      else{
        env->SDLboard[i][j].texture = IMG_LoadTexture(ren,WATER);
        if (!env->SDLboard[i][j].texture) ERROR("IMG_LoadTexture: %s\n", WATER);
      }
    }

  }

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

  /* render the board */
  int xTable = rect.x;
  for(int i = 0; i<game_nb_cols(env->board);i++){
    for(int j = 0;j<game_nb_rows(env->board);j++){
      SDL_QueryTexture(env->SDLboard[i][j].texture, NULL, NULL, &rect.w, &rect.h);
      SDL_RenderCopy(ren, env->SDLboard[i][j].texture, NULL, &rect);
      rect.x += OFFSETTEXTURE;
    }
    rect.y += OFFSETTEXTURE;
    rect.x = xTable;
  }
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

  for(int i = 0; i<game_nb_cols(env->board);i++){
    for(int j = 0; j<game_nb_rows(env->board);j++){
      SDL_DestroyTexture(env->SDLboard[i][j].texture);
    }
    free(env->SDLboard[i]);
  }
  free(env->SDLboard);

  SDL_DestroyTexture(env->monkey);
  SDL_DestroyTexture(env->sand);
  SDL_DestroyTexture(env->water);
  SDL_DestroyTexture(env->coco);
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->table);

  free(env);
}

/* **************************************************************** */
