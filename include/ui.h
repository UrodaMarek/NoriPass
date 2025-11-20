#include <ncurses.h>
#ifndef UI_H
#define UI_H

typedef struct {
    int id;
    char login[128];
    char password[128];
} Row;

typedef struct {
    int is_logged_in;
    WINDOW *tab_icon;
    WINDOW *main;
    Row *data;
    int row_count;
} Tab;

typedef struct {
    Tab *tabs;
    WINDOW *menu_bar[2];
    int tab_count;
} Ui;

void ui_init(Ui *ui);
void new_tab(Ui *ui, int *current_tab);
void change_tab(Ui *ui, int *current_tab, char flag);
void close_tab(Ui *ui, int *current_tab);
void ui_end(Ui *ui);

//void show_menu();
//void list_passwords();
//void manage_password();
//void log_in();

#endif
