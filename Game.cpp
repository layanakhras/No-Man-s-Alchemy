/*****************************************
** File: Game.cpp
** Project: CMSC 202 Project 2, Spring 2021
** Author: Layan Akhras
** Date: 3/11/21
** Section: 50/51
** E-mail: lakhras1@umbc.edu
**
** This file contains the main driver program for 
** project 2. It stores major Game function
** definitions and runs the majority of the
** No Man's Alchemy game.
******************************************/
#include "Game.h"
#include <fstream>

  // Name: Game() Default Constructor
  // Desc - Builds a new game by:
  // 1. Loads all materials and their recipes into m_materials
  // 2. Asks user for their Ship's name (store in m_myShip as m_myName)
  // 3. Copies all materials from m_materials into the Ship's material array
  // Preconditions - None
  // Postconditions - m_materials is populated

Game::Game(){
  int counter = 0;    // integer variable to increment the while loop
  GameTitle();
  // load m_materials and m_myMaterials
  // add all the materials into the user's array
  LoadMaterials();
  while (counter < PROJ2_SIZE){
    m_myShip.AddMaterial(m_materials[counter]);
    counter++;
  }
}

  // Name: LoadMaterials
  // Desc - Loads each material into m_materials from file
  // Preconditions - Requires file with valid material data
  // Postconditions - m_material is populated with material structs
void Game::LoadMaterials(){
  string name, type, material1, material2;   // strings to store each value in the file
  int quantity = 0;                          // integer to store the quantity of each material
  int counter = 0;                           // integer to increment the while loop

  // declares new variable and opens file
  ifstream myfile (PROJ2_DATA);
  if (myfile.is_open()){
    while (counter < PROJ2_SIZE){
      // retrieves name, type, material1, and material2
      getline(myfile, name, DELIMETER);
      getline(myfile, type, DELIMETER);
      getline(myfile, material1, DELIMETER);
      getline(myfile, material2);
      // adds them to the materials array
      m_materials[counter] = Material(name, type, material1, material2, quantity);
      counter++;
    }
    cout << counter - 1 << " materials loaded." << endl;
  }else
    cout << "Unable to open file." << endl;
}
  
  // Name: StartGame()
  // Desc - Manages the game itself including win conditions continually
  //         calling the main menu
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5
void Game::StartGame(){
  string nameOfShip;         // string to store the name of the ship that the user enters
  int option;                // string to store the user's option from the menu

  cout << "What is the name of your ship?" << endl;
  getline(cin, nameOfShip);
  m_myShip.SetName(nameOfShip);
  do{
    // displays the main menu and does input validation
    option = MainMenu();
    switch (option){
    case 1:
      // display the materials and quantity
      DisplayMaterials();
      break;
    case 2:
      // randomly searches for a raw material
      SearchMaterials();
      break;
    case 3:
      // attempt to combine two materials and complete a series of checks
      CombineMaterials();
      break;
    case 4:
      // output the ship name and ship rank
      CalcScore();
      break;
    case 5:
      // exit the game
      cout << "Thanks for playing No Man's Alchemy. Goodbye!" << endl;
      break;
    }
    // runs the game as long as the user has not won, or has not quit
  }while(m_myShip.GetRank() != WINNING_RANK  and option != QUIT_OPTION);
}

  // Name: DisplayMyMaterials()
  // Desc - Displays the Ship's materials (Uses GetMaterial)
  // Preconditions - Player's Ship has materials
  // Postconditions - Displays a numbered list of materials
void Game::DisplayMaterials(){
  for (int i = 0; i < PROJ2_SIZE; i++){
    // loops through the array and outputs each material name and quantity
    cout << i + 1 << ". " << m_myShip.GetMaterial(i).m_name << " " <<
      m_myShip.GetMaterial(i).m_quantity << endl;
  }
}

  // Name: MainMenu()
  // Desc - Displays and manages menu. Also checks win condition (Ship reaches S rank).
  // Preconditions - Player has a Ship
  // Postconditions - Returns number including exit
int Game::MainMenu(){
  int menuOption;        // integer to store the user's option from the menu 
  do{
  cout << "What would you like to do?" << endl;
  cout << "1. Display your Ship's Materials" << endl;
  cout << "2. Search for Raw Materials" << endl;
  cout << "3. Attempt to Merge Materials" << endl;
  cout << "4. See Score" << endl;
  cout << "5. Quit" << endl;
  cin >> menuOption;
  // reprompts if the user doesn't enter an integer from 1 to 5
  }while(menuOption > 5 and menuOption < 1);
  return menuOption;
}

  // Name: SearchMaterials()
  // Desc - Attempts to search for raw materials (must be type "raw")
  // Preconditions - Raw materials loaded
  // Postconditions - Increases quantity in Ship's possession of materials
