/*BBQCPU System Tool
Copyright (C) 2013  Joe Brock

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/


#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;
int alpha = 1;

char *choices[] = { 
			"BBQ ACPI-CPU",
			"BBQ CPU Modules",
			"Tutor Mode",
			"CPU Info",
			"Create Detailed Info File",
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
		if(choice == 6){	//clean exit, requires change if main menu has more items
			endwin();
			printf("\033[2J\033[1;H");
			printf("\n\n\033[1;31mHappy roasting!\033[1;m\n\n");
			alpha = 0;
			exit(1);
		}
		else if(choice == 1){ //BBQ CPU Routine
			int fmode, numCPU, dec;
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33mGoverning Settings for acpi-cpufreq.\033[1;m\n");
			printf("Press a number to go set value and go to menu.\n");
			printf("\033[1;31m1).\033[1;mConservative.\n");
			printf("\033[1;31m2).\033[1;mPowerSave.\n");
			printf("\033[1;31m3).\033[1;mOn Demand\n");
			printf("\033[1;31m4).\033[1;mPerformance.\n");
			printf("\033[1;31m5).\033[1;mKeep Current.\n");
			numCPU = sysconf( _SC_NPROCESSORS_ONLN );
			scanf("%d", &fmode);
			if(fmode == 1){
				printf("\033[1;32mConservative chosen\033[1;m\n");
				system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo conservative > $cpu; done");
			}
			else if(fmode == 2){
				printf("\033[1;32mPowersave chosen\033[1;m\n");
				system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo powersave > $cpu; done");
			}
			else if(fmode == 3){
				printf("\033[1;32mOn Demand chosen\033[1;m\n");
				system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo ondemand > $cpu; done");
			}
			else if(fmode == 4){
				printf("\033[1;32mPerformance Chosen\033[1;m\n");
				system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo performance > $cpu; done");
			}
			else if(fmode ==5){
				printf("\033[1;32mNothing Changed\033[1;m\n");
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
		else if(choice == 3){ //BBQ Expert Mode
			int mode;
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");			
			printf("\033[1;33m\tVerbose Expert Mode\033[1;m\n");
			printf("NOT COMPLETE YET.");
			printf("Type '\033[1;32mexit\033[1;m' at any time to return to scripted mode\n\n");
			printf("To load a specific loadable kernel module, type in\n\033[1;31m");
			printf("\tmodprobe \033[1;32mmodule_name\033[1;m\n");
			printf("To remove a specific loadable kernel module, type in\n\033[1;31m");
			printf("\trmmod \033[1;32mmodule_name\033[1;m\n");
			printf("To list ALL modules, use\n");
			printf("\t\033[1;31mlsmod\033[1;m\n");
			printf("then type '\033[1;32mexit'\033[1;m to continue the script.\n\n");
			system("/bin/bash");
			printf("\033[2J\033[1;H");
			printf("To set MAX clock frequency, use\n");
			printf("\t\033[1;31mcpufreq-set -u \033[1;32m (your setting)\033[1;31mMHz or GHz\033[1;m\n\n");
			printf("To set MIN clock frequency, use\033[1;31m\n");
			printf("\tcpufreq-set -d \033[1;32m (your setting)\033[1;31mMhz or GHz\033[1;m\n\n");
			system("/bin/bash");
			printf("\033[2J\033[1;H");
			printf("You can ATTEMPT to ignore BIOS settings for CPU max value\n");
			printf("by setting the value in /sys/module/processors/parameters/ignore_ppc\n");
			printf("from 0 to 1.  This is a temporary option.\n\n");
			printf("For a permanent change, append \033[1;32mprocessor.ignore_ppc=1\033[1;m to the kernel boot line, or:\n\n");
			printf("\033[1;34mtouch /etc/modprobe.d/ignore_ppc.conf\033[1;m\n");
			printf("\033[1;34mecho 'option processor ignore_ppc=1' > /etc/modprobe.d/ignore_ppc.conf\n\n\033[1;m");
			printf("this option is potentially damaging so use with caution.\n");
			system("/bin/bash");
			printf("\033[2J\033[1;H");
			reset_prog_mode();
			refresh();
		}
		else if(choice == 4){ //BBQ System Frequency information
			//int mode;
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33mCpufreq Info\033[1;m\n");
			system("cpufreq-info");
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
