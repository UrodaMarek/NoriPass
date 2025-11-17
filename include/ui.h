#include <ncurses.h>
#ifndef UI_H
#define UI_H

typedef struct {
    int id;
    char login[128];
    char password[128];
} Row;

typedef struct {
    int id;
    int is_logged_in;
    WINDOW *window;
    Row *data;
    int size;
} Tab;

typedef struct {
    Tab *tabs;
    WINDOW *main;
    WINDOW *menu_bar;
} Ui;

void ui_init(Ui *ui);
//void add_password();
//void ui_end()

//void show_menu();
//void list_passwords();
//void manage_password();
//void log_in();

#endif
