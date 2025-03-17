#include <iostream>
#include <string>
#include "aStar.h"
using namespace std;

//Function Prototype
void evaluatePath(Grid*, int[], int[], string**);
void checkVisitedSpaces(Grid*);
void printGrid(Grid*, string**);

int main(int argc, char* argv[])
{
    //Grid Size
    int g_x, g_y;

    //User Input
    int input;

    //Starting & Goal Nodes
    int start_node[2], goal_node[2];
    
    //Set Either Grid Size or Start and Goal Nodes based on passed parameters
    if (argc == 7) {
        g_x = stoi(argv[1]);
        g_y = stoi(argv[2]);
        start_node[0] = stoi(argv[3]);
        start_node[1] = stoi(argv[4]);
        goal_node[0] = stoi(argv[5]);
        goal_node[1] = stoi(argv[6]);
    } else if (argc == 3) {
        g_x = stoi(argv[1]);
        g_y = stoi(argv[2]);
    } else if ((argc <= 1) || (argc < 7 && argc > 3) || (argc > 7)){
        //Print Usage Cases if incorrect parameters
        cout << "Usage: ./astar <int Size:X> <int Size:Y>\n"
                << "\t|OR|\n"
                << "Usage: ./astar <int GridX> <int GridY>\n"
                << "\t<int Pos1:X> <int Pos1:Y>\n"
                << "\t<int Pos2:X> <int Pos2:Y>\n";
        return 1;
    } else {
        g_x = 30;
        g_y = 30;
    };
    
    //Initialize Node Grid
    Grid world(g_x, g_y);
    Grid* ptr = &world;
    //Initialize String Grid
    string** console = new string *[g_x];
    for (int x = 0; x < g_x; x++) {
        console[x] = new string [g_y];
    }

    //Print Initial Grid to The World
    cout << "\nInitial Grid:\n\n";
    for (int x = 0; x < g_x; x++) {
        cout << "| ";
        for (int y = 0; y < g_y; y++) {
            console[x][y] = '*';
            cout << "* ";
        }
        cout << "|\n";
    }

    //Ask User for Starting Node:
    bool flag = true;
    while (flag) {
        cout << "\nInput Starting Coordinate X: ";
        cin >> input;
        if (input >= 0 && input < g_x) {
            flag = false;
            start_node[0] = input;
        } else {
            cout << "\nError: Value not within range of 0-"
                 << to_string(g_x - 1)
                 << "\n\n";
        }
    }
    flag = true;
    while (flag) {
        cout << "\nInput Starting Coordinate Y: ";
        cin >> input;
        if (input >= 0 && input < g_y) {
            flag = false;
            start_node[1] = input;
        } else {
            cout << "\nError: Value not within range of 0-"
                 << to_string(g_y - 1)
                 << "\n\n";
        }
    }
    flag = true;
    cout << "\nStart Node Coordinates: ("
         << start_node[0] << ", "
         << start_node[1] << ")\n\n";
    console[start_node[0]][start_node[1]] = 'S';

    //Ask User for Goal Node:
    bool check_start_goal = true;
    while (check_start_goal) {
        while (flag) {
            cout << "\nInput Goal Coordinate X: ";
            cin >> input;
            if (input >= 0 && input < g_x) {
                flag = false;
                goal_node[0] = input;
            } else {
                cout << "\nError: Value not within range of 0-"
                     << to_string(g_x - 1)
                     << "\n\n";
            }
        }
        flag = true;
        while (flag) {
            cout << "\nInput Goal Coordinate Y: ";
            cin >> input;
            if (input >= 0 && input < g_x) {
                flag = false;
                goal_node[1] = input;
            } else {
                cout << "\nError: Value not within range of 0-" 
                     << to_string(g_x - 1)
                     << "\n\n";
            }
        }
        if (start_node[0] == goal_node[0] && start_node[1] == goal_node[1]) {
            cout << "\nError: Cannot place start and "
                 << " goal nodes on the same coordinate\n\n";
        } else {
            check_start_goal = false;
        }
    }
    flag = true;
    cout << "Goal Node Coordinates: ("
         << goal_node[0] << ", "
         << goal_node[1] << ")\n\n";
    console[goal_node[0]][goal_node[1]] = 'X';

    //Place Obstacle Nodes
    while (flag) {
        cout << "\nSet New Obstacle?: YES[1] / NO[0]\n";
        cin >> input;
        if (input == 1) {
            int temp[2];
            while (flag) {
                cout << "\nObstacle Coordinate X: ";
                cin >> input;
                if (input >= 0 && input < g_x) {
                    flag = false;
                    temp[0] = input;
                } else {
                    cout << "\nError: Value not within range of 0-"
                         << to_string(g_x - 1)
                         << "\n\n";
                }
            }
            flag = true;
            while (flag) {
                cout << "\nObstacle Coordinate Y: ";
                cin >> input;
                if (input >= 0 && input < g_y) {
                    flag = false;
                    temp[1] = input;
                } else {
                    cout << "\nError: Value not within range of 0-"
                         << to_string(g_y - 1)
                         << "\n\n";
                }
            }
            flag = true;
            if ((temp[0] != start_node[0] && temp[1] != start_node[1]) &&
                (temp[0] != goal_node[0] && temp[1] != goal_node[1])) {
                    world.setObstacle(temp[0], temp[1]);
                    console[temp[0]][temp[1]] = '#';
            } else {
                cout << "\nError: Obstacle Cannot Overlap"
                     << " with Start or Goal Nodes\n\n";
            }
        } else if (input == 0) {
            flag = false;
        }
    }

    //Run A* Algorithm
    aStar(ptr, start_node, goal_node);

    //Check All Node Grid Visited Booleans
    checkVisitedSpaces(ptr);

    //Set String Grid with New Values
    evaluatePath(ptr, start_node, goal_node, console);

    //Print New String Grid
    cout << "\n\nA* Algorithm Complete:\n";
    printGrid(ptr, console);
    
    //Delete Console Grid
    for (int x = 0; x < g_x; x++) {
        delete [] console[x];    
    }
    delete [] console;
    
    //Terminate Program
    return 0;
}

