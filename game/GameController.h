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
    Serial.println(message);

    String action = getAction(message);
    String reply = generatePlayersCsv();

    if (action == START_GAME) {

      createPlayers("TODO");
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
    String mock[] = { "Michal", "Hania" };  // todo later when i dont have depression

    numberOfPlayers = sizeof(mock) / sizeof(String);

    players = new Player[numberOfPlayers];
    for (int i = 0; i < numberOfPlayers; i++) {
      players[i] = Player(mock[i]);
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