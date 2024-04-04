#include <iostream>
#include "Game.h"

int main() {
    //Item firstItem = Item("Shortstaff", "This is a shortstaff");
    //firstItem.Description();

    //Room roomOne = Room("What a cool room", new Item[1]{ Item("itemName", "itemDesc") }, 1);
    //
    //roomOne.Description();
    Game newGame;
    String nameInput;
    String::WriteInColor(48, "Welcome to the game, enter your player's name to begin the journey\n\n");
    nameInput.ReadFromConsole();

    int playerDmg = 5;
    int playerHealth = 100;
    Player newPlayer(nameInput, playerDmg, playerHealth);
    newGame.setPlayer(newPlayer);

    Enemy enemy1("Lanesra", 10, 100);
    Enemy enemy2("Enemy 2", 15.0, 80);
    Enemy enemy3("Enemy 3", 10.0, 110);
    Enemy enemy4("Enemy 4", 12.0, 120);
    newGame.setEnemies(enemy1, enemy2, enemy3, enemy4);

    while (true) {
        newGame.Run();
    }
}