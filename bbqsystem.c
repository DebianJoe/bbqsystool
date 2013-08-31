/*BBQCPU System Tool
Copyright (C) 2013  Joe Brock

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/

//TODO: PID/Pmap by pid tutorial


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
			"Tutor Mode",
			"CPU Info",
			"Create Detailed Info File",
            "htop",
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
		int c, row, col;

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
			getmaxyx(stdscr, row, col);
			if(row < 22 || col < 60){
				endwin();
				printf("\n\033[1;31mTerm must be at least 60 x 22\n\n\033[1;m");
				alpha = 0;
				exit(1);
			}
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
		if(choice == 7){	//clean exit, requires change if main menu has more items
			endwin();
			printf("\033[2J\033[1;H");
			printf("\n\n\033[1;31mHappy roasting!\033[1;m\n\n");
			alpha = 0;
			exit(1);
		}
		else if(choice == 1){ //BBQ CPU Routine
			int fmode;
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
			scanf("%d", &fmode);
			switch(fmode){
				case '1':
					printf("\033[1;32mConservative chosen\033[1;m\n");
					system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo conservative > $cpu; done");
					break;
				case '2':
					printf("\033[1;32mPowersave chosen\033[1;m\n");
					system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo powersave > $cpu; done");
					break;
				case '3':
					printf("\033[1;32mOn Demand chosen\033[1;m\n");
					system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo ondemand > $cpu; done");
					break;
				case '4':
					printf("\033[1;32mPerformance Chosen\033[1;m\n");
					system("for cpu in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do echo performance > $cpu; done");
					break;
				default:
					printf("\033[1;32mNothing Changed\033[1;m\n");
			}
			getch();
			reset_prog_mode();
			refresh();
			choice = 0;
		}
		else if(choice == 2){ //BBQ List kernel modules 
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33mAvailable CPU  Kernel Modules on Your System.\033[1;m\n");
			system("ls /lib/modules/$(uname -r)/kernel/drivers/cpufreq/");
			getch();
			reset_prog_mode();
			refresh();
		}
		else if(choice == 3){ //BBQ Tutor Mode
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33m\tVerbose Expert Mode\033[1;m\n");
			printf("At the BBQ, it is believed that it's better\n");
			printf("to teach a man to fish than to simply give \n");
			printf("them the fish.\n\n");
			printf("This mode is designed to walk the user through.\n");
			printf("performing CPU kernel adjustments from command line.\n\033[1;33m{press RETURN to continue}\033[1;m\n");
			getch();
			//start Kernel Module loading section
			printf("\033[2J\033[1;H");
			printf("Type '\033[1;32mexit\033[1;m' at any time to exit the shell\nand return to scripted mode\n\n");
			printf("To load a specific loadable kernel module, type in\n\033[1;31m");
			printf("\tmodprobe \033[1;32mmodule_name\033[1;m\n");
			printf("To remove a specific loadable kernel module, type in\n\033[1;31m");
			printf("\trmmod \033[1;32mmodule_name\033[1;m\n");
			printf("To list ALL modules, use\n");
			printf("\t\033[1;31mlsmod\033[1;m\n");
			printf("then type '\033[1;32mexit'\033[1;m to continue the script.\n\n");
			system("/bin/bash");
			//start max/min CPU freq section
			printf("\033[2J\033[1;H");
			printf("To set MAX clock frequency, use\n");
			printf("\t\033[1;31mcpufreq-set -u \033[1;32m (your setting)\033[1;31mMHz or GHz\033[1;m\n\n");
			printf("To set MIN clock frequency, use\033[1;31m\n");
			printf("\tcpufreq-set -d \033[1;32m (your setting)\033[1;31mMhz or GHz\033[1;m\n\n");
			system("/bin/bash");
			//start BIOS override section
			printf("\033[2J\033[1;H");
			printf("You can ATTEMPT to ignore BIOS settings for CPU max value\n");
			printf("by setting the value in /sys/module/processors/parameters/ignore_ppc\n");
			printf("from 0 to 1.  This is a temporary option.\n\n");
			printf("For a permanent change, append \033[1;32mprocessor.ignore_ppc=1\033[1;m to the kernel boot line, or:\n\n");
			printf("\033[1;34mtouch /etc/modprobe.d/ignore_ppc.conf\033[1;m\n");
			printf("\033[1;34mecho 'option processor ignore_ppc=1' > /etc/modprobe.d/ignore_ppc.conf\n\n\033[1;m");
			printf("this option is potentially damaging so use with caution.\n");
			system("/bin/bash");
			//start proc vmstat section
			printf("\033[2J\033[1;H");
			printf("To read the generated files regarding your system's configuration use\n");
			printf("\033[1;34mcat /proc/*info\ncat /proc/mounts\nvmstat\nvmstat -m\033[1;m\n");
			printf("use '\033[1;34mman vmstat\033[1;m' for more details.\n");
			system("/bin/bash");
			//start process ID pid/pmap section
			printf("\033[2J\033[1;H");
			printf("To display a diagram of running processes, type:\n");
			printf("\033[1;34mpstree\033[1;m\n");
			printf("To find the PID number for any of the processes:\n");
			printf("\033[1;34mpidof \033[1;32m<the program>\033[1;m\n");
			printf("\n*it is best to supply a full path if possible.\n");
			printf("to avoid getting a symlink's process ID.\n\n");
			printf("After getting the PID number, use:\n");
			printf("\033[1;34mpmap -x \033[1;32m<PID_Number>\033[1;m");
			printf("to get a full memory map of the process.\n");
			system("/bin/bash");
			//start Kernel Removal Section
			printf("\033[2J\033[1;H");
			printf("\033[1;32mOld Kernel Removal (manual method)\033[1;m\n\n");
			printf("To remove any kernel not being used still, use \n\033[1;34muname -r\033[1;m\nto check your current kernel.");
			printf("  Then type in \n\033[1;34mdpkg --list | grep linux-image\033[1;m\n to list all installed kernel images.\n\n");
			printf("To list ONLY the headers and image that you currently are NOT booted into.  Use:\n");
			printf("\033[1;34mdpkg -l|awk '/^ii  linux-(im|he)/{print $2}'|grep -v $(uname -r)\033[1;m\n");
			printf("If you are satisfied with the list, then you can remove them all with\n");
			printf("\033[1;34msudo apt-get remove $(dpkg -l|awk '/^ii  linux-(im|he)/{print $2}'|grep -v $(uname -r))\033[1;m\n");
			printf("Otherwise, you can remove individual kernel images/headers.\n");
			system("/bin/bash");
			reset_prog_mode();
			refresh();
		}
		else if(choice == 4){ //BBQ System Frequency information
			def_prog_mode();
			endwin();
			printf("\033[2J\033[1;H");
			printf("\033[1;33mCpufreq Info\033[1;m\n");
			system("cpufreq-info");
			getch();
			reset_prog_mode();
			refresh();
		}
		else if(choice == 5){
			system("cat /proc/*info > ~/detailed_cpu_file");
			system("cat /proc/mounts >> ~/detailed_cpu_file");
		}
        else if(choice == 6) {
            def_prog_mode();
            endwin();
            system("exec 'htop'");
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
