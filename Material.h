/*****************************************
** File: Material.h
** Project: CMSC 202 Project 2, Spring 2021
** Author: Layan Akhras
** Date: 3/11/21
** Section: 50/51
** E-mail: lakhras1@umbc.edu
**
** This file contains the Material struct
** and member variables for the No Man's
** Alchemy game.
******************************************/

#ifndef MATERIAL_H //Include/Header Guard
#define MATERIAL_H //Include/Header Guard

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

// Name: Material struct
// Desc - Used to store data about materials
struct Material{
public: //Public by default
  Material(){} //Default constructor
  Material(string name, string type, string material1, string material2,
	   int quantity){
    m_name = name; //Name of this material
    m_type = type; //Type of the material (raw, common, uncommon, or unique)
    m_material1 = material1; //Name of first required material to create
    m_material2 = material2; //Name of second required material to create
    m_quantity = quantity; //Quantity of the material
  }
  string m_name; //Name of the material
  string m_type; //Type of the material (raw, common, uncommon, or unique)
  string m_material1; //Required material 1 to create
  string m_material2; //Required material 2 to create
  int m_quantity; //Quantity of material owned
};

#endif
