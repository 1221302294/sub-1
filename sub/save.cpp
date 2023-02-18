#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "movement.cpp"
using namespace std;

const char HOLD = ',';

void initBoard(vector< vector<char> >& board, int& rows, int& cols)
{
   board.resize(rows);
   for (int i = 0; i < rows; i++)
   {
      board[i].resize(cols);
   }
}

void saveGame(vector< vector<char> >& board, vector <Character>& zombies, Character& alien, int& noOfZombies,  int& rows, int& cols, const string filename)
{
    ofstream save(filename);

    save << rows << HOLD;
    save << cols << HOLD;
    save << noOfZombies << HOLD;

     for (int row = 0; row < rows; row++)
   {
      for (int col = 0; col < cols; col++)
      {
         save << (int)getDimension(board, row, col) << HOLD;
      }
   }

   save << alien.row << HOLD;
   save << alien.col << HOLD;
   save << alien.attack << HOLD;
   save << alien.health << HOLD;

   for (int i = 0; i < noOfZombies; i++)
   {
      save << zombies.at(i).row << HOLD;
      save << zombies.at(i).col << HOLD;
      save << zombies.at(i).attack << HOLD;
      save << zombies.at(i).health << HOLD;
      save << zombies.at(i).ranged << HOLD;
   }
}

void loadGame(vector< vector<char> >& board, vector <Character>& zombies, Character& alien, int& noOfZombies,  int& rows, int& cols, const string filename)
{
    ifstream load(filename);
    string data;

    getline(load, data, HOLD);
     rows = stoi(data);

    getline(load, data, HOLD);
    cols = stoi(data);

    getline(load, data, HOLD);
    noOfZombies = stoi(data);
   
   int counter = 0;
   board.clear();
   initBoard(board, rows, cols);


   for (int row = 0; row < rows; row++)
   {
      for (int col = 0; col < cols; col++)
      {
         getline(load, data, HOLD);
         
         setDimension(board, row, col, (char)stoi(data));
      }
   }

   getline(load, data, HOLD);
   alien.row = stoi(data);

   getline(load, data, HOLD);
   alien.col = stoi(data);
   
   getline(load, data, HOLD);
   alien.health = stoi(data);

   getline(load, data, HOLD);
   alien.attack = stoi(data);

   counter = 0;

   zombies.clear();
   zombies.resize(noOfZombies);

    while (counter < noOfZombies)
   {
      getline(load, data, HOLD);
      zombies.at(counter).row = stoi(data);

      getline(load, data, HOLD);
      zombies.at(counter).col = stoi(data);

      getline(load, data, HOLD);
      zombies.at(counter).attack = stoi(data);

      getline(load, data, HOLD);
      zombies.at(counter).health = stoi(data);

      getline(load, data, HOLD);
      zombies.at(counter).ranged = stoi(data);

      counter++;
   }

   load.close();
}