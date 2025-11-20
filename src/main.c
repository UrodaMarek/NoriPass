#include <ncurses.h>
#include "ui.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int choice, current_tab = 0, is_logged_in, flag = 1;
    Ui ui;
    ui_init(&ui);
    new_tab(&ui, &current_tab);
    while (flag) {
        is_logged_in = ui.tabs[current_tab].is_logged_in;
        wrefresh(ui.menu_bar[is_logged_in]);
        choice = wgetch(ui.menu_bar[is_logged_in]);
        switch(choice) {
            case KEY_F(1):
                if ((ui.tab_count + 1) < 9) {
                    new_tab(&ui, &current_tab);
                }
                break;
            case KEY_F(2):
                if (ui.tab_count == 1) {
                    flag = 0;
                    break;
                }
                close_tab(&ui, &current_tab);
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
            case KEY_LEFT:
                change_tab(&ui, &current_tab, 'l');
                break;
            case KEY_RIGHT:
                change_tab(&ui, &current_tab, 'r');
                break;
        }
    }
    ui_end(&ui);
    return 0;
}