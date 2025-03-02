#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "setup.hpp"
#include "colour.hpp"
#include "buffer.hpp"

// Forward declarations
void clrscr();
void dispBanner();

struct Score {
    int time;
    int score;
    GAME_MODE mode;
    std::time_t date;
    
    Score(int t, GAME_MODE m) : time(t), mode(m) {
        // Score calculation: 1000 - time (minimum score is 1)
        score = std::max(1, 1000 - time);
        date = std::time(nullptr);
    }
    
    Score() : time(0), score(0), mode(BEGINNER), date(0) {}
};

class HighScoreManager {
private:
    static const int MAX_SCORES = 10;
    std::vector<Score> scores;
    const std::string SCORE_FILE = "highscores.dat";
    
    void loadScores() {
        std::ifstream file(SCORE_FILE, std::ios::binary);
        if (file) {
            Score score;
            while (file.read(reinterpret_cast<char*>(&score), sizeof(Score))) {
                scores.push_back(score);
            }
        }
    }
    
    void saveScores() {
        std::ofstream file(SCORE_FILE, std::ios::binary);
        for (const auto& score : scores) {
            file.write(reinterpret_cast<const char*>(&score), sizeof(Score));
        }
    }

public:
    HighScoreManager() {
        loadScores();
    }
    
    void addScore(int time, GAME_MODE mode) {
        if (mode == CUSTOM) return; // Don't save custom game scores
        
        scores.emplace_back(time, mode);
        
        // Sort scores by mode and score (descending)
        std::sort(scores.begin(), scores.end(), 
            [](const Score& a, const Score& b) {
                if (a.mode != b.mode) return a.mode < b.mode;
                return a.score > b.score;
            });
            
        // Keep only top 10 scores for each mode
        std::vector<Score> filtered;
        int countBeg = 0, countInt = 0, countExp = 0;
        for (const auto& score : scores) {
            if (score.mode == BEGINNER && countBeg < MAX_SCORES) {
                filtered.push_back(score);
                countBeg++;
            }
            else if (score.mode == INTERMEDIATE && countInt < MAX_SCORES) {
                filtered.push_back(score);
                countInt++;
            }
            else if (score.mode == EXPERT && countExp < MAX_SCORES) {
                filtered.push_back(score);
                countExp++;
            }
        }
        
        scores = filtered;
        saveScores();
    }
    
    void displayScores() {
        clrscr();
        dispBanner();
        
        const char* modeNames[] = {"Beginner", "Intermediate", "Expert"};
        COLOUR modeColors[] = {green_fg, yellow_fg, red_fg};
        
        for (int mode = BEGINNER; mode <= EXPERT; mode++) {
            writeBuf << modeColors[mode-1] << "\n  " << modeNames[mode-1] << " High Scores:\n" << white_fg;
            writeBuf << "  Rank  Score  Time   Date\n";
            writeBuf << "  --------------------------------\n";
            
            int rank = 1;
            for (const auto& score : scores) {
                if (score.mode == mode) {
                    char dateStr[11];
                    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", std::localtime(&score.date));
                    
                    // Convert numbers to strings
                    std::stringstream ss;
                    ss << "   " << rank << ".    " << score.score 
                       << "    " << score.time << "s    " << dateStr;
                    writeBuf << ss.str() << "\n";
                    rank++;
                }
            }
            writeBuf << "\n";
        }
        
        writeBuf << white_fg << "\n  Press any key to return to menu..." << reset;
        writeBuf.disp();
        writeBuf.clear();
        getch();
    }
};

HighScoreManager highScores; 