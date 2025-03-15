#include <iostream>
#include <string>
#include "aStar.h"
using namespace std;

//Function Prototype
void printGrid(Grid&, string[]);

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

    //Initialize String Grid
    string** console = new string *[g_x];
    for (int i = 0; i < g_x; i++) {
        console[i] = new string [g_y];
    }

    //Print Initial Grid to The World
    cout << "\nInitial Grid:\n\n";
    for (int i = 0; i < g_x; i++) {
        cout << "| ";
        for (int j = 0; j < g_y; j++) {
            if (world.node_grid[i][j].obstacle) {
                cout << '#';
                console[i][j] = '#';
            } else {
                cout << '*';
                console[i][j] = '*';
            }
            cout << ' ';
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
            cout << "\nError: Value not within range of 0-" << to_string(g_x)
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
            cout << "\nError: Value not within range of 0-" << to_string(g_y)
                 << "\n\n";
        }
    }
    flag = true;
    cout << "\nStart Node Coordinates: ("
         << start_node[0] << ", "
         << start_node[1] << ")\n\n";

    //Ask User for Goal Node:
    bool check_start_goal = true;
    while (check_start_goal) {
        while (flag) {
            cout << "\nInput Goal Coordinate X: ";
            cin >> input;
            if (input > 0 && input < g_x) {
                flag = false;
                goal_node[0] = input;
            } else {
                cout << "\nError: Value not within range of 0-"
                     << to_string(g_x)
                     << "\n\n";
            }
        }
        flag = true;
        while (flag) {
            cout << "\nInput Goal Coordinate Y: ";
            cin >> input;
            if (input > 0 && input < g_x) {
                flag = false;
                goal_node[0] = input;
            } else {
                cout << "\nError: Value not within range of 0-" 
                     << to_string(g_x)
                     << "\n\n";
            }
        }
        if (start_node[0] == goal_node[0] && start_node[1] == goal_node[1]) {
            cout << "\nError: Cannot place start and "
                 << "goal nodes on the same coordinate\n\n";
        } else {
            check_start_goal = false;
        }
    }
    cout << "Goal Node Coordinates: ("
         << goal_node[0] << ", "
         << goal_node[1] << ")\n\n";
    
    //Place Obstacle Nodes
    while (flag) {
        cout << "\nSet New Obstacle?: YES[1] / NO[0]\n";
        cin >> input;
        if (input == 1) {
            int temp[2];
            while (flag) {
                cout << "\nObstacle Coordinate X: ";
                cin >> input;
                if (input > 0 && input < g_x) {
                    flag = false;
                    temp[0] = input;
                } else {
                    cout << "\nError: Value not within range of 0-"
                         << to_string(g_x)
                         << "\n\n";
                }
            }
            flag = true;
            while (flag) {
                cout << "\nObstacle Coordinate Y: ";
                cin >> input;
                if (input > 0 && input < g_y) {
                    flag = false;
                    goal_node[0] = input;
                } else {
                    cout << "\nError: Value not within range of 0-"
                         << to_string(g_y)
                         << "\n\n";
                }
            }
            flag = true;
            if ((temp[0] != start_node[0] && temp[1] != start_node[1]) &&
                (temp[0] != goal_node[0] && temp[1] != goal_node[1])) {
                    world.setObstacle(temp[0], temp[1]);
            } else {
                cout << "\nError: Obstacle Cannot Overlap"
                     << "with Start or Goal Nodes\n\n";
            }
        } else if (input == 0) {
            flag = false;
        }
    }

    aStar(&world, start_node, goal_node);

    //Delete Console Grid
    for (int i = 0; i < g_x; i++) {
        delete [] console[i];    
    }
    delete [] console;
    
    //Terminate Program
    return 0;
}

//Print Grid to The World
void printGrid(Grid& grid_ptr, string console[])
{
    int g_x, g_y;
    g_x = grid_ptr.getSizeX();
    g_y = grid_ptr.getSizeY();
    for (int i = 0; i < g_x; i++) {
        cout << "| ";
        for (int j = 0; j < g_y; j++) {
            cout << console[i][j] << ' ';
        }
        cout << "|\n";
    }
}