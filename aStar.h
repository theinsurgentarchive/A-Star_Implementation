#include <vector>

//Grid of Node Elements, Used in A* Search
class Grid
{
    private:
        //Grid's X & Y Axis Size
        int size[2];

        //Grid Element
        class Node
        {
            public:
                //Node Conditionals
                bool obstacle, visited;
                
                //Node Distance from Initial/Goal Node
                float dist[2];

                //Node Grid Position
                int pos[2];

                //Vector Matrix of Neighboring Nodes
                std::vector<Node*> neighbors;

                //Node Directly Preceding Current Node
                Node* parent;

                //Constructor
                Node();
                Node(int, int);
                Node(int, int, bool);
        };
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
        void initGrid();

        //Destructor
        ~Grid();
};

//A* Search Algorithm
void aStar(Grid, int[2], int[2]);