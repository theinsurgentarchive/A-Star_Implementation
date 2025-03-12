#include <vector>

class Grid
{
    private:
        int size[2];
        class Node
        {
            public:
                bool obstacle, visited;
                float dist[2];
                int pos[2];
                Node();
                Node(int, int);
                Node(int, int, bool);
                std::vector<Node*> neighbors;
                Node* parent;
        };
    public:
        //Variables
        Node** node_grid;
        
        //Functions
        Grid();
        Grid(int, int);
        void setObstacle(int, int);
        int getSize();
        void initGrid();
        ~Grid();
};

//A* Search Algorithm
void aStar(Grid, int[2], int[2]);