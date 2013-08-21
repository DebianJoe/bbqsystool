#include <ncurses.h>
#include <stdio.h>
#include <string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main (int argc, char *argv[]) //thinking about switches, perhaps colorless?
{
    int ch, row, col;       //declare ch
    int startx, starty, width, height;
    initscr();              //initialize curses
    getmaxyx(stdscr,row,col);
    raw();                  //line buffering disabled
    keypad(stdscr, TRUE);   //F1, F2, etc activated
    noecho();
    start_color();

    height = 30;
    width = 10;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;

    char intro[]="BBQ System Tweak Tool\n";
    char opt1[]="Selection1";
    char opt2[]="Selection2";
    char opt3[]="Whatever";
    char opt4[]="Junk";
    int centered = (col-strlen(intro))/2;
    int left_third = (col-strlen(opt1))/3;
    int right_third = (col-strlen(opt2))/1.5;

    mvprintw(0,centered, "%s",intro); 
    mvprintw(2,left_third, "%s",opt1);
    mvprintw(2,right_third, "%s", opt2);
    mvprintw(3,left_third, "%s", opt3);
    mvprintw(3,right_third, "%s", opt4);
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
