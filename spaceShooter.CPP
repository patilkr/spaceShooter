

/* *************************************************
*
*  Author: Prof. Kailas Patil
*  Vishwakarma University, Pune, India
*  Email: kailas [DOT] patil [AT] vupune [DOT] ac [DOT] in
*  ProgramName: Space Shooter
*  Operating system: Windows
*  Compiler Used: TurboC++
*
* **************************************************
*/

/* C-standard Libraries */ 
#include<stdio.h>
#include<dos.h>    /* sound(), nosound(), delay() */
#include<ctype.h>  /* tolower() */
#include<conio.h>  /* cprintf(), textcolor(), window(), kbhit(), getch(), clrscr(), _setcursortype() */
#include<stdlib.h>  /* random(), randomize() */
// #include<string.h>

int gMissiles_Xpos[20],gMissiles_Ypos[20]; // Maximum 20 user missiles at a time in parallel */
const int gTotalEnemySize=6;  /* Maximum number of enemies on the screen */
int gEnemy_X[gTotalEnemySize],gEnemy_Y[gTotalEnemySize]; /* Enemy object positions */

/*
*
* Function name: drawPlayer
* Parameter: z = horizontal (X-axis) location on the screen
* Task: Draw player space shooter rocket
*
*/
void drawPlayer(int z)
{
	window(z+1,22,70,25);
	textcolor(10);
	cprintf("    Û  ");
	window(z+1,23,70,25);
	cprintf("   Þ");
	textcolor(9);
	cprintf("Û");
	textcolor(10);
	cprintf("Ý  ");
	window(z+1,24,70,25);
	cprintf("  Þ");
	textcolor(9);
	cprintf("ÛßÛ");
	textcolor(10);
	cprintf("Ý  ");
}


/*
*
* Function Name : gameStatus
* Paramter :  kStatusCode = Status Code
*    kStatusCode = 1 means User is Playing the Game
*    kStatusCode = 2 means User has Paused the Game
*    kStatusCode = 3 or other values  the Game has Stopped. That is enemy reached to user coordinates
*
*/

void gameStatus(int kStatusCode)
{
	window(66,17,79,19);
	if(kStatusCode == 1)
	{
		textcolor(LIGHTGREEN);
		cprintf("  Playing.. ");
	}
	else if(kStatusCode == 2) {
		cprintf("   Paused   ");
	}else
	{
		textcolor(LIGHTRED);
		cprintf("   Stoped   ");
	}
}


/*
*
* Function Name: moveMissileUP
* Parameters: None
* Tasks: 1) Show the user missile in Green Color
         2) Move user missiles Upwards in the Space 
*
*/
void moveMissileUP()
{
	int flag = 0, k;
	static scr = 0;

        /* Check, if any of user missile is hit to Enemy objects */
	for(int i = 0; i<gTotalEnemySize && gEnemy_X[i]!=0; i++)
	{
		for(k = 0; k < 20; k++)
		{
			/* Remove Enemy, if green missile hits enemy */
			if(gEnemy_X[i] == gMissiles_Xpos[k] && gEnemy_Y[i] == gMissiles_Ypos[k] && gMissiles_Xpos[k]!=0)
			{
				gEnemy_X[i] = 0;
				window(74,20,80,24);
				scr++;
				textcolor(15);
				cprintf("%d",scr);
				if(scr < 10)
				     cprintf("  ");
				else cprintf(" ");
			}
		}
	}

	/* Move User Missiles onepoistion UP in the Space */
	textcolor(GREEN);  /* Set color To GREEN for missile display */

	for(i = 0; i < 20; i++)  /* User can fire 20 missiles in parallel */
	{
		if(gMissiles_Xpos[i]!=0)   /* if Missile present at this X coordinates */
		{
			flag++;
			/* Display a missile one poistion higher at X Co-ordinates */
			window(gMissiles_Xpos[i],gMissiles_Ypos[i],gMissiles_Xpos[i]+1,gMissiles_Ypos[i]+1);
			if(gMissiles_Ypos[i]!=1)   /* Not yet reached to the Top of the screen */
				cprintf("%c",4);

                        /* Remove the old position missile trace */
			window(gMissiles_Xpos[i], gMissiles_Ypos[i]+1, gMissiles_Xpos[i]+1, gMissiles_Ypos[i]+2);
			if(gMissiles_Ypos[i]!=21) 
				cprintf(" ");

			gMissiles_Ypos[i]--;  /* Move Y possition of the missile by one posisiton UP */
			delay(22/flag);
		}

		if(gMissiles_Ypos[i] == 0)  /* If missile reached top of the screen, then remove it from screen */
			gMissiles_Xpos[i] = 0;
	}

	textcolor(WHITE); /* Reset Screen Color back to White */
}

