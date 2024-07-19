#pragma once
#include "../HardwareController.h"
#include <WebSocket.h>
#include "Actions.h"
#include "Player.h"
#include "../util/StringUtils.h"
#include "../util/CsvUtils.h"

class GameController {

private:
  HardwareController hwController;
  WebSocket* ws;
  Player* players;
  int numberOfPlayers;
  int currentTurn = 1;
  int currentPlayerIndex = 0;
  const int TURN_TIME = 7000;
  const int TIMER_TIME = 3000;

public:
  GameController()
    : hwController(), ws(nullptr) {}

  void setWebSocket(WebSocket& webSocket) {
    ws = &webSocket;
  }
  void react(const String& message) {
    Serial.println(message);

    String action = getAction(message);
    String reply = generatePlayersCsv();

    if (action == START_GAME) {
      startGame(message);
      sendCurrentTurn();
    } else if (action == INITIATE_TIMER) {

      initiateTimer();

    } else if (action == MUTE_GAME) {

      switchBuzzerState();
    } else {
      const char* reply = "ERROR";
      ws->send(WebSocket::DataType::TEXT, reply, strlen(reply));
    }
  }

  void startGame(String message) {
    createPlayers(StringUtils::getSpecificLine(message, 1));
    String reply = SET_PLAYERS;
    reply += generatePlayersCsv();
    const char* replyChar = reply.c_str();
    ws->send(WebSocket::DataType::TEXT, replyChar, strlen(replyChar));
  }

  void sendCurrentTurn() {
    String turn = CURRENT_TURN;
    turn += "\n";
    turn += currentTurn;
    turn += ", ";
    turn += players[currentPlayerIndex].getId();
    const char* replyChar = turn.c_str();
    ws->send(WebSocket::DataType::TEXT, replyChar, strlen(replyChar));
  }

  void initiateTimer() {
    //start buzzer
    String reply = START_TIMER;
    const char* replyChar = reply.c_str();
    ws->send(WebSocket::DataType::TEXT, replyChar, strlen(replyChar));
    executeTurn();
  }

  void executeTurn() {
    Serial.println("execute turn");

    delay(TIMER_TIME);  // here play 3...2...1
    Serial.println("start");

    unsigned long startMs = millis();
    unsigned long endMs;
    int points = 0;

    while (millis() - startMs < TURN_TIME) {
      points = hwController.handleTargetsAndReturnPoints();
      if (points > 0) {
        //play buzzer
        endMs = millis();
        break;
      }
    }

    if (points == 0) {
      endMs = millis();
    }

    float elapsedTimeInSeconds = (endMs - startMs) / 1000.0;
    float remainingTimeInSeconds = max(0.0, (TURN_TIME / 1000.0) - elapsedTimeInSeconds);
    int score = points * remainingTimeInSeconds;

    char reply[64];  // Adjust size if needed
    snprintf(reply, sizeof(reply),
             "%s\n%d,%d,%d,%.3f",
             LAST_ROUND_SCORE,
             currentTurn,
             players[currentPlayerIndex].getId(),
             score,
             elapsedTimeInSeconds);

    ws->send(WebSocket::DataType::TEXT, reply, strlen(reply));

    if (currentPlayerIndex + 1 == numberOfPlayers) {
      currentTurn++;
      currentPlayerIndex = 0;
    } else {
      currentPlayerIndex++;
    }
    Serial.println(currentPlayerIndex);
  }

  String getAction(String text) {
    return StringUtils::getSpecificLine(text, 0);
  }

  void createPlayers(String playersCsv) {
    String* names = CsvUtils::parseCSVToArray(playersCsv);

    numberOfPlayers = 0;
    while (names[numberOfPlayers] != "" && numberOfPlayers < 10) {
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
  void switchBuzzerState() {
  }
};