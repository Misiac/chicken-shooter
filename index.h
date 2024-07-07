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
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
      }
      .gameScreen {
        display: none;
        color: #333; /* Dark gray text */
      }
      .title {
        padding-top: 50px;
        font-size: 5rem;
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
      .player-turn {
        font-size: 5rem;
        margin: 20px 0;
        color: #ff6347; /* Tomato red */
      }
      .start-button,
      .shoot-button {
        background-color: #4caf50; /* Green */
        color: #fff;
        border: none;
        padding: 15px 30px; /* Increased size */
        font-size: 40px;
        cursor: pointer;
        border-radius: 5px;
        transition: background-color 0.3s ease;
        margin-top: 20px;
      }
      .start-button:hover,
      .shoot-button:hover {
        background-color: #45a049; /* Darker green on hover */
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
      .score-table {
        margin-top: 20px;
        border-collapse: collapse;
        width: 80%;
        max-width: 600px;
      }
      .score-table th,
      .score-table td {
        border: 1px solid #ddd;
        padding: 8px;
        text-align: center;
      }
      .score-table th {
        background-color: #f2f2f2; /* Light gray */
        color: #333;
      }
      .header {
        display: none;
        justify-content: space-between;
        align-items: flex-start; /* Align items to the top */
        padding: 10px;
      }
      .connected {
        display: flex;
        align-items: center;
        font-size: 20px;
        font-weight: bold;
      }
      .connected-circle {
        width: 15px;
        height: 15px;
        background-color: green;
        border-radius: 50%;
        margin-right: 5px;
      }
      .mute-game {
        color: #555; /* Dark gray text */
        font-size: 16px;
        font-weight: bold;
        margin-right: 10px;
        margin-top: 10px;
        align-self: flex-start;
      }
      .round-title {
        font-size: 4rem;
        margin: 20px 0;
        font-weight: bold;
      }
      .timer,
      .result {
        font-size: 5rem;
        margin: 20px 0;
      }
      .total-label {
        font-weight: bold;
      }
    </style>
  </head>
  <body>
    <div class="header">
      <div class="connected" id="connected">
        <div class="connected-circle"></div>
        Connected
      </div>
      <div class="mute-game">Mute Game</div>
    </div>
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
    <div class="gameScreen" id="gameScreen">
      <div class="round-title">ROUND 1</div>
      <div class="player-turn" id="playerTurn">Michal, your turn</div>
      <button class="shoot-button" id="startTimer" onclick="startTimer()">
        Start Timer
      </button>
      <div class="timer" id="timer">3</div>
      <div class="result" id="result">SCORE / TOO BAD</div>

      <table class="score-table">
        <thead>
          <tr id="headerRow">
            <th></th>
          </tr>
        </thead>
        <tbody id="scoreTableBody"></tbody>
      </table>
    </div>

    <script>
      //ACTIONS
      const START_GAME = "START GAME"; // players names in csv
      const INITIATE_TIMER = "INITIATE_TIMER"; // INITIATE_TIMER, PLAYERNAME, ROUNDNR
      const MUTE_GAME = "MUTE GAME"; //mutes buzzer

      //RESPONSE ACTIONS
      const SET_PLAYERS = "SET PLAYERS"; // SET PLAYERS /n id,name,score
      const LAST_ROUND_SCORE = "LAST ROUND SCORE"; // LAST ROUND SCORE /n playedId, roundScore, timeBonus
      const START_TIMER = "START TIMER";

      var ws;
      var wsm_max_len = 4096;

      var playerNames = [];
      var players = [];
      var roundNr = 1;

      function startGame() {
        var playerNameFields = ["player1", "player2", "player3", "player4"];

        playerNameFields.forEach(function (playerName) {
          var playerNameValue = document.getElementById(playerName).value;
          if (playerNameValue) {
            playerNames.push(playerNameValue);
          }
        });

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
        document.getElementById("mainScreen").style.display = "none";
        document.getElementById("gameScreen").style.display = "flex";
        document.querySelector(".header").style.display = "flex";

        let messageToSend =
          START_GAME + "\n" + playerNames.map((name) => name).join(",") + "\n";

        // Log the message to console for debugging
        console.log("Sending message:");
        console.log(messageToSend);

        // Send the message via WebSocket
        ws.send(messageToSend);
      }

      function ws_onclose() {
        ws.onopen = null;
        ws.onclose = null;
        ws.onmessage = null;
        ws = null;
      }

      function ws_onmessage(message) {
        response = message.data || window.event;
        console.log(message.data);
        let action = getAction(response);

        if (action == SET_PLAYERS) {
          setPlayers(response);
          console.log(players);
        }
      }

      function setPlayers(response) {
        let lines = response.split(/\r?\n/);
        lines.shift();
        lines.shift();

        lines.forEach(function (line) {
          if (line.trim() !== "") {
            let player = line.split(",");
            players.push({
              id: player[0].trim(),
              name: player[1].trim(),
              score: parseInt(player[2].trim(), 10),
            });
          }
        });
        generateTable();
      }

      function getAction(response) {
        let lines = response.split(/\r?\n/);
        return lines[0];
      }

      function startTimer() {
        ws.send("TEST" + "\n");
      }

      function generateTable() {
        const headerRow = document.getElementById("headerRow");
        const scoreTableBody = document.getElementById("scoreTableBody");

        headerRow.innerHTML = "<th></th>";
        scoreTableBody.innerHTML = "";

        players.forEach((player) => {
          let th = document.createElement("th");
          th.textContent = player.name;
          headerRow.appendChild(th);
        });

        for (let round = 1; round <= 5; round++) {
          let tr = document.createElement("tr");
          let tdRound = document.createElement("td");
          tdRound.textContent = `Round ${round}`;
          tr.appendChild(tdRound);

          players.forEach((player) => {
            let td = document.createElement("td");
            td.id = `${player.name.toLowerCase()}Round${round}`;
            tr.appendChild(td);
          });

          scoreTableBody.appendChild(tr);
        }

        let totalRow = document.createElement("tr");
        let tdTotalLabel = document.createElement("td");
        tdTotalLabel.textContent = "Total";
        tdTotalLabel.classList.add("total-label");
        totalRow.appendChild(tdTotalLabel);

        players.forEach((player) => {
          let tdTotal = document.createElement("td");
          tdTotal.id = `${player.name.toLowerCase()}Total`;
          totalRow.appendChild(tdTotal);
        });

        scoreTableBody.appendChild(totalRow);
      }
    </script>
  </body>
</html>

)=====";