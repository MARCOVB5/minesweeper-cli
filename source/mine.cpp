#include "field.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "colour.hpp"
#include "display.hpp"
#include <stdio.h>
#include <thread>
#include <atomic>

std::atomic<bool> gameRunning(true);

void clrscr()
{
    int n;
    for (n = 0; n < 10; n++)
        printf( "\n\n\n\n\n\n\n\n\n\n" );
}

void updateTimer(Field& field) {
    while (gameRunning) {
        if (gameState == RUNNING) {
            field.updateTimer();
            // Update display
            clrscr();
            dispBanner();
            field.drawField();
            dispFlagCounter();
            if (gameState != RUNNING)
                dispVictoryOrDefeat();
            else
                dispControls();
            writeBuf.disp();
            writeBuf.clear();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    clrscr();
    setGameMode();
    getQuickClearSettings();

    Field field;
    
    // Start timer thread
    std::thread timerThread(updateTimer, std::ref(field));

    while (true)
    {
        if (gameState != RUNNING) {
            gameRunning = false;
            if (gameState == VICTORY) {
                int finalTime = field.getElapsedTime();
                highScores.addScore(finalTime, gameMode);
            }
            break;
        }
        field.getMove();
    }

    // Wait for timer thread to finish
    timerThread.join();

    std::cout << endl
              << reset;

    return 0;
}