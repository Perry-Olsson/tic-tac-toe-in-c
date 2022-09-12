#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "helper.h"

#define DISPLAY_CHAR 'O'
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

int CHAR_HEIGHT = 14;
int CHAR_WIDTH = 15;
int BOARD_SIZE = 3;

struct Board {
   char *spots[3][3];
};

void create_blank_char(char b[CHAR_HEIGHT][CHAR_WIDTH]) {
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            b[i][j] = ' ';
        }
    }
}

void create_x_char(char x[CHAR_HEIGHT][CHAR_WIDTH]) {
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            if (j == i || j == CHAR_WIDTH - i - 1) {
                x[i][j] = DISPLAY_CHAR;
            } else {
                x[i][j] = ' ';
            }
        }
    }
}

bool is_put_top_chars(int index) {
    return index == 0 || index == CHAR_HEIGHT - 1;
}

int calc_number_of_top_chars() {
    int is_odd_offset = CHAR_WIDTH % 2;
    int char_div_2 = CHAR_WIDTH / 2;
    int char_mod_five = CHAR_WIDTH % 5;
    int number_of_top_chars = CHAR_WIDTH / 5;
    int tmp = char_mod_five % 2;
    if (is_odd_offset == 0 && char_mod_five != 0 && tmp != 0) {
        number_of_top_chars++;
    } else if (tmp != 0) {
        number_of_top_chars++;
    }

    return number_of_top_chars;
}

void create_o_char(char o[CHAR_HEIGHT][CHAR_WIDTH]) {
    int number_of_top_chars = calc_number_of_top_chars();
    int top_chars_offset = (CHAR_WIDTH - number_of_top_chars) / 2;

    // side char helpers
    int char_height_div_2 = CHAR_HEIGHT / 2;
    int is_height_odd_offset = CHAR_HEIGHT % 2;
    int number_of_size_chars = char_height_div_2 + (char_height_div_2 % 2) - (CHAR_HEIGHT % 2);

    int side_chars_created = 0;

    // diaganol chars
    int diaganol_char_height = CHAR_HEIGHT - number_of_size_chars - 2;
    int diaganol_char_width = CHAR_WIDTH - number_of_top_chars - 1;
    int diaganol_char_offset = diaganol_char_height / 2;
    int added_diaganol_zeros = 0;

    for (int i = 0; i < CHAR_HEIGHT; i++) {
        bool added_side_zero = false;
        bool added_diaganol_zero = false;
        int top_chars_created = 0;
        for (int j = 0; j < CHAR_WIDTH; j++) {
            bool added_zero = false;
            if (is_put_top_chars(i)) {
                if (j >= top_chars_offset && top_chars_created < number_of_top_chars) {
                    o[i][j] = DISPLAY_CHAR;
                    added_zero = true;
                    top_chars_created++;
                }
            } else if (i >= (CHAR_HEIGHT - number_of_size_chars) / 2 && side_chars_created < number_of_size_chars) {
                if (j == 0 || j == CHAR_WIDTH - 1) {
                    o[i][j] = DISPLAY_CHAR;
                    added_zero = true;
                    added_side_zero = true;
                }
            } else {
                if (j == diaganol_char_offset || j == CHAR_WIDTH - diaganol_char_offset - 1) {
                    o[i][j] = DISPLAY_CHAR;
                    added_zero = true;
                    added_diaganol_zero = true;
                    added_diaganol_zeros++;
                }
            }
            if (!added_zero) {
                o[i][j] = ' ';
            }
        }
        if (added_side_zero == true) {
            side_chars_created++;
        }
        if (added_diaganol_zero == true && added_diaganol_zeros != diaganol_char_height) {
            if (i < char_height_div_2) {
                diaganol_char_offset--;
            } else {
                diaganol_char_offset++;
            }
        }
    }
}

bool is_put_diaganol_chars(int index);
bool is_put_side_chars(int index);

void print_board(char (*board[3][3])[14][15]) {
    clear();
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < CHAR_HEIGHT; j++) {
            for (int k = 0; k < CHAR_WIDTH; k++) {
                putchar((*board[i][0])[j][k]);
            }
            printf("  |  ");
            for (int k = 0; k < CHAR_WIDTH; k++) {
                putchar((*board[i][1])[j][k]);
            }
            printf("  |  ");
            for (int k = 0; k < CHAR_WIDTH; k++) {
                putchar((*board[i][2])[j][k]);
            }
            putchar('\n');
        }
        if (i != 2) {
            for (int l = 0; l < CHAR_WIDTH * 3 + 10; l++) {
                putchar('_');
            }
        }
        if (i != 2) {
            putchar('\n');
            putchar('\n');
        }
    }
    printf("------------------------------------------------------------------------------------\n");
}

void delay(long milliseconds) {
    milliseconds = milliseconds * 1000;
    clock_t start_time = clock();

    while (clock() < start_time + milliseconds)
        ;
}

int main() 
{
    char o[CHAR_HEIGHT][CHAR_WIDTH];
    create_o_char(o);
    char x[CHAR_HEIGHT][CHAR_WIDTH];
    create_x_char(x);
    char blank[CHAR_HEIGHT][CHAR_WIDTH];
    create_blank_char(blank);

    char (*board[3][3])[14][15] = {
     {&blank, &blank, &blank}, {&blank, &blank, &blank}, {&blank, &blank, &blank}
    };

    print_board(board);
    delay(1000);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = &o;
            print_board(board);
            delay(500);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = &x;
            print_board(board);
            delay(500);
        }
    }

    return 0;
}
