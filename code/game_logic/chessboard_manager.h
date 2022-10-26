#ifndef piece_manager
#define piece_manager

#include <stdio.h>

int find_king_pos(const char signature);

void collect_allies(int pos_pieces_allies[16], int is_white);

int check_out_of_range(int posX, int posY);

#endif