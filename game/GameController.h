#pragma once
#include "../HardwareController.h"
#include <WebSocket.h>
#include "Actions.h"
#include "Player.h"
#include "../util/StringUtils.h"
#include "../util/CsvUtils.h"

class GameController {

private:
  HardwareController& hwController;
  WebSocket* ws;
  Player* players;
  int numberOfPlayers;
  int currentTurn = 1;
  int currentPlayerIndex = 0;
  const int TURN_TIME = 7000;

public:
  GameController(HardwareController& hwController)
    : hwController(hwController), ws(nullptr) {}

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

      int startMs = millis();
    while (millis() - startMs < TURN_TIME) {

      int points = hwController.handleTargetsAndReturnPoints();
      if (points > 0) {
        //play buzzer
        //send info to front
        String reply = "JAAAAAA";                                           //debug
        const char* replyChar = reply.c_str();                              //debug
        ws->send(WebSocket::DataType::TEXT, replyChar, strlen(replyChar));  //debug
        break;
      }
    }
    //time's up, play negative buzzer and send 0 score to front
    String reply = "NICHT";                                             //debug
    const char* replyChar = reply.c_str();                              //debug
    ws->send(WebSocket::DataType::TEXT, replyChar, strlen(replyChar));  //debug
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