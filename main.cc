#include "card.h"
#include "deck.h"
#include "game.h"
#include <iostream>
#include <string>
#include <istream>
#include <numeric>
#include <algorithm>

class InvalidCommandException{};

int main(int argc, char **argv) {
    unsigned int seed = 0;
    if (argc > 2) {
		std::cerr << "Too many arguments" << std::endl;
		exit(1);
	};
    if (argc == 2) {
		seed = std::stoi(argv[1]);
	};

    Game g;
    std::string response1;
    std::string response2;
    std::string response3;
    std::string response4;
    std::cout << "Is Player1 a human (h) or a computer (c)?" << std::endl << ">";
    std::cin >> response1;
    while (!(response1 == "h" || response1 == "c")) {
        std::cout << "Please enter a valid player type. Is Player1 a human (h) or a computer (c)?" << std::endl << ">";
        std::cin >> response1;
    }
    std::cout << "Is Player2 a human (h) or a computer (c)?" << std::endl << ">";
    std::cin >> response2;
    while (!(response2 == "h" || response2 == "c")) {
        std::cout << "Please enter a valid player type. Is Player2 a human (h) or a computer (c)?" << std::endl << ">";
        std::cin >> response2;
    }
    std::cout << "Is Player3 a human (h) or a computer (c)?" << std::endl << ">";
    std::cin >> response3;
    while (!(response3 == "h" || response3 == "c")) {
        std::cout << "Please enter a valid player type. Is Player3 a human (h) or a computer (c)?" << std::endl << ">";
        std::cin >> response3;
    }
    std::cout << "Is Player4 a human (h) or a computer (c)?" << std::endl << ">";
    std::cin >> response4;
    while (!(response4 == "h" || response4 == "c")) {
        std::cout << "Please enter a valid player type. Is Player4 a human (h) or a computer (c)?" << std::endl << ">";
        std::cin >> response4;
    }

    if (response1 == "c") {
        g.addPlayers(false, "Player1");
    } else {
        g.addPlayers(true, "Player1");
    }
    if (response2 == "c") {
        g.addPlayers(false, "Player2");
    } else {
        g.addPlayers(true, "Player2");
    }
    if (response3 == "c") {
        g.addPlayers(false, "Player3");
    } else {
        g.addPlayers(true, "Player3");
    }
    if (response4 == "c") {
        g.addPlayers(false, "Player4");
    } else {
        g.addPlayers(true, "Player4");
    }

    std::string cmd;
    bool quit_true = false;
    while (true) {
        g.beginNewRound(seed);
        while (true) {
            if (g.handEmpty() == true) break;
            // human
            std::string ranks = "A23456789TJQK";
            std::string suits = "CSHD";
            if ((g.getPlayersList().at(g.getCurrentPlayer())->getType() == true) && std::cin >> cmd) {
                try {
                    if (cmd == "play") {
                        Card theCard;
                        std::cin >> theCard;
                        if (!g.playTurn(theCard, true)) {
                            std::cout << "This is not a legal play." << std::endl;
                            continue;
                        }
                        g.printMessage(); 
                        std::cout << theCard << "." << std::endl;
                        g.nextPlayer();
                    } else if (cmd == "discard") {
                        Card theCard;
                        std::cin >> theCard; 
                        if (!g.discardTurn(theCard, true)) {
                            std::cout << "You have a legal play. You may not discard." << std::endl;
                            continue;
                        }
                        g.printMessage();
                        std::cout << theCard << "." << std::endl;
                        g.nextPlayer();
                    } else if (cmd == "deck") {
                        g.getDeck().print();
                    } else if (cmd == "ragequit") {
                        g.ragequit();
                        Card theCard; 
                        g.addLegal(g.getPlayersList().at(g.getCurrentPlayer()));
                        bool val_play = false;
                        bool val_discard = false;
                        if (g.getLegalExists() == true) {
                            val_play = g.playTurn(theCard, false);
                        } else {
                            val_discard = g.discardTurn(theCard, false);
                        }
                        g.printMessage();
                        if (val_play == true) { 
                            std::cout << *g.getPlayersList().at(g.getCurrentPlayer())->getLegalCards().at(0) << "." << std::endl; 
                        } else if (val_discard == true) {
                            std::cout << *g.getPlayersList().at(g.getCurrentPlayer())->getPlayerDiscards().at(0) << "." << std::endl;
                        }
                        g.nextPlayer();
                    } else if (cmd == "quit") {
                        quit_true = true;
                        break;
                    } else throw InvalidCommandException{};
                } catch (InvalidValueException &i) {
                    std::cout << "Invalid card! Please put your command again." << std::endl;
                    continue;
                } catch (InvalidDiscardCardException &i) {
                    std::cout << "Input card doesn't exist in your hand. Please put a valid card." << std::endl;
                    continue;
                } catch (InvalidCommandException &i) {
                    std::cout << "Invalid command! Please enter a valid command." << std::endl;
                    continue;
                }
            } else {
            // computer
            Card theCard; 
            g.addLegal(g.getPlayersList().at(g.getCurrentPlayer()));
            bool val_play = false;
            bool val_discard = false;
            if (g.getLegalExists() == true) {
                val_play = g.playTurn(theCard, false);
            } else {
                val_discard = g.discardTurn(theCard, false);
            }
            g.printMessage();
            if (val_play == true) { 
                std::cout << *g.getPlayersList().at(g.getCurrentPlayer())->getLegalCards().at(0) << "." << std::endl; 
            } else if (val_discard == true) {
                std::cout << *g.getPlayersList().at(g.getCurrentPlayer())->getPlayerDiscards().at(0) << "." << std::endl;
            }
            g.nextPlayer();
            }
        }
        if (quit_true == true) return 1;
        g.recalculateAllScores();
        if (g.getGameOver() == true) break;
        g.clearAllDiscards();
    }

    std::cout << "Player1's discards:" << g.getPlayersList().at(0)->printDiscards() << std::endl;
    std::cout << "Player1's score: " << g.getPlayersScore().at(0);
    std::cout << " + " << g.getPlayersList().at(0)->recalculateScore() << " = ";
    std::cout << g.getPlayersScore().at(0) + g.getPlayersList().at(0)->recalculateScore() << std::endl;
    std::cout << std::endl;
    std::cout << "Player2's discards:" << g.getPlayersList().at(1)->printDiscards() << std::endl;
    std::cout << "Player2's score: " << g.getPlayersScore().at(1);
    std::cout << " + " << g.getPlayersList().at(1)->recalculateScore() << " = ";
    std::cout << g.getPlayersScore().at(1) + g.getPlayersList().at(1)->recalculateScore() << std::endl;
    std::cout << std::endl;
    std::cout << "Player3's discards:" << g.getPlayersList().at(2)->printDiscards() << std::endl;
    std::cout << "Player3's score: " << g.getPlayersScore().at(2);
    std::cout << " + " << g.getPlayersList().at(2)->recalculateScore() << " = ";
    std::cout << g.getPlayersScore().at(2) + g.getPlayersList().at(2)->recalculateScore() << std::endl;
    std::cout << std::endl;
    std::cout << "Player4's discards:" << g.getPlayersList().at(3)->printDiscards() << std::endl;
    std::cout << "Player4's score: " << g.getPlayersScore().at(3);
    std::cout << " + " << g.getPlayersList().at(3)->recalculateScore() << " = ";
    std::cout << g.getPlayersScore().at(3) + g.getPlayersList().at(3)->recalculateScore() << std::endl;
    std::cout << std::endl;
    
    std::vector<int> final_scores{0,0,0,0};
    final_scores.at(0) = g.getPlayersScore().at(0) + g.getPlayersList().at(0)->recalculateScore();
    final_scores.at(1) = g.getPlayersScore().at(1) + g.getPlayersList().at(1)->recalculateScore();
    final_scores.at(2) = g.getPlayersScore().at(2) + g.getPlayersList().at(2)->recalculateScore();
    final_scores.at(3) = g.getPlayersScore().at(3) + g.getPlayersList().at(3)->recalculateScore();
    auto it = std::min_element(std::begin(final_scores), std::end(final_scores));
    int lowestScore = *it;
    for (unsigned int i = 0; i < 4; ++i) {
        if (final_scores.at(i) == lowestScore) {
            std::cout << "" << g.getPlayersList().at(i)->getName() << " wins!" << std::endl;
        }
    }
}