void Game::SearchMaterials(){
  int randomNum = 0;       // integer to store the random number
  do{
    // picks a random number
    randomNum = rand() % PROJ2_SIZE;
    // checks if the material at the random index is raw
    if (m_myShip.GetMaterial(randomNum).m_type == "raw"){
      cout << m_myShip.GetMaterial(randomNum).m_name << " found!" << endl;
    // if it is raw, it increments it
    m_myShip.IncrementQuantity(m_myShip.GetMaterial(randomNum));
  }
    // run the loop until it finds a raw material
  }while(m_myShip.GetMaterial(randomNum).m_type != "raw");
}

  // Name: CombineMaterials()
  // Desc - Attempts to combine known materials. If combined, quantity of material decreased
  // Preconditions - Ship is populated with materials
  // Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineMaterials(){
  int choice;                    // stores the integer that represents the material
                                 // the user wants to merge
  int materialIndex1;            // stores the index of the first material
  int materialIndex2;            // stores the index of the second material
  bool ownItem1 = false;         // bool to determine if we have the first material
  bool ownItem2 = false;         // bool to determine if we have the second material
  bool quantityCheck = false;    // bool to determine if we have enough of each material
  int recipeIndex;               // integer that stores the index of the recipe
  bool decrement1 = false;       // bool to determine if we can decrement the 1st material
  bool decrement2 = false;       // bool to determine if we can decrement the 2nd material

  // request the first material
  RequestMaterial(choice);
  if (choice != -1){
    // check if we have this material
    materialIndex1 = m_myShip.CheckMaterial(m_materials[choice - 1]);
    if (materialIndex1 == -1){
      cout << "You do not have this material yet." << endl;
      ownItem1 = false;
    }else
      ownItem1 = true;
  }
  // request the second material
  RequestMaterial(choice);
  if (choice != -1){
    // check if we have this material
    materialIndex2 = m_myShip.CheckMaterial(m_materials[choice - 1]);
    if (materialIndex2 == -1){
      cout << "You do not have this material yet." << endl;
      ownItem2 = false;
    }else
      ownItem2 = true;
  }
  // if we have both of these materials...
  if (ownItem1 == true and ownItem2 == true)
    // check that we have at least one of each
    quantityCheck = m_myShip.CheckQuantity(m_myShip.GetMaterial(materialIndex1),
					   m_myShip.GetMaterial(materialIndex2));
  // if we do not have enough...
  if (quantityCheck == false)
    cout << "You do not have enough " << m_myShip.GetMaterial(materialIndex1).m_name << " or "
	 << m_myShip.GetMaterial(materialIndex2).m_name << " to attempt that merge." << endl;
    // if we do have enough...
  else{
    // check if there is a recipe for the two materials
    recipeIndex = SearchRecipes(m_myShip.GetMaterial(materialIndex1).m_name,
				m_myShip.GetMaterial(materialIndex2).m_name);
  }

  // if there is no recipe for these two materials...
  if (recipeIndex == -1)
    cout << "You cannot merge these two materials." << endl;
    // if there is a recipe...
  else{
    // decrease the quantities of the two materials
    decrement1 = m_myShip.DecrementQuantity(m_myShip.GetMaterial(materialIndex1));
    decrement2 = m_myShip.DecrementQuantity(m_myShip.GetMaterial(materialIndex2));
  }
  
  // if we can decrease the quantities of the two materials...
  if (decrement1 == true and decrement2 == true){
    // then we can go ahead and merge
    m_myShip.IncrementQuantity(m_myShip.GetMaterial(recipeIndex));
    cout << m_myShip.GetMaterial(materialIndex1).m_name << " combined with "
	 << m_myShip.GetMaterial(materialIndex2).m_name << " to make " <<
      m_myShip.GetMaterial(recipeIndex).m_name << "!" << endl;
    cout << "You have built " << m_myShip.GetMaterial(recipeIndex).m_name << " for your ship!" << endl;
    // if the material we merged is unique...
    if (m_myShip.GetMaterial(recipeIndex).m_type == "unique")
      // increment the rank
      m_myShip.IncRank();
  }
}

  // Name: RequestMaterial()
  // Desc - Requests material to use to merge
  // Preconditions - Ship has materials to try and merge
  // Postconditions - Returns integer of item selected by user
void Game::RequestMaterial(int &choice){
  //int chosenNum;      // intger to store the index of the material to merge
  cout << "Which materials would you like to merge?" << endl;
  cout << "To List known materials enter -1" << endl;
  cin >> choice;

  // reprompt to make sure that input is between -1 and 62
  while (choice > PROJ2_SIZE or choice < -1){
    cout << "Which materials would you like to merge?" << endl;
    cout << "To List known materials enter -1" << endl;
    cin >> choice;
  }
  // display the materials if the user enters -1
  if (choice == -1)
    DisplayMaterials();
  //else{
    // update the value of choice
    //choice = chosenNum;
}

  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings (name of item)
  // Preconditions - m_materials is populated
  // Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string material1, string material2){
  int recipeIndex = -1;      // integer to store the index of the recipe
  for (int i = 0; i < PROJ2_SIZE; i++){
    // check each material's recipe and see if the two materials match any of them
    if ((material1 == m_materials[i].m_material1 and material2 == m_materials[i].m_material2) or
	(material1 == m_materials[i].m_material2 and material2 ==  m_materials[i].m_material1))
	recipeIndex = i;
  }
  return recipeIndex;
}

  // Name: CalcScore()
  // Desc - Displays current score for Ship
  // Preconditions - Ship is populated with materials
  // Postconditions - Displays total
void Game::CalcScore(){
  // output ship name and rank
  cout << "Ship name: " << m_myShip.GetName() << endl;
  cout << "Ship rank: " << m_myShip.GetRank() << endl;
}

  // Name: GameTitle()
  // Desc - Title for Game (Do not edit)
  // Preconditions - None
  // Postconditions - None
void GameTitle(){
    cout << "N   N OOO   M   M  AA  N   N '' SSS    AA  L   CCC H  H EEE M   M Y   Y" << endl;
    cout << "NN  N O O   MM MM A  A NN  N    S     A  A L   C   H  H E   MM MM  Y Y " << endl;
    cout << "N N N O O   M M M AAAA N N N    SSS   AAAA L   C   HHHH EEE M M M   Y  " << endl;
    cout << "N  NN O O   M   M A  A N  NN      S   A  A L   C   H  H E   M   M   Y  " << endl;
    cout << "N   N OOO   M   M A  A N   N    SSS   A  A LLL CCC H  H EEE M   M   Y  " << endl;
  }
