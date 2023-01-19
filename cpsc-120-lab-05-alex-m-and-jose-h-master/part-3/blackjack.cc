// Jose Hernandez
// CPSC 120-01
// 2022-10-06
// josehernandez503@csu.fullerton.edu
// @josehernandez503
// Partners: @alex3809, @EthLo-deimos
//
// Lab 05-03
//
// Counting in Blackjack using command arguments.
 
#include <iostream>
#include <string>
#include <vector>

  std::string J("J");
  std::string Q ("Q");
  std::string K ("K");
  std::string A ("A");
  int score(0);
int main(int argc, char* argv[]) {
 std::vector<std::string> arguments(argv, argv + argc);
  if (arguments.size() < 1) {
   std::cout << "Error, you must supply at least 2 cards\n";
   return 1;
  }
  std::string command{arguments.at(0)};
  std::string cardone{arguments.at(1)};
  if (cardone == J) {
    int cardone(10);
    score = score + cardone;
  } else if (cardone == Q) {
    int cardone(10);
    score = score + cardone;
  } else if (cardone == K) {
    int cardone(10);
    score = score + cardone;
  } else if (cardone == A) {
    int cardone(11);
    score = score + cardone; 
  }
  std::string cardtwo{arguments.at(2)};
  if (cardtwo == J) {
    int cardtwo(10);
    score = score + cardtwo;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  } else if (cardtwo == Q) {
    int cardtwo(10);
    score = score + cardtwo;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  } else if (cardtwo == K) {
    int cardtwo(10);
    score = score + cardtwo;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  } else if (cardtwo == A) {
    int cardtwo(11);
    score = score + cardtwo;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  }
  std::string cardthree{arguments.at(3)};
  if (cardthree == J) {
    int cardthree(10);
    score = score + cardthree;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  }else if (cardthree == Q) {
    int cardthree(10);
    score = score + cardthree;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  } else if (cardthree == K) {
    int cardthree(10);
    score = score + cardthree;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  } else if (cardthree == A) {
    int cardthree(11);
    score = score + cardthree;
    if (score == 21) {
      std::cout << "Your score is: " << score << "- Black Jack you WIN.\n";
      return 0;
    } else if (score > 21){
      std::cout << "Your score is: " << score << "- Bust \n";
      return 0;
    }
    std::cout << "Your score is: " << score;
  }
  return 0;
}