/*
*
* Function Name: moveEnemyDOWN
* Parameters: None
* Tasks: 1) Show Enemy in RED color
	 2) Move Enemy Downwards from the Space
*
*/
void moveEnemyDOWN()
{
	int x,i;

	/* Generate a random number to insert enemy at random position on the screen (Space) */
	if(random(10) == 1) {
	x = random(52) + 7;
	textcolor(RED); /* Set Enemy Color to RED */

	for(i = 0; i < gTotalEnemySize; i++)
	{
		if(gEnemy_X[i] == 0)
		{
			gEnemy_X[i] = x;
			gEnemy_Y[i] = 2;  /* start an enemy object from the top of the screen */ 
			window(gEnemy_X[i], gEnemy_Y[i], gEnemy_X[i]+1, gEnemy_Y[i]+1);
			cprintf("*");
			break;
		}
	}             /// after

	for(i = 0; i < gTotalEnemySize; i++)
	{
		if(random(2)) {
			window(gEnemy_X[i], gEnemy_Y[i], gEnemy_X[i], gEnemy_Y[i]+2);
			cprintf("+#");
		
			/* If enemy reached to user coordinates. STOP the Game */
			if(gEnemy_Y[i] >= 20)
			{
				gameStatus(3); /* STOP the game */
				sound(100);
				delay(210);
				nosound();
				sound(250);
				delay(100);
				nosound();
				sound(100);
				delay(210);
				nosound();
				sound(250);
				delay(250);
				nosound();

				getch();
				delay(1500);
				exit(0);
			}
			gEnemy_Y[i]++;      
		}
	}

	textcolor(WHITE);
	delay(300);

	}
}



/*
* 
* Function Name: main
* Parameters: None
* Tasks: Draw game box, display score andgame status to user. accept user inputs
*
*/
void main()
{
	clrscr();
	char ch;
	_setcursortype(_NOCURSOR);
	randomize();

	/* Draw white box on the screen */
	textcolor(15);
	cprintf("\n Ú                                                             ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ");
	for(int i = 0; i < 18; i++)
		cprintf(" ³                                                             ³              ³ ");

	cprintf(" À                                                             ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ");

	/* Write a display message in the right white color box */
	window(66,3,78,21);
	textcolor(11);
	cprintf("Press X      ");
	cprintf("to Exit_____ \n");
	textcolor(14);
	cprintf("Press P to   ");
	cprintf("Pause Game__ \n");
	textcolor(11);
	cprintf("Press Space  ");
	cprintf("to Shoot____ \n");
	textcolor(14);
	cprintf("Press Left,  ");
	cprintf("Right to Move\n");
	textcolor(WHITE);
	cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄ ");
	cprintf("Status:      ");
	cprintf("   Stoped    \n");  // cprintf("  Playing.. "); cprintf("   Stoped   ");
	cprintf("Score :      ");
	cprintf("        0   ");
//	getch(); return;


	int x = 0;
	for(i = 0; i < 20; i++)
	{
		gMissiles_Xpos[i]=0;
	}
	for(i = 0; i < gTotalEnemySize; i++)
		gEnemy_X[i] = 0;
	drawPlayer(x);

	while(1)
	{
		gameStatus(1); /* set game status to the PLAYING Mode */
		while(!kbhit())
		{
			moveMissileUP();
			moveEnemyDOWN();
		}

		ch=getch();
		switch(tolower(ch))
		{
			case 'p' :  gameStatus(2);  /* Set game status to the PAUSED status */
						sound(1500);
						delay(110);
						nosound();
						sound(500);
						delay(200);
						nosound();
						sound(2200);
						delay(150);
						nosound();
						getch();
			case ' ' :  sound(600);   /* Play Sound (Generate BEEP sound) */
						delay(40);
						nosound();
						sound(1500);
						delay(40);
						nosound();
						for(i = 0; i < 20; i++)
						{
							if(gMissiles_Xpos[i] == 0)
							{
								gMissiles_Xpos[i] = x + 5;
								gMissiles_Ypos[i] = 21;
								break;
							}
						}
						break;
			case 0 : 	ch=getch();
						if(ch == 75 && x > 0)  /* If LEFT Arrow key is pressed */
						{
							x -= 1;  /* Move the Player by one poistion the LEFT */
							drawPlayer(x);
						}
						else if(ch == 77 && x < 55) /* If RIGHT Arrow key is pressed */
						{
							x += 1;   /* Move the Player by one poistion to the RIGHT */
							drawPlayer(x);
						}
						break;
			case 'x' : return;   /* EXIT the game */
		}
	}
}
