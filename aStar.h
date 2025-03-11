#include <vector>

class Grid
{
    private:
        int size[2];
        class Node
        {
            public:
                bool obstacle, visited;
                int pos[2];
                Node();
                Node(int, int);
                Node(int, int, bool);
                std::vector<Node*> neighbors;
                Node* parent;
        };
        Node** node_grid;
    public:
        Grid();
        Grid(int, int);
        void setObstacle(int, int);
        void initGrid();
        ~Grid();
};

void aStar(Grid, int[2], int[2]);