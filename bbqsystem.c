#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main (int argc, char *argv[]) //thinking about switches, perhaps colorless?
{
    WINDOW *main_win;
    int ch, row, col;       //declare ch
    int startx, starty, width, height;
    initscr();              //initialize curses
    getmaxyx(stdscr,row,col);
    raw();                  //line buffering disabled
    keypad(stdscr, TRUE);   //F1, F2, etc activated
    noecho();
    if(has_colors()== FALSE)
    {   endwin();
        printf("Your Terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    height = 10;
    width = 50;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;

    char intro[]="BBQ System Tweak Tool\n";
    char opt1[]="BBQ CPU";
    char opt2[]="Selection2";
    char opt3[]="Whatever";
    char opt4[]="Junk";
    char key_exit[]="Press F12 to exit";
    char help[]="Press F1 for  Help";
    int centered = (col-strlen(intro))/2;
    int left_third = (col-strlen(opt1))/3;
    int right_third = (col-strlen(opt2))/1.5;

    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    mvprintw(0,centered, "%s",intro); 
    attroff(COLOR_PAIR(1));
    attroff(A_BOLD);
    mvprintw(2,left_third, "%s",opt1);
    mvprintw(2,right_third, "%s", opt2);
    mvprintw(3,left_third, "%s", opt3);
    mvprintw(3,right_third, "%s", opt4);
    mvprintw(7,centered, "%s", key_exit);
    mvprintw(6,centered, "%s", help);
    ch = getch();   //this is why we call raw(), to not have
                    //have to press "return" after every 
                    //keypress
    if(ch == KEY_F(12)){
        endwin();
        printf("Happy Roasting\n");
        exit(1);
    }
    else if(ch == KEY_F(1)){
        mvprintw(8,0,"This is where I'll put some help");
    }
    //obviously need to spawn some windows and add logic
    else{
        mvprintw(8,0,"we'll echo our choices here\n");
        attron(A_BOLD);
        printw("%c", ch);
        attroff(A_BOLD);
    }
    refresh();
    getch();
    while((ch =getch()) != KEY_F(12))
    {{//switch(ch)
       // {   case KEY(1):
        getch();
         }}
    endwin();

    return 0;
}
