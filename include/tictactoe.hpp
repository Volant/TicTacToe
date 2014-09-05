#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include "util.h"

typedef struct game_status {
    char places[3][3];
    bool done;
} game_status;

class TicTacToe {
private:
    game_status game;
    Mark X;
    char next_mark;
public:
    TicTacToe();
    bool check_mouse_click (SDL_Event);
    void Draw ();
    int check_winner ();
    bool can_play ();
    void AI_move ();
    void move_done ();
    void game_loop ();

    ~TicTacToe() {};
};

#endif
