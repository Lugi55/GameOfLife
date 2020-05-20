/*
 ============================================================================
 Name        : GameOfLife.c
 Author      : Lugi55
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */




#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


int cursor(int x,int y);		//Funktion cursor setzen
int hidecursor(int s);			//Funktion cursor hiden
int Rand(int X, int Y);			//Rand ausgeben

int main(void) {
		//Initialisierung der Variablen
		/////////////////////////////////////////////////////////////////////////////////////////////////
		const int X=45,Y=45;		//Programm rechnet nur mit X und Y => änderung ohne Korrektur
		int	x,y;					//Koordinaten
		int time;					//wie oft die delay loop durchlaufen wird
		char EN;					//Bedingung für Gen loop
		char pfeil;
		char Leertaste;
		int n;
		int GEN;					//Generationszähler
		int speed;					//0 bis 10
		SetConsoleOutputCP(1250);
		system("mode 150,50");		//Window größe


	//Hauptschleife
	/////////////////////////////////////////////////////////////////////////////////////////////////
	for(;;){

	//reset der Variablen
	/////////////////////////////////////////////////////////////////////////////////////////////////
		system("CLS");
		Leertaste=0;
		n=0;
		GEN=0;
		EN='s';
		time=32;
		hidecursor(0);
		speed=5;


	//Initialisierung der Feldvariablen
	/////////////////////////////////////////////////////////////////////////////////////////////////
		char Feld_alt[X][Y];
		char Feld_neu[X][Y];
		int Nachbarn[X][Y];									//Array zum zählen der Nachbarn
		system("CLS");										//Maske Löschen


	//Initialisierungsschleife
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=0;y<Y;y++){
			for (x=0;x<X;x++){
				Feld_alt[x][y]=' ';
				Feld_neu[x][y]=' ';
				Nachbarn[x][y]=0;
			}
		}

	//Eingabe Maske 2
	/////////////////////////////////////////////////////////////////////////////////////////////////
		Rand(X,Y);
		cursor(X+5,1);
		printf("Parametierung der Anfangsgeneration");
		cursor(X+5,2);
		printf("+++++++++++++++++++++++++++++++++++");
		cursor(X+5,4);
		printf("benutzen Sie die Pfeiltasten um im Spielfeld zu navigieren\n");
		cursor(X+5,6);
		printf("1\t\t=>Zelle setzen");
		cursor(X+5,7);
		printf("0\t\t=>Zelle löschen");
		cursor(X+5,8);
		printf("t\t\t=>Beispiel verwenden Tribole");
		cursor(X+5,9);
		printf("g\t\t=>Beispiel verwenden Gleier");
		cursor(X+5,10);
		printf("r\t\t=>Beispiel verwenden r explosion");
		cursor(X+5,11);
		printf("Leertaste\t=>Spielstartet");
		cursor(X+5,14);
		printf("q\t\t=>Exit");
		fflush(stdout);

	//Erste Geration
	//////////////////////////////////////////////////////////////////////////////////////////////////
		x=X/2;												//Anfangs cursor Position (Mitte)
		y=Y/2;
		while (Leertaste == 0){
			cursor(x+1,y+1);
			pfeil=getch();
			fflush(stdin);

					if(pfeil==72){							//Nach oben
						if(y==0){							//Sprung von oben nach unten
							y=Y;
						}
					y--;
					}

					if(pfeil==80){							//Nach unten
						if(y==Y-1){							//Sprung von unten nach oben
							y=-1;
						}
						y++;
					}


					if(pfeil==75){							//Nach links
						if(x==0){							//Sprung von links nach rechts
							x=X;
						}
						x--;
					}

					if(pfeil==77){              			//Nach rechts
						if(x==X-1){							//Sprung von rechts nach links
							x=-1;
						}
						x++;
					}

					if(pfeil=='t' && x>=0 && x<X-4 && y>=0 && y<Y-4){													//BSP Tribole
						Feld_alt[x  ][y  ]='O', cursor(x+1,y+1), printf("O");
						Feld_alt[x+1][y  ]='O', cursor(x+2,y+1), printf("O");
						Feld_alt[x  ][y+1]='O', cursor(x+1,y+2), printf("O");
						Feld_alt[x+2][y+1]='O', cursor(x+3,y+2), printf("O");
						Feld_alt[x+2][y+3]='O', cursor(x+3,y+4), printf("O");
						Feld_alt[x+4][y+4]='O', cursor(x+5,y+5), printf("O");
						Feld_alt[x+3][y+4]='O', cursor(x+4,y+5), printf("O");
						Feld_alt[x+4][y+3]='O', cursor(x+5,y+4), printf("O");
					}

					if(pfeil=='g' && x>0 && x<X-1 && y>=0 && y<Y-2){													//BSP Gleiter
						Feld_alt[x  ][y  ]='O', cursor(x+1,y+1), printf("O");
						Feld_alt[x+1][y+1]='O', cursor(x+2,y+2), printf("O");
						Feld_alt[x+1][y+2]='O', cursor(x+2,y+3), printf("O");
						Feld_alt[x  ][y+2]='O', cursor(x+1,y+3), printf("O");
						Feld_alt[x-1][y+2]='O', cursor(x  ,y+3), printf("O");
					}

					if(pfeil=='r' && x>0 && x<X-2 && y>=0 && y<Y-2){				//BSP r explosion
						Feld_alt[x  ][y  ]='O', cursor(x+1,y+1), printf("O");
						Feld_alt[x  ][y+1]='O', cursor(x+1,y+2), printf("O");
						Feld_alt[x  ][y+2]='O', cursor(x+1,y+3), printf("O");
						Feld_alt[x-1][y+1]='O', cursor(x  ,y+2), printf("O");
						Feld_alt[x+1][y  ]='O', cursor(x+2,y+1), printf("O");
					}

					if(pfeil=='1')Feld_alt[x][y]='O', cursor(x+1,y+1), printf("O");		//Zelle setzen
					if(pfeil=='0')Feld_alt[x][y]=' ', cursor(x+1,y+1), printf(" ");		//Zelle löschen
					if(pfeil==' ')Leertaste=1;											//Start Generationsablauf
					if(pfeil=='q')return(0);											//Exit
					fflush(stdout);
					fflush(stdin);
				}

	//Maske löschen
	/////////////////////////////////////////////////////////////////////////////////////////////////
		system("CLS");

	//Anzeige während Spiel
	/////////////////////////////////////////////////////////////////////////////////////////////////
		Rand(X,Y);									//Rand muss neu ausgegeben werden
		cursor(X+5,1);
		printf("Spiel des Lebens");
		cursor(X+5,2);
		printf("+++++++++++++++++");
		cursor(X+5,4);
		printf("x\t=>Reset");
		cursor(X+5,5);
		printf("q\t=>Exit");
		cursor(X+5,6);
		printf("down\t=>langsamer");
		cursor(X+5,7);
		printf("up\t=>schneller");


	while(EN!='x'){			//GEN. Schleife
	hidecursor(1);			//während GEN Schleife hidecursor = True = 1 //Fehler vermeidung => in EN loop

	//Nachbarn zählen (geografisch benachbart)
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=1;y<Y-1;y++){
			for (x=1;x<X-1;x++){
				if(Feld_alt[x  ][y+1]=='O')n++;		//unten
				if(Feld_alt[x+1][y+1]=='O')n++;		//rechts unten
				if(Feld_alt[x+1][y  ]=='O')n++;		//rechts
				if(Feld_alt[x+1][y-1]=='O')n++;		//rechts oben
				if(Feld_alt[x  ][y-1]=='O')n++;		//oben
				if(Feld_alt[x-1][y-1]=='O')n++;		//oben links
				if(Feld_alt[x-1][y  ]=='O')n++;		//links
				if(Feld_alt[x-1][y+1]=='O')n++;  	//links unten
				Nachbarn[x][y]=n;
				n=0;
			}
		}

	//Nachbarn zählen Ecke links Oben [0][0]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		if(Feld_alt[0  ][0+1]=='O')n++;   			//unten
		if(Feld_alt[0+1][0+1]=='O')n++;				//unten rechts
		if(Feld_alt[0+1][0  ]=='O')n++;				//rechts
		if(Feld_alt[0+1][Y-1]=='O')n++;				//(oben rechts)			logischer Nachbar
		if(Feld_alt[0  ][Y-1]=='O')n++;				//(oben)				logischer Nachbar
		if(Feld_alt[X-1][Y-1]=='O')n++;				//(oben links) 			logischer Nachbar
		if(Feld_alt[X-1][0  ]=='O')n++;				//(links)				logischer Nachbar
		if(Feld_alt[X-1][0+1]=='O')n++;				//(unten links) 		logischer Nachbar
		Nachbarn[0][0]=n;
		n=0;

	//Nachbarn zählen Ecke rechts oben [X-1][0]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		if(Feld_alt[X-1][0+1]=='O')n++;   			//unten
		if(Feld_alt[x-1][0+1]=='O')n++;  			//links unten
		if(Feld_alt[x-1][0  ]=='O')n++;				//links
		if(Feld_alt[X-1][Y-1]=='O')n++;				//(oben)				logischer Nachbar
		if(Feld_alt[0  ][0  ]=='O')n++;				//(rechts)				logischer Nachbar
		if(Feld_alt[0  ][Y-1]=='O')n++;				//(rechts oben)			logischer Nachbar
		if(Feld_alt[x-1][Y-1]=='O')n++;				//(links oben)			logischer Nachbar
		if(Feld_alt[0  ][1  ]=='O')n++;				//(rechts unten)		logischer Nachbar
		Nachbarn[X-1][0]=n;
		n=0;

	//Nachbarn zählen Ecke rechts unten [X-1][Y-1]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		if(Feld_alt[x  ][y-1]=='O')n++;				//oben
		if(Feld_alt[x-1][y-1]=='O')n++;				//oben links
		if(Feld_alt[x-1][y  ]=='O')n++;				//links
		if(Feld_alt[0  ][0  ]=='O')n++;				//(rechts unten)		logischer Nachbar
		if(Feld_alt[0  ][Y-1]=='O')n++;				//(rechts)				logischer Nachbar
		if(Feld_alt[X-1][0  ]=='O')n++;   			//(unten)				logischer Nachbar
		if(Feld_alt[0  ][y-1]=='O')n++;				//(oben rechts)			logischer Nachbar
		if(Feld_alt[x-1][0  ]=='O')n++;  			//(links unten)			logischer Nachbar
		Nachbarn[X-1][Y-1]=n;
		n=0;

	//Nachbarn zählen Ecke links unten [0][Y-1]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		if(Feld_alt[0  ][y-1]=='O')n++;				//oben
		if(Feld_alt[0+1][y-1]=='O')n++;				//rechts oben
		if(Feld_alt[0+1][Y-1]=='O')n++;				//rechts
		if(Feld_alt[X-1][0  ]=='O')n++;  			//(links unten)			logischer Nachbar
		if(Feld_alt[X-1][Y-1]=='O')n++;				//(links)				logischer Nachbar
		if(Feld_alt[0  ][0  ]=='O')n++;   			//(unten)				logischer Nachbar
		if(Feld_alt[1  ][0  ]=='O')n++;				//(rechts unten)		logischer Nachbar
		if(Feld_alt[X-1][y-1]=='O')n++;				//(links oben)			logischer Nachbar
		Nachbarn[0][Y-1]=n;
		n=0;

	//Nachbarn zählen Seite oben[1 bis X-2][0]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (x=1;x<X-1;x++){
			if(Feld_alt[x  ][0+1]=='O')n++;		//unten
			if(Feld_alt[x+1][0+1]=='O')n++;		//rechts unten
			if(Feld_alt[x+1][0  ]=='O')n++;		//rechts
			if(Feld_alt[x-1][0  ]=='O')n++;		//links
			if(Feld_alt[x-1][0+1]=='O')n++;  	//links unten
			if(Feld_alt[x  ][Y-1]=='O')n++;		//(oben)				logischer Nachbar
			if(Feld_alt[x+1][Y-1]=='O')n++;		//(rechts oben)			logischer Nachbar
			if(Feld_alt[x-1][Y-1]=='O')n++;		//(oben links)			logischer Nachbar
			Nachbarn[x][0]=n;
			n=0;
		}

	//Nachbarn zählen Seite unten [1 bis X-2][Y-1]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (x=1;x<X-1;x++){
			if(Feld_alt[x  ][Y-2]=='O')n++;		//oben
			if(Feld_alt[x+1][Y-1]=='O')n++;		//rechts
			if(Feld_alt[x-1][Y-1]=='O')n++;		//links
			if(Feld_alt[x+1][Y-2]=='O')n++;		//rechts oben
			if(Feld_alt[x-1][Y-2]=='O')n++;		//oben links
			if(Feld_alt[x  ][0  ]=='O')n++;		//(unten)				logischer Nachbar
			if(Feld_alt[x+1][0  ]=='O')n++;		//(rechts unten)		logischer Nachbar
			if(Feld_alt[x-1][0  ]=='O')n++;  	//(links unten)			logischer Nachbar
			Nachbarn[x][Y-1]=n;
			n=0;
		}

	//Nachbarn zählen Seite links [0][1 bis Y-2]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=1;y<Y-1;y++){
			if(Feld_alt[0+1][y  ]=='O')n++;		//rechts
			if(Feld_alt[0  ][y-1]=='O')n++;		//oben
			if(Feld_alt[0  ][y+1]=='O')n++;		//unten
			if(Feld_alt[0+1][y-1]=='O')n++;		//rechts oben
			if(Feld_alt[0+1][y+1]=='O')n++;		//rechts unten
			if(Feld_alt[X-1][y-1]=='O')n++;		//(oben links)			logischer Nachbar
			if(Feld_alt[X-1][y  ]=='O')n++;		//(links)				logischer Nachbar
			if(Feld_alt[X-1][y+1]=='O')n++;  	//(links unten)			logischer Nachbar
			Nachbarn[0][y]=n;
			n=0;
		}

	//Nachbarn zählen Seite rechts [X-1][1 bis Y-2]
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=1;y<Y-1;y++){
			if(Feld_alt[x-1][y-1]=='O')n++;		//oben links
			if(Feld_alt[x-1][y  ]=='O')n++;		//links
			if(Feld_alt[x-1][y+1]=='O')n++;  	//links unten
			if(Feld_alt[x  ][y+1]=='O')n++;		//unten
			if(Feld_alt[x  ][y-1]=='O')n++;		//oben
			if(Feld_alt[0  ][y  ]=='O')n++;		//(rechts)				logischer Nachbar
			if(Feld_alt[0  ][y-1]=='O')n++;		//(rechts oben)			logischer Nachbar
			if(Feld_alt[0  ][y+1]=='O')n++;		//(rechts unten)		logischer Nachbar
			Nachbarn[X-1][y]=n;
			n=0;
		}


	//Regeln
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=0;y<Y;y++){
			for (x=0;x<X;x++){
				if(Feld_alt[x][y]=='O') Feld_neu[x][y]='O';
				if(Nachbarn[x][y]<=1) Feld_neu[x][y]=' ';	//stirbt wegen Einsamkeit
				if(Nachbarn[x][y]>3) Feld_neu[x][y]=' ';	//stirbt an Überbevölkerung
				if(Nachbarn[x][y]==3) Feld_neu[x][y]='O';	//Zelle bleibt am leben oder wird geboren
			}
		}


	//Ausgabeschleife Feld_alt
	/////////////////////////////////////////////////////////////////////////////////////////////////
		if(GEN==0){
			for (y=0;y<Y;y++){
				for (x=0;x<X;x++){
					cursor(x+1,y+1);
					printf("%c",Feld_alt[x][y]);
					fflush(stdout);
				}
			printf("\n");
			fflush(stdout);
			}
		}


		cursor(X+5,Y);
		printf("Gen\t=%i",GEN);


	//delay loop and getch loop
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for(n=0;n<=time;n++){
			Sleep(2);																	//Offset => ca. alle 2ms Abfrage auf EN
			if(kbhit())EN=getch();
			if(EN=='q')return (0);
			if(EN==72 && speed<10)time=time/2,speed++;									//Keine delay bei EN eingabe => ähnlich interrupt
			if(EN==80 && speed>0)time=time*2,speed--;									//Nachteil Rechenleistung
			cursor(X+5,10);
			printf("Speed\t=%02i\t(0-10)",speed);
			if(speed==0)n=0, cursor(X+5,15), printf("right\t=>nächste Generation");
				else cursor(X+5,15), printf("                                    ");	//löschen "nächste Generation"
			if(EN==77 && speed==0)n=time;												//nächste Generation
			if(EN=='x')n=time;
				else EN='0';
		}
		n=0;



	//Feld_neu Ausgeben
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=0;y<Y;y++){
			for (x=0;x<X;x++){
				if(Feld_neu[x][y]!=Feld_alt[x][y]){
					cursor(x+1,y+1);
					printf("%C",Feld_neu[x][y]);
					fflush(stdout);
				}
			}
		}

	//Feld_neu in Feld_alt
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=0;y<Y;y++){
			for (x=0;x<X;x++){
			Feld_alt[x][y]=Feld_neu[x][y];
			}
		}

	//Feld_neu löschen
	/////////////////////////////////////////////////////////////////////////////////////////////////
		for (y=0;y<Y;y++){
			for (x=0;x<X;x++){
				Feld_neu[x][y]=' ';
			}
		}
		GEN++;								//GEN Zähler kein Reset
	  }
	}
	return (0);
}






int Rand(int X,int Y){
	int m;
	for(m=0;m<X+2;m++){
			cursor(0,m);
				printf("+");
				fflush(stdout);
			cursor(X+1,m);
				printf("+");
				fflush(stdout);
			cursor(m,0);
				printf("+");
				fflush(stdout);
			cursor(m,Y+1);
				printf("+");
				fflush(stdout);
		}
	return 0;
}

int hidecursor(int s)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   if(s==0){
	   info.bVisible = TRUE;			//cursor sichtbar
   }
   if(s==1){
	   info.bVisible = FALSE;			//cursor hide
   }
   SetConsoleCursorInfo(consoleHandle, &info);
   return 0;
}

int cursor(int x,int y)
	{

	    COORD coord = {x,y};
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	    return (0);
	}
