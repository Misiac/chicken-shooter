#pragma once
#include "../HardwareController.h"
#include <WebSocket.h>
#include "Actions.h"
#include "Player.h"
#include "../util/TextUtils.h"
#include "../data/Config.h"

class GameController {

private:
  HardwareController hwController;
  WebSocket* ws;
  Player* players;
  int numberOfPlayers;
  int currentTurn = 1;
  int currentPlayerIndex = 0;
  boolean isMuted = false;

public:
  GameController()
    : hwController(), ws(nullptr) {}

  void setWebSocket(WebSocket& webSocket) {
    ws = &webSocket;
  }

  String react(const String& message) {

    String action = getAction(message);
    String reply = generatePlayersCsv();

    if (action == START_GAME) {
      reply = startGame(message);
    } else if (action == INITIATE_TIMER) {
      reply = initiateTimer();
    } else if (action == SWITCH_MUTE) {
      switchBuzzerState();
      reply = "MUTE STATE CHANGED";
    } else if (action == INITIATE_END_GAME) {
      reply = endGame();
    } else {
      reply = "UNKNOWN ACTION";
    }

    return reply;
  }

  String startGame(String message) {
    createPlayers(TextUtils::getSpecificLine(message, 1));
    String reply = SET_PLAYERS;
    reply += generatePlayersCsv();
    hwController.playStartAndTurnConnectDiode();
    return reply;
  }

  String initiateTimer() {
    String reply = executeTurn();
    return reply;
  }

  String executeTurn() {
    hwController.resetTargets();
    if (!isMuted) {
      hwController.playTimer();
    }

    unsigned long startMs = millis();
    unsigned long endMs;
    int points = 0;

    while (millis() - startMs < Config::SHOOT_TIME_LIMIT) {
      points = hwController.handleTargetsAndReturnPoints();
      if (points > 0) {
        if (!isMuted) {
          hwController.playHit();
        }
        endMs = millis();
        break;
      }
    }

    if (points == 0) {
      endMs = millis();
      if (!isMuted) {
        hwController.playMiss();
      }
    }

    float elapsedTimeInSeconds = (endMs - startMs) / 1000.0;
    float remainingTimeInSeconds = max(0.0, (Config::SHOOT_TIME_LIMIT / 1000.0) - elapsedTimeInSeconds);
    int score = points * remainingTimeInSeconds;

    players[currentPlayerIndex].addScore(points);

    char result[64];
    snprintf(result, sizeof(result),
             "%s\n%d,%d,%d,%.3f",
             LAST_ROUND_SCORE,
             currentTurn,
             players[currentPlayerIndex].getId(),
             score,
             elapsedTimeInSeconds);

    if (currentPlayerIndex + 1 == numberOfPlayers) {
      currentTurn++;
      currentPlayerIndex = 0;
    } else {
      currentPlayerIndex++;
    }

    return String(result);
  }

  String endGame() {
    if (currentTurn == Config::ROUNDS_PER_GAME + 1) {
      if (!isMuted) {
        logGameScore();
        hwController.playWinner();
      }
    }
    return END_GAME;
  }

  String getAction(String text) {
    return TextUtils::getSpecificLine(text, 0);
  }

  void createPlayers(String playersCsv) {
    String* names = TextUtils::parseCSVToArray(playersCsv);

    numberOfPlayers = 0;
    while (names[numberOfPlayers] != "" && numberOfPlayers < Config::MAX_PLAYERS) {
      numberOfPlayers++;
    }

    players = new Player[numberOfPlayers];
    for (int i = 0; i < numberOfPlayers; i++) {
      players[i] = Player(names[i]);
    }
  }

  const char* generatePlayersCsv() {
    String csv = "id,name,score\n";

    for (int i = 0; i < numberOfPlayers; i++) {
      csv += String(players[i].getId()) + "," + players[i].getName() + "," + String(players[i].getScore()) + "\n";
    }
    return csv.c_str();
  }

  void logGameScore() {
    String logMessage;
    for (int i = 0; i < numberOfPlayers; i++) {
      logMessage += "Player " + String(players[i].getId()) + ": " + players[i].getName() + " - Score: " + String(players[i].getScore());
      if (i < numberOfPlayers - 1) {
        logMessage += "\n";
      }
    }
    DebugLogger::log("Game Score", logMessage);
  }

  void switchBuzzerState() {
    isMuted = !isMuted;
  }
};