#include <vector>

class Node
{
    public:
        //Node Conditionals
        bool obstacle, visited;
        
        //Node Distance from Initial/Goal Node
        float init_dist;
        float goal_dist;
        
        //Vector Matrix of Neighboring Nodes
        std::vector<Node*> neighbors;
        
        //Node Directly Preceding Current Node
        Node* parent;
        
        //Constructor
        Node();
        Node(bool);

        //Function
};

//Grid of Node Elements, Used in A* Search
class Grid 
{
    private:
        //Grid's X & Y Axis Size
        int grid_size[2];
    public:
        //Dynamic Node Grid
        Node** node_grid;

        //Constructor
        Grid();
        Grid(int, int);

        //Functions
        void setObstacle(int, int);
        int getSizeX();
        int getSizeY();
        Node* getNode(int, int);
        void initGrid();
        //Destructor
        ~Grid();
};
        
//A* Search Algorithm
void aStar(Grid, int[2], int[2]);