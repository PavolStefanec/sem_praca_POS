#pragma once
#ifndef UNTITLED_GRAPHICSSYSTEM_H
#define UNTITLED_GRAPHICSSYSTEM_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <stdio.h>
#include "../consts.h"

class GraphicsSystem {
private:
    SDL_Window* win = nullptr;
    SDL_Renderer* rend = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture* tex = nullptr;
    // struct to hold the position and size of the sprite
    SDL_Rect dest;

public:
    GraphicsSystem();
    ~GraphicsSystem();
    void inicialization();
    void createsWindow();
    void setUpGraphicsHardware();
    void loadImage();
    void clearWindow();
    void drawImage();
};
#endif //UNTITLED_GRAPHICSSYSTEM_H