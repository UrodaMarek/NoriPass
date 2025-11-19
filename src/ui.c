#include <ncurses.h>
#include "ui.h"
#include <stdlib.h>
//#include "storage.h"

void ui_init(Ui *ui) {
    initscr();
    cbreak();
    noecho();

    ui->tabs = (Tab*)malloc(0);
    ui->tab_count = 0;
    ui->menu_bar[1] = newwin(3, COLS, LINES - 3, 0);
    ui->menu_bar[0] = newwin(3, COLS, LINES - 3, 0);

    box(ui->menu_bar[1], 0, 0);
    box(ui->menu_bar[0], 0, 0);

    mvwprintw(ui->menu_bar[1], 1, COLS / 2 - 41, "F1. New Tab | F2. Create database | F3. Delete database | F4. Open database | F5. Close");
    mvwprintw(ui->menu_bar[0], 1, COLS / 2 - 41, "F1. New Tab | F2. Create database | F3. Delete database | F4. Open database | F5. Close");

    keypad(ui->menu_bar[1], TRUE);
    keypad(ui->menu_bar[0], TRUE);
    wrefresh(ui->menu_bar[0]);
}

void new_tab(Ui *ui) {
    int starty, startx, count, id;

    ui->tab_count++;
    count = ui->tab_count;
    id = count - 1;
    starty = 0;
    startx = 5 * id;
    ui->tabs = (Tab*)realloc(ui->tabs, (count) * sizeof(Tab));
    ui->tabs[id].id = id;
    ui->tabs[id].is_logged_in = 0;
    ui->tabs[id].tab_icon = newwin(3, 5, starty, startx);
    ui->tabs[id].data = NULL;

    box(ui->tabs[id].tab_icon, 0, 0);
    mvwprintw(ui->tabs[id].tab_icon, 1, 2, "%d", count);
    wrefresh(ui->tabs[id].tab_icon);


    starty = 3;
    startx = 0;

    ui->tabs[id].main = newwin(LINES - 6, COLS, starty, startx);
    box( ui->tabs[id].main, 0, 0);
    wrefresh(ui->tabs[id].main);
}

void ui_end() {
    endwin();
}