#include <ncurses.h>

int main()
{
    initscr(); // Initialization of TUI
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    printw("Test");
    getch();
    endwin(); // Ending of TUI
    return 0;
}