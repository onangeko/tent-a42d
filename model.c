// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "model.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"
#include <SDL2/SDL.h>
#include <SDL_image.h> // required to load transparent texture from PNG
#include <SDL_ttf.h> // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MONKEY "monkey.png"
#define WATER "water.png"
#define COCO "coconutTree.png"
#define SAND "sand.png"
#define BACKGROUND "background.png"
#define TABLE "table.png"
#define OFFSETTEXTURE 45
#define TEXTURESIZE 40

#define FONT "Tiki-Tako.ttf"
#define FONTSIZE 36

/* **************************************************************** */

typedef struct SDLSquare {
    SDL_Texture* texture;
    SDL_Rect hitBox;
} SDLSquare;

struct Env_t {
    SDLSquare** SDLboard;
    game board;
    SDL_Texture* monkey;
    SDL_Texture* sand;
    SDL_Texture* water;
    SDL_Texture* coco;
    SDL_Texture* background;
    SDL_Texture* table;
    SDL_Texture * errorText;
    SDL_Texture** nbTentsRow;
    SDL_Texture** nbTentsCol;
};

/* **************************************************************** */

Env* init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{
    Env* env = malloc(sizeof(struct Env_t));

    game board = NULL;
    if (argc < 2)
        board = game_default();
    else
        board = game_load(argv[1]);
    env->board = board;

    env->nbTentsRow = malloc(game_nb_rows(board) * sizeof(SDL_Texture*));
    env->nbTentsCol = malloc(game_nb_cols(board) * sizeof(SDL_Texture*));
    env->SDLboard = malloc(game_nb_cols(board) * sizeof(SDLSquare*));

    SDL_Color color = { 0, 0, 255, 255 }; /* blue color in RGBA */
    TTF_Font* font = TTF_OpenFont(FONT, FONTSIZE);
    if (!font)
        ERROR("TTF_OpenFont: %s\n", FONT);

    for (int i = 0; i < game_nb_cols(board); i++) {
        env->SDLboard[i] = malloc(game_nb_rows(board) * sizeof(SDLSquare));

        char buffer[2];
        sprintf(buffer, "%d", game_get_expected_nb_tents_col(env->board, i));

        SDL_Surface* surf = TTF_RenderText_Blended(font, buffer, color); // blended rendering for ultra nice text
        env->nbTentsCol[i] = SDL_CreateTextureFromSurface(ren, surf);
        SDL_FreeSurface(surf);

        sprintf(buffer, "%d", game_get_expected_nb_tents_row(env->board, i));

        surf = TTF_RenderText_Blended(font, buffer, color); // blended rendering for ultra nice text
        env->nbTentsRow[i] = SDL_CreateTextureFromSurface(ren, surf);
        SDL_FreeSurface(surf);
        for (int j = 0; j < game_nb_rows(board); j++) {

            if (game_get_square(board, i, j) == TREE) {
                env->SDLboard[i][j].texture = IMG_LoadTexture(ren, COCO);
                if (!env->SDLboard[i][j].texture)
                    ERROR("IMG_LoadTexture: %s\n", COCO);
            } else {
                env->SDLboard[i][j].texture = IMG_LoadTexture(ren, WATER);
                if (!env->SDLboard[i][j].texture)
                    ERROR("IMG_LoadTexture: %s\n", WATER);
            }
        }
    }

    SDL_Color color2 = {255,0,0, 255}; /* blue color in RGBA */
    SDL_Surface* surf2 = TTF_RenderText_Blended(font,"Perdu !",color2);  // blended rendering for ultra nice text
    env->errorText= SDL_CreateTextureFromSurface(ren, surf2);
    env->errorText = IMG_LoadTexture(ren, COCO);
    if (!env->errorText) ERROR("IMG_LoadTexture: %s\n", COCO);
    SDL_FreeSurface(surf2);
    TTF_CloseFont(font);

    

    /* init background texture from PNG image */
    env->monkey = IMG_LoadTexture(ren, MONKEY);
    if (!env->monkey)
        ERROR("IMG_LoadTexture: %s\n", MONKEY);

    /* init background texture from PNG image */
    env->sand = IMG_LoadTexture(ren, SAND);
    if (!env->sand)
        ERROR("IMG_LoadTexture: %s\n", SAND);

    /* init background texture from PNG image */
    env->coco = IMG_LoadTexture(ren, COCO);
    if (!env->coco)
        ERROR("IMG_LoadTexture: %s\n", COCO);

    /* init background texture from PNG image */
    env->water = IMG_LoadTexture(ren, WATER);
    if (!env->water)
        ERROR("IMG_LoadTexture: %s\n", WATER);

    /* init background texture from PNG image */
    env->background = IMG_LoadTexture(ren, BACKGROUND);
    if (!env->background)
        ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

    /* init background texture from PNG image */
    env->table = IMG_LoadTexture(ren, TABLE);
    if (!env->table)
        ERROR("IMG_LoadTexture: %s\n", TABLE);

    return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env* env)
{
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
    for (int i = 0; i < game_nb_cols(env->board); i++) {
        for (int j = 0; j < game_nb_rows(env->board); j++) {
            SDL_Rect square;
            square.h = TEXTURESIZE;
            square.w = TEXTURESIZE;
            square.x = rect.x;
            square.y = rect.y;
            env->SDLboard[i][j].hitBox = square;
            SDL_QueryTexture(env->SDLboard[i][j].texture, NULL, NULL, &rect.w, &rect.h);
            SDL_RenderCopy(ren, env->SDLboard[i][j].texture, NULL, &rect);
            rect.x += OFFSETTEXTURE;
            if (j == game_nb_rows(env->board)-1) {
                rect.x += OFFSETTEXTURE;
                SDL_QueryTexture(env->nbTentsRow[i], NULL, NULL, &rect.w, &rect.h);
                SDL_RenderCopy(ren, env->nbTentsRow[i], NULL, &rect);
            }
        }
        rect.y += OFFSETTEXTURE;
        rect.x = xTable;
    }
    for (int i = 0; i < game_nb_cols(env->board); i++) {
        SDL_QueryTexture(env->nbTentsCol[i], NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(ren, env->nbTentsCol[i], NULL, &rect);
        rect.x += OFFSETTEXTURE;
    }
}

/* **************************************************************** */

void refreshBoard(Env* env)
{
    for (int i = 0; i < game_nb_rows(env->board); i++) {
        for (int j = 0; j < game_nb_cols(env->board); j++) {
            switch (game_get_square(env->board, i, j)) {
            case TENT:
                if (env->SDLboard[i][j].texture != env->monkey) {
                    env->SDLboard[i][j].texture = env->monkey;
                }
                break;
            case GRASS:
                if (env->SDLboard[i][j].texture != env->sand) {
                    env->SDLboard[i][j].texture = env->sand;
                }
                break;
            case EMPTY:
                if (env->SDLboard[i][j].texture != env->water) {
                    env->SDLboard[i][j].texture = env->water;
                }
                break;
            default:
                break;
            }
        }
    }
}

bool process(SDL_Window* win, SDL_Renderer* ren, Env* env, SDL_Event* e)
{
    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    SDL_Rect rect_monkey;

    /* generic events */
    if (e->type == SDL_QUIT) {
        return true;
    }

    if (e->type == SDL_MOUSEBUTTONDOWN) {
        //IF LEFT CLICK
        if (e->button.button == SDL_BUTTON_LEFT) {
            for (int i = 0; i < game_nb_rows(env->board); i++) {
                for (int j = 0; j < game_nb_cols(env->board); j++) {
                    //If the mouse is inside the square at position i,j▬
                    if (e->motion.x >= env->SDLboard[i][j].hitBox.x
                        && e->motion.x <= env->SDLboard[i][j].hitBox.x + env->SDLboard[i][j].hitBox.w
                        && e->motion.y >= env->SDLboard[i][j].hitBox.y
                        && e->motion.y <= env->SDLboard[i][j].hitBox.y + env->SDLboard[i][j].hitBox.h) {
                        //If there is not already a Tent on (i,j)
                        if (game_get_square(env->board, i, j) != TENT) {
                            switch (game_check_move(env->board, i, j, TENT)) {
                            case LOSING:
                                //TODO AFFICHER TEXT LOSING
                            case REGULAR:
                                game_play_move(env->board, i, j, TENT);
                                break;
                            default:
                                break;
                            }
                        } else {
                            game_play_move(env->board, i, j, EMPTY);
                        }
                    }
                }
            }
        }
        //IF RIGHT CLICK
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        for (int i = 0; i < game_nb_rows(env->board); i++) {
            for (int j = 0; j < game_nb_cols(env->board); j++) {
                //If the mouse is inside the square at position i,j
                if (e->motion.x >= env->SDLboard[i][j].hitBox.x
                    && e->motion.x <= env->SDLboard[i][j].hitBox.x + env->SDLboard[i][j].hitBox.w
                    && e->motion.y >= env->SDLboard[i][j].hitBox.y
                    && e->motion.y <= env->SDLboard[i][j].hitBox.y + env->SDLboard[i][j].hitBox.h) {
                    //If there is not already a Grass on (i,j)
                    if (game_get_square(env->board, i, j) != GRASS) {
                        switch (game_check_move(env->board, i, j, GRASS)) {
                        case LOSING:
                            //TODO AFFICHER TEXT LOSING
                        case REGULAR:
                            game_play_move(env->board, i, j, GRASS);
                            break;
                        default:
                            break;
                        }
                    } else {
                        game_play_move(env->board, i, j, EMPTY);
                    }
                }
            }
        }
    } else if (e->type == SDL_KEYDOWN) {
        SDL_Keycode key = e->key.keysym.sym;
        if (key == SDLK_z) {
            game_undo(env->board);
        } else if (key == SDLK_y) {
            game_redo(env->board);
        } else if (key == SDLK_s) {
            char text[150];
            time_t now = time(NULL);
            struct tm* t = localtime(&now);
            sprintf(text, "%02d-%02d-%04d-%02d-%02d.tnt", t->tm_mday, t->tm_mon + 1,
                t->tm_year + 1900, t->tm_hour, t->tm_min);
            printf(text);
            game_save(env->board, text);
        } else if (key == SDLK_q || key == SDLK_ESCAPE) {
            return true;
        } else if (key == SDLK_r) {
            game_restart(env->board);
        } else if (key == SDLK_t) {
            game_solve(env->board);
        }
    }
    refreshBoard(env);
    return false; /* don't quit */
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env* env)
{
    /* PUT YOUR CODE HERE TO CLEAN MEMORY */

    if (win == NULL || ren == NULL || env == NULL) {
        exit(0);
    }

    for (int i = 0; i < game_nb_cols(env->board); i++) {
        for (int j = 0; j < game_nb_rows(env->board); j++) {
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
