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

    mvwprintw(ui->menu_bar[1], 1, COLS / 2 - 38, "F1. New Tab | F2. Close tab | F3. Create database | F4. Open database | F5. Exit");
    mvwprintw(ui->menu_bar[0], 1, COLS / 2 - 38, "F1. New Tab | F2. Close tab | F3. Create database | F4. Open database | F5. Exit");

    keypad(ui->menu_bar[1], TRUE);
    keypad(ui->menu_bar[0], TRUE);
    wrefresh(ui->menu_bar[0]);
}

void set_current_tab(Tab *tab, int *current_tab) {
    werase(tab->tab_icon);
    wattron(tab->tab_icon, A_REVERSE);
    box(tab->tab_icon, 0, 0);
    mvwprintw(tab->tab_icon, 1, 1, " %d ", (*current_tab)+1);
    wattroff(tab->tab_icon, A_REVERSE); 
    wrefresh(tab->tab_icon);
}

void unset_current_tab(Tab *tab, int *current_tab) {
    werase(tab->tab_icon);
    box(tab->tab_icon, 0, 0);
    mvwprintw(tab->tab_icon, 1, 2, "%d", (*current_tab)+1);
    wrefresh(tab->tab_icon);
}

void new_tab(Ui *ui, int *current_tab) {
    int starty, startx, count, id;
    if (ui->tab_count > 0) unset_current_tab(&ui->tabs[*current_tab], &(*current_tab));
    *current_tab = ui->tab_count;
    ui->tab_count++;
    count = ui->tab_count;
    id = count - 1;
    starty = 0;
    startx = 5 * id;
    ui->tabs = (Tab*)realloc(ui->tabs, (count) * sizeof(Tab));
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
    set_current_tab(&ui->tabs[id], &id);
}

void free_tab(Tab *tab) {
    if (tab->tab_icon) {
        werase(tab->tab_icon);
        wrefresh(tab->tab_icon);
        delwin(tab->tab_icon);
        tab->tab_icon = NULL;
    }
    if (tab->main) {
        werase(tab->main);
        wrefresh(tab->main);
        delwin(tab->main);
        tab->main = NULL;
    }
    if (tab->data) {
        free(tab->data);
        tab->data = NULL;
    }
    tab->is_logged_in = 0;
    tab->row_count = 0;
}


void close_tab(Ui *ui, int *current_tab) {
    int target = *current_tab, i = 0, startx = 0;
    unset_current_tab(&ui->tabs[target], &(target));

    free_tab(&ui->tabs[target]);

    for (i = target; i < ui->tab_count - 1; i++) {
        ui->tabs[i] = ui->tabs[i + 1];
    }

    ui->tab_count--;
    ui->tabs = (Tab*)realloc(ui->tabs, ui->tab_count * sizeof(Tab));

    if (*current_tab == ui->tab_count) *current_tab = ui->tab_count - 1;

    for (i = 0; i < ui->tab_count; i++) {

        mvwin(ui->tabs[i].tab_icon, 0, startx);
        werase(ui->tabs[i].tab_icon);
        box(ui->tabs[i].tab_icon, 0, 0);
        mvwprintw(ui->tabs[i].tab_icon, 1, 2, "%d", i+1);

        touchwin(ui->tabs[i].main);
        wrefresh(ui->tabs[i].main);
        wrefresh(ui->tabs[i].tab_icon);
        startx += 5;
    }
    set_current_tab(&ui->tabs[*current_tab], &(*current_tab));
}

void ui_end(Ui *ui) {
    int i, tab_count;
    tab_count = ui->tab_count;
    for (i = 0; i < tab_count; i++) {
        free_tab(&ui->tabs[i]);
    }

    free(ui->tabs);
    ui->tabs = NULL;
    ui->tab_count = 0;

    for (i = 0; i < 2; i++) {
        if (ui->menu_bar[i]) {
            delwin(ui->menu_bar[i]);
            ui->menu_bar[i] = NULL;
        }
    }
    endwin();
}