/*****************************************
** File: proj2.cpp
** Project: No Man's Alchemy
** Author: Layan Akhras
**
** This file contains the main driver program for
** project 2. It runs the entire game in the main
** function below.
******************************************/

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Game newGame;
  newGame.StartGame();
  return 0;
}
