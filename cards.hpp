#pragma once
#include <cstdlib>
#include <format>
#include <new>
#include <string>
#include <vector>
class card;
typedef std::vector<card *> hand;
typedef std::vector<card *> deck;
inline int value(hand* h);
inline int valueWithHidden(hand* h);
static const std::string suits[] = {"♥", "♣", "♠", "♦"};
class card {
private:
  card();
  void genName() {
    if (this->hidden) {
      this->name = "?? of ?";
    } else if (this->ace) {
      this->name = std::format("A{} {}", this->value, this->suit);
    } else {
      this->name = std::format("{} {}", this->symbol, this->suit);
    }
  }

public:
  std::string suit;
  int value;
  bool ace;
  std::string symbol;
  std::string name;
  bool hidden;
  card(std::string suit, int value, bool ace = false,
       std::string symbol = std::string(), bool hidden = false)
      : suit(suit), value(value), ace(ace), hidden(hidden), symbol(symbol) {
    if (this->symbol.empty()) {
      this->symbol = std::to_string(value);
    }
    this->genName();
  }
  void aceMark11() {
    if (!this->ace) {
      return;
    }
    this->value = 11;
    this->genName();
  }
  void aceMarkOne() {
    if (!this->ace) {
      return;
    }
    this->value = 1;
    this->genName();
  }
  card* unhide() {
    if (this->hidden) {
      this->hidden = false;
      this->genName();
    }
    return this;
  }
  card* hide(){
    if(!this->hidden){
      this->hidden = true;
      this->genName();
    }
    return this;
  }
};
inline deck newDeck() {
  deck cards;
  for (std::string suit : suits) {
    for (int i = 2; i < 11; i++) {
      cards.push_back(new card(suit, i));
    }
    cards.push_back(new card(suit, 10, false, "J"));
    cards.push_back(new card(suit, 10, false, "Q"));
    cards.push_back(new card(suit, 10, false, "K"));
    cards.push_back(new card(suit, 11, true, "A"));
  }
  return cards;
}
inline card* deal(deck* d) {
  int rand = std::rand() % d->size();
  card *c = d->at(rand);
  d->erase(d->begin() + rand);
  return c;
}
inline void playerHit(card *newCard, hand* playerHand) {
  auto playerHandValue = value(playerHand);
  if (newCard->ace && newCard->value + playerHandValue > 21) {
    newCard->aceMarkOne();
  }
  playerHand->push_back(newCard);
  return;
}
inline void dealerPlay(card *newCard, hand* dealerHand) {
  auto dealerValueHand = valueWithHidden(dealerHand);
  if (newCard->ace && newCard->value + dealerValueHand > 21) {
    newCard->aceMarkOne();
  }
  dealerHand->push_back(newCard);
  return;
}
inline int value(hand* h) {
  auto aces = std::vector<card *>();
  auto total = 0;
  for (auto c : *h) {
    if (c->hidden) {
      continue;
    }
    if (c->ace) {
      aces.push_back(c);
      continue;
    }
    total += c->value;
  }
  auto al = aces.size();
  if (aces.empty()) {
    return total;
  }
  if (total == 0) {
    for (auto x = 1; x < aces.size(); x++) {
      aces.at(x)->aceMarkOne();
    }
    return 10 + aces.size();
  }
  if (aces.size() == 1) {
    if (total + 11 > 21) {
      aces.at(0)->aceMarkOne();
      return total + 1;
    }
    return total + 11;
  }
  auto t = aces.at(0)->value + aces.size() - 1 + total;
  if (t > 21) {
    for (auto a : aces) {
      a->aceMarkOne();
    }
    return aces.size() + total;
  }
  aces.erase(aces.begin());
  for (auto a : aces) {
    a->aceMarkOne();
  }
  return t;
}
inline int valueWithHidden(hand* h) {
  auto aces = std::vector<card *>();
  auto total = 0;
  for (auto c : *h) {
    if (c->ace) {
      aces.push_back(c);
      continue;
    }
    total += c->value;
  }
  auto al = aces.size();
  if (aces.empty()) {
    return total;
  }
  if (total == 0) {
    for (auto x = 1; x < aces.size(); x++) {
      aces.at(x)->aceMarkOne();
    }
    return 10 + aces.size();
  }
  if (aces.size() == 1) {
    if (total + 11 > 21) {
      aces.at(0)->aceMarkOne();
      return total + 1;
    }
    return total + 11;
  }
  auto t = aces.at(0)->value + aces.size() - 1 + total;
  if (t > 21) {
    for (auto a : aces) {
      a->aceMarkOne();
    }
    return aces.size() + total;
  }
  aces.erase(aces.begin());
  for (auto a : aces) {
    a->aceMarkOne();
  }
  return t;
}
inline void dealerFinish(deck* d, hand* dealerHand) {
  while (valueWithHidden(dealerHand) < 17) {
    dealerPlay(deal(d), dealerHand);
  }
}
inline void unhideHand(hand h) {
  for (auto c : h) {
    c->unhide();
  }
}
inline std::string printable(hand h){
  std::string toRet  = "";
  for(auto c:h){
    toRet += c->name;
    toRet += " | ";
  }
  return toRet;
}