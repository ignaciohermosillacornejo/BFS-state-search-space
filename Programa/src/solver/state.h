#include "arraylist.h"

typedef struct state State;
/* State of the board (value for our queue) */
struct state
{
    ArrayList *ships;
    ArrayList *asteroids;
    int count_asteroids;
    State *parent;
    int parent_x;
    int parent_y;
};