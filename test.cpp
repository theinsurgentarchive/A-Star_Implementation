#include <iostream>
#include <string>
#include "aStar.h"
using namespace std;

//Function Prototypes
void printGrid(Grid*, string[]);

int main(int argc, char* argv[])
{
    //get size of grid
    int g_x, g_y;
    int init_node[2], goal_node[2];
    if (argc == 5) {
        g_x = 30;
        g_y = 30;
        init_node[0] = stoi(argv[1]);
        init_node[1] = stoi(argv[2]);
        goal_node[0] = stoi(argv[3]);
        goal_node[1] = stoi(argv[4]);
    } else if (argc == 3) {
        g_x = stoi(argv[1]);
        g_y = stoi(argv[2]);
    } else if ((argc <= 1) || (argc == 4 || argc > 5)){
        cout << "Usage: ./astar <int Size:X> <int Size:Y>\n"
                << "\t|OR|\n"
                << "Usage: ./astar <int Pos1:X> <int Pos1:Y>"
                << "<int Pos2:X> <int Pos2:Y>\n";
        return 1;
    } else {
        g_x = 30;
        g_y = 30;
    };
    
    //Generate Grids
    Grid world(g_x, g_y);
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
    g_x, g_y = grid_ptr.getSize();
    for (int i = 0; i < g_x; i++) {
        cout << "| ";
        for (int j = 0; j < g_y; j++) {
            cout << console[i][j] << ' ';
        }
        cout << "|\n";
    }
}