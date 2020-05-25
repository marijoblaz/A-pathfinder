#include "Game.h"
#include <windows.h>
#define _WIN32_WINNT 0x0500


/*
 * File:   main.cpp
 * Author: Marijo Blazevic https://github.com/marijoblaz
 * Class: SPA
 * Assigment: RVS20-SPA-DZ-03
 * See "RVS20-SPA-DZ-03.pdf" for game decisions.
 *
 *
 *
 */

int main()
{
    /*    Hide console - COMMENT NEXT 2 LINES TO HIDE CONSOLE */
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    Game game;

    game.run();

    return 0;
}