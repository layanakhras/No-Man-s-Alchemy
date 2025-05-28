/*****************************************
** File: Ship.cpp
** Project: No Man's Alchemy
** Author: Layan Akhras
**
** This file contains the function definitions
** of the Ship class for the No Man's Alchemy
** game.
******************************************/


#include "Ship.h"

Ship::Ship(){
  // default constructor
  SetName("Ahoy ship");
  m_numMaterials = 0;
  m_shipRank = 'D';
}


Ship::Ship(string name){
  // constructor
  SetName(name);
  m_numMaterials = 0;
  m_shipRank = 'D';
}

  // Name: GetName()
  // Desc - Getter for the Player Ship's name
  // Preconditions - Player Ship exists
  // Postconditions - Returns the name of the Player Ship
string Ship::GetName(){
  return m_shipName;
}
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Player Ship
  // Preconditions - Player Ship exists
  // Postconditions - Sets name of Player Ship
void Ship::SetName(string name){
  m_shipName = name;
}
  // Name: CheckMaterial(Material)
  // Desc - Checks to see if the Ship has a material
  // Preconditions - Ship already has materials
  // Postconditions - Returns index of material if the Ship has it else -1
int Ship::CheckMaterial(Material myMaterial){
  int i = 0;       // declares and initializes an integer used to increment
  // loops through the list of my materials
  while (i < PROJ2_SIZE){
    // checks if this material exists in that array
    if (m_myMaterials[i].m_name == myMaterial.m_name){
      return i;
    }
    i++;    
  }
  return -1;
}
  

  // Name: AddMaterial(string)
  // Desc - Inserts a material into the Ship's list of materials
  // Preconditions - Ship exists
  // Postconditions - Add a material to the Ship's m_myMaterials with a quantity of 0
void Ship::AddMaterial(Material myMaterial){
  // check to make sure it doesn't already exist in m_myMaterials
  int checkIndex = CheckMaterial(myMaterial);
  // if it doesn't already exist in m_myMaterials..
  if (checkIndex == -1){
    // add it
    m_myMaterials[m_numMaterials] = myMaterial;
    m_numMaterials++;
  }
}

  // Name: IncrementQuantity(Material)
  // Desc - Adds quantity to list of materials the Ship knows
  // Preconditions - Ship exists
  // Postconditions - Increases quantity of material for the Ship
void Ship::IncrementQuantity(Material myMaterial){
  // add one to the quantity of this material
  m_myMaterials[CheckMaterial(myMaterial)].m_quantity++;
}

  // Name: DecrementQuantity(Material)
  // Desc - Reduces quantity from the Ship's inventory with true, if no quantity false
  // Preconditions - A Ship exists
  // Postconditions - Reduces quantity of material for the Ship
bool Ship::DecrementQuantity(Material myMaterial){
  bool decreaseOne = false;        // boolean variable to determine if we can decrement
  // if we can decrease without having a negative
  if (CheckMaterial(myMaterial) > -1){
    if (myMaterial.m_quantity >= 1){
      m_myMaterials[CheckMaterial(myMaterial)].m_quantity--;
      decreaseOne = true;
  }else
      decreaseOne = false;
  }
  return decreaseOne;
}

  // Name: CheckQuantity(Material)
  // Desc - Checks to see if quantity of two merge materials are available
  // Preconditions - Ship exists with materials
  // Postconditions - Returns true if both are available (including two of same material)
bool Ship::CheckQuantity(Material myMaterial1, Material myMaterial2){
  // if we have at least one of each material...
  if (myMaterial1.m_quantity >= 1 and myMaterial2.m_quantity >= 1)
    return true;
  else
    return false;
}

  // Name: GetMaterial(int)
  // Desc - Checks to see if the Ship has any materials
  // Preconditions - The Ship already has materials
  // Postconditions - Returns material at specific index
Material Ship::GetMaterial(int num){
  return m_myMaterials[num];
}

  // Name: IncRank()
  // Desc - Increments the rank of the ship to the next rank.
  // Preconditions - Ship exists and has a rank
  // Postconditions - m_shipRank will move to the next character
void Ship::IncRank(){
  // increment rank one level higher
  if (m_shipRank == 'D')
    m_shipRank = 'C';
  else if (m_shipRank == 'C')
    m_shipRank = 'B';
  else if (m_shipRank == 'B')
    m_shipRank = 'A';
  else if (m_shipRank == 'A'){
    m_shipRank = 'S';
    cout << "Congrats! You have built your ship and can escape!" << endl; 
  }
}
  // Name: GetRank()
  // Desc - Checks to see what the current ship's rank is
  // Preconditions - The ship exists
  // Postconditions - Returns the character indicating the rank of the ship
char Ship::GetRank(){
  return m_shipRank;
}
