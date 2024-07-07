#pragma once
#include "../HardwareAggregator.h"
#include <WebSocket.h>
#include "Actions.h"
#include "Player.h"
#include "../util/StringUtils.h"

class GameController {

private:
  HardwareAggregator& hardware;
  WebSocket* ws;
  Player* players;
  int numberOfPlayers;

public:
  GameController(HardwareAggregator& hardware)
    : hardware(hardware), ws(nullptr) {}

  void setWebSocket(WebSocket& webSocket) {
    ws = &webSocket;
  }

  void react(const String& message) {
    String action = getAction(message);

    if (action == START_GAME) {
      //port to functions
      String namesLine = StringUtils::getSpecificLine(message, 1);

      createPlayers(namesLine);
      String reply = SET_PLAYERS;
      reply += generatePlayersCsv();

      const char* replyChar = reply.c_str();
      ws->send(WebSocket::DataType::TEXT, replyChar, strlen(replyChar));

    } else if (action == INITIATE_TIMER) {

    } else if (action == MUTE_GAME) {

      switchBuzzerState();
    } else {
      const char* reply = "ERROR";
      ws->send(WebSocket::DataType::TEXT, reply, strlen(reply));
    }
  }

  String getAction(String text) {
    return StringUtils::getSpecificLine(text, 0);
  }

  void createPlayers(String playersCsv) {
    int numberOfPlayers = 0;
    for (int i = 0; i < playersCsv.length(); i++) {
      if (playersCsv.charAt(i) == ',') {
        numberOfPlayers++;
      }
    }
    numberOfPlayers++;

    int currentIndex = 0;
    int previousIndex = 0;
    for (int i = 0; i < playersCsv.length(); i++) {
      if (playersCsv.charAt(i) == ',' || i == playersCsv.length() - 1) {
        String playerName = playersCsv.substring(previousIndex, i);  //todo
        Player currentPlayer(playerName);
        players[currentIndex] = currentPlayer;

        Serial.println(players[currentIndex].getName());

        currentIndex++;
        previousIndex = i + 1;
      }
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