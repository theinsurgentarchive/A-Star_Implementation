#include "aStar.h"
#include <cmath>
#include <list>
#include <iostream>

Node::Node()
{
    //Initialize Variables
    obstacle = false;
    visited = false;
    local_dist = 0;
    global_dist = 0;
    parent = nullptr;
    child = nullptr;
}

Node::Node(bool isObstacle)
{
    //Initialize Variables
    obstacle = isObstacle;
    visited = false;
    local_dist = 0;
    global_dist = 0;
    parent = nullptr;
    child = nullptr;
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
    if ((x <= grid_size[0]) && (y <= grid_size[1])) {
        return &node_grid[x][y];
    }
}

//Generate Node Grid, Set Node Positions
void Grid::initGrid()
{
    //Generate Nodes
    node_grid = new Node *[grid_size[0]];
    for (int x = 0; x < grid_size[0]; x++) {
        node_grid[x] = new Node [grid_size[1]];
        for (int y = 0; y < grid_size[1]; y++) {
            node_grid[x][y].x = x;
            node_grid[x][y].y = y;
            node_grid[x][y].obstacle = false;
            node_grid[x][y].visited = false;
            node_grid[x][y].parent = nullptr;
            node_grid[x][y].child = nullptr;
        }
    }

    //Fill Each Node's Neighbors Vector Matrix
    genNeighbors();
}

void Grid::genNeighbors()
{
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

bool Grid::hasNeighbors(Node* node)
{
    return (node->neighbors.empty() == false);
}

Grid::~Grid()
{
    for (int x = 0; x < grid_size[0]; x++) {
        delete [] node_grid[x];
    }
    delete [] node_grid;
}

void aStar(Grid* grid, int begin_node[], int ending_node[])
{

    //Retrieve Pointer to Start Node
    Node* start = grid->getNode(
        begin_node[0],
        begin_node[1]
    );

    //Retrieve Pointer to Goal Node
    Node* goal = grid->getNode(
        ending_node[0],
        ending_node[1]
    );

    //Reset All Nodes to Default
    resetNodes(grid);

    //Check if the Node has Neighbors
    if (!grid->hasNeighbors(start)) {
        return;
    }

    //Initialize Start Node
    start->local_dist = 0.0f;
    start->global_dist = heuristics(start, goal);

    //Set Current Node to the Start Node
    Node* current = start;

    //Initialize Array of Untested Nodes
    std::list<Node*> untestedNodes;
    untestedNodes.push_back(start);

    //Primary Algorithm Loop
    while (!untestedNodes.empty()) {
        //Sort the list from least to greatest distance from the Goal
        untestedNodes.sort(
            //This is a Lambda function, which is a unnamed function call
            [](const Node* a, const Node* b)
            {
                return a->global_dist < b->global_dist;
            }
        );
        
        //If the best Node has been visited, pop it from the list
        while ((!untestedNodes.empty()) && (untestedNodes.front()->visited)) {
            untestedNodes.pop_front();
        }

        //If the list is empty, break out of the loop
        if (untestedNodes.empty()) {
            break;
        }
        
        //Set The Current Node to the front of the list and set to visited
        current = untestedNodes.front();
        current->visited = true;

        //Check All Neighbors of The Current Node
        for (Node* neighbor : current->neighbors) {
            //Add Node to List if it's Not Been Visited and is Not a Obstacle
            if (!neighbor->visited && !neighbor->obstacle) {
                untestedNodes.push_back(neighbor);
            }

            //Generate a Potentially Lower Local Distance Based On Distance 
            //From current Node and The Selected neighbor
            //Plus current->local_dist
            float potential_low_goal = (
                current->local_dist + distance(current, neighbor)
            );

            //If the current local is smaller than the potential,
            //Set neigbor->parent to the current Node and
            //Set neighbor->local_dist to The Generated Value
            if (potential_low_goal > current->local_dist) {
                if ((neighbor->parent == nullptr)) {
                    neighbor->parent = current;
                    current->child = neighbor;
                    neighbor->local_dist = potential_low_goal;

                    //The global_dist is a Measure of local_dist
                    //+ The Heuristic of neighbor Node and goal Node
                    neighbor->global_dist = (
                        neighbor->local_dist + heuristics(neighbor, goal)
                    );

                    //If Neighboring Node is Goal Node, Exit Algorithm
                    if (neighbor == goal) {
                        current->child = goal;
                        return;
                    }
                }
            }
        } 
    }
}

void resetNodes(Grid* grid)
{
    for (int x = 0; x < grid->getSizeX(); x++) {
        for (int y = 0; y < grid->getSizeY(); y++) {
            grid->node_grid[x][y].visited = false;
            grid->node_grid[x][y].global_dist = INFINITY;
            grid->node_grid[x][y].local_dist = INFINITY;
            grid->node_grid[x][y].parent = nullptr;
            grid->node_grid[x][y].child = nullptr;
        }
    }
}

float distance(Node* a, Node* b)
{
    return sqrtf(
        ((a->x - b->x) * ((a->x - b->x))) + ((a->y - b->y) * (a->y - b->y))
    );
}

float heuristics(Node* a, Node* b)
{
    return distance(a, b);
}