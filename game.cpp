#include <bits/stdc++.h>
using namespace std;

typedef pair<vector<vector<int>>, int> PuzzleState;
vector<vector<int>> goalPuzzle(3, vector<int>(3));
vector<vector<int>> initialPuzzle(3, vector<int>(3));
map<vector<vector<int>>, bool> visited;
map<vector<vector<int>>, vector<vector<int>>> parent;

int findInversionCount(int arr[])
{
    int inversionCount = 0;
    for (int i = 0; i < 9 - 1; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inversionCount++;
        }
    }
    return inversionCount;
}

bool isSolvable(vector<vector<int>> puzzle)
{
    int puzzleArray[8];
    int p = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            puzzleArray[p++] = puzzle[i][j];
        }
    }
    int inversionCount = findInversionCount(puzzleArray);

    return (inversionCount % 2 == 0);
}

bool hasVisited(vector<vector<int>> state)
{
    return visited[state];
}

bool isValidPosition(int x, int y)
{
    return (x >= 0 && x <= 2 && y >= 0 && y <= 2);
}

int calculateManhattanDistance(PuzzleState puzzleState)
{
    vector<vector<int>> currentState = puzzleState.first;
    int totalDistance = puzzleState.second;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (currentState[i][j] != 0)
            {
                for (int u = 0; u < 3; ++u)
                {
                    for (int v = 0; v < 3; ++v)
                    {
                        if (goalPuzzle[u][v] == currentState[i][j])
                            totalDistance += abs(u - i) + abs(v - j);
                    }
                }
            }
        }
    }
    return totalDistance;
}

vector<vector<vector<int>>> getPossibleMoves(vector<vector<int>> currentState)
{
    vector<vector<vector<int>>> possibleMoves;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int x, y;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (currentState[i][j] == 0)
            {
                x = i;
                y = j;
            }
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        vector<vector<int>> nextState = currentState;
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValidPosition(newX, newY))
        {
            swap(nextState[newX][newY], nextState[x][y]);
            possibleMoves.push_back(nextState);
        }
    }
    return possibleMoves;
}

struct CompareStates
{
    bool operator()(PuzzleState stateA, PuzzleState stateB)
    {
        int distanceA = calculateManhattanDistance(stateA);
        int distanceB = calculateManhattanDistance(stateB);
        return distanceA > distanceB;
    }
};

void printSolutionPath(vector<vector<int>> currentState, int moveNumber)
{
    if (parent.count(currentState))
    {
        printSolutionPath(parent[currentState], moveNumber - 1);
    }
    cout << "Move " << moveNumber << ":\n";
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << currentState[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

void solvePuzzle()
{
    priority_queue<PuzzleState, vector<PuzzleState>, CompareStates> priorityQueue;
    priorityQueue.push(PuzzleState(initialPuzzle, 0));

    int moveNumber = 1;

    while (!priorityQueue.empty())
    {
        PuzzleState currentState = priorityQueue.top();
        vector<vector<int>> currentStateConfig = currentState.first;
        int moves = currentState.second;

        priorityQueue.pop();
        visited[currentStateConfig] = true;
        if (currentStateConfig == goalPuzzle)
        {
            printSolutionPath(currentStateConfig, moveNumber);
            break;
        }

        vector<vector<vector<int>>> adjacentStates = getPossibleMoves(currentStateConfig);
        vector<vector<vector<int>>>::iterator it;
        for (it = adjacentStates.begin(); it != adjacentStates.end(); it++)
        {
            vector<vector<int>> nextState = *it;
            if (!hasVisited(nextState))
            {
                priorityQueue.push(PuzzleState(nextState, moves + 1));
                parent.insert(pair<vector<vector<int>>, vector<vector<int>>>(nextState, currentStateConfig));
            }
        }
        moveNumber++;
    }
    return;
}

int main()
{
    cout << "Give input for 3 by 3 puzzle:" << endl;
    cout << endl;
    int puzzleNumber = 1;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i == j && j == 2)
                goalPuzzle[i][j] = 0;
            else
                goalPuzzle[i][j] = puzzleNumber++;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> initialPuzzle[i][j];
        }
    }

    if (isSolvable(initialPuzzle))
    {
        cout << endl;
        cout << "Sequence of moves: " << endl;
        solvePuzzle();
    }
    else
        cout << "Puzzle is not solvable" << endl;
    return 0;
}
