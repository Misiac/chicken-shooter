const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Chicken Shooter Game</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
  body {
    font-family: Arial, sans-serif;
    background-color: #E1EFEF;
    text-align: center;
  }
  .container {
    margin-top: 50px;
  }
  .logo {
    margin-bottom: 30px;
  }
  .player-input {
    margin-bottom: 10px;
  }
  .start-button {
    background-color: #007bff;
    color: #fff;
    border: none;
    padding: 10px 20px;
    font-size: 18px;
    cursor: pointer;
  }
</style>
</head>
<body>
  <div class="container">
    <img src="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 200 50'%3E%3Ctext x='0' y='35' font-family='Arial, sans-serif' font-size='36' font-weight='bold' fill='%23007bff'%3EChicken Shooter%3C/text%3E%3C/svg%3E" alt="Chicken Shooter Logo">

    <div>
      <input type="text" id="player1" class="player-input" placeholder="Player 1 Name">
    </div>
    <div>
      <input type="text" id="player2" class="player-input" placeholder="Player 2 Name">
    </div>
    <div>
      <input type="text" id="player3" class="player-input" placeholder="Player 3 Name">
    </div>
    <div>
      <input type="text" id="player4" class="player-input" placeholder="Player 4 Name">
    </div>
    <button class="start-button" onclick="startGame()">Start Game</button>
  </div>

  <script>
    function startGame() {
      var player1 = document.getElementById("player1").value;
      var player2 = document.getElementById("player2").value;
      var player3 = document.getElementById("player3").value;
      var player4 = document.getElementById("player4").value;
      
      // You can send the player names to your Arduino server via WebSocket
      // Example: ws.send(JSON.stringify({ player1, player2, player3, player4 }));
      // Replace ws with your WebSocket object.
    }
  </script>
</body>
</html>
)=====";
