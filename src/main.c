#include <stdio.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper.h"

int CHAR_HEIGHT = 14;
int CHAR_WIDTH = 15;
#define DISPLAY_CHAR 'O'

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

void create_o_char(char o[CHAR_HEIGHT][CHAR_WIDTH]) {
    // top char helpers
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

    // side char helpers
    int char_height_div_2 = CHAR_HEIGHT / 2;
    int is_height_odd_offset = CHAR_HEIGHT % 2;
    int number_of_size_chars = char_height_div_2 + (char_height_div_2 % 2) - (CHAR_HEIGHT % 2);
    printf("%d\n", number_of_size_chars);

    int side_chars_created = 0;

    // diaganol chars
    int diaganol_char_height = CHAR_HEIGHT - number_of_size_chars - 2;
    int diaganol_char_width = CHAR_WIDTH - number_of_top_chars - 1;
    int diaganol_char_offset = (CHAR_HEIGHT - number_of_size_chars - 2) / 2;
    int added_diaganol_zeros = 0;
    printf("height: %d, width: %d, offset: %d\n", diaganol_char_height, diaganol_char_width, diaganol_char_offset);

    for (int i = 0; i < CHAR_HEIGHT; i++) {
        bool added_side_zero = false;
        bool added_diaganol_zero = false;
        for (int j = 0; j < CHAR_WIDTH; j++) {
            bool added_zero = false;
            if (i == 0 || i == CHAR_HEIGHT - 1) {
                if (j + 1 >= char_div_2 + 2 - number_of_top_chars + is_odd_offset && j - is_odd_offset <= char_div_2 + 2 - number_of_top_chars + is_odd_offset) {
                    o[i][j] = DISPLAY_CHAR;
                    added_zero = true;
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

int main() 
{
    for (int i = 10; i < 20; i++) {
        CHAR_HEIGHT = i;
        printf("--------------%d------------\n", i);
        char tmp[CHAR_HEIGHT][CHAR_WIDTH];
        create_o_char(tmp);
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < CHAR_WIDTH; k++) {
                putchar(tmp[j][k]);
            }
            putchar('\n');
        }
    }
    // print x
//    char o[CHAR_HEIGHT][CHAR_WIDTH];
//    create_o_char(o);
//    char x[CHAR_HEIGHT][CHAR_WIDTH];
//    create_x_char(x);
//    for (int i = 0; i < CHAR_HEIGHT; i++) {
//        for (int j = 0; j < CHAR_WIDTH; j++) {
//            putchar(o[i][j]);
//        }
//        putchar('\n');
//    }
//    for (int i = 0; i < CHAR_HEIGHT; i++) {
//        for (int j = 0; j < CHAR_WIDTH; j++) {
//            putchar(x[i][j]);
//        }
//        putchar('\n');
//    }

    return 0;
}


/* O     O       OO
 *            O    O
 *                 O
 *  O   O    O        O
 *   O O     O        O
 *    O      O        O   
 *   O O     O        O
    O   O     O      O
   O     O       OO
 */
//    char o[CHAR_HEIGHT][CHAR_WIDTH] = {
//       {' ',' ', ' ', ' ', 'O', 'O', ' ', ' ', ' ', ' '},
//       {' ',' ', 'O', ' ', ' ', ' ', ' ', 'O', ' ', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ','O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' '},
//       {' ',' ', 'O', ' ', ' ', ' ', ' ', 'O', ' ', ' '},
//       {' ',' ', ' ', ' ', 'O', 'O', ' ', ' ', ' ', ' '},
//    };

//    for (int i = 0; i < CHAR_HEIGHT; i++) {
//        for (int j = 0; j < CHAR_WIDTH; j++) {
//            putchar(x[i][j]);
//        }
//        putchar('\n');
//    }
//    for (int i = 0; i < CHAR_HEIGHT; i++) {
//        for (int j = 0; j < CHAR_WIDTH; j++) {
//            putchar(o[i][j]);
//        }
//        putchar('\n');
//    }
//    #define ROW_SIZE 5
//    #define COL_SIZE 5
//    char *test = '―';
//    char board[ROW_SIZE][COL_SIZE] = {
//        {' ', '|', ' ', '|', ' '},
//        {'_', '_', '_', '_', '_'},
//        {' ', '|', ' ', '|', ' '},
//        {'_', '_', '_', '_', '_'},
//        {' ', '|', ' ', '|', ' '}
//    };
//    
//    for (int i = 0; i < ROW_SIZE; i++) {
//        for (int j = 0; j < COL_SIZE; j++) {
//            putchar(board[i][j]);
//        }
//        putchar('\n');
//    }
