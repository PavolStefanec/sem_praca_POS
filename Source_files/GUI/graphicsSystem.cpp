#include "../../Header_files/GUI/graphicsSystem.h"

GraphicsSystem::GraphicsSystem(int pNumberOfPlayers, char* imageBoard, char* imagePieces[]) {
    numberOfPlayers = pNumberOfPlayers;
    initialization();
    createsWindow();
    setUpGraphicsHardware();
    loadImageBoard(imageBoard);
    loadImagePieces(imagePieces);
    clearWindow();
}

GraphicsSystem::~GraphicsSystem() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        //vycisti panacikov
        for (int i = 0; i < numberOfPlayers; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                if (pieces[i][j]) {
                    SDL_DestroyTexture(pieces[i][j]);
                }
            }
        }
        //vycisti hraciu dosku
        if (board) {
            SDL_DestroyTexture(board);
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }

        if ( win) {
            SDL_DestroyWindow(win);
        }
        //unicializacia
        SDL_Quit();
    }

}


void GraphicsSystem::initialization() {
    //inicializacia
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf(SDL_GetError());
        work = false;
    }
}


void GraphicsSystem::createsWindow() {
    if (work) {
        win = SDL_CreateWindow("Clovece, nehnevaj sa",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WIDTH, HEIGHT, 0);
        if (!win) {
            printf(SDL_GetError());
            work = false;
        }
    }
}

void GraphicsSystem::setUpGraphicsHardware() {
    if (work) {
        Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        renderer = SDL_CreateRenderer(win, -1, render_flags);
        if (!renderer) {
            printf(SDL_GetError());
            work = false;
        }
    }
}

void GraphicsSystem::loadImageBoard(char* path)
{
    if (work) {
        board = IMG_LoadTexture(renderer, path);
        if (!board) {
            printf(SDL_GetError());
            work = false;
        }
        int w, h;
        //SDL_QueryTexture(board, NULL, NULL,&w, &h);
        textureBoard.w = WIDTH;
        textureBoard.h = HEIGHT;
        textureBoard.x = 0;
        textureBoard.y = 0;
    }
}

void GraphicsSystem::loadImagePieces(char* paths[])
{
    if (work) {
        for (int i = 0; i < numberOfPlayers; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                pieces[i][j] = IMG_LoadTexture(renderer, paths[i]);
                if (!pieces[i][j]) {
                    printf(SDL_GetError());
                    work = false;
                }
                //int w,h;
                //SDL_QueryTexture(board, NULL, NULL,&w, &h);
                texturePieces[i][j].w = PIECE_WIDTH;
                texturePieces[i][j].h = PIECE_HEIGHT;
                texturePieces[i][j].x = 0;
                texturePieces[i][j].y = 0;
            }
        }
    }
}

void GraphicsSystem::clearWindow() {
    if (work) {
        SDL_RenderClear(renderer);
    }
}

void GraphicsSystem::drawImages() {
    if (work) {
        SDL_RenderCopy(renderer, board, NULL, &textureBoard);
        for (int i = 0; i < numberOfPlayers; i++) {
            for (int j = 0; j < NUMBER_OF_PIECES; j++) {
                SDL_RenderCopy(renderer, pieces[i][j], NULL, &texturePieces[i][j]);
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void GraphicsSystem::setTexturePiece(int idPlayer, int piece, int x, int y) {
    texturePieces[idPlayer - 1][piece].x = x;
    texturePieces[idPlayer - 1][piece].y = y;
}

void GraphicsSystem::listenEvent(int& position) {
    // event handling
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                (&position)[0] = x;
                (&position)[1] = y;
                return;
            } else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RSHIFT) {
                (&position)[0] = -1;
                (&position)[1] = -1;
                return;
            }
        }
    }
}
