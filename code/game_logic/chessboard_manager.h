#ifndef piece_manager
#define piece_manager

#include <stdio.h>

void init_pieces(piece pieces[64], const char init_chessboard[8][8]);
void init_kings();
void find_king_pos(const char signature);

#endif