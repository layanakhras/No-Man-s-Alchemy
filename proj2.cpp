/*****************************************
** File: proj2.cpp
** Project: CMSC 202 Project 2, Spring 2021
** Author: Layan Akhras
** Date: 3/11/21
** Section: 50/51
** E-mail: lakhras1@umbc.edu
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
