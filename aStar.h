#include <vector>

class Node
{
    public:
        //Node Conditionals
        bool obstacle, visited;
        
        //Node Position
        int x, y;
        
        //Node Distance from Initial Node
        float local_dist;

        //Node Distance from Goal Node
        float global_dist;
        
        //Vector Matrix of Neighboring Nodes
        std::vector<Node*> neighbors;
        
        //Node Directly Preceding Current Node
        Node* parent;
        
        //Constructor
        Node();
        Node(bool);
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

        //Function
        void setObstacle(int, int);
        int getSizeX();
        int getSizeY();
        Node* getNode(int, int);
        void initGrid();
        void genNeighbors();
        bool hasNeighbors(Node*);
        
        //Destructor
        ~Grid();
};

//A* Search Algorithm
void aStar(Grid*, int[2], int[2]);

//Node Refresh
void resetNodes(Grid*);

//Calculate The Distance From One Node to The Next
float distance(Node*, Node*);

//Calls distance() (May be Deprecated in The Future Due to Redundancy)
float heuristics(Node*, Node*);
