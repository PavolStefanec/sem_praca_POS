#pragma once
#ifndef UNTITLED_GRAPHICSSYSTEM_H
#define UNTITLED_GRAPHICSSYSTEM_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <stdio.h>
#include "../consts.h"
#define WIDTH 800
#define HEIGHT 800
#define PIECE_WIDTH 40
#define PIECE_HEIGHT 40

class GraphicsSystem {
private:
    SDL_Window* win = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* board = nullptr;
    SDL_Texture* pieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_PIECES];
    SDL_Rect textureBoard;
    SDL_Rect texturePieces[NUMBER_OF_MAX_PLAYERS][NUMBER_OF_PIECES];

    bool work = true;
    int numberOfPlayers;

public:
    GraphicsSystem(int pNumberOfPlayers, char* imageBoard, char* imagePieces[]);
    ~GraphicsSystem();
    void initialization();
    void createsWindow();
    void setUpGraphicsHardware();
    void loadImageBoard(char* path);
    void loadImagePieces(char* paths[]);
    void clearWindow();
    void drawImages();
    void setTexturePiece(int idPlayer, int piece, int x, int y);
    void listenEvent(int& position);
};
#endif //UNTITLED_GRAPHICSSYSTEM_H