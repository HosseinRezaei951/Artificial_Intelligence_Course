# Implementation of Hitori Game and Its Solution Using Hill Climbing Algorithms, Simulated Annealing, and CSP

This project is part of the **Artificial Intelligence Course** and focuses on implementing the Hitori game—a Japanese logic puzzle—along with various algorithms to find its solution. The algorithms explored in this project include Hill Climbing, Simulated Annealing, and Constraint Satisfaction Problem (CSP) with a backtracking approach. The performance and effectiveness of these algorithms are analyzed based on their ability to solve the Hitori puzzle.

## Problem Definition

Hitori is a logic puzzle consisting of an \(n \times n\) grid filled with numbers. The objective is to eliminate certain cells so that the following conditions are met:
1. No number appears more than once in any row or column.
2. Eliminated cells (black cells) cannot be adjacent horizontally or vertically, although they can be diagonally adjacent.
3. All non-eliminated (white) cells must be connected, meaning that no white cell can be isolated by black cells.

### Sample Hitori Puzzle

A sample Hitori grid is illustrated below (for reference, you can visualize this as a grid filled with numbers). The aim is to eliminate cells to satisfy the conditions mentioned above.

## Solution Approach

### Hill Climbing Algorithm

The Hill Climbing algorithm is a heuristic-based search method. It begins by generating a random solution (initial state) and then iteratively attempts to improve it by moving to neighboring states. The process involves the following steps:

1. **Neighbor Generation**: For each cell in the grid, toggle its state (from eliminated to non-eliminated or vice versa) to generate neighboring states. Each state is evaluated based on how well it satisfies the puzzle's conditions.
   
2. **Heuristic Calculation**: The heuristic value is calculated for each state. The heuristic is defined such that a state satisfying all conditions has a heuristic value of zero. States with violations have negative heuristic values, with the severity of violations affecting the magnitude of the heuristic.

3. **State Selection**: The algorithm selects the neighbor with the best (highest) heuristic value as the next state. This process repeats until a state with a heuristic value of zero is found (indicating a solution) or no better neighbors are available, resulting in a local maximum.

### Simulated Annealing Algorithm

Simulated Annealing is an optimization algorithm similar to Hill Climbing but includes a probabilistic mechanism to escape local maxima. The process differs from Hill Climbing in the following ways:

1. **Random Selection**: Instead of always choosing the best neighbor, a neighbor is selected randomly.
   
2. **Acceptance Probability**: The difference in heuristic values between the current and selected neighbor states is calculated. If the neighbor is worse (lower heuristic), it may still be accepted based on a probability determined by the formula \(e^{\Delta E / T}\), where \(\Delta E\) is the difference in heuristic values and \(T\) is a temperature parameter that decreases over time.

3. **Cooling Schedule**: The algorithm gradually reduces the temperature \(T\) over time, decreasing the probability of accepting worse states as the search progresses.

### Backtracking with CSP

The CSP-based solution models the Hitori puzzle using variables, domains, and constraints:

- **Variables**: Each cell in the grid is a variable.
- **Domains**: Each variable can either be 1 (not eliminated) or 0 (eliminated).
- **Constraints**: The puzzle's conditions (no duplicates in rows/columns, no adjacent eliminated cells, and connectivity of non-eliminated cells) are enforced as constraints.

The backtracking algorithm, akin to Depth-First Search (DFS), explores possible configurations of the grid by systematically assigning values to variables and backtracking when constraints are violated. The algorithm continues until a solution is found or all possibilities are exhausted.

## Analysis of Results

The performance of the algorithms was evaluated based on the number of nodes generated, the number of black cells in the final solution, and the time taken to reach the solution. The key findings are summarized below:

- **Hill Climbing**: Generated a moderate number of nodes and found solutions with reasonable heuristic values but occasionally converged to local maxima.
  
- **Simulated Annealing**: Produced the highest number of nodes but often ended far from the optimal solution (heuristic values far from zero). This algorithm had the worst performance in terms of both accuracy and efficiency.

- **Backtracking with CSP**: Consistently found solutions and performed better than Hill Climbing in terms of both time and correctness. This method was more reliable, always finding a valid solution when possible.

## Directory Structure

### CSP
- **Source.cpp**: Contains the implementation of the CSP-based backtracking algorithm for solving the Hitori puzzle.

### HillClimbing_SimulatedAnnealing
- **Source.cpp**: Includes the implementations of the Hill Climbing and Simulated Annealing algorithms for solving the Hitori puzzle.

## How to Use

1. **CSP Solution**: Compile and run `Source.cpp` in the `CSP` directory to solve the Hitori puzzle using the CSP-based backtracking algorithm.
2. **Hill Climbing and Simulated Annealing**: Compile and run `Source.cpp` in the `HillClimbing_SimulatedAnnealing` directory to test both heuristic search algorithms on the Hitori puzzle.

This project provides a comparative study of different AI algorithms applied to a logic puzzle, demonstrating their strengths and limitations in solving constraint satisfaction problems.
