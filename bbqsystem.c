#include <ncurses.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
  int ch, row, col;         //declare ch
    initscr();              //initialize curses
    getmaxyx(stdscr,row,col);
    raw();                  //line buffering disabled
    keypad(stdscr, TRUE);   //F1, F2, etc activated
    noecho();

    char intro[]="BBQ System Tweak Tool\n";
    char opt1[]="Selection1";
    char opt2[]="Selection2\n";
    int left_third = (col-strlen(opt1))/3;
    int right_third = (col-strlen(opt2))/1.5;

    mvprintw(0, (col-strlen(intro))/2, "%s",intro); 
    mvprintw(1,left_third, "%s",opt1);
    mvprintw(1,right_third, "%s", opt2);
    ch = getch();   //this is why we call raw(), to not have
                    //have to press "return" after every 
                    //keypress
    if(ch == KEY_F(1)){
        printw("This is where I'll put some help");
    }
    //obviously need to spawn some windows and add logic
    else{
        printw("we'll echo our choices here\n");
        attron(A_BOLD);
        printw("%c", ch);
        attroff(A_BOLD);
    }
    refresh();
    getch();
    endwin();

    return 0;
}
