#include "pch.h"

#define TAHOMA "c:/z/_MI/data/font/Tahoma.ttf"

#define T(a,b,c)											\
	if(board[a][b] == '-')								\
	{															\
		if(X_KEY)											\
		{														\
			bx[c] = true;									\
			bo[c] = false;									\
		}														\
		if(O_KEY)											\
		{														\
			bx[c] = false;									\
			bo[c] = true;									\
		}														\
	}															\

#define TT(a,b,c1,d,e)																	\
	if(board[a][b] == '-')																\
	{																							\
		if     (bx[c1]){drawFontSolid(0,0,4,x+   (c+d),y+(yheight/2*1)+e,"X",WHITE,TAHOMA,100); blink(c+d,0+e);} \
		else if(bo[c1]){drawFontSolid(0,0,4,x+ (c+d)-7,y+(yheight/2*1)+e,"O",WHITE,TAHOMA,100); blink(c+d,0+e);} \
		else          {blink(c+d,0+e);}												\
	}																							\
	else																						\
	{																							\
		if     (bx[c1])																	\
		{																						\
			if  (bx[c1]){drawFontSolid(0,0,4,x+   (c+d),y+(yheight/2*1)+e,"X",WHITE,TAHOMA,100);} \
		}																						\
		else if(bo[c1])																	\
		{																						\
			if  (bo[c1]){drawFontSolid(0,0,4,x+ (c+d)-7,y+(yheight/2*1)+e,"O",WHITE,TAHOMA,100);} \
		}																						\
	}																							\

#define WWX(a,b,c)																		\
	if(bx[a] && bx[b] && bx[c])														\
	{																							\
		gamestate = WIN;																	\
		xwin = true;																		\
	}																							\

#define WWO(a,b,c)																		\
	if(bo[a] && bo[b] && bo[c])														\
	{																							\
		gamestate = WIN;																	\
		owin = true;																		\
	}																							\

int x = 140;
int y = 0;
int yheight = 140;
static bool bo[9];
static bool bx[9];
int sep = 96;
int c = 38;

bool keydown = false;

bool playbutton = false;
bool quitbutton = false;

bool xwin = false;
bool owin = false;

char board[3][3+1]=
{
	{"-  "},
	{"   "},
	{"   "},
};

enum {MENU,GAME,WIN,EXIT};
int gamestate = MENU;

int val = 100;
double angle = 0.0;
int alpha = 255;

SDL_Texture *img;
SDL_Surface *surface;
SDL_Rect rect;// = {0,0,100+val,600};

void blink(int xpos, int ypos)
{
	static int incre = 0;
	if(incre >= 30)
	{
		static int incre2 = 0;
		if(incre2 >= 30)
		{
			incre = 0;
			incre2 = 0;
		}
		else
		{
			drawFontSolid(0,0,0,x+(xpos)+5, y+(yheight/2*1)+ypos,"-",GREEN,"c:/z/_MI/data/font/Tahoma.ttf",100);
		}
		incre2++;
	}
	incre++;
}

bool flip    = false;
bool flipoff = true;

