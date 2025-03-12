#include "aStar.h"

Node::Node()
{
    //Initialize Variables
    obstacle = false;
    visited = false;
    init_dist = 0;
    goal_dist = 0;
    parent = nullptr;
}

Node::Node(bool isObstacle)
{
    //Initialize Variables
    obstacle = isObstacle;
    visited = false;
    init_dist = 0;
    goal_dist = 0;
    parent = nullptr;
}

Grid::Grid()
{
    //Initialize Variables
    grid_size[0] = 10;
    grid_size[1] = 10;

    //Initialize Grid Nodes
    initGrid();
}

Grid::Grid(int x_size, int y_size)
{
    grid_size[0] = x_size;
    grid_size[1] = y_size;

    //Initalize Grid Nodes
    initGrid();
}

//Sets The Given Coordinate's Node to an Obstacle
void Grid::setObstacle(int x, int y)
{
    node_grid[x][y].obstacle = true;
}

//Return Grid's X-Axis Size
int Grid::getSizeX()
{
    return grid_size[0];
}

//Return Grid's Y-Axis Size
int Grid::getSizeY()
{
    return grid_size[1];
}

//Retrieves The Node requested in the Grid
Node* Grid::getNode(int x, int y)
{
    return &node_grid[x][y];
}

//Generate Node Grid, Set Node Positions
void Grid::initGrid()
{
    //Generate Nodes
    node_grid = new Node *[grid_size[0]];
    for (int i = 0; i < grid_size[0]; i++) {
        node_grid[i] = new Node [grid_size[1]];
    }

    //Fill Each Node's Neighbors Vector Matrix
    for (int x = 0; x < grid_size[0]; x++) {
        for (int y = 0; y < grid_size[1]; y++) {
            
            //Load All Y-Axis Neighbors into The Node's Vector Matrix
            if (y > 0) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x][y - 1]
                );
            }
            if (y < grid_size[1] - 1) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x][y + 1]
                );
            }

            //Load All X-Axis Neighbors into The Node's Vector Matrix
            if (x > 0) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x - 1][y]
                );
            }
            if (x < grid_size[0] - 1) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x + 1][y]
                );
            }

            //Load All Diagonal Neighbors into The Node's Vector Matrix
            if (x > 0 && y > 0) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x - 1][y - 1]
                );
            }
            if (x > 0 && y < grid_size[1] - 1) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x - 1][y + 1]
                );
            }
            if (x < grid_size[0] - 1 && y > 0) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x + 1][y - 1]
                );
            }
            if (x < grid_size[0] - 1 && y < grid_size[1] - 1) {
                node_grid[x][y].neighbors.push_back(
                    &node_grid[x + 1][y + 1]
                );
            }
        }
    }
    
}

Grid::~Grid()
{
    for (int i = 0; i < grid_size[0]; i++) {
        delete [] node_grid[i];
    }
    delete [] node_grid;
}

void aStar(Grid grid, int begin_node[], int ending_node[])
{
    //Retrieve Pointer to Start Node
    Node* start = grid.getNode(
        begin_node[0],
        begin_node[1]
    );

    //Retrieve Pointer to Goal Node
    Node* goal = grid.getNode(
        ending_node[0],
        ending_node[1]
    );


}