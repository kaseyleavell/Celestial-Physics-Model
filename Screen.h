#pragma once
#include<iostream>
#include "SDL.h"
#include "Mass.h"
#define WIND_WIDTH 640
#define WIND_HEIGHT 480
class Screen
{
public:
    SDL_Window* window;
    SDL_Surface* screenSurface = NULL;
    SDL_Renderer* renderer = NULL;
    int screenEdgeX, screenEdgeY, screenSizeX, screenSizeY;

	int Initialize() {

        SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

        // Create an application window with the following settings:
        window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            WIND_WIDTH,                               // width, in pixels
            WIND_HEIGHT,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
        );
        renderer = SDL_CreateRenderer(window, -1, 0);
        // Check that the window was successfully created
        if (window == NULL) {
            // In the case that the window could not be made...
            printf("Could not create window: %s\n", SDL_GetError());
            return 1;
        }

        screenSurface = SDL_GetWindowSurface(window);

        if (!screenSurface) {
            fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        return 0;
	}
    void screenUpdate(Mass* head) {
        //function will be called by an external function to update the screen.
        //Clears screen, prints planets, then scales the screen window.
        ClearScreen();
        PrintPlanets(head);
        updateScreenSize();     //function has yet to be implimented
        return;
    }
    void PrintPlanets(Mass* head) {
        /*
        Function will need to change slightly so that it calls printSingleBody()
        */
        ClearScreen();
        //iterate through all of the planets and print them to the window
        Mass* runner = head;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);       //setting draw color
        while (runner != NULL) {
            //print to the pixel equivalent of the x and y
            //write the pixel
            if (runner->GetX() < WIND_WIDTH && runner->GetY() < WIND_HEIGHT) {
                //check to make sure the printing will occur in the window
                printSingleBody(runner->GetX(), runner->GetY(),runner->GetAsc());
            }
            runner = runner->nextNode;
        }

        //render the screen
        SDL_RenderPresent(renderer);
    }
    void ClearScreen() {
        //set the color to clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        int i = 0;
        int j = 0;
        for (i = 0; i < WIND_WIDTH; i++) {
            for (j = 0; j < WIND_HEIGHT; j++) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
        //render the screen
        SDL_RenderPresent(renderer);
    }
    void printSingleBody(int x, int y, char ascii) {
        //function will print a single body to the screen object using SDL_RenderDrawPOint()
        //for now function will only be printing a 3x3 pixelblock
        int i = 0;
        int j = 0;
        //what if the planet is at 0,0 will this funciton break?
        //Increment through the rows
        for (j = y - 1; j <= y + 1; j++) {
            //increment through the columns and print the specific pixel
            for (i = x - 1; i <= x + 1; i++) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
        return;
    }
    void updateScreenSize() {
        //checks the sliders that are on the viewre window and changes the screen size according to slider orientation
        
        return;
    }
};

