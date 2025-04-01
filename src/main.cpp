// #include <iostream>
#include <fstream>
#include <regex>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "inc/pages.h"

#define BELL "]"
//from stackoverflow
std::string do_replace( std::string const & in, std::string const & from, std::string const & to )
{
  return std::regex_replace( in, std::regex(from), to );
}
// also from stackoverflow
std::string operator * (std::string a, unsigned int b) {
    std::string output = "";
    while (b--) {
        output += a;
    }
    return output;
}

void renderPage(int a, std::string buffer, int e) {
	for(int i = 0; i < buffer.length(); i++) {
		if(a > 11) {
			if (a>23) break;
			if(buffer.at(i) == '\n'){
				a++;
				e=i+1;
				continue;
			}
	
			mvprintw(5+a-12, 1+i-e+22, "%c", buffer.at(i));
			if(inch() == '|') {
				a++;
				e=i+1;
				continue;
			}

		} else {
			if(buffer.at(i) == '\n'){
				a++;
				e=i+1;
				continue;
			}
	
			mvprintw(5+a, 1+i-e, "%c", buffer.at(i));
			if(inch() == '|') {
				a++;
				e=i+1;
				continue;
			}
		}
	}
}

void turnPageTimed() {
	refresh();
	usleep(100000);
	mvprintw(0, 0, "%s", pageTurn1);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", pageTurn2);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", pageTurn3);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", pageTurn4);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", pageTurn5);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", page);
	refresh();
		usleep(100000);

}
void turnPageTimedR() {
	refresh();
	usleep(100000);
	mvprintw(0, 0, "%s", pageTurn5);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", pageTurn4);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", pageTurn3);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", pageTurn2);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", pageTurn1);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", page);
	refresh();
	usleep(100000);

}
void turnFrontPageTimed() {
	refresh();
	usleep(100000);
	mvprintw(0, 0, "%s", frontPageTurn1);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn2);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn3);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn4);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn5);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", page);
	refresh();
		usleep(100000);

}
void turnFrontPageTimedR() {
	refresh();
	usleep(100000);
	mvprintw(0, 0, "%s", frontPageTurn5);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn4);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn3);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn2);
	refresh();
	usleep(100000);

	mvprintw(0, 0, "%s", frontPageTurn1);
	refresh();
		usleep(100000);

	mvprintw(0, 0, "%s", frontPage);
	refresh();
		usleep(100000);

}

int main(int argc, char* argv[]) {
	std::ifstream file(argv[1]);
	std::string buffer = "";
	char bufChar;
	while (file) {
		bufChar = file.get();
		buffer += bufChar;
	}
	file.close();
	int pageNum = 0;
		std::string bufferFull = buffer;
	std::string temp = "";
	initscr();
	noecho();
	int lineNumber =0;
	int xNumber=0;
	
		mvprintw(0, 0, "%s", frontPage);
		mvprintw(8, 24, "%s", buffer.substr(0, 19).c_str());
	/*for(int i = 0; i < hello.length(); i++) {
		if(a > 11) {
			if (a>23) break;
			if(hello.at(i) == '\n'){
				a++;
				e=i+1;
				continue;
			}
	
			mvprintw(5+a-12, 1+i-e+22, "%c", hello.at(i));
			if(inch() == '|') {
				a++;
				e=i+1;
				continue;
			}

		} else {
			if(hello.at(i) == '\n'){
				a++;
				e=i+1;
				
				continue;
			}
	
			mvprintw(5+a, 1+i-e, "%c", hello.at(i));
			if(inch() == '|') {
				a++;
				e=i+1;
				continue;
			}
		}
	}*/
	char input = ' ';
	for (;;) {

	buffer = do_replace(buffer, "\n", " ");
//	buffer = do_replace(buffer, BELL, "\n");
//	buffer.erase(0, ((pageNum-1)*504)-count);
	buffer.erase(0, ((pageNum-1)*504));
	renderPage(lineNumber, buffer, xNumber);
	if(pageNum != 0){	
//	buffer = do_replace(buffer, BELL, "\n");
	}
	
	buffer=bufferFull;
//	getch();
	again:
	input = (char)getch();
	if(input == 'd'){
	pageNum++;
	if(pageNum != 1) {
		turnPageTimed();
	} else {
		turnFrontPageTimed();
	}
	} else if(input == 'a'){
	if(pageNum == 1) {
		turnFrontPageTimedR();
		pageNum--;
	} else if(pageNum != 0) {
		pageNum--;
		turnPageTimedR();
	}
	} else if(input == 'l') {
		endwin();
		return 0;
	} else {
		goto again;
	}

//	turnPageTimed();
//	buffer.erase(0, (pageNum-1)*504);
//	buffer = do_replace(buffer, BELL, "\n");
//	renderPage(lineNumber, buffer, xNumber);
	if(pageNum == 0){
		mvprintw(0, 0, "%s", frontPage);
		mvprintw(8, 24, "%s", buffer.substr(0, 19).c_str());
	}
	refresh();
	}
	endwin();
	
}
