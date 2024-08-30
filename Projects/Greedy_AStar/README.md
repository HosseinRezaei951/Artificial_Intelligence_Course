# Implementation of Hitori Game Solver Using A* and Greedy Algorithms

This project focuses on solving the Hitori game using two popular search algorithms: A* and Greedy. The objective is to eliminate certain cells in the grid while adhering to the rules of the Hitori puzzle. The implementation includes data structures and methods necessary for the algorithms to function effectively.

## Problem Definition

Hitori is a logic puzzle represented by an $$n \times n$$ grid filled with numbers. The goal is to eliminate cells such that:
1. No number appears more than once in any row or column.
2. Eliminated cells cannot be adjacent horizontally or vertically, but can be diagonally adjacent.
3. All non-eliminated cells must remain connected.

## Solution Approach

### A* Algorithm

The A* algorithm is a heuristic search algorithm that finds the least-cost path from a start node to a goal node. In this implementation, the A* algorithm operates as follows:

1. **Initialization**: Start with the initial state of the grid and check if it is the goal state.
2. **Priority Queue**: Use a priority queue to explore nodes based on their cost and heuristic values.
3. **Node Expansion**: Expand the node with the lowest cost from the priority queue. If it is a goal state, print the result and exit.
4. **Successor Generation**: Generate successor states by eliminating valid cells and applying heuristic functions.
5. **Cost Calculation**: Update the cost for each neighbor and push them into the priority queue.
6. **Repeat**: Continue the process until a solution is found or the queue is empty.

### Greedy Algorithm

The Greedy algorithm focuses on making the locally optimal choice at each stage with the hope of finding a global optimum. In this implementation, the Greedy algorithm functions as follows:

1. **Initialization**: Start with the initial state and check if it is the goal state.
2. **Priority Queue**: Push the initial state into the priority queue.
3. **Node Expansion**: Expand the node with the lowest heuristic value. If it is a goal state, print the result and exit.
4. **Successor Generation**: Generate successor states and apply heuristic functions to determine their values.
5. **Repeat**: Continue the process until a solution is found or the queue is empty.

## Implementation Details

The project consists of the following files:

1. **Source.cpp**: Contains the main implementation of the A* and Greedy algorithms for solving the Hitori puzzle.

2. **Data/sample2.txt**: A sample input file containing the initial state of the Hitori puzzle.

The `Node` struct represents the state of the Hitori grid, including the matrix, heuristic value, cost, and counters for cleared cells and children.

The `Hitori` class encapsulates the game logic and provides methods for:
- Initializing the game state from an input file.
- Printing the current state of the grid.
- Implementing the A* and Greedy algorithms.
- Generating successor states.
- Checking the validity of a state.

## How to Use

1. Compile the `Source.cpp` file using a C++ compiler.
2. Run the compiled executable.
3. The program will read the initial state from the `Data/sample2.txt` file and print the original grid.
4. The A* and Greedy algorithms will be executed sequentially, and the results will be printed for each algorithm.

The output will display the solved grid along with additional information such as the number of nodes generated, the number of children for the current node, and the number of cleared cells.

## Analysis

The A* and Greedy algorithms have distinct characteristics and performance in solving the Hitori puzzle:

- **A*** guarantees finding the least-cost path to the solution due to its use of both cost and heuristic values. However, it may require significant memory to maintain the priority queue.

- **Greedy** focuses solely on the heuristic value, which can lead to faster solutions in some cases but may not always yield the optimal solution.

The choice of algorithm depends on the specific requirements of the problem, such as the size of the grid, the complexity of the puzzle, and the desired solution quality.