#include <curses.h>	// ncurses header file.
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void Border(){
	//if (x == 1 || x==COLS-1) 
	//if (y==1 || y==LINES-1)

	for (int i=1; i<=LINES-1; i++){
		mvaddch(i,0,'+');
		mvaddch(i,COLS-1,'+');
	}
	for (int j=0; j<=COLS-1; j++){
		mvaddch(1,j,'+');
		mvaddch(LINES-1,j,'+');
	}
return;
}

void DrawSnake(size_t len, int snake[]){
	for (int i=0; i<len; i++){
		int x=snake[i]%COLS;
		int y=(snake[i]-x)/COLS+1;
		mvaddch(y,x,'0');
	}
	return;
}

void Food(int size, int plat[]){
	srand(time(NULL));
	int a=rand()%(COLS*LINES)+1;
	int x=a%COLS;
	int y=(a-x)/COLS+1;
	plat[(y-1)*COLS+x]=1;

	for(int i=0; i<size; i++){ 
		if(plat[i]==1){
			int x=i%COLS;
			int y=(i-x)/COLS+1;
			mvaddch(y,x,'$');
		} 
	}
	Border();
}

int Check(int length, int snake[]){
	for (int i=0; i<length; i++){
		if ( snake[0]==snake[i] && i!=0 ) return 0;
		//Border case.
		int x=snake[i]%COLS;
		int y=(snake[i]-x)/COLS+1;
		if (x == 0 || x == COLS-1) return 0;
		if (y == 1 || y == LINES-1) return 0;
	}
	return 1;
}

int main(){
	
	int snake[10000];
	int plat[10000];
	
	initscr();	// Initialize the ncurses lib
	cbreak();      // Disbale keyboard line buffering
	curs_set(FALSE);	// Hide cursor
	noecho();	// Don't echo keyboard inputs to screen
	keypad(stdscr, TRUE);	// Enable arrow keys
	nodelay(stdscr, TRUE); 

	int y0=LINES/2-5, x0=COLS/2; // Actual screen dim is LINES x COLS
	int length=3;
	snake[0]=x0+(y0-1)*COLS;
	snake[1]=snake[0]+COLS;
	snake[2]=snake[1]+COLS;
	
	DrawSnake(length, snake);
	refresh(); // Copy screen buffer to display	

	int temp;
	int ch;
	int k=1;
	int times=0;

	while( Check(length,snake)==1  && ch != KEY_F(1) ){
		clear();
		int temp2=snake[length-1];
		int ch = getch();
		switch(ch) {
			case KEY_LEFT : k=1; break;
			case KEY_RIGHT: k=2; break;
			case KEY_UP   : k=3; break;
			case KEY_DOWN : k=4; break;
		}
		
		if (k==1) temp=snake[0]-1;
		if (k==2) temp=snake[0]+1;
		if (k==3) temp=snake[0]-COLS;
		if (k==4) temp=snake[0]+COLS; 
		
		for(int i=0 ; i<=length-2; i++)	snake[length-1-i]=snake[length-2-i];
			snake[0]=temp;

		if (plat[snake[0]]==1){
			plat[snake[0]]=0;
			length=length+1;
			snake[length-1]=temp2;
		}

		clear();
		if (times%8 == 0)	Food(COLS*LINES,plat); //Approximately 1.0 second per food.
		DrawSnake(length, snake);
		refresh();
		
		if (k==3 || k==4) usleep(150000);
		if (k==1 || k==2) usleep(100000);//0.1s per move
		
	}

	//Terminate the game.
	clear();
	endwin();     // Shutdown ncurses and return to normal terminal mode.
	printf("The Score Is: %d !\n", length);                                 

return 0;
}

