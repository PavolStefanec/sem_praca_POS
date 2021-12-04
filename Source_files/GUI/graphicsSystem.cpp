#include "../../Header_files/GUI/graphicsSystem.h"

GraphicsSystem::GraphicsSystem() {
    try {
        inicialization();
        createsWindow();
        setUpGraphicsHardware();
    } catch(...) {

    }
}

GraphicsSystem::~GraphicsSystem() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        if (tex != nullptr && tex) {
            SDL_DestroyTexture(tex);
        }
        if (rend != nullptr && rend) {
            //okno
            SDL_DestroyRenderer(rend);
        }
        if (win != nullptr && win) {
            //graficky hardware
            SDL_DestroyWindow(win);
        }
        //unicializacia
        IMG_Quit();
        SDL_Quit();
    }

}


void GraphicsSystem::inicialization() {
    //inicializacia
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        throw SDL_GetError();
    }
}


void GraphicsSystem::createsWindow() {
    win = SDL_CreateWindow("Clovece, nehnevaj sa",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1200, 1200, 0);
    if (!win)
    {
        throw SDL_GetError();
    }
}

void GraphicsSystem::setUpGraphicsHardware() {
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        throw SDL_GetError();
    }
}

void GraphicsSystem::loadImage()
{

    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("C:/Users/miska/Documents/Data/ProgramovacieJazyky/C/C++/PrincipyOperacnychSystemov/SemestralnaPraca2021/sem_praca_POS/Images/green.png");
    if (!surface) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        //throw printf(SDL_GetError());
    }
}

void GraphicsSystem::clearWindow() {
    SDL_RenderClear(rend);
}

void GraphicsSystem::drawImage() {
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);
}