int main(int argc, char* args[])
{

	std::ofstream outputfile;
	std::ifstream inputfile;
	
	init_Window(300,200,800,600,0);

	loading();

	rect.x = 0;
	rect.y = 0;
	rect.w = 600;
	rect.h = 600;

	surface = IMG_Load("../data/images/bg.png");
	img = SDL_CreateTextureFromSurface(renderer,surface);	

	while(running)
	{
		while(POLLEVENT)
		{
			if(QUIT){ exit(0); }
			
			if(DOWNPRESS)
			{
				
				if(UP){  angle   += 12.0;}
				if(DOWN){angle   -= 12.0;}
				if(LEFT){rect.w  -= 20;}
				if(RIGHT){rect.w += 20;}
				if(BACKSPACE){flipoff = false; flip = !flip;}
				if(SPACE){flipoff = !flipoff;}
				if(O_KEY){alpha -= 20;}
				if(P_KEY){alpha += 20;}
				
			}
			if(UPPRESS)
			{
				if(gamestate == MENU)
				{
					if(ESCAPE){exit(0);}
					
					if(UP)
					{
						playbutton = true;
						quitbutton = false;
						angle += 0.1f;
					}
					if(DOWN)
					{
						playbutton = false;
						quitbutton = true;
					}
				}

				if(RETURN)
				{
					if(playbutton)
					{
						gamestate = GAME;
					}
					if(quitbutton)
					{
						gamestate = EXIT;
					}
				}
				
				if(gamestate == GAME)
				{
					playbutton = false;
					quitbutton = false;
					
					if(ESCAPE){gamestate = MENU;}
					
					keydown = true;

					for(int i = 0; i < 3; i++)
					{
						for(int j = 0; j < 3; j++)
						{
							switch(board[i][j])
							{
								case '-':
								{
									T(0,0,0)
									T(0,1,1)
									T(0,2,2)
									T(1,0,3)
									T(1,1,4)
									T(1,2,5)
									T(2,0,6)
									T(2,1,7)
									T(2,2,8)

									if(keydown)
									{
										if(UP)
										{
											if(i > 0)
											{
												char temp     = board[i-1][j];
												board[i-1][j] = board[i  ][j];
												board[i][j  ] = temp;
												keydown = false;
											}
										}
										if(DOWN)
										{
											if(i < 2)
											{
												char temp     = board[i+1][j];
												board[i+1][j] = board[i  ][j];
												board[i][j  ] = temp;
												keydown = false;
											}
										}
										if(LEFT)
										{
											if(j > 0)
											{
												char temp     = board[i][j-1];
												board[i][j-1] = board[i][j  ];
												board[i][j  ] = temp;
												keydown = false;
											}
										}
										if(RIGHT)
										{
											if(j < 2)
											{
												char temp     = board[i][j+1];
												board[i][j+1] = board[i][j  ];
												board[i][j  ] = temp;
												keydown = false;
											}
										}
									}
								}
							}
						}
					}
				}
				
				if(gamestate == WIN)
				{
					if(ESCAPE)
					{
						gamestate = MENU;
					}
				}
			}
		}
		
		SDL_SetRenderDrawColor(renderer,128,128,211,255);
		SDL_RenderClear(renderer);

		if(gamestate == MENU)
		{
			for(int i = 0; i < 9; i++)
			{
				bx[i] = false;
				bo[i] = false;
			}
			xwin = false;
			owin = false;

			board[0][0] = '-';board[0][1] = ' ';board[0][2] = ' ';
			board[1][0] = ' ';board[1][1] = ' ';board[1][2] = ' ';
			board[2][0] = ' ';board[2][1] = ' ';board[2][2] = ' ';
			
			//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //NONE, BLEND, ADD, MOD
			//drawFillRect(0,0,100,100,255,255,255,128);

			//SDL_SetTextureAlphaMod(img,(Uint8)alpha);
			//SDL_SetTextureBlendMode(img,SDL_BLENDMODE_BLEND); //NONE, BLEND, ADD, MOD
			//SDL_SetTextureColorMod(img,255,0,0);

			// if(flipoff)
			// {
			// 	SDL_RenderCopyEx(renderer,img,0,&rect,angle,NULL,SDL_FLIP_NONE);
			// }
			// else
			// {
			// 	if(flip)
			// 	{
			// 		SDL_RenderCopyEx(renderer,img,0,&rect,angle,NULL,SDL_FLIP_VERTICAL);
			// 	}
			// 	else
			// 	{
			// 		SDL_RenderCopyEx(renderer,img,0,&rect,angle,NULL,SDL_FLIP_HORIZONTAL);
			// 	}
			// }
			
			drawFillRect(0,0,600,600,BLACK);
			drawFillRect(125,160,350,100,MAROON);
			drawFillRect(125,270,350,100,MAROON);
			
			drawFontSolid(1,0,4,x+ 150,y+(yheight/2*1)+50+50, "PLAY GAME",WHITE,TAHOMA,64);
			drawFontSolid(1,0,4,x+ 150,y+(yheight/2*1)+150+50,"QUIT",     WHITE,TAHOMA,64);

			if(playbutton)
			{
				drawFillRect(50,180,50,50,GRAY);
			}
			if(quitbutton)
			{
				drawFillRect(50,180+120,50,50,GRAY);
			}
		}
		
		if(gamestate == GAME)
		{
			//print out cmd
		
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					std::cout << board[i][j];
				}
				std::cout << std::endl;
			}
			
			for(int i = 0; i < 3; i++)
			{
				std::cout << std::endl;
			}

			//draw graphics
		
			drawFontSolid(0,0,4,x,y+(yheight/2*0),"---------",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x,y+(yheight/2*2),"---------",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x,y+(yheight/2*4),"---------",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x,y+(yheight/2*6),"---------",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);

			drawFontSolid(0,0,4,x               ,y+(yheight/2*1),    "|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x               ,y+(yheight/2*1),    "|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep)        ,y+(yheight/2*1),    "|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep+sep)    ,y+(yheight/2*1),    "|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep+sep+sep),y+(yheight/2*1),    "|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);

			drawFontSolid(0,0,4,x               ,y+(yheight/2*1)+140,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x               ,y+(yheight/2*1)+140,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep)        ,y+(yheight/2*1)+140,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep+sep)    ,y+(yheight/2*1)+140,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep+sep+sep),y+(yheight/2*1)+140,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);

			drawFontSolid(0,0,4,x               ,y+(yheight/2*1)+280,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x               ,y+(yheight/2*1)+280,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep)        ,y+(yheight/2*1)+280,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep+sep)    ,y+(yheight/2*1)+280,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
			drawFontSolid(0,0,4,x+ (sep+sep+sep),y+(yheight/2*1)+280,"|",WHITE,"c:/z/_MI/data/font/Tahoma.ttf",100);
		
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					if(board[i][j])
					{
					
						TT(0,0, 0, 0,         0)
						TT(0,1, 1, sep,       0)
						TT(0,2, 2, sep+sep,   0)
						TT(1,0, 3, 0,       140)
						TT(1,1, 4, sep,     140)
						TT(1,2, 5, sep+sep, 140)
						TT(2,0, 6, 0,       280)
						TT(2,1, 7, sep,     280)
						TT(2,2, 8, sep+sep, 280)
					}
				}
			}
			//check win
			
			WWX(0,4,8)
			WWX(2,4,6)
			
			WWX(0,1,2)
			WWX(3,4,5)
			WWX(6,7,8)
			
			WWX(0,3,6)
			WWX(1,4,7)
			WWX(2,5,8)

			WWO(0,4,8)
			WWO(2,4,6)
			
			WWO(0,1,2)
			WWO(3,4,5)
			WWO(6,7,8)
			
			WWO(0,3,6)
			WWO(1,4,7)
			WWO(2,5,8)
		}

		if(gamestate == WIN)
		{
			drawFillRect(0,0,600,600,BLACK);
			drawFillRect(50,50,600-100,600-100,50,0,0,255);
			drawFillRect(125,250,350,100,MAROON);
			if(xwin)
			{
				drawFontSolid(0,0,4,x+ (c)-7+5,y+(yheight/2*1)+180,"X WINS !!!",WHITE,TAHOMA,64);
			}
			if(owin)
			{
				drawFontSolid(0,0,4,x+ (c)-7,y+(yheight/2*1)+180,"O WINS !!!",WHITE,TAHOMA,64);
			}
		}

		if(gamestate == EXIT)
		{
			running = false;
		}
		
		SDL_Delay(1000/33);
		SDL_RenderPresent(renderer);
	}

	destroy_Window();
	return(0);
}

