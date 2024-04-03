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
    //Player enemy1("Lanesra", 10.0, 80);
    while (true) {
        newGame.Run();
    }
}