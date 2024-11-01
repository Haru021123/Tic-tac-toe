Autonomous Tic Tac Toe Playing Robot Arm
Project Overview
This project is a fascinating blend of artificial intelligence, robotics, and software development, aimed at creating an autonomous Tic Tac Toe playing robot arm. The robot is capable of playing Tic Tac Toe against human players in real-time, showcasing the integration of various technologies to achieve a seamless gaming experience.

Key Components:
App Development: A user-friendly mobile application developed using React Native and Echo. This app allows players to input their moves in real-time.

Real-Time Server Communication: A server designed to handle incoming moves from the app. It processes these moves instantaneously, ensuring the game progresses smoothly.

Minimax AI Algorithm: The heart of the project's intelligence. The Minimax algorithm analyzes the game state and determines the optimal move for the robot, simulating human-like strategic thinking.

ESP8266 NodeMCU Integration: This microcontroller receives data from the server over WiFi, enabling wireless communication between the server and the robot.

Dobot Magician Lite: The robotic arm that physically interacts with the Tic Tac Toe board, making moves as directed by the AI.

How It Works:
Move Collection: Players make their moves using the mobile app. These moves are sent to the server in real-time.

AI Processing: The server, upon receiving a move, uses the Minimax algorithm to compute the best possible response move for the robot.

Data Transmission: The computed move is sent to the ESP8266 NodeMCU, which then relays the move to the Dobot Magician Lite.

Robot Action: The Dobot Magician Lite executes the move, placing its marker on the physical Tic Tac Toe board, thus completing the cycle.

Future Enhancements:
Multi-Board Integration: The full project aims to expand this setup to four game boards, allowing up to four players to compete against the robot simultaneously.

Enhanced AI: Further optimization of the AI algorithm to improve decision-making speed and accuracy.

Development and Contribution:
This project was developed at Inker Robotics in Thrissur, Kerala, from October to November 2024. The work involved a collaborative effort to seamlessly integrate hardware and software, achieving a fully functional prototype.

Setup and Usage
Prerequisites
Software: React Native, Echo, Dobot Studio, Node.js, Arduino IDE

Hardware: ESP8266 NodeMCU, Dobot Magician Lite

Installation
Clone the Repository:

sh

Copy
git clone https://github.com/YourUsername/TicTacToeRobotArm.git
cd TicTacToeRobotArm
Install Dependencies:

sh

Copy
npm install
Start the Server:

sh

Copy
node server.js
Running the App
Start the React Native App:

sh

Copy
npx react-native run-android
# or
npx react-native run-ios
Configure the ESP8266 NodeMCU:

Upload the Arduino sketch to the ESP8266 to handle WiFi communication and move processing.

Ensure the ESP8266 is connected to the same network as the server.

Control the Dobot Magician Lite:

Use Dobot Studio to establish a serial connection with the Dobot Magician Lite.

Ensure the Dobot Magician Lite executes moves based on the AI's decisions.

Contributors
Harman - Haru021122
Anagha - AnuTris
