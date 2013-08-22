#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

char *choices[] = { 
			"BBQ CPU",
			"BBQ WTF",
			"BBQ Mem",
			"BBQ Screen",
			"Exit",
		  };
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (40 - WIDTH) / 2;
	starty = (20 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	attron(A_BOLD);
	mvprintw(0, 8, "BBQ System Tweak Tool");
	attroff(A_BOLD);
	mvprintw(2, 4, "Use arrow keys to go up and down");
	mvprintw(3, 4, " Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(20, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	if(choice == 5){
		endwin();
		exit(1);
	}
	clrtoeol();
	refresh();
	getch();
	endwin();
	return 0;
}


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
