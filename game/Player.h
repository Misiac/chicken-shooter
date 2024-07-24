#pragma once

class Player {
private:

  static int prevId;

  int id;
  String name;
  int score;

public:
  Player(){};
  Player(String playerName) {
    name = playerName;
    id = ++prevId;
    score = 0;
  }

  int getId() {
    return id;
  }
  String getName() {
    return name;
  }
  int getScore() {
    return score;
  }

  int addScore(int scoreToAdd) {
    score += scoreToAdd;
    return score;
  }
};

int Player::prevId = 0;