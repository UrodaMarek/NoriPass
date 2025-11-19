#include <ncurses.h>
#include "ui.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int choice, default_tab = 0, is_logged_in, flag = 1;
    Ui ui;
    ui_init(&ui);
    new_tab(&ui);
    while (flag) {
        is_logged_in = ui.tabs[default_tab].is_logged_in;
        wrefresh(ui.menu_bar[is_logged_in]);
        choice = wgetch(ui.menu_bar[is_logged_in]);
        switch(choice) {
            case KEY_F(1):
                new_tab(&ui);
                break;
            case KEY_F(2):
                //new_tab();
                break;
            case KEY_F(3):
                //new_tab();
                break;
            case KEY_F(4):
                //add_password();
                break;
            case KEY_F(5):
                flag = 0;
                break;
        }
    }
    getchar();
    ui_end();
    return 0;
}