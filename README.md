# 8-Puzzle Solver using A* Algorithm

This C++ program implements a solver for the classic 8-puzzle problem using the A* algorithm. The 8-puzzle is a sliding puzzle where the objective is to rearrange a 3x3 grid of numbered tiles to achieve a specific configuration.

For more information about the sliding puzzle, you can visit [here](https://en.wikipedia.org/wiki/Sliding_puzzle).

## Table of Contents

- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [A* Algorithm Overview](#a-algorithm-overview)
- [Working of the Code](#working-of-the-code)

## Prerequisites

- C++ Compiler
- Standard Template Library (STL)
- Terminal/Command Prompt

## Usage

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/your-username/8-puzzle-solver.git
    cd 8-puzzle-solver
    ```

2. **Compile and Run:**

    ```bash
    g++ -o 8puzzle 8puzzle.cpp
    ./8puzzle
    ```

    Follow the on-screen instructions to input the initial puzzle configuration.

3. **View Solution:**

    The program will display the sequence of moves needed to solve the puzzle.

## A* Algorithm Overview

The A* algorithm is a widely used search algorithm employed in pathfinding and graph traversal. It aims to find the shortest path from a start state to a goal state by efficiently exploring the search space. Key aspects of the A* algorithm in this implementation include:

- **Priority Queue:**
  - Utilizes a priority queue to manage states based on their estimated costs.

- **Heuristic Function: Manhattan Distance**
  - Employs the Manhattan distance heuristic to estimate the cost from the current state to the goal state.

- **State Comparison:**
  - States are compared based on their heuristic values, prioritizing states with lower total costs.

- **Optimal Path Finding:**
  - Iteratively explores states in a prioritized manner, ensuring an optimal path is found.

## Working of the Code

The program uses simple logic to explore possible moves and find a solution to the 8-puzzle. The solvability of the puzzle is checked using the inversion count of the tiles. If the inversion count is even, the puzzle is considered solvable.

### 1. Inversion Count for Solvability Check

Before attempting to solve the puzzle, the program checks whether the given initial configuration is solvable. The inversion count is the number of pairs of tiles that are in the wrong order when counting from the bottom-right corner, including the blank tile.

### 2. Generating Possible Moves

The `getPossibleMoves` function generates all possible next states from the current state. It considers moving the blank tile in four possible directions: up, down, left, and right. This function ensures that only valid moves within the boundaries of the puzzle are considered.

### 3. Printing Solution Path

The `printSolutionPath` function recursively prints the sequence of moves needed to reach the solution. It uses a map to backtrack from the goal state to the initial state, printing each state along with its corresponding move number.
