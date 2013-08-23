#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;
int alpha = 1;

char *choices[] = { 
			"BBQ ACPI-CPU",
			"BBQ CPU Modules",
			"BBQ Mem",
			"CPU Info",
			"Exit",
		  };
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{	
	while(alpha != 0){
		WINDOW *menu_win;
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
		while (choice == 0){
			c = wgetch(menu_win);
			switch(c){
				case KEY_UP:
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
					mvprintw(15, 0, "Please Choose an option.");
					refresh();
					break;
			}
			print_menu(menu_win, highlight);
			if(choice != 0)	/* User did a choice come out of the infinite loop */
				break;
		}	
		if(choice == 5){	//clean exit, requires change if main menu has more items
			endwin();
			printf("\033[2J\033[1;H");
			printf("\n\n\033[1;31mHappy roasting!\033[1;m\n\n");
			alpha = 0;
			exit(1);
		}
		else if(choice == 1){ //BBQ CPU Routine
			int mode;
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33mGoverning Settings for acpi-cpufreq.\033[1;m\n");
			printf("Press a number to go set value and go to menu.\n");
			printf("\033[1;31m1).\033[1;mConservative.\n");
			printf("\033[1;31m2).\033[1;mPowersave.\n");
			printf("\033[1;31m3).\033[1;mOnDemand.\n");
			printf("\033[1;31m4).\033[1;mPerformance.\n");
			scanf("%d", &mode);
			if(mode == 1){
				printf("Conservative chosen\n");
				system("sudo cpufreq-set -g conservative");//needs looped through CPUs
			}
			else if(mode == 2){
				printf("Powersave chosen\n");
				system("sudo cpufreq-set -g powersave");//needs loop
			}
			else if(mode == 3){
				printf("On Demand chosen\n");
				system("sudo cpufreq-set -g ondemand");//needs loop
			}
			else if(mode == 4){
				printf("Performance Chosen\n");
				system("sudo cpufreq-set -g performance");//needs loop
			}
			else{
				printf("\033[1;31m...no valid choice made!\033[1;m");
			}
			getch();
			reset_prog_mode();
			refresh();
			choice = 0;
		}
		else if(choice == 2){ //BBQ List kernel modules 
			int mode;
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33mAvailable Kernel Modules on Your System.\033[1;m\n");
			system("ls /lib/modules/$(uname -r)/kernel/drivers/cpufreq/");
			getch();
			reset_prog_mode();
			refresh();
		}
		else if(choice == 3){ //BBQ 3rd Routine
			int mode;
			def_prog_mode();
			endwin();
			printf("\033[1;33mThis is where the 3rd set of choices will go.\033[1;m\n");
			printf("Press a number to go set value and go to menu.");
			scanf("%d", &mode);
			printf("You chose %d\n", mode);
			getch();
			reset_prog_mode();
			refresh();
		}
		else if(choice == 4){ //BBQ System Frequency information
			int mode;
			def_prog_mode();
			endwin();
			printf("\033[1;33mCpufreq Info\033[1;m\n");
			system("cpufreq-info");
			//scanf("%d", &mode);
			//printf("You chose %d\n", mode);
			getch();
			reset_prog_mode();
			refresh();
		}
		clrtoeol();
		refresh();
	}
	endwin();
	return 0;
}


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i){	
		if(highlight == i + 1){
			wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
