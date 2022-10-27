#ifndef piece_manager
#define piece_manager

#include <stdio.h>

int is_same_color(const char p1, const char p2);

int check_out_of_range(const int posX, const int posY);

int find_king_pos(const char signature);

void collect_allies(int pos_pieces_allies[16], const char ally);

void make_move(const int position, const int destination);

void undo_move();

#endif