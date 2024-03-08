#include <iostream>
#include "Room.h"

int main() {
    Item firstItem = Item("Shortstaff", "This is a shortstaff");
    //firstItem.Description();

    Room roomOne = Room("What a cool room", &firstItem, 1);
    
    roomOne.Description();
}