#include "util.h"
#include "mark.hpp"
#include "tictactoe.hpp"

#include <cstdlib>
#include <unistd.h>
#include <ctime>

TicTacToe::TicTacToe () {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->game.places[i][j] = '\0';
        }
    }
    this->next_mark = 'X';
    this->game.done = false;
    srand (time (NULL));
}

int check_square (int coord) {
    if (coord >= 0 and coord <= 160) {
        return 1;
    } else if (coord > 160 and coord <= 320) {
        return 2;
    } else {
        return 3;
    }

    return 0;
}

bool TicTacToe::check_mouse_click (SDL_Event event) {

    int check_square (int coord);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (event.button.state == SDL_PRESSED) {
                int x = event.button.x;
                if (x >= 80 and x <= 560) {
                    x -= 80;
                    x = check_square (x);
                } else {
                	return 0;
                }
                int y = event.button.y;
                if (y >= 0 and y <= 480) {
	                y = check_square (y);
                } else {
                	return 0;
                }
                if (
                	x >= 1 and x <= 3 and y >= 1 and y <= 3
                	and
                	this->game.places[x-1][y-1] == '\0'
                ) {
                	this->game.places[x-1][y-1] = this->next_mark;
                    this->move_done ();
                    return true;
                }
            }
        }
    }

    return false;
}

void TicTacToe::move_done () {
    if ('X' == this->next_mark) {
        this->next_mark = 'O';
    } else if ('O' == this->next_mark) {
        this->next_mark = 'X';
    }
}

void TicTacToe::Draw () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = i * 160 + 80;
            int y = j * 160;
            if ('X' == this->game.places[i][j]) {
            	this->X.Draw (x, y, x + 150, y + 150);
            	this->X.Draw (x, y + 150, x + 150, y);
        	} else if ('O' == this->game.places[i][j]) {
            	this->X.Draw (x + 80, y + 80, 75);
        	}
        }
    }

    SDL_GL_SwapBuffers();
}

int TicTacToe::check_winner () {

	char winner = '\0';

	for (int i = 0; i < 3; i++) {
		if (
			this->game.places[i][0] == this->game.places[i][1]
			and
			this->game.places[i][0] == this->game.places[i][2]
		) {
			winner = this->game.places[i][0];
		}
		if (
			this->game.places[0][i] == this->game.places[1][i]
			and
			this->game.places[0][i] == this->game.places[2][i]
		) {
			winner = this->game.places[0][i];
		}
		if (
			this->game.places[0][0] == this->game.places[1][1]
			and
			this->game.places[0][0] == this->game.places[2][2]
		) {
			winner = this->game.places[0][0];
		}
		if (
			this->game.places[2][0] == this->game.places[1][1]
			and
			this->game.places[2][0] == this->game.places[0][2]
		) {
			winner = this->game.places[1][1];
		}
	}

	if (winner == 'X' or winner == 'O') {
		this->game.done = true;
		return winner;
	}

    return '\0';
}

bool TicTacToe::can_play () {
	bool game_done = this->game.done;

    if (!game_done) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (this->game.places[i][j] == '\0') {
                    return true;
                }
            }
        }
        return false;
    }

	return !game_done;
}

void TicTacToe::AI_move () {
    bool found = false;
    while (!found) {
        int x = rand () % 3;
        int y = rand () % 3;
        if (this->game.places[x][y] == '\0') {
            // our move
            this->game.places[x][y] = this->next_mark;
            this->move_done ();
            found = true;
        }
    }
}

void TicTacToe::game_loop () {
    bool human_move = false;
    char winner = '\0';
    SDL_Event event;

    while (this->can_play ()) {
        while (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT)
                this->game.done = true;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    this->game.done = true;
            } else if (this->can_play ()) {
                human_move = this->check_mouse_click (event);
                this->Draw ();
                winner = this->check_winner ();
            }
        }

        if (human_move && this->can_play ()) {

            this->AI_move ();
            while (SDL_PollEvent (&event));

            // make it more realistic
            sleep (1);

            this->Draw ();
            winner = this->check_winner ();
            human_move = false;
        }
    }

    winner = '\0';
    winner = this->check_winner ();
    if (winner == '\0') {
        printf ("Drawn game\n");
    } else {
        printf ("Winner: '%C'\n", winner);
    }
}


