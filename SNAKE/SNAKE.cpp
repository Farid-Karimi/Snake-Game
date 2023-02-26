#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <fstream>

using namespace std;

void menu();
void setup();
void draw();
void input();
void logic();
void hidecursor();
void deathScreen();
void StartMenu(int&);
void clearScreen();
void saveHighScore();
int readHighScore();
//-----------------------------------------------------------------------------------------------------------
int dificulty;
int score;
int const width=20 , height=20;
bool GAMEOVER;
int Xtail[100];
int Ytail[100];
int Ntail;

struct location{
	int x,y;
};

location player , fruit;

enum eDirection {STOP=0 , LEFT , RIGHT , UP , DOWN};
eDirection dir;
//-----------------------------------------------------------------------------------------------------------
void clearScreen(){

    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;

    SetConsoleCursorPosition(hOut, Position);
}
//-----------------------------------------------------------------------------------------------------------
void setup(){
	player.x=width/2;
	player.y=height/2;
	dir = STOP;
	fruit.x = (rand() % (width-2))+1;
	fruit.y = (rand() % (height-2))+1;

	GAMEOVER = false;
	score = 0;
}
//-----------------------------------------------------------------------------------------------------------
void draw(){
	
	//color department :))
	int wallsColor=3;
	int fruitColor=4;
	int headColor=5;


    clearScreen();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, wallsColor);
    cout<<"\u2554";
    for(int i=1 ; i<width-1 ; i++)
    	cout<<"\u2550";
    	cout<<"\u2557";
    SetConsoleTextAttribute(hConsole, 15);
	cout<<endl;
	
    for (int i=0 ; i < height ; i++){
        for (int j=0 ; j < width ; j++){
        	
			if(j==0 || j==width-1){
        		SetConsoleTextAttribute(hConsole, wallsColor);
        		cout<<"\u2551";
        		SetConsoleTextAttribute(hConsole, 15);
			}
			else if(i==player.y && j==player.x){
			SetConsoleTextAttribute(hConsole, headColor);	
				cout<<"\u041E";
			SetConsoleTextAttribute(hConsole, 15);
			}
			else if(i==fruit.x && j==fruit.y){
			SetConsoleTextAttribute(hConsole, fruitColor);	
				cout<<"\u01D1";
			SetConsoleTextAttribute(hConsole, 15);
			}
			else{
				bool print = false;
				for(int k=0 ; k < Ntail ;k++){
					if(Xtail[k] == j && Ytail[k] == i){
						SetConsoleTextAttribute(hConsole, ((k+1)%13 +1));
						cout<<"o";
						SetConsoleTextAttribute(hConsole, 15);
						print = true;
					}
				}
				if(!print)
					cout<<" ";
			}
		}
	cout<<endl;	
	}
    SetConsoleTextAttribute(hConsole, wallsColor);
    cout<<"\u255A";
    for(int i=1 ; i<width-1 ; i++)
    	cout<<"\u2550";
    cout<<"\u255D";
    cout<<endl;
    cout<<"score: "<<score<<endl;
    SetConsoleTextAttribute(hConsole, 15);
}
//-----------------------------------------------------------------------------------------------------------
void input(){
	if(kbhit()){
		switch(getch()){
			case 'a':
			 dir=LEFT; 	break;
			case 's':
			 dir=DOWN; 	break;
			case 'd':
			 dir=RIGHT; break;
			case 'w':
			 dir=UP; 	break;
			case 'x':
			 menu(); 	break;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void logic(){
	int prevX = Xtail[0];
	int prevY = Ytail[0];
	int prev2X , prev2Y;
	Xtail[0]=player.x;
	Ytail[0]=player.y;
	for(int i=1 ; i<Ntail ; i++){
		prev2X = Xtail[i];
		prev2Y = Ytail[i];
		Xtail[i] = prevX;
		Ytail[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir){
		case UP:
		 player.y--;	 break;
		case DOWN:
		 player.y++;	 break;
		case LEFT:
		 player.x--;	 break;
		case RIGHT:
		 player.x++;	 break;
		default:
		 break;
	}
	//deathScreen by wallsColor
	// if(player.x >= width || player.x <= 0 || player.y >= height || player.y < 0){
	// 	GAMEOVER=true;
	// }
	
	if (player.x >= width)
		player.x=0;
	else if (player.x<0) 
		player.x=width-1;
	if (player.y >= height)
		player.y=0;
	else if (player.y<0) 
		player.y=height-1;

	for(int i=0 ; i<Ntail ; i++){
		if(Xtail[i]==player.x && Ytail[i]==player.y){
			GAMEOVER=true;
		}
	}
	
	if(player.x == fruit.y && player.y == fruit.x){
		score++;
		fruit.x = (rand() % (width-2))+1;
		fruit.y = (rand() % (height-2))+1;
		Ntail++;
	}
}
//-----------------------------------------------------------------------------------------------------------
void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
//-----------------------------------------------------------------------------------------------------------
void menu(){
    system("cls");
    int primaryColor = 2;
    int secondaryColor = 6;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, primaryColor);
	cout<<"╔══════════════════════════════════════╗"<<endl;
	
	cout<<"║     ";
    SetConsoleTextAttribute(hConsole, secondaryColor);	
	cout<<"___  _  _    _    _  __ ___";
    SetConsoleTextAttribute(hConsole, primaryColor);
	cout<<"      ║"<<endl;

	cout<<"║    ";
    SetConsoleTextAttribute(hConsole, secondaryColor);
	cout<<"/ __|| \\| |  /_\\  | |/ /| __|";
    SetConsoleTextAttribute(hConsole, primaryColor);
	cout<<"     ║"<<endl;

	cout<<"║    ";
    SetConsoleTextAttribute(hConsole, secondaryColor);
	cout<<"\\__ \\| .` | / _ \\ | ' < | _|";
    SetConsoleTextAttribute(hConsole, primaryColor);
	cout<<"      ║"<<endl;
    
    cout<<"║    ";
    SetConsoleTextAttribute(hConsole, secondaryColor);
    cout<<"|___/|_|\\_|/_/ \\_\\|_|\\_\\|___|";
    SetConsoleTextAttribute(hConsole, primaryColor);
    cout<<"     ║"<<endl;
    
    cout<<"║                                      ║"<<endl;
	
	cout<<"╚══════════════════════════════════════╝"<<endl;

	
	cout<<"	   ╔════════════════╗			"<<endl;
	
	cout<<"	   ║    ";
	SetConsoleTextAttribute(hConsole, secondaryColor);
	cout<<"1-RESUME";
    SetConsoleTextAttribute(hConsole, primaryColor);
	cout<<"    ║			"<<endl;
	
	cout<<"	   ╚════════════════╝			"<<endl;
	
	
	cout<<"	   ╔════════════════╗			"<<endl;
	
	cout<<"	   ║     ";
	SetConsoleTextAttribute(hConsole, secondaryColor);
	cout<<"2-EXIT";
    SetConsoleTextAttribute(hConsole, primaryColor);
	cout<<"     ║			"<<endl;
	
	cout<<"	   ╚════════════════╝			"<<endl;
	SetConsoleTextAttribute(hConsole, 15);

		switch(getch()){
			case '1':
			 Beep(850,100);
			 break;
			case '2':
			 Beep(850,100);
			 exit(0); break;
		}
	system("cls");
}
//-----------------------------------------------------------------------------------------------------------
void deathScreen(){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"════════════════════════════════════════════════════════════════"<<endl; Sleep(50);
    SetConsoleTextAttribute(hConsole, 12);
    cout<<"     __     __ ____   _    _   _____  _____  ______  _____      "<<endl; Sleep(50);
    cout<<"     \\ \\   / // __ \\ | |  | | |  __ \\|_   _||  ____||  __ \\     "<<endl; Sleep(50);
    cout<<"      \\ \\_/ /| |  | || |  | | | |  | | | |  | |__   | |  | |    "<<endl; Sleep(50);
    cout<<"       \\   / | |  | || |  | | | |  | | | |  |  __|  | |  | |    "<<endl; Sleep(50);
    cout<<"        | |  | |__| || |__| | | |__| |_| |_ | |____ | |__| |    "<<endl; Sleep(50);
    cout<<"        |_|   \\____/  \\____/  |_____/|_____||______||_____/     "<<endl; Sleep(50);
    cout<<"                                                                "<<endl; Sleep(50);
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"════════════════════════════════════════════════════════════════"<<endl;
    cout<<"                   ══════════════════════════                   "<<endl;
    SetConsoleTextAttribute(hConsole, 12);
    cout<<"                           Score: "<< score <<"                   "<<endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout<<"                   ══════════════════════════                   "<<endl;    
    SetConsoleTextAttribute(hConsole, 12);
    
    int currentHighScore=readHighScore();
    
    if(score>currentHighScore){
    	saveHighScore();
    }
    currentHighScore=readHighScore();
    cout<<"                         HighScore:"<<currentHighScore<<endl;

	system("pause");
}
//-----------------------------------------------------------------------------------------------------------
void StartMenu(int &dificulty){
    int BorderColor = 9;
    int InsideColor = 11;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BorderColor);
    cout<<"                    ╒════════════════════════════════╕                 "<<endl;

    cout<<"                    │ ";
    cout<<"       ";
    SetConsoleTextAttribute(hConsole, InsideColor);    
    cout<<"CHOOSE DIFFICULTY       ";
    SetConsoleTextAttribute(hConsole, BorderColor);    
    cout<<"│                 "<<endl;

    cout<<"                    ╘════════════════════════════════╛                 "<<endl;

    SetConsoleTextAttribute(hConsole, 10);
    cout<<"                         ╒═══╤══════════════════╕                 "<<endl;

    cout<<"                         │ ";
    SetConsoleTextAttribute(hConsole, 2);
    cout<<"1";
    SetConsoleTextAttribute(hConsole, 10);
    cout<<" │       ";
    SetConsoleTextAttribute(hConsole, 2);    
    cout<<"EASY       ";
    SetConsoleTextAttribute(hConsole, 10);    
    cout<<"│                 "<<endl;

    cout<<"                         ╘═══╧══════════════════╛                 "<<endl;    

    SetConsoleTextAttribute(hConsole, 6);
    cout<<"                         ╒═══╤══════════════════╕                 "<<endl;

    cout<<"                         │ ";
    SetConsoleTextAttribute(hConsole, 6);
    cout<<"2";
    SetConsoleTextAttribute(hConsole, 6);
    cout<<" │      ";
    SetConsoleTextAttribute(hConsole, 6);    
    cout<<"NORMAL      ";
    SetConsoleTextAttribute(hConsole, 6);    
    cout<<"│                 "<<endl;

    cout<<"                         ╘═══╧══════════════════╛                 "<<endl;    

    SetConsoleTextAttribute(hConsole, 4);
    cout<<"                         ╒═══╤══════════════════╕                 "<<endl;

    cout<<"                         │ ";
    SetConsoleTextAttribute(hConsole, 12);
    cout<<"3";
    SetConsoleTextAttribute(hConsole, 4);
    cout<<" │       ";
    SetConsoleTextAttribute(hConsole, 12);    
    cout<<"HARD       ";
    SetConsoleTextAttribute(hConsole, 4);    
    cout<<"│                 "<<endl;

    cout<<"                         ╘═══╧══════════════════╛                 "<<endl; 
		
	switch(getch()){
		case '1':
		 dificulty=55;	Beep(850,100);	 break;
		case '2':
		 dificulty=40;	Beep(850,100);	 break;
		case '3':
		 dificulty=25;	Beep(850,100);	 break;	 
	}
		system("cls");
}

void saveHighScore(){
	fstream fio;
	fio.open("HighScore.txt" , ios::out);
	if(fio){
		fio << score;
	}
	fio.close();
}
int readHighScore(){
	fstream fio;
	int high;
	fio.open("HighScore.txt" , ios::in);
	if(fio){
		while(!fio.eof()){
			fio>>high;
		}
	}
	fio.close();
	return high;
}

int main(){

	hidecursor();
	
	srand(time(0));
	setup();
	StartMenu(dificulty);

	while (!GAMEOVER){
        draw();
        input();
        logic();
        Sleep(dificulty);
    }
    deathScreen();

    return 0;
}