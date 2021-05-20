#include "inputManager.h"

keyHandler kh;

void onKeyPress(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            break;
        case 'A':
            break;
        case 'D':
            break;
        case 'R':
            break;
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
    }
}
void onKeyUp(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            break;
        case 'A':
            break;
        case 'D':
            break;
        case 'R':
            break;
    }
}

void onMousePress(int state, int button, int x, int y) {

}

void onMouseMove(int x, int y) {

}
