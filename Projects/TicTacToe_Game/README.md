# 3D Tic-Tac-Toe with Minimax and Alpha-Beta Pruning

## Project Overview

This project implements a 3D version of the classic Tic-Tac-Toe game using a 4x4x4 grid. The goal is to align four markers in a row, column, or diagonal, either within a single 4x4 grid or across multiple grids. The game includes an AI opponent that makes decisions using the Minimax algorithm enhanced by Alpha-Beta pruning.

## Features

- **3D Game Grid**: A 4x4x4 three-dimensional grid is used for the game.
- **Game Rules**:
  - Players take turns placing their markers on any empty cell.
  - A player wins by aligning four markers in a row, column, or diagonal.
  - If the grid is filled and no player has aligned four markers, the game ends in a draw.
  - If a player takes more than 60 seconds to make a move, they lose the game.
- **AI Implementation**:
  - The AI uses the Minimax algorithm to evaluate the best possible moves.
  - Alpha-Beta pruning is used to optimize the Minimax algorithm by eliminating unnecessary branches in the search tree.

## Implementation Details

### Minimax Algorithm

The Minimax algorithm is a recursive search algorithm used for decision-making in turn-based games like Tic-Tac-Toe. It operates by simulating all possible moves from the current state, evaluating the outcome of each move, and selecting the move that maximizes the AI's chances of winning (for the maximizing player) while minimizing the opponent's chances (for the minimizing player).

- **Maximizing Player**: The AI acts as the maximizing player, aiming to maximize its score by choosing the best possible move.
- **Minimizing Player**: The opponent (or another instance of the AI) acts as the minimizing player, aiming to minimize the AI's score by choosing the best possible counter-move.

The algorithm evaluates the game state by assigning a score based on the likelihood of winning or losing. The recursion continues until it reaches a terminal state (win, lose, draw, or depth limit), where it then backtracks, selecting the optimal move for the AI.

### Alpha-Beta Pruning

Alpha-Beta pruning is an optimization technique for the Minimax algorithm that reduces the number of nodes evaluated in the search tree. It does this by keeping track of two values during the search:

- **Alpha**: The best score that the maximizing player can guarantee at the current level or above.
- **Beta**: The best score that the minimizing player can guarantee at the current level or above.

During the search, if the algorithm finds a branch where the minimizer's score is lower than the maximizer's alpha (i.e., `beta <= alpha`), it prunes that branch, meaning it stops exploring that branch because it won't affect the final decision. This significantly reduces the computation time and allows the algorithm to search deeper within the same time constraints.

### `Best_Action` Function

The core of the AI's decision-making process is encapsulated in the `Best_Action` function. This function generates all possible moves from the current game state and evaluates them using the Minimax algorithm with Alpha-Beta pruning. It then selects the move with the highest value as the optimal choice.

## Results

The AI's performance was tested in three scenarios:

1. **Minimax AI vs. Random Player**:
   - When the Minimax AI starts first, it wins against the Random Player.
   - When the Random Player starts first, the Minimax AI still wins.

2. **Minimax AI vs. Minimax AI with Variable Depth**:
   - The depth starts at 1 and increases by 1 after every 5 moves.
   - The AI starting first wins.

3. **Minimax AI vs. Minimax AI with Fixed Depth**:
   - A fixed depth of 2 is used to avoid stack overflow due to the high computational load.
   - The AI starting first wins.

## How to Run

1. Compile the `Source.cpp` file using any C++ compiler.
2. Run the compiled program and follow the on-screen instructions to play against the AI or to watch the AI play against itself or a random player.

## Conclusion

This project successfully demonstrates the implementation of the Minimax algorithm with Alpha-Beta pruning in a 3D Tic-Tac-Toe game. The AI performs well against random players and can compete effectively with another Minimax AI.
