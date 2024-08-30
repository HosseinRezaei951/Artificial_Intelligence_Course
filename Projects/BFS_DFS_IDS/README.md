# Hitori Game Solver using BFS, DFS, and IDS Algorithms

This project implements a solution for the Hitori game using three different algorithms: Breadth-First Search (BFS), Depth-First Search (DFS), and Iterative Deepening Search (IDS). The goal is to find a valid solution for the Hitori puzzle by eliminating certain cells while satisfying the game's rules.

## Problem Definition

Hitori is a logic puzzle where an $$n \times n$$ grid is filled with numbers. The objective is to eliminate certain cells (black cells) such that:
1. No number appears more than once in any row or column.
2. Eliminated cells cannot be adjacent horizontally or vertically (but can be diagonally adjacent).
3. All non-eliminated (white) cells must be connected.

## Solution Approach

### Breadth-First Search (BFS)

BFS is a graph traversal algorithm that explores all the neighboring nodes at the present depth before moving on to the nodes at the next depth level. In the context of the Hitori game, BFS works as follows:

1. **Initialize**: Start with the initial state (the original grid).
2. **Enqueue**: Add the initial state to the queue.
3. **Dequeue**: Remove the first state from the queue.
4. **Check Goal**: If the dequeued state is a goal state (satisfies all the rules), print the result and exit.
5. **Generate Successors**: If the dequeued state is not a goal, find all possible successor states by eliminating cells that satisfy the rules.
6. **Enqueue Successors**: Add the successor states to the queue.
7. **Repeat**: Repeat steps 3-6 until a goal state is found or the queue is empty (no solution exists).

### Depth-First Search (DFS)

DFS is a graph traversal algorithm that explores as far as possible along each branch before backtracking. In the context of the Hitori game, DFS works as follows:

1. **Initialize**: Start with the initial state (the original grid).
2. **Push**: Add the initial state to the stack.
3. **Pop**: Remove the top state from the stack.
4. **Check Goal**: If the popped state is a goal state (satisfies all the rules), print the result and exit.
5. **Generate Successors**: If the popped state is not a goal, find all possible successor states by eliminating cells that satisfy the rules.
6. **Push Successors**: Add the successor states to the stack.
7. **Repeat**: Repeat steps 3-6 until a goal state is found or the stack is empty (no solution exists).

### Iterative Deepening Search (IDS)

IDS is a state space search strategy that combines the benefits of Depth-Limited Search (DLS) and BFS. It performs a series of DLS searches with increasing depth limits until a goal state is found. In the context of the Hitori game, IDS works as follows:

1. **Initialize**: Start with the initial state (the original grid).
2. **Iterate**: Perform a series of DLS searches with increasing depth limits.
3. **DLS**: In each iteration, perform a DLS search starting from the initial state:
   - **Check Goal**: If the current state is a goal state (satisfies all the rules), print the result and exit.
   - **Push**: Add the current state to the stack.
   - **Pop**: Remove the top state from the stack.
   - **Generate Successors**: If the popped state is not a goal, find all possible successor states by eliminating cells that satisfy the rules.
   - **Push Successors**: Add the successor states to the stack.
   - **Repeat**: Repeat the above steps until a goal state is found, the stack is empty, or the depth limit is reached.
4. **Increment Limit**: Increase the depth limit for the next iteration.
5. **Repeat**: Repeat steps 2-4 until a goal state is found or the depth limit reaches the maximum (no solution exists).

## Implementation Details

The project consists of the following files:

1. **Source.cpp**: Contains the main implementation of the BFS, DFS, and IDS algorithms for solving the Hitori puzzle.

2. **Data/sample2.txt**: A sample input file containing the initial state of the Hitori puzzle.

The `Node` struct is used to represent the state of the Hitori grid, including the matrix itself and various counters for tracking the progress of the algorithms.

The `Hitori` class encapsulates the game logic and provides methods for:
- Initializing the game state from an input file
- Printing the current state of the grid
- Implementing the BFS, DFS, and IDS algorithms
- Generating successor states
- Checking the validity of a state

## How to Use

1. Compile the `Source.cpp` file using a C++ compiler.
2. Run the compiled executable.
3. The program will read the initial state from the `Data/sample2.txt` file and print the original grid.
4. The BFS, DFS, and IDS algorithms will be executed sequentially, and the results will be printed for each algorithm.

The output will display the solved grid, along with additional information such as the number of nodes generated, the number of children for the current node, and the number of cleared cells.

## Analysis

The BFS, DFS, and IDS algorithms have different characteristics and performance in solving the Hitori puzzle:

- **BFS** explores all possible states at the current depth before moving to the next depth level. It guarantees finding the shortest path to the solution (if it exists) but may require more memory due to the queue.

- **DFS** explores as far as possible along each branch before backtracking. It may find a solution faster than BFS but is not guaranteed to find the shortest path. DFS may also get stuck in infinite loops if not implemented carefully.

- **IDS** combines the benefits of DLS and BFS by performing a series of DLS searches with increasing depth limits. It ensures that all states up to a certain depth are explored before moving to the next depth level. IDS is complete and optimal (finds the shortest path) but may be slower than BFS due to the repeated searches.

The choice of algorithm depends on factors such as the size of the grid, the complexity of the puzzle, and the available memory and time constraints.