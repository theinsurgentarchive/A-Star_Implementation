#include "aStar.h"

Grid::Node::Node()
{
    //Initialize Variables
    obstacle = false;
    visited = false;
    pos[0] = 0;
    pos[1] = 0;
}

Grid::Node::Node(int x, int y)
{
    //Initialize Variables
    obstacle = false;
    visited = false;
    pos[0] = x;
    pos[1] = y;
}

Grid::Node::Node(int x, int y, bool isObstacle)
{
    //Initialize Variables
    obstacle = isObstacle;
    visited = false;
    pos[0] = x;
    pos[1] = y;

}

Grid::Grid()
{
    //Initialize Variables
    size[0] = 10;
    size[1] = 10;

    //Initialize Grid Nodes
    initGrid();
}

void Grid::setObstacle(int x, int y)
{
    node_grid[x][y].obstacle = true;
}

void Grid::initGrid()
{
    node_grid = new Node *[size[0]];
    for (int i = 0; i < size[0]; i++) {
        node_grid[i] = new Node [size[1]];
        for (int j = 0; j < size[1]; j++) {
            node_grid[i][j].pos[0] = i;
            node_grid[i][j].pos[1] = j;
        }
    }
}

Grid::Grid(int x_size, int y_size)
{
    size[0] = x_size;
    size[1] = y_size;

    //Initalize Grid Nodes
    initGrid();
}

Grid::~Grid()
{
    for (int i = 0; i < size[0]; i++) {
        delete [] node_grid[i];
    }
    delete [] node_grid;
    
}

void aStar(Grid grid, int begin[2], int ending[2])
{

}