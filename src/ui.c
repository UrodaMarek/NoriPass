#include <ncurses.h>
#include "ui.h"
#include <stdlib.h>
//#include "storage.h"

void ui_init(Ui *ui) {
    int height, width, starty, startx;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    height = 3;
    width = 5;
    starty = 0;
    startx = 0;

    ui->tabs = (Tab*)malloc(sizeof *ui->tabs);
    ui->tabs[0].id = 0;
    ui->tabs[0].is_logged_in = 0;
    ui->tabs[0].window = newwin(height, width, starty, startx);
    ui->tabs[0].data = NULL;
    ui->tabs[0].size = 1;

    box(ui->tabs[0].window, 0, 0);
    mvwprintw(ui->tabs[0].window, 1, 2, "1");
    wrefresh(ui->tabs[0].window);


    starty += height;
    width = COLS;
    height = LINES - height - 3; 
    ui->main = newwin(height, width, starty, startx);
    box(ui->main, 0, 0);
    wrefresh(ui->main);


    starty += height;
    width = COLS;
    height = 3; 
    ui->menu_bar = newwin(height, width, starty, startx);
    box(ui->menu_bar, 0, 0);
    mvwprintw(ui->menu_bar, 1, COLS / 2 - 41, "Q. New Tab | W. Create database | E. Delete database | R. Open database | T. Close");
    wrefresh(ui->menu_bar);
}

void ui_close() {
    endwin();
}