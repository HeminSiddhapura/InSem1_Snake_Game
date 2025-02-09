# InSem1_Snake_Game


Functions:
•	InitializeGame(): Sets up initial game state (snake, food, score, etc.).
•	DrawGameBoard(): Renders the game board, snake, and food.
•	ProcessInput(): Handles keyboard input to change the snake's direction.
•	UpdateGameState(): Moves the snake, handles collisions, and checks for food consumption.
•	SetCursorPosition(): Updates cursor position for smooth rendering.
•	SetColor(): Changes text color in the console.

Game Logic:
The snake moves in the chosen direction, and the tail follows the head's previous position.
Collisions with walls or the snake's tail end the game.
Eating food increases the score and grows the tail.

Game Movement:
We Have used the Most common method of directing The character (W,A,S,D)
W:- UP
A:- LEFT
S:- DOWN
D:-RIGHT

Game Setup:
The game initializes the snake in the middle of the board and places a randomly generated food item.
Initial variables like the snake's position, tail length, and direction are set

Scoring and Ranking:
Players earn 10 points for every piece of food eaten.
The final score determines the player's rank:

Beginner: < 50
Intermediate: 50–99
Expert: 100–199
Legend: ≥ 200

Limitations
The game is designed for Windows due to the use of windows.h.
