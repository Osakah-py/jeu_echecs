# include <stdio.h>

/* note :
position = x
horizontal pos = x % 8
vertical pos = x / 8

movement = {x, y, z}
x = horizontal movement
y = vertical movement
z = can repeat this single movement ? (0 : nope, other value : yes)
*/


// GLOBAL VARIABLES ------------------------------------------------------------------------------
// a dictionnary of movement to each piece
const char piece_key[6] = {'p', 'r', 'n', 'b', 'k', 'q'};
//const int movement_value = {{1, 0}, {1, 0}}

// PROTOTYPES ------------------------------------------------------------------------------------
char check_movement(int position, char signature);

// FUNCTIONS -------------------------------------------------------------------------------------
char check_movement(int position, char signature)
{
    // need to find a general solution for all types of chess piece
}
