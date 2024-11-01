#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "INKER_ROBOTICS.....!!!!!";
const char* password = "Inker.Robotics@2022";
const char* serverUrl = "http://192.168.18.168:3000/move";

WiFiClient wifiClient;
String lastMove = "";  // Store the last received move
bool gameReset = false; // Flag to indicate if the game was just reset

const int PLAYER = -1; // Human player
const int AI = 1; // AI or computer
int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Board positions from 0 to 8
bool playerMoved = false; // Track if the player has made a move

void setup() {
  Serial.begin(9600);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, serverUrl);
    int httpResponseCode = http.GET();

    if (httpResponseCode == HTTP_CODE_OK) {
      String currentMoveJson = http.getString();

      // Deserialize JSON
      StaticJsonDocument<200> doc;
      deserializeJson(doc, currentMoveJson);
      String currentMoveStr = doc["move"].as<String>();

      // Ignore if the move is null or empty (indicating a reset state from the server)
      if (currentMoveStr == "null" || currentMoveStr.isEmpty()) {
        Serial.println("Waiting for a new move...");
      } 
      // Ensure move is valid and only process if it's a new move
      else if (currentMoveStr != lastMove) {
        if (gameReset) {
          // Clear the gameReset flag when a fresh move arrives
          gameReset = false;
        }
        int playerMove = currentMoveStr.toInt();

        // Debug: Display received move
        Serial.print("Converted player move: ");
        Serial.println(playerMove);

        // Validate and process the player move
        if (playerMove >= 0 && playerMove < 9 && board[playerMove] == 0) {
          board[playerMove] = PLAYER;  // Mark player's move on the board
          lastMove = currentMoveStr;  // Update lastMove to the current move
          playerMoved = true;  // Indicate that a valid move was made

          // Check for a winner after player's move
          int winner = checkWinner();
          if (winner != 0 || !isMovesLeft()) {
            printResult(winner);
            resetBoard(); // Reset the board and clear lastMove for a new game
            return;
          }

          // AI makes its move if player has moved
          if (playerMoved) {
            int aiMove = findBestMove();
            board[aiMove] = AI; // Mark AI's move
            Serial.print("AI chooses position: ");
            Serial.println(aiMove);

            // Check for a winner after AI's move
            winner = checkWinner();
            if (winner != 0 || !isMovesLeft()) {
              printResult(winner);
              resetBoard(); // Reset the board and clear lastMove for a new game
            }

            playerMoved = false; // Reset playerMoved flag after AI's turn
          }
        } else {
          Serial.println("Invalid move! Position already taken or out of bounds.");
        }
      }
    } else {
      Serial.print("Error in HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Wi-Fi disconnected");
  }

  delay(2000);
}

// Helper functions
void resetBoard() {
  for (int i = 0; i < 9; i++) board[i] = 0;
  Serial.println("Game reset. Enter a move (0-8) to start:");
  lastMove = ""; // Clear lastMove after game reset
  gameReset = true; // Set gameReset to true to ignore any lingering moves
}

bool isMovesLeft() {
  for (int i = 0; i < 9; i++) {
    if (board[i] == 0) return true;
  }
  return false;
}

int checkWinner() {
  int winPatterns[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
                            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
                            {0, 4, 8}, {2, 4, 6} };          // Diagonals
  for (int i = 0; i < 8; i++) {
    if (board[winPatterns[i][0]] == board[winPatterns[i][1]] &&
        board[winPatterns[i][1]] == board[winPatterns[i][2]] &&
        board[winPatterns[i][0]] != 0) {
      return board[winPatterns[i][0]];
    }
  }
  return 0; // No winner yet
}

int minimax(int depth, bool isAI) {
  int score = checkWinner();
  if (score == AI) return 10 - depth;
  if (score == PLAYER) return depth - 10;
  if (!isMovesLeft()) return 0;

  int bestScore = isAI ? -1000 : 1000;
  for (int i = 0; i < 9; i++) {
    if (board[i] == 0) {
      board[i] = isAI ? AI : PLAYER;
      int currentScore = minimax(depth + 1, !isAI);
      board[i] = 0;
      bestScore = isAI ? max(bestScore, currentScore) : min(bestScore, currentScore);
    }
  }
  return bestScore;
}

int findBestMove() {
  int bestMove = -1;
  int bestValue = -1000;
  for (int i = 0; i < 9; i++) {
    if (board[i] == 0) {
      board[i] = AI;
      int moveValue = minimax(0, false);
      board[i] = 0;
      if (moveValue > bestValue) {
        bestMove = i;
        bestValue = moveValue;
      }
    }
  }
  return bestMove;
}

void printResult(int winner) {
  if (winner == PLAYER) Serial.println("Player wins!");
  else if (winner == AI) Serial.println("AI wins!");
  else Serial.println("It's a draw!");
  Serial.println();
}
