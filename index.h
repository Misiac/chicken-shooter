const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Chicken Shooter Game</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      body {
        font-family: Arial, sans-serif;
        background-color: #ffefd5; /* Light cream */
        text-align: center;
        margin: 0;
        padding: 0;
      }
      .mainScreen,
      .gameScreen {
        margin-top: 50px;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
      }
      .gameScreen {
        display: none;
      }
      .title {
        font-size: 3rem;
        font-weight: bold;
        color: #ff6347; /* Tomato red */
        text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
        margin-bottom: 30px;
      }
      .player-input {
        margin-bottom: 15px;
        padding: 10px;
        font-size: 16px;
        width: 80%;
        max-width: 300px;
      }
      .start-button {
        background-color: #4caf50; /* Green */
        color: #fff;
        border: none;
        padding: 10px 20px;
        font-size: 18px;
        cursor: pointer;
        border-radius: 5px;
        transition: background-color 0.3s ease;
      }
      .start-button:hover {
        background-color: #45a049; /* Darker green */
      }
      .rules {
        margin-top: 20px;
        text-align: left;
        padding: 20px;
        background-color: #fff;
        border-radius: 8px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        max-width: 80%;
      }
      .rules h2 {
        color: #ff6347; /* Tomato red */
        font-size: 24px;
        margin-bottom: 10px;
      }
      .rules p {
        font-size: 18px;
        line-height: 1.6;
        margin-bottom: 10px;
      }
    </style>
  </head>
  <body>
    <!-- MAIN SCREEN -->
    <div class="mainScreen" id="mainScreen">
      <div class="title">Chicken Shooter</div>

      <div>
        <input
          type="text"
          id="player1"
          class="player-input"
          placeholder="Player 1 Name"
        />
      </div>
      <div>
        <input
          type="text"
          id="player2"
          class="player-input"
          placeholder="Player 2 Name"
        />
      </div>
      <div>
        <input
          type="text"
          id="player3"
          class="player-input"
          placeholder="Player 3 Name"
        />
      </div>
      <div>
        <input
          type="text"
          id="player4"
          class="player-input"
          placeholder="Player 4 Name"
        />
      </div>
      <button class="start-button" onclick="startGame()">Start Game</button>

      <div class="rules">
        <h2>Game Rules</h2>
        <p>
          Chicken Shooter is a target shooting game where players aim to score
          points by hitting various targets.
        </p>
        <p>
          Each round, players take turns shooting, with points awarded based on
          the target's score multiplied by the remaining time (from start).
        </p>
        <p>
          To initiate their turn, a player must click "Shoot" to start the
          countdown timer (3... 2... 1...).
        </p>
        <p>
          The player has 7 seconds to take their shot starting with an unloaded
          Nerf gun.
        </p>
        <p>
          A player's turn ends either by hitting the target or running out of
          time.
        </p>
        <p>
          Shooting before the countdown starts results in a penalty of -10
          points.
        </p>
      </div>
    </div>
    <!-- GAME SCREEN -->

    <div class="gameScreen" id="gameScreen">ssdsd</div>

    <script>
      var ws;
      var wsm_max_len = 4096;
      var players = [];

      function startGame() {
        var playerNames = ["player1", "player2", "player3", "player4"];
        var playerId = 1;

        playerNames.forEach(function (playerName) {
          var playerNameValue = document.getElementById(playerName).value;
          if (playerNameValue) {
            var player = {
              id: playerId++,
              name: playerNameValue,
              score: 0,
            };
            players.push(player);
          }
        });
        console.log(players);

        openWebSocket();
      }

      function openWebSocket() {
        if (ws == null) {
          ws = new WebSocket("ws://" + window.location.host + ":81");
          ws.onopen = ws_onopen;
          ws.onclose = ws_onclose;
          ws.onmessage = ws_onmessage;
        } else {
          ws.close();
        }
      }

      function ws_onopen() {
        // Hide the mainScreen div
        document.getElementById("mainScreen").style.display = "none";

        // Make the gameScreen div visible
        document.getElementById("gameScreen").style.display = "block";

        ws.send("TEST" + "\n");
      }

      // function update_text(text) {
      //   var chat_messages = document.getElementById("chat-messages");
      //   chat_messages.innerHTML +=
      //     '<div style="width:100%;overflow: auto;">' + text + "</div>";
      //   chat_messages.scrollTop = chat_messages.scrollHeight;
      // }

      // function send_onclick() {
      //   if (ws != null) {
      //     var message = document.getElementById("message").value;

      //     if (message) {
      //       document.getElementById("message").value = "";
      //       ws.send(message + "\n");
      //       update_text('<p class="message-sent">' + message + "</p>");
      //     }
      //   }
      // }

      function ws_onclose() {
        ws.onopen = null;
        ws.onclose = null;
        ws.onmessage = null;
        ws = null;
      }

      function ws_onmessage(e_msg) {
        e_msg = e_msg || window.event;
        console.log(e_msg.data);
      }
    </script>
  </body>
</html>
)=====";