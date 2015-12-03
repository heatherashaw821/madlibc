////////////////////////////////////////////////////////////////////////////////
// THE SCOTCH-WARE LICENSE (Revision 0):
// <aaronryool/gmail.com> wrote this file. As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a shot of scotch in return
////////////////////////////////////////////////////////////////////////////////

#ifndef __COLORS_H
#define __COLORS_H

// Hide cursor
#define HIDE_CURSOR     "\e[?25l"

//Show cursor
#define SHOW_CURSOR     "\e[?25h"

// Cursor position
#define CURSOR(x, y) printf("\e[%i;%iH\n", y, x)

// Clear
#define CLEAR           "\e[2J"

// Reset
#define RESET		"\e[0m"

// Regular Colors
#define BLACK		"\e[030m"
#define RED	    	"\e[031m"
#define GREEN		"\e[032m"
#define YELLOW		"\e[033m"
#define BLUE		"\e[034m"
#define PURPLE		"\e[035m"
#define CYAN		"\e[036m"
#define WHITE		"\e[037m"

// Bold
#define BBLACK		"\e[130m"
#define BRED		"\e[131m"
#define BGREEN		"\e[132m"
#define BYELLOW		"\e[133m"
#define BBLUE		"\e[134m"
#define BPURPLE		"\e[135m"
#define BCYAN		"\e[136m"
#define BWHITE		"\e[137m"

// Underline
#define UBLACK		"\e[430m"
#define URED		"\e[431m"
#define UGREEN		"\e[432m"
#define UYELLOW		"\e[433m"
#define UBLUE		"\e[434m"
#define UPURPLE		"\e[435m"
#define UCYAN		"\e[436m"
#define UWHITE		"\e[437m"

///////////////////////////////////

// Background
#define BGBLACK		"\e[40m"
#define BGRED		"\e[41m"
#define BGGREEN		"\e[42m"
#define BGYELLOW	"\e[43m"
#define BGBLUE		"\e[44m"
#define BGPURPLE	"\e[45m"
#define BGCYAN		"\e[46m"
#define BGWHITE		"\e[47m"

// High Intensity
#define IBLACK		"\e[090m"
#define IRED		"\e[091m"
#define IGREEN		"\e[092m"
#define IYELLOW		"\e[093m"
#define IBLUE		"\e[094m"
#define IPURPLE		"\e[095m"
#define ICYAN		"\e[096m"
#define IWHITE		"\e[097m"

// Bold High Intensity
#define BIBLACK		"\e[190m"
#define BIRED		"\e[191m"
#define BIGREEN		"\e[192m"
#define BIYELLOW	"\e[193m"
#define BIBLUE		"\e[194m"
#define BIPURPLE	"\e[195m"
#define BICYAN		"\e[196m"
#define BIWHITE		"\e[197m"

// High Intensity backgrounds
#define BGIBLACK	"\e[0100m"
#define BGIRED		"\e[0101m"
#define BGIGREEN	"\e[0102m"
#define BGIYELLOW	"\e[0103m"
#define BGIBLUE		"\e[0104m"
#define BGIPURPLE	"\e[0105m"
#define BGICYAN		"\e[0106m"
#define BGIWHITE	"\e[0107m"

#endif //