void evaluatePath(Grid* grid, int start[], int end[], string** console)
{
    //Initialize Variables
    int g_x, g_y;
    Node* start_node = grid->getNode(start[0], start[1]);
    Node* goal_node = grid->getNode(end[0], end[1]);
    g_x = grid->getSizeX();
    g_y = grid->getSizeY();
    //Initialize Current Node to The Start Node
    Node* current = start_node;

    //Set All Visited Nodes That Are Not The Start, to '&' Characters
    for (int x = 0; x < g_x; x++) {
        for (int y = 0; y < g_y; y++) {
            if (grid->node_grid[x][y].visited &&
                ((start_node != grid->getNode(x, y)) &&
                (goal_node != grid->getNode(x,y)))
            ) {
                console[x][y] = '0';
            }
        }
    }

    //Check if the End Node has a path leading to it
    cout << start_node->parent;
    if (start_node->parent != nullptr) {
        //Check if the Current Node is Not The Start Node and Assigns a 
        //Percent Character to the Console Grid to Represent The Path
        int number = 0;
        while (current->parent != nullptr) {
            console[current->x][current->y] = '%';
            current = current->parent;
        }
    }
}

void checkVisitedSpaces(Grid* grid)
{
    cout << "\n\n";
    int g_x, g_y;
    g_x = grid->getSizeX();
    g_y = grid->getSizeY();
    for (int x = 0; x < g_x; x++) {
        cout << "| ";
        for (int y = 0; y < g_y; y++) {
            cout << grid->node_grid[x][y].visited << ' ';
        }
        cout << "|\n";
    }
    cout << "\n\n";
}

//Print Grid to The World
void printGrid(Grid* grid, string** console)
{
    int g_x, g_y;
    g_x = grid->getSizeX();
    g_y = grid->getSizeY();
    for (int x = 0; x < g_x; x++) {
        cout << "| ";
        for (int y = 0; y < g_y; y++) {
            cout << console[x][y] << ' ';
        }
        cout << "|\n";
    }
}