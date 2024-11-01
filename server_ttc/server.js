const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 3000;

app.use(cors());
app.use(bodyParser.json());

let latestMove = null;

// Endpoint to update the move from the app
app.post('/move', (req, res) => {
  const { move } = req.body;
  console.log(`Received move: ${move}`);
  latestMove = move;  // Store the latest move
  res.send(`Move updated to: ${move}`);
});

// Endpoint for ESP8266 to poll the latest move
app.get('/move', (req, res) => {
  res.json({ move: latestMove });  // Send the latest move in JSON format
});

// New endpoint to handle game restart
app.post('/restart', (req, res) => {
  latestMove = null;  // Reset the latest move
  console.log('Game restarted, latest move reset');
  res.send('Game has been restarted');
});

app.listen(port, () => {
  console.log(`Server is running at http://0.0.0.0:${port}`);
});
