#include <ncurses.h>
#include "ui.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int choice;
    int default_tab = 0;
    Ui ui;
    ui_init(&ui);
/*
    while (1) {
        if (size_of(tabs) == 0) {
            add_table();
            tabs = (Tab*)realloc(tabs,sizeof(Tab))
        }
        show_menu();
        

        switch(choice) {
            case 'N':
                new_tab();
                break;
            case 2:
                add_password();
                break;
            case 3:
                ui_end();
                exit(0);
        }
    }
    */
    getchar();
    ui_close();
    return 0;
}