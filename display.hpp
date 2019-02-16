#pragma once

#include <iostream>
#include <iomanip>
#include "setup.hpp"
#include "colour.hpp"

void dispBanner(){ //will be moved to separate header later
    std::cout << blue_fg;
    std::cout << "##     ##  ##  ##    ## ########  ######  ##      ## ######## ######## ########  ######## ######## \n"; 
    std::cout << "###   ###  ##  ###   ## ##       ##    ## ##  ##  ## ##       ##       ##     ## ##       ##     ##\n"; 
    std::cout << "#### ####  ##  ####  ## ##       ##       ##  ##  ## ##       ##       ##     ## ##       ##     ##\n"; 
    std::cout << "## ### ##  ##  ## ## ## ######    ######  ##  ##  ## ######   ######   ########  ######   ######## \n"; 
    std::cout << "##     ##  ##  ##  #### ##             ## ##  ##  ## ##       ##       ##        ##       ##   ##  \n"; 
    std::cout << "##     ##  ##  ##   ### ##       ##    ## ##  ##  ## ##       ##       ##        ##       ##    ## \n"; 
    std::cout << "##     ##  ##  ##    ## ########  ######   ###  ###  ######## ######## ##        ######## ##     ##\n";
    std::cout << endl << reset;
}

void setGameMode(){
    int ch;
    //std::cout << cyan_fg << "5. Quit\n" << reset;
    do{
        dispBanner();
        std::cout << std::setw(30);
        std::cout << white_fg << "Choose Game Mode:\n";
        std::cout << std::setw(30);
        std::cout << green_fg << "1. Beginner\n";
        std::cout << std::setw(30);
        std::cout << yellow_fg << "2. Intermediate\n";
        std::cout << std::setw(30);
        std::cout << red_fg << "3. Expert\n";
        std::cout << std::setw(30);
        std::cout << blue_fg << "4. Custom\n\n";
        
        std::cin >> ch;
        
        if(ch < 1 || ch > 4) std::cout << red_fg <<"Invalid Choice. Try again\n";
        else mode = (GAME_MODE)ch;
        system("clear");
    
    } while(ch < 1 || ch > 4);
}