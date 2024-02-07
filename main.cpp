#include "cards.hpp"
#include "input.hpp"
#include <iostream>
#include <ostream>
#include <string>
static double bal;
static deck d;
static hand playerHand;
static hand dealerHand;
static double wager;
inline void printHands();
void startGame();
int main() {
  if (ask("do you want to play blackjack")) {
    bal = askInt("starting bal?");
    startGame();
  }
}
void startGame() {
  d = newDeck();
  playerHand = hand();
  playerHand.push_back(deal(&d));
  playerHand.push_back(deal(&d));
  dealerHand = hand();
  dealerHand.push_back(deal(&d));
  dealerHand.push_back(deal(&d)->hide());
askWager:
  wager = askInt("how much do you want to wager\nYour bal is: " + std::to_string(bal));
  if (wager > bal) {
    std::cout << "your wager is too much\n";
    goto askWager;
  }
    printHands();
    while(ask("do you want to hit (say no to stand)")){
      playerHit(deal(&d), &playerHand);
      printHands();
    }
    
    std::cout << "standing, dealer finishing hand" << "\n";
    unhideHand(dealerHand);
    dealerFinish(&d, &dealerHand);
    printHands();
    int delaerValue = value(&dealerHand);
    int playerValue = value(&playerHand);
    if(delaerValue == playerValue){
      std::cout << "Push!" << std::endl;
      return;
    }else if(playerValue > 21){
      std::cout << "lose" << std::endl;
      bal -= wager;
      return;
    }else if (delaerValue > 21){
      std::cout << "you win!" << std::endl;
      bal += wager*.5;
      return;
    }else if(dealerHand>playerHand){
      std::cout << "dealer wins" << std::endl;
      bal -= wager;
    }else{
      std::cout << "player wins" << std::endl;
      bal += wager*.5;
    }
}
inline void printHands() {
  std::cout << "Your hand:\n"
            << printable(playerHand) << "\nDealer hand: \n"
            << printable(dealerHand) << std::endl;
}