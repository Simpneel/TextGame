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
    String::WriteInColor(11, "Welcome to the game, enter your player's name to begin the journey\n\n");
    nameInput.ReadFromConsole();
    std::cout << std::endl << std::endl;

    String::WriteInColor(14, "Your objective in this game is to explore the entire dungeon, find and defeat\n the four bosses with whatever means possible.\n\n");
    String::WriteInColor(14, "To begin with, you can try to move in any direction with these commands:\n\n");
    String::WriteInColor(14, "move north\tmove south\tmove west\tmove east\n\n");
    String::WriteInColor(14, "These are your movement commands, you also have a basic attack command to hit enemies with in the beginning\nBut you will get stronger the more you explore\n\n\n");
   

    int playerDmg = 5;
    int playerHealth = 100;
    Player newPlayer(nameInput, playerDmg, playerHealth);
    newPlayer.addItem("apple");
    newPlayer.addItem("satchel");
    newPlayer.addItem("torch");

    newGame.setPlayer(newPlayer);

    
    Enemy enemy1("Lanesra", 10, 100);
    Enemy enemy2("Kurt", 15.0, 80);
    Enemy enemy3("Ilton", 10.0, 110);
    Enemy enemy4("Orion", 12.0, 120);
    newGame.setEnemies(enemy1, enemy2, enemy3, enemy4);

    while (newGame.keepGameRunning) {
        newGame.Run();
        if (newGame.gameWon) {
            system("cls");
            String::WriteInColor(10, "______________________________________________________________________");
            String::WriteInColor(10, "\n\n\t\t\t\t\t\tYOU WON THE GAME, CONGRATULATIONS!\n\n\n\t\t\t\t\t\tnow what?\n\n");
            String::WriteInColor(10, "______________________________________________________________________");
            break;
        }
    }
}