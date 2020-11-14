#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
//máximo de balas da arma
#define MAX_BULLETCOUNT 50
#define MAX_ENEMY 12
//variaveis
const int SCREEN_WIDTH = 973;
const int SCREEN_HEIGHT = 486;
//Largura e altura do dos frames do inimigo
int in_frameW = 50;
int in_frameH = 53;
int cont;
//largura e altura do frame do player
int player_frameW = 50;
int player_frameH = 53;
int vida_framW=50;
int vida_framH=50;
//velocidade
int velx=0;//player
int vely=0;//player
float velo=2;//Inimigos
float velobull=15;//tiro
//jogo
int gameRunning = 1;
//Pontuação
int pont=0;
char pontuacao[100];
int aux;
//recorde
int rec[5];
char recordes1[100];
char recordes2[100];
char recordes3[100];
char recordes4[100];
char recordes5[100];
//variaveis do tiro
int i=0, e;
float j, k;
int cont_frame_bullet;
float teste;
float teste2;
int Pause=1;
//estrutura do tiro
typedef struct _BULLET
{
    int posi;
    int tiro;
}BULLET;
//variaveis do chefe
int Cposi=1;
//Vidas
int vida=5;//player
int vidaIni1=1;//inimigo 1
int vidaIni2=1;//inimigo 2
int vidaIni3=1;//inimigo 3
int vidaIni4=1;//inimigo 4
int vidaIni5=1;//inimigo 5
int vidaIni6=1;//inimigo 6
int vidaIni7=1;//inimigo 7
int vidaIni8=1;//inimigo 8
int vidaC=12;// chefe// chefe
int vidaE[MAX_ENEMY];
int totInimigos;
//arquivos
FILE * pe;
FILE* ps;
//menu
int opcao=0;
//tiro again
BULLET bullet_vet[MAX_BULLETCOUNT];
//Surfaces
SDL_Window* window = NULL;//janela
SDL_Surface* Screen = NULL;//janela
SDL_Surface* menu=NULL;
SDL_Surface* Background = NULL;
SDL_Surface* Player = NULL;    
SDL_Surface* bullet=NULL;
SDL_Surface* In1 = NULL; 
SDL_Surface* In2 = NULL; 
SDL_Surface* In3 = NULL; 
SDL_Surface* in4 = NULL; 
SDL_Surface* Boss = NULL;
SDL_Surface* logo=NULL;
SDL_Surface* instrucoes=NULL;
SDL_Surface* creditos=NULL;
SDL_Surface* lose=NULL;
SDL_Surface* win=NULL;
SDL_Surface* Vida = NULL;
SDL_Surface* cursor=NULL;
SDL_Surface* escrever=NULL;
SDL_Surface* bullet2=NULL;
SDL_Surface* bullet3=NULL;
SDL_Surface* pausa=NULL;
SDL_Surface* Bos=NULL;
SDL_Surface* Recordes[10];
//musicas
Mix_Music* musica = NULL;
Mix_Music* fase=NULL;
Mix_Chunk* explosao=NULL;
//ttf
TTF_Font* fonte;
//cor
SDL_Color cor = {255, 255, 255};
//rects
SDL_Rect player_frame, pause_position, player_position, In1_frame, In1_position, In2_frame, In2_position, In3_frame, In3_position, In4_frame, In4_position,
In5_frame, In5_position, In6_frame, In6_position, In7_frame, In7_position, In8_frame, In8_position, chefe_position, lose_position,
 bullet_frame[MAX_BULLETCOUNT], bullet_position[MAX_BULLETCOUNT], logo_position, vida_position, vida_frame, cursor_position,
  dst_rect = {0, 0, 0, 0}, enemy_frame[MAX_ENEMY], enemy_position[MAX_ENEMY], chefe2_position, rec1 = {450, 0, 0, 0},
  rec2 = {450, 40, 0, 0}, rec3 = {450, 80, 0, 0}, rec4 = {450, 120, 0, 0}, rec5 = {450, 160, 0, 0};
//Funções 
void atirador(BULLET bullet_vet[], float velobull, SDL_Surface* bullet, SDL_Rect bullet_frame[], SDL_Rect bullet_position[], SDL_Surface* Background, SDL_Surface* Screen);
void apareceVagabundo();
void correVagabundo();
void apareceVagabundo1();
void aparecechefe();
void Chora();
void pegaAsImagens();
void vidaP();
void anda();
void pontuacaob();
void fase1();
void Menu();
void fase2();
void fase3();
void fase4();
void liberouGeral();
void apareceGeral();
void leRecorde();
void guardaRecorde();
void ImprimeRecerde();

SDL_Event event;
int main( int argc, char* args[] )
{
    cursor_position.x=650;
    cursor_position.y=278;

    for(cont_frame_bullet=0; cont_frame_bullet<MAX_BULLETCOUNT; cont_frame_bullet++)
    {
        bullet_frame[cont_frame_bullet].x = 0;
        bullet_frame[cont_frame_bullet].y = 0;
        bullet_frame[cont_frame_bullet].w = 50;
        bullet_frame[cont_frame_bullet].h = 50;

        bullet_position[cont_frame_bullet].x = 811;
        bullet_position[cont_frame_bullet].y = 0;
        bullet_position[cont_frame_bullet].w = 11;
        bullet_position[cont_frame_bullet].h = 10;
    }

    //Rect do frame
    player_frame.x = 0;
    player_frame.y = 0;
    player_frame.w = player_frameW;
    player_frame.h = player_frameH;
    //Rect da posição do player na tela
    player_position.x = SCREEN_WIDTH/2;
    player_position.y = SCREEN_HEIGHT/2;
    player_position.w = player_frameW;
    player_position.h = player_frameH;
    //rect da posição da imagem
    logo_position.x=179;
    logo_position.y=73;
    //rect da posição do game over
    lose_position.x=246.5;
    lose_position.y=63;
    //rect da posição do pause
    pause_position.x=230.5;
    pause_position.y=0;
    
    //Inicializa o SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    fonte = TTF_OpenFont("Starjedi.ttf",18);
    //Cria a janela
    window = SDL_CreateWindow( "Galaxy Rush"/*Nome da janela*/, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    //recebe a janela
    Screen = SDL_GetWindowSurface( window ); 

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
        Mix_GetError());

        return 0;
    }
    pegaAsImagens();
    musica=Mix_LoadMUS("star wars.mp3");
    fase=Mix_LoadMUS("play hard.mp3");
    explosao=Mix_LoadWAV("explosao.wav");


    SDL_BlitSurface(logo, NULL, Screen, &logo_position);
    SDL_UpdateWindowSurface( window );
    SDL_Delay(5000);
    Menu();
    //SDL_BlitSurface(logo, NULL, Screen, &logo_position);
    SDL_UpdateWindowSurface( window );
    SDL_Delay(5000); //Creditos de fim de jogo
    //Liberar as imagens da memória
    SDL_FreeSurface(Background);
    SDL_FreeSurface(Player);
    SDL_FreeSurface(In1);
    SDL_FreeSurface(In2);
    SDL_FreeSurface(In3);
    SDL_FreeSurface(lose);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(bullet);
    SDL_FreeSurface(creditos);
    SDL_FreeSurface(instrucoes);
    SDL_FreeSurface(Boss);
    SDL_FreeSurface(escrever);
    SDL_FreeSurface(Bos);
    SDL_FreeSurface(bullet2);
    SDL_FreeSurface(bullet3);
    SDL_FreeSurface(in4);
    TTF_CloseFont(fonte);
    TTF_Quit();

    //Destruir janela
    SDL_DestroyWindow( window );
    atexit(Mix_CloseAudio);
    //Encerrar o SDL
    SDL_Quit();
    return 0;
}
void apareceVagabundo()
{

    //Rect do frame
    In1_frame.x = 0;
    In1_frame.y = 0;
    In1_frame.w = in_frameW;
    In1_frame.h = in_frameH;
    //Rect da posição do player na tela
    In1_position.x = 0;
    In1_position.y = 0;
    In1_position.w = in_frameW;
    In1_position.h = in_frameH;
    //Rect do frame
    In2_frame.x = 0;
    In2_frame.y = 0;
    In2_frame.w = 53;
    In2_frame.h = in_frameH;
    //Rect da posição do player na tela
    In2_position.x = 0;
    In2_position.y = SCREEN_HEIGHT-63;
    In2_position.w = in_frameW;
    In2_position.h = in_frameH;
    //Rect do frame
    In3_frame.x = 0;
    In3_frame.y = 0;
    In3_frame.w = 53;
    In3_frame.h = in_frameH;
    //Rect da posição do player na tela
    In3_position.x = 837;
    In3_position.y = 0;
    In3_position.w = in_frameW;
    In3_position.h = in_frameH;
    //Rect do frame
    In4_frame.x = 0;
    In4_frame.y = 0;
    In4_frame.w = in_frameW;
    In4_frame.h = in_frameH;
    //Rect da posição do player na tela
    In4_position.x = SCREEN_WIDTH-63;
    In4_position.y = SCREEN_HEIGHT-63;
    In4_position.w = 53;
    In4_position.h = in_frameH;

    vidaIni1=1;//inimigos 1
    vidaIni2=1;//inimigo 2
    vidaIni3=1;//inimigo 3
    vidaIni4=1;//inimigo 4

    //totInimigos=vidaIni4+vidaIni3+vidaIni2+vidaIni1;
}

void apareceVagabundo1()
{

    //Rect do frame
    In5_frame.x = 0;
    In5_frame.y = 0;
    In5_frame.w = in_frameW;
    In5_frame.h = in_frameH;
    //Rect da posição do player na tela
    In5_position.x = (SCREEN_WIDTH/2);
    In5_position.y = 0;
    In5_position.w = 53;
    In5_position.h = in_frameH;
    //Rect do frame
    In6_frame.x = 0;
    In6_frame.y = 0;
    In6_frame.w = 53;
    In6_frame.h = in_frameH;
    //Rect da posição do player na tela
    In6_position.x = 0;
    In6_position.y = (SCREEN_HEIGHT/2);
    In6_position.w = in_frameW;
    In6_position.h = in_frameH;
    //Rect do frame
    In7_frame.x = 0;
    In7_frame.y = 0;
    In7_frame.w = 53;
    In7_frame.h = in_frameH;
    //Rect da posição do player na tela
    In7_position.x = SCREEN_WIDTH/2;
    In7_position.y = SCREEN_HEIGHT-63;
    In7_position.w = in_frameW;
    In7_position.h = in_frameH;
    //Rect do frame
    In8_frame.x = 0;
    In8_frame.y = 0;
    In8_frame.w = in_frameW;
    In8_frame.h = in_frameH;
    //Rect da posição do player na tela
    In8_position.x = SCREEN_WIDTH-63;
    In8_position.y = SCREEN_HEIGHT/2;
    In8_position.w = 53;
    In8_position.h = in_frameH;

    vidaIni5=1;//inimigo 5
    vidaIni6=1;//inimigo 6
    vidaIni7=1;//inimigo 7
    vidaIni8=1;//inimigo 8

    //totInimigos=vidaIni4+vidaIni3+vidaIni2+vidaIni1;
}

void correVagabundo()
{
    if(vidaIni1==1){
        if(In1_position.x!=player_position.x && In1_position.y!=player_position.y)
        {
            
            if(In1_position.x>player_position.x)
            {
                if(In1_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x -= j;
                        In1_position.y -=j;
                        In1_frame.x=50;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In1_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x -= j;
                        In1_position.y +=j;
                        In1_frame.x=150;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In1_position.x<player_position.x)
            {
                if(In1_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x += j;
                        In1_position.y -=j;
                        In1_frame.x=350;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In1_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x += j;
                        In1_position.y +=j;
                        In1_frame.x=250;
                        if(In1_position.x==player_position.x || In1_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In1_position.x!=player_position.x && In1_position.y==player_position.y)
        {
            
            if(In1_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x -= j;
                        In1_frame.x=100;
                        if(In1_position.x==player_position.x)
                            j=2;
                    } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.x += j;
                        In1_frame.x=300;
                        if(In1_position.x==player_position.x)
                            j=2;
                    } 
            }
        }
        else if(In1_position.x==player_position.x && In1_position.y!=player_position.y)
        {
            
            if(In1_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.y -= j;
                        In1_frame.x=0;
                        if(In1_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In1_position.y += j;
                        In1_frame.x=200;
                        if(In1_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In1_position.x==player_position.x && In1_position.y==player_position.y)
        {
            vidaIni1=0;
            vida--;
        }

    }
    if(vidaIni2==1)
    {
        if(In2_position.x!=player_position.x && In2_position.y!=player_position.y)
        {
            
            if(In2_position.x>player_position.x)
            {
                if(In2_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x -= j;
                        In2_position.y -=j;
                        In2_frame.x=53;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In2_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x -= j;
                        In2_position.y +=j;
                        In2_frame.x=159;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In2_position.x<player_position.x)
            {
                if(In2_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x += j;
                        In2_position.y -=j;
                        In2_frame.x=371;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In2_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x += j;
                        In2_position.y +=j;
                        In2_frame.x=265;
                        if(In2_position.x==player_position.x || In2_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In2_position.x!=player_position.x && In2_position.y==player_position.y)
        {
            
            if(In2_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x -= j;
                        In2_frame.x=106;
                        if(In2_position.x==player_position.x)
                            j=2;
                    } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.x += j;
                        In2_frame.x=318;
                        if(In2_position.x==player_position.x)
                            j=2;
                    } 
            }
        }
        else if(In2_position.x==player_position.x && In2_position.y!=player_position.y)
        {
            
            if(In2_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.y -= j;
                        In2_frame.x=0;
                        if(In2_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In2_position.y += j;
                        In2_frame.x=212;
                        if(In2_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In2_position.x==player_position.x && In2_position.y==player_position.y)
        {
            vidaIni2=0;
            vida--;
        }

    }
    if(vidaIni3==1)
    {
        if(In3_position.x!=player_position.x && In3_position.y!=player_position.y)
        {
            if(In3_position.x>player_position.x)
            {
                if(In3_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x -= j;
                        In3_position.y -=j;
                        In3_frame.x=53;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In3_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x -= j;
                        In3_position.y +=j;
                        In3_frame.x=159;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In3_position.x<player_position.x)
            {
                if(In3_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x += j;
                        In3_position.y -=j;
                        In3_frame.x=371;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In3_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.x += j;
                        In3_position.y +=j;
                        In3_frame.x=265;
                        if(In3_position.x==player_position.x || In3_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In3_position.x!=player_position.x && In3_position.y==player_position.y)
        {
            
            if(In3_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In3_position.x -= j;
                    In3_frame.x=106;
                    if(In3_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In3_position.x += j;
                    In3_frame.x=318;
                    if(In3_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In3_position.x==player_position.x && In3_position.y!=player_position.y)
        {
            
            if(In3_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.y -= j;
                        In3_frame.x=0;
                        if(In3_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In3_position.y += j;
                        In3_frame.x=212;
                        if(In3_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In3_position.x==player_position.x && In3_position.y==player_position.y)
        {
            vidaIni3=0;
            vida--;
        }
    }
    if(vidaIni4==1)
    {
        if(In4_position.x!=player_position.x && In4_position.y!=player_position.y)
        {
            if(In4_position.x>player_position.x)
            {
                if(In4_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x -= j;
                        In4_position.y -=j;
                        In4_frame.x=53;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In4_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x -= j;
                        In4_position.y +=j;
                        In4_frame.x=159;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In4_position.x<player_position.x)
            {
                if(In4_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x += j;
                        In4_position.y -=j;
                        In4_frame.x=371;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In4_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.x += j;
                        In4_position.y +=j;
                        In4_frame.x=265;
                        if(In4_position.x==player_position.x || In4_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In4_position.x!=player_position.x && In4_position.y==player_position.y)
        {
            
            if(In4_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In4_position.x -= j;
                    In4_frame.x=106;
                    if(In4_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In4_position.x += j;
                    In4_frame.x=318;
                    if(In4_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In4_position.x==player_position.x && In4_position.y!=player_position.y)
        {
            
            if(In4_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.y -= j;
                        In4_frame.x=0;
                        if(In4_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In4_position.y += j;
                        In4_frame.x=212;
                        if(In4_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In4_position.x==player_position.x && In4_position.y==player_position.y)
        {
            vidaIni4=0;
            vida--;
        }
    }
        if(vidaIni5==1){
        if(In5_position.x!=player_position.x && In5_position.y!=player_position.y)
        {
            
            if(In5_position.x>player_position.x)
            {
                if(In5_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x -= j;
                        In5_position.y -=j;
                        In5_frame.x=50;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In5_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x -= j;
                        In5_position.y +=j;
                        In5_frame.x=150;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In5_position.x<player_position.x)
            {
                if(In5_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x += j;
                        In5_position.y -=j;
                        In5_frame.x=350;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In5_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x += j;
                        In5_position.y +=j;
                        In5_frame.x=250;
                        if(In5_position.x==player_position.x || In5_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In5_position.x!=player_position.x && In5_position.y==player_position.y)
        {
            
            if(In5_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x -= j;
                        In5_frame.x=100;
                        if(In5_position.x==player_position.x)
                            j=2;
                    } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.x += j;
                        In5_frame.x=300;
                        if(In5_position.x==player_position.x)
                            j=2;
                    } 
            }
        }
        else if(In5_position.x==player_position.x && In5_position.y!=player_position.y)
        {
            
            if(In5_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.y -= j;
                        In5_frame.x=0;
                        if(In5_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In5_position.y += j;
                        In5_frame.x=200;
                        if(In5_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In5_position.x==player_position.x && In5_position.y==player_position.y)
        {
            vidaIni5=0;
            vida--;
        }

    }
    if(vidaIni6==1)
    {
        if(In6_position.x!=player_position.x && In6_position.y!=player_position.y)
        {
            if(In6_position.x>player_position.x)
            {
                if(In6_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x -= j;
                        In6_position.y -=j;
                        In6_frame.x=53;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In6_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x -= j;
                        In6_position.y +=j;
                        In6_frame.x=159;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In6_position.x<player_position.x)
            {
                if(In6_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x += j;
                        In6_position.y -=j;
                        In6_frame.x=371;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In4_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.x += j;
                        In6_position.y +=j;
                        In6_frame.x=265;
                        if(In6_position.x==player_position.x || In6_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In6_position.x!=player_position.x && In6_position.y==player_position.y)
        {
            
            if(In6_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In6_position.x -= j;
                    In6_frame.x=106;
                    if(In6_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In6_position.x += j;
                    In6_frame.x=318;
                    if(In6_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In6_position.x==player_position.x && In6_position.y!=player_position.y)
        {
            
            if(In6_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.y -= j;
                        In6_frame.x=0;
                        if(In6_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In6_position.y += j;
                        In6_frame.x=212;
                        if(In6_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In6_position.x==player_position.x && In6_position.y==player_position.y)
        {
            vidaIni6=0;
            vida--;
        }

    }
    if(vidaIni7==1)
    {
        if(In7_position.x!=player_position.x && In7_position.y!=player_position.y)
        {
            if(In7_position.x>player_position.x)
            {
                if(In7_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x -= j;
                        In7_position.y -=j;
                        In7_frame.x=53;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In7_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x -= j;
                        In7_position.y +=j;
                        In7_frame.x=159;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In7_position.x<player_position.x)
            {
                if(In7_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x += j;
                        In7_position.y -=j;
                        In7_frame.x=371;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In7_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.x += j;
                        In7_position.y +=j;
                        In7_frame.x=265;
                        if(In7_position.x==player_position.x || In7_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In7_position.x!=player_position.x && In7_position.y==player_position.y)
        {
            
            if(In7_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In7_position.x -= j;
                    In7_frame.x=106;
                    if(In7_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In7_position.x += j;
                    In7_frame.x=318;
                    if(In7_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In7_position.x==player_position.x && In7_position.y!=player_position.y)
        {
            
            if(In7_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.y -= j;
                        In7_frame.x=0;
                        if(In7_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In7_position.y += j;
                        In7_frame.x=212;
                        if(In7_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In7_position.x==player_position.x && In7_position.y==player_position.y)
        {
            vidaIni7=0;
            vida--;
        }

    }
    if(vidaIni8==1)
    {
        if(In8_position.x!=player_position.x && In8_position.y!=player_position.y)
        {
            if(In8_position.x>player_position.x)
            {
                if(In8_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x -= j;
                        In8_position.y -=j;
                        In8_frame.x=53;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In8_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x -= j;
                        In8_position.y +=j;
                        In8_frame.x=159;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (In8_position.x<player_position.x)
            {
                if(In8_position.y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x += j;
                        In8_position.y -=j;
                        In8_frame.x=371;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
                else if(In8_position.y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.x += j;
                        In8_position.y +=j;
                        In8_frame.x=265;
                        if(In8_position.x==player_position.x || In8_position.y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(In8_position.x!=player_position.x && In8_position.y==player_position.y)
        {
            
            if(In8_position.x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In8_position.x -= j;
                    In8_frame.x=106;
                    if(In8_position.x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    In8_position.x += j;
                    In8_frame.x=318;
                    if(In8_position.x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(In8_position.x==player_position.x && In8_position.y!=player_position.y)
        {
            
            if(In8_position.y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.y -= j;
                        In8_frame.x=0;
                        if(In8_position.y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        In8_position.y += j;
                        In8_frame.x=212;
                        if(In8_position.y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(In8_position.x==player_position.x && In8_position.y==player_position.y)
        {
            vidaIni8=0;
            vida--;
        }

    }
}

void atirador(BULLET bullet_vet[], float velobull, SDL_Surface* bullet, SDL_Rect bullet_frame[], SDL_Rect bullet_position[], SDL_Surface* Background, SDL_Surface* Screen)
{
    int j;
    if(vida!=0)
    {
    for(j=0; j<MAX_BULLETCOUNT; j++)
    {
        if(bullet_vet[j].tiro == 1)
        {
            if(bullet_vet[j].posi==1)
            {
                teste=bullet_position[j].y;
                teste2=bullet_position[j].x;
                for(k=0.5; k<velobull; k++)
                {
                    teste-=k;
                    if(teste==In1_position.y && teste2==In1_position.x)
                    {
                        vidaIni1=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;

                    }
                    if(teste==In2_position.y && teste2==In2_position.x)
                    {
                        vidaIni2=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.y && teste2==In3_position.x)
                    {
                        vidaIni3=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.y && teste2==In4_position.x)
                    {
                        vidaIni4=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.y && teste2==In5_position.x)
                    {
                        vidaIni5=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.y && teste2==In6_position.x)
                    {
                        vidaIni6=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.y && teste2==In7_position.x)
                    {
                        vidaIni7=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.y && teste2==In8_position.x)
                    {
                        vidaIni8=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    } 
                }
                bullet_position[j].y -= velobull;
            }
            if(bullet_vet[j].posi==2)
            {
                teste=bullet_position[j].x;
                teste2=bullet_position[j].y;
                for(k=0.5; k<velobull; k++)
                {
                    teste-=k;
                    if(teste==In1_position.x && teste2==In1_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni1=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.x && teste2==In2_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni2=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.x && teste2==In3_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni3=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.x && teste2==In4_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni4=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.x && teste2==In5_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni5=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.x && teste2==In6_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni6=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.x && teste2==In7_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni7=0;
                         if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.x && teste2==In8_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni8=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    }
                }
                bullet_position[j].x -= velobull;
            }
            if(bullet_vet[j].posi==3)
            {
                teste=bullet_position[j].y;
                teste2=bullet_position[j].x;
                for(k=0.5; k<velobull; k++)
                {
                    teste+=k;
                    if(teste==In1_position.y && teste2==In1_position.x)
                    {
                        vidaIni1=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.y && teste2==In2_position.x)
                    {
                        vidaIni2=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.y && teste2==In3_position.x)
                    {
                        vidaIni3=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.y && teste2==In4_position.x)
                    {
                        vidaIni4=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.y && teste2==In5_position.x)
                    {
                        vidaIni5=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.y && teste2==In6_position.x)
                    {
                        vidaIni6=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.y && teste2==In7_position.x)
                    {
                        vidaIni7=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.y && teste2==In8_position.x)
                    {
                        vidaIni8=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    }
                }
                bullet_position[j].y += velobull;
            }
            if(bullet_vet[j].posi==4)
            {
                teste=bullet_position[j].x;
                teste2=bullet_position[j].y;
                for(k=0.5; k<velobull; k++)
                {
                    teste+=k;
                    if(teste==In1_position.x && teste2==In1_position.y)
                    {
                        vidaIni1=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.x && teste2==In2_position.y)
                    {
                        vidaIni2=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.x && teste2==In3_position.y)
                    {
                        vidaIni3=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.x && teste2==In4_position.y)
                    {
                        vidaIni4=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.x && teste2==In5_position.y)
                    {
                        vidaIni5=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.x && teste2==In6_position.y)
                    {
                        vidaIni6=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.x && teste2==In7_position.y)
                    {
                        vidaIni7=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.x && teste2==In8_position.y)
                    {
                        vidaIni8=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    }
                }
                bullet_position[j].x += velobull;
            }
            if(bullet_vet[j].posi==5)
            {
                teste=bullet_position[j].x;
                teste2=bullet_position[j].y;
                for(k=0.5; k<velobull; k++)
                {
                    teste+=k;
                    teste2-=k;
                    if(teste==In1_position.x && teste2==In1_position.y)
                    {
                        vidaIni1=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.x && teste2==In2_position.y)
                    {
                        vidaIni2=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.x && teste2==In3_position.y)
                    {
                        vidaIni3=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.x && teste2==In4_position.y)
                    {
                        vidaIni4=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.x && teste2==In5_position.y)
                    {
                        vidaIni5=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.x && teste2==In6_position.y)
                    {
                        vidaIni6=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.x && teste2==In7_position.y)
                    {
                        vidaIni7=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.x && teste2==In8_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni8=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    }
                }
                bullet_position[j].y -= velobull;
                bullet_position[j].x += velobull;
            }
            if(bullet_vet[j].posi==6)
            {
                teste=bullet_position[j].x;
                teste2=bullet_position[j].y;
                for(k=0.5; k<velobull; k++)
                {
                    teste+=k;
                    teste2+=k;
                    if(teste==In1_position.x && teste2==In1_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni1=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.x && teste2==In2_position.y)
                    {
                        vidaIni2=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.x && teste2==In3_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni3=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.x && teste2==In4_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni4=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.x && teste2==In5_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni5=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.x && teste2==In6_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni6=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.x && teste2==In7_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni7=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.x && teste2==In8_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni8=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    }
                }
                bullet_position[j].y += velobull;
                bullet_position[j].x += velobull;
            }
            if(bullet_vet[j].posi==7)
            {
                teste=bullet_position[j].x;
                teste2=bullet_position[j].y;
                for(k=0.5; k<velobull; k++)
                {
                    teste-=k;
                    teste2-=k;
                    if(teste==In1_position.x && teste2==In1_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni1=0;
                         if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.x && teste2==In2_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni2=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.x && teste2==In3_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni3=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.x && teste2==In4_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni4=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.x && teste2==In5_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni5=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.x && teste2==In6_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni6=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.x && teste2==In7_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni7=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.x && teste2==In8_position.y)
                    {
                        Mix_PlayChannel( -1, explosao, 0 );
                        vidaIni8=0;
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                            pont+=40;
                        }
                    }
                }
                bullet_position[j].y -= velobull;
                bullet_position[j].x -= velobull;
            }
            if(bullet_vet[j].posi==8)
            {
                teste=bullet_position[j].x;
                teste2=bullet_position[j].y;
                for(k=0.5; k<velobull; k++)
                {
                    teste-=k;
                    teste2+=k;
                    if(teste==In1_position.x && teste2==In1_position.y)
                    {
                        vidaIni1=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In2_position.x && teste2==In2_position.y)
                    {
                        vidaIni2=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In3_position.x && teste2==In3_position.y)
                    {
                        vidaIni3=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In4_position.x && teste2==In4_position.y)
                    {
                        vidaIni4=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                         if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In5_position.x && teste2==In5_position.y)
                    {
                        vidaIni5=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In6_position.x && teste2==In6_position.y)
                    {
                        vidaIni6=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In7_position.x && teste2==In7_position.y)
                    {
                        vidaIni7=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    if(teste==In8_position.x && teste2==In8_position.y)
                    {
                        vidaIni8=0;
                        Mix_PlayChannel( -1, explosao, 0 );
                        if(gameRunning==1)
                            pont+=10;
                        else if(gameRunning==2)
                            pont+=20;
                        else if(gameRunning==3)
                            pont+=30;
                    }
                    for(e=0; e<MAX_ENEMY; e++)
                    {
                        if(teste==enemy_position[e].y && teste2==enemy_position[e].x)
                        {
                        vidaE[e]=0;
                        vidaC--;
                        Mix_PlayChannel( -1, explosao, 0 );
                        pont+=40;
                        }
                    }
                }
                bullet_position[j].y += velobull;
                bullet_position[j].x -= velobull;
            }
        }

        if(bullet_position[j].y > 0 && bullet_position[j].y < SCREEN_HEIGHT && bullet_position[j].x > 0 && bullet_position[j].x < SCREEN_WIDTH)
        {
                SDL_BlitSurface(bullet, &bullet_frame[j], Screen, &bullet_position[j]);
            //SDL_BlitSurface(Background, NULL, Screen, NULL);
        }
        else
        {
            bullet_vet[j].tiro=0;
            bullet_position[j].x= SCREEN_WIDTH+1;
            bullet_position[j].y= 0;
        }
    }
}
}
void aparecechefe()
{
    chefe_position.x=0;
    chefe_position.y=(SCREEN_HEIGHT/2);
    chefe_position.w = in_frameW;
    chefe_position.h = in_frameH;
    chefe2_position.x=SCREEN_WIDTH-200;
    chefe2_position.y=(SCREEN_HEIGHT/2);
    chefe2_position.w = in_frameW;
    chefe2_position.h = in_frameH;
}
void Chora()
{
    if(vidaIni1==0)
    {
        In1_position.x = 0;
        In1_position.y = 0;
    }
    if(vidaIni2==0)
    {
        In2_position.x = 0;
        In2_position.y = 0;
    }
    if(vidaIni3==0)
    {
        In3_position.x = 0;
        In3_position.y = 0;
    }
    if(vidaIni4==0)
    {
        In4_position.x = 0;
        In4_position.y = 0;
    }     
    if(vidaIni5==0)
    {
        In5_position.x = 0;
        In5_position.y = 0;
    }
    if(vidaIni6==0)
    {
        In6_position.x = 0;
        In6_position.y = 0;
    }
    if(vidaIni7==0)
    {
        In7_position.x = 0;
        In7_position.y = 0;
    }
    if(vidaIni8==0)
    {
        In8_position.x = 0;
        In8_position.y = 0;
    }    
}
void pegaAsImagens()
{
    Background = IMG_Load("aa.png");
    Player = IMG_Load("nova nova1.png");
    In1 = IMG_Load("inimigo 1.png");
    In2 = IMG_Load("inimigo 1.1.png");
    In3 = IMG_Load("inimigo 1.2.png");
    in4 = IMG_Load("Inimigo 2.png");
    Boss = IMG_Load("boss.png");
    bullet = IMG_Load("missile.png");
    menu=IMG_Load("menu.png");
    logo=IMG_Load("logo1.png");
    instrucoes=IMG_Load("instruções.png");
    creditos=IMG_Load("sobre.png");
    lose=IMG_Load("lose.png");
    win=IMG_Load("You Win.png");
    Vida = IMG_Load("lives.png");
    cursor = IMG_Load("nn.png");
    bullet2 = IMG_Load("tiro3.png");
    bullet3=IMG_Load("tiro2.png");
    pausa=IMG_Load("pause.png"); 
    Bos=IMG_Load("bos.png");
}
void vidaP()
{
    vida_position.x=0;
    vida_position.y=0;
    vida_position.w=vida_framW;
    vida_frame.h=vida_framH;
    if(vida==5)
    {
        vida_frame.x=0;
        vida_frame.y=0;
        vida_frame.w=240;
        vida_frame.h=vida_framH;
    }
    else if(vida==4)
    {
        vida_frame.x=0;
        vida_frame.y=0;
        vida_frame.w=192;
        vida_frame.h=vida_framH;
    }
    else if(vida==3)
    {
        vida_frame.x=0;
        vida_frame.y=0;
        vida_frame.w=144;
        vida_frame.h=vida_framH;
    }
    else if(vida==2)
    {
        vida_frame.x=0;
        vida_frame.y=0;
        vida_frame.w=96;
        vida_frame.h=vida_framH;
    }
    else if(vida==1)
    {
        vida_frame.x=0;
        vida_frame.y=0;
        vida_frame.w=48;
        vida_frame.h=vida_framH;
    }
    if(vida!=0)
        SDL_BlitSurface(Vida, &vida_frame, Screen, &vida_position);
}
void anda()
{
    if(player_frame.x==0)
            player_position.y-=vely;
    else if(player_frame.x==50)
    {
        player_position.x-=velx;
        player_position.y-=vely;
    }
    else if(player_frame.x==100)
        player_position.x-=velx;
    else if(player_frame.x==150)
    {
        player_position.x-=velx;
        player_position.y+=vely;
    }
    else if(player_frame.x==200)
        player_position.y+=vely;
    else if(player_frame.x==250)
    {
        player_position.x+=velx;
        player_position.y+=vely;
    }
    else if(player_frame.x==300)
        player_position.x+=velx;
    else if(player_frame.x==350)
    {
        player_position.x+=velx;
        player_position.y-=vely;
    }
    if(player_position.y > 50){
        player_position.y -= vely;
    }
    if(player_position.x > 0)
    {
        player_position.x -= velx;
    }
    if(player_position.x < SCREEN_WIDTH - in_frameW)
    {
        player_position.x += velx;
    }
    if(player_position.y < SCREEN_HEIGHT - in_frameH)
    {
        player_position.y += vely;
    }
}

void fase1()
{
    while(gameRunning==1)
    { 
        //Mix_PlayMusic(fase, 1 );
        //Checar se há eventos
        if(SDL_PollEvent(&event))
        {                   
            if(event.type == SDL_QUIT)
            {
                gameRunning = 0;
            }
            //Verifica se houve tecla pressionada
            if(event.type == SDL_KEYDOWN)
            {
                // Declarando uma variavel para teclado
                const Uint8 *keystates = SDL_GetKeyboardState(NULL);
                //definindo teclas
                int cima_pressionado = keystates[SDL_SCANCODE_UP];
                int baixo = keystates[SDL_SCANCODE_DOWN];
                int esquerda = keystates[SDL_SCANCODE_LEFT];
                int direita = keystates[SDL_SCANCODE_RIGHT];
                int tiro_pressionado = keystates[SDL_SCANCODE_SPACE];
                int pausar = keystates[SDL_SCANCODE_RETURN];
                int w=keystates[SDL_SCANCODE_W];
                int d=keystates[SDL_SCANCODE_D];
                int s=keystates[SDL_SCANCODE_S];
                int a=keystates[SDL_SCANCODE_A];
                // Executando movimentacoes
                if(pausar)
                {
                    if(Pause==0)
                        Pause=1;
                    else 
                        Pause=0;
                }
                if(Pause==1) 
                {
                //Principais
                    if (cima_pressionado)
                    {
                        if(velx<10 && vely<10)
                        {
                            velx+=2;
                            vely+=2;
                        }
                    }
                    else if (baixo)
                    {
                        velx-=2;
                        vely-=2;
                    }
                    else if (esquerda)
                    {
                        if(player_frame.x==350)
                            player_frame.x=0;
                        else
                            player_frame.x += player_frame.w;
                    }
                    else if (direita)
                    {
                        if(player_frame.x==0)
                            player_frame.x=350;
                        else
                            player_frame.x -= player_frame.w;
                    }
                    if(tiro_pressionado)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        if(player_frame.x==0)
                        {
                            bullet_vet[i].posi=1;
                            bullet_frame[i].x=0;
                        }      
                        else if(player_frame.x==50)
                        {
                            bullet_frame[i].x=50;
                            bullet_vet[i].posi=7;
                        }
                        else if(player_frame.x==100)
                        {
                            bullet_frame[i].x=100;
                            bullet_vet[i].posi=2;
                        }
                        else if(player_frame.x==150)
                        {
                            bullet_frame[i].x=150;
                            bullet_vet[i].posi=8;
                        }
                        else if(player_frame.x==200)
                        {
                            bullet_frame[i].x=200;
                            bullet_vet[i].posi=3;
                        }
                        else if(player_frame.x==250)
                        {
                            bullet_frame[i].x=250;
                            bullet_vet[i].posi=6;
                        }
                        else if(player_frame.x==300)
                        {
                            bullet_frame[i].x=300;
                            bullet_vet[i].posi=4;
                        }
                        else if(player_frame.x==350)
                        {
                            bullet_frame[i].x=350;
                            bullet_vet[i].posi=5;
                        }
                    }
                    //tiro
                    if(d && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=5;
                    }
                    else if(d && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        {
                            i=0;
                        }
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=6;
                    }
                    else if(a && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=7;
                    }
                    else if(a && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=8;
                    }
                    else if(w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=1;
                    }
                    else if(a)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=2;
                    }
                    else if(s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=3;
                    }       
                    else if(d)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=4;
                    }
                }
            }
            if (event.type == SDL_KEYUP) // Se o usuário soltou um botão do teclado
            {
                // Verifica qual tecla foi solta
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(vely>2 && velx>2)
                        {
                            vely = 2;
                            velx = 2;
                        }
                    break;
                    case SDLK_DOWN:
                        vely = 2;
                        velx =2;
                    break;
                    default:
                    break;
                }
            }
        }
        if(Pause==1) 
        {
            anda();
            correVagabundo();
            Chora();
        }
        //Atualiza a tela de fundo
        SDL_BlitSurface(Background, NULL, Screen, NULL);
        sprintf(pontuacao, "                                                                 Pontos: %d", pont);
        escrever = TTF_RenderText_Solid(fonte, pontuacao, cor);
        SDL_BlitSurface(escrever, NULL, Screen, &dst_rect);
        if(Pause==0)
            SDL_BlitSurface(pausa, NULL, Screen, &pause_position);
        //SDL_BlitSurface(gPlayer, NULL, gScreen, NULL); não usar
        totInimigos=vidaIni1+vidaIni2+vidaIni3+vidaIni4+vidaIni5+vidaIni6+vidaIni7+vidaIni8;
        if(totInimigos==0)
        {
            gameRunning=2;
            SDL_Delay(30);
        }
        if (vida==0)
        {
            int j;
            vidaIni1=0;
            vidaIni2=0;
            vidaIni3=0;
            vidaIni4=0;
            vidaIni5=0;
            vidaIni6=0;
            vidaIni7=0;
            vidaIni8=0;
            for(j=0; j<MAX_BULLETCOUNT; j++)
            {
                bullet_vet[j].tiro = 0;
            }
            atirador(bullet_vet, velobull, bullet, bullet_frame, bullet_position, Background, Screen);
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            SDL_BlitSurface(lose, NULL, Screen, &lose_position);
            gameRunning=0;
            SDL_Delay(30);
        }
        if(gameRunning!=0 || vida!=0)
            SDL_BlitSurface(Player, &player_frame, Screen, &player_position);
        if(vidaIni1==1)
            SDL_BlitSurface(In1, &In1_frame, Screen, &In1_position);
        if(vidaIni2==1)
            SDL_BlitSurface(In1, &In2_frame, Screen, &In2_position);
        if(vidaIni3==1)
            SDL_BlitSurface(In1, &In3_frame, Screen, &In3_position);
        if(vidaIni4==1)
            SDL_BlitSurface(In1, &In4_frame, Screen, &In4_position);
        if(vidaIni5==1)
            SDL_BlitSurface(In1, &In5_frame, Screen, &In5_position);
        if(vidaIni6==1)
            SDL_BlitSurface(In1, &In6_frame, Screen, &In6_position);
        if(vidaIni7==1)
            SDL_BlitSurface(In1, &In7_frame, Screen, &In7_position);
        if(vidaIni8==1)
            SDL_BlitSurface(In1, &In8_frame, Screen, &In8_position);
        if(gameRunning!=0)
            vidaP();
        if(gameRunning!=0 || vida!=0)
            atirador(bullet_vet, velobull, bullet, bullet_frame, bullet_position, Background, Screen);
        //Atualiza a surface
        SDL_UpdateWindowSurface( window );
        //Delay de 2 segundos
        SDL_Delay(30);

    }
    if(gameRunning==0)
    { 
        guardaRecorde();
        SDL_Delay(5000);
        opcao=0;
        Menu();
    }
    else
    {
        apareceVagabundo();
        apareceVagabundo1();
        fase2();
    }
}       
    
    void fase2()
    {
        while(gameRunning==2)
     { 
            //Mix_PlayMusic(fase, 1 );
            //Checar se há eventos
         if(SDL_PollEvent(&event))
            {                   
             if(event.type == SDL_QUIT)
                {
                    exit(1);
                }
                //Verifica se houve tecla pressionada
             if(event.type == SDL_KEYDOWN)
            {
                // Declarando uma variavel para teclado
                const Uint8 *keystates = SDL_GetKeyboardState(NULL);
                //definindo teclas
                int cima_pressionado = keystates[SDL_SCANCODE_UP];
                int baixo = keystates[SDL_SCANCODE_DOWN];
                int esquerda = keystates[SDL_SCANCODE_LEFT];
                int direita = keystates[SDL_SCANCODE_RIGHT];
                int tiro_pressionado = keystates[SDL_SCANCODE_SPACE];
                int pausar = keystates[SDL_SCANCODE_RETURN];
                int w=keystates[SDL_SCANCODE_W];
                int d=keystates[SDL_SCANCODE_D];
                int s=keystates[SDL_SCANCODE_S];
                int a=keystates[SDL_SCANCODE_A];
                // Executando movimentacoes
                if(pausar)
                {
                    if(Pause==0)
                        Pause=1;
                    else 
                        Pause=0;
                }
                if(Pause==1) 
                {
                //Principais
                    if (cima_pressionado)
                    {
                        if(velx<10 && vely<10)
                        {
                            velx+=2;
                            vely+=2;
                        }
                    }
                    else if (baixo)
                    {
                        velx-=2;
                        vely-=2;
                    }
                    else if (esquerda)
                    {
                        if(player_frame.x==350)
                            player_frame.x=0;
                        else
                            player_frame.x += player_frame.w;
                    }
                    else if (direita)
                    {
                        if(player_frame.x==0)
                            player_frame.x=350;
                        else
                            player_frame.x -= player_frame.w;
                    }
                    if(tiro_pressionado)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        if(player_frame.x==0)
                        {
                            bullet_vet[i].posi=1;
                            bullet_frame[i].x=0;
                        }      
                        else if(player_frame.x==50)
                        {
                            bullet_frame[i].x=50;
                            bullet_vet[i].posi=7;
                        }
                        else if(player_frame.x==100)
                        {
                            bullet_frame[i].x=100;
                            bullet_vet[i].posi=2;
                        }
                        else if(player_frame.x==150)
                        {
                            bullet_frame[i].x=150;
                            bullet_vet[i].posi=8;
                        }
                        else if(player_frame.x==200)
                        {
                            bullet_frame[i].x=200;
                            bullet_vet[i].posi=3;
                        }
                        else if(player_frame.x==250)
                        {
                            bullet_frame[i].x=250;
                            bullet_vet[i].posi=6;
                        }
                        else if(player_frame.x==300)
                        {
                            bullet_frame[i].x=300;
                            bullet_vet[i].posi=4;
                        }
                        else if(player_frame.x==350)
                        {
                            bullet_frame[i].x=350;
                            bullet_vet[i].posi=5;
                        }
                    }
                    //tiro
                    if(d && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=5;
                    }
                    else if(d && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        {
                            i=0;
                        }
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=6;
                    }
                    else if(a && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=7;
                    }
                    else if(a && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=8;
                    }
                    else if(w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=1;
                    }
                    else if(a)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=2;
                    }
                    else if(s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=3;
                    }       
                    else if(d)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=4;
                    }
                }
            }
            if (event.type == SDL_KEYUP) // Se o usuário soltou um botão do teclado
            {
                // Verifica qual tecla foi solta
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(vely>2 && velx>2)
                        {
                            vely = 2;
                            velx = 2;
                        }
                    break;
                    case SDLK_DOWN:
                        vely = 2;
                        velx =2;
                    break;
                    default:
                    break;
                }
            }
        }
        if(Pause==1)
        {
            anda();
            correVagabundo();
            Chora();
        }
        //Atualiza a tela de fundo
        SDL_BlitSurface(Background, NULL, Screen, NULL);
        sprintf(pontuacao, "                                                                 Pontos: %d", pont);
        escrever = TTF_RenderText_Solid(fonte, pontuacao, cor);
        SDL_BlitSurface(escrever, NULL, Screen, &dst_rect);
        if(Pause==0)
            SDL_BlitSurface(pausa, NULL, Screen, &pause_position);
        totInimigos=vidaIni1+vidaIni2+vidaIni3+vidaIni4+vidaIni5+vidaIni6+vidaIni7+vidaIni8;
        if(totInimigos==0)
        {
            gameRunning=3;
            SDL_Delay(30);
        }
        if (vida==0)
        {
            int j;
            vidaIni1=0;
            vidaIni2=0;
            vidaIni3=0;
            vidaIni4=0;
            vidaIni5=0;
            vidaIni6=0;
            vidaIni7=0;
            vidaIni8=0;
            for(j=0; j<MAX_BULLETCOUNT; j++)
            {
                bullet_vet[j].tiro = 0;
            }
            atirador(bullet_vet, velobull, bullet2, bullet_frame, bullet_position, Background, Screen);
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            SDL_BlitSurface(lose, NULL, Screen, &lose_position);
            gameRunning=0;
            SDL_Delay(30);
        }
        if(gameRunning!=0 || vida!=0)
            SDL_BlitSurface(Player, &player_frame, Screen, &player_position);
        if(vidaIni1==1)
            SDL_BlitSurface(In2, &In1_frame, Screen, &In1_position);
        if(vidaIni2==1)
            SDL_BlitSurface(In2, &In2_frame, Screen, &In2_position);
        if(vidaIni3==1)
            SDL_BlitSurface(In2, &In3_frame, Screen, &In3_position);
        if(vidaIni4==1)
            SDL_BlitSurface(In2, &In4_frame, Screen, &In4_position);
        if(vidaIni5==1)
            SDL_BlitSurface(In2, &In5_frame, Screen, &In5_position);
        if(vidaIni6==1)
            SDL_BlitSurface(In2, &In6_frame, Screen, &In6_position);
        if(vidaIni7==1)
            SDL_BlitSurface(In2, &In7_frame, Screen, &In7_position);
        if(vidaIni8==1)
            SDL_BlitSurface(In2, &In8_frame, Screen, &In8_position);
        if(gameRunning!=0)
            vidaP();
        if(gameRunning!=0 || vida!=0)
            atirador(bullet_vet, velobull, bullet2, bullet_frame, bullet_position, Background, Screen);
        //Atualiza a surface
        SDL_UpdateWindowSurface( window );
        //Delay de 2 segundos
        SDL_Delay(30);

    }
    if(gameRunning==0)
    {
        SDL_Delay(5000);
        opcao=0;
        Menu();
    }
    else
    {
        apareceVagabundo();
        apareceVagabundo1();
        fase3();
    }
}
void fase3()
{
    while(gameRunning==3)
    { 
        //Mix_PlayMusic(fase, 1 );
        //Checar se há eventos
        if(SDL_PollEvent(&event))
        {                   
            if(event.type == SDL_QUIT)
            {
                exit(1);
            }
            //Verifica se houve tecla pressionada
            if(event.type == SDL_KEYDOWN)
            {
                // Declarando uma variavel para teclado
                const Uint8 *keystates = SDL_GetKeyboardState(NULL);
                //definindo teclas
                int cima_pressionado = keystates[SDL_SCANCODE_UP];
                int baixo = keystates[SDL_SCANCODE_DOWN];
                int esquerda = keystates[SDL_SCANCODE_LEFT];
                int direita = keystates[SDL_SCANCODE_RIGHT];
                int tiro_pressionado = keystates[SDL_SCANCODE_SPACE];
                int pausar = keystates[SDL_SCANCODE_RETURN];
                int w=keystates[SDL_SCANCODE_W];
                int d=keystates[SDL_SCANCODE_D];
                int s=keystates[SDL_SCANCODE_S];
                int a=keystates[SDL_SCANCODE_A];
                // Executando movimentacoes
                if(pausar)
                {
                    if(Pause==0)
                        Pause=1;
                    else 
                        Pause=0;
                }
                if(Pause==1) 
                {
                //Principais
                    if (cima_pressionado)
                    {
                        if(velx<10 && vely<10)
                        {
                            velx+=2;
                            vely+=2;
                        }
                    }
                    else if (baixo)
                    {
                        velx-=2;
                        vely-=2;
                    }
                    else if (esquerda)
                    {
                        if(player_frame.x==350)
                            player_frame.x=0;
                        else
                            player_frame.x += player_frame.w;
                    }
                    else if (direita)
                    {
                        if(player_frame.x==0)
                            player_frame.x=350;
                        else
                            player_frame.x -= player_frame.w;
                    }
                    if(tiro_pressionado)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        if(player_frame.x==0)
                        {
                            bullet_vet[i].posi=1;
                            bullet_frame[i].x=0;
                        }      
                        else if(player_frame.x==50)
                        {
                            bullet_frame[i].x=50;
                            bullet_vet[i].posi=7;
                        }
                        else if(player_frame.x==100)
                        {
                            bullet_frame[i].x=100;
                            bullet_vet[i].posi=2;
                        }
                        else if(player_frame.x==150)
                        {
                            bullet_frame[i].x=150;
                            bullet_vet[i].posi=8;
                        }
                        else if(player_frame.x==200)
                        {
                            bullet_frame[i].x=200;
                            bullet_vet[i].posi=3;
                        }
                        else if(player_frame.x==250)
                        {
                            bullet_frame[i].x=250;
                            bullet_vet[i].posi=6;
                        }
                        else if(player_frame.x==300)
                        {
                            bullet_frame[i].x=300;
                            bullet_vet[i].posi=4;
                        }
                        else if(player_frame.x==350)
                        {
                            bullet_frame[i].x=350;
                            bullet_vet[i].posi=5;
                        }
                    }
                    //tiro
                    if(d && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=5;
                    }
                    else if(d && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        {
                            i=0;
                        }
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=6;
                    }
                    else if(a && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=7;
                    }
                    else if(a && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=8;
                    }
                    else if(w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=1;
                    }
                    else if(a)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=2;
                    }
                    else if(s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=3;
                    }       
                    else if(d)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=4;
                    }
                }
            }
            if (event.type == SDL_KEYUP) // Se o usuário soltou um botão do teclado
            {
                // Verifica qual tecla foi solta
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(vely>2 && velx>2)
                        {
                            vely = 2;
                            velx = 2;
                        }
                    break;
                    case SDLK_DOWN:
                        vely = 2;
                        velx =2;
                    break;
                    default:
                    break;
                }
            }
        }
        if(Pause==1)
        {
            anda();
            correVagabundo();
            Chora();
        }
        //Atualiza a tela de fundo
        SDL_BlitSurface(Background, NULL, Screen, NULL);
        sprintf(pontuacao, "                                                                 Pontos: %d", pont);
        escrever = TTF_RenderText_Solid(fonte, pontuacao, cor);
        SDL_BlitSurface(escrever, NULL, Screen, &dst_rect);
        if(Pause==0)
            SDL_BlitSurface(pausa, NULL, Screen, &pause_position);
        totInimigos=vidaIni1+vidaIni2+vidaIni3+vidaIni4+vidaIni5+vidaIni6+vidaIni7+vidaIni8;
        if(totInimigos==0)
        {
            gameRunning=4;
            SDL_Delay(30);
        }
        if (vida==0)
        {
            int j;
            vidaIni1=0;
            vidaIni2=0;
            vidaIni3=0;
            vidaIni4=0;
            vidaIni5=0;
            vidaIni6=0;
            vidaIni7=0;
            vidaIni8=0;
            for(j=0; j<MAX_BULLETCOUNT; j++)
            {
                bullet_vet[j].tiro = 0;
            }
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            SDL_BlitSurface(lose, NULL, Screen, &lose_position);
            gameRunning=0;
            SDL_Delay(30);
        }
        if(gameRunning!=0 || vida!=0)
            SDL_BlitSurface(Player, &player_frame, Screen, &player_position);
        if(vidaIni1==1)
            SDL_BlitSurface(In3, &In1_frame, Screen, &In1_position);
        if(vidaIni2==1)
            SDL_BlitSurface(In3, &In2_frame, Screen, &In2_position);
        if(vidaIni3==1)
            SDL_BlitSurface(In3, &In3_frame, Screen, &In3_position);
        if(vidaIni4==1)
            SDL_BlitSurface(In3, &In4_frame, Screen, &In4_position);
        if(vidaIni5==1)
            SDL_BlitSurface(In3, &In5_frame, Screen, &In5_position);
        if(vidaIni6==1)
            SDL_BlitSurface(In3, &In6_frame, Screen, &In6_position);
        if(vidaIni7==1)
            SDL_BlitSurface(In3, &In7_frame, Screen, &In7_position);
        if(vidaIni8==1)
            SDL_BlitSurface(In3, &In8_frame, Screen, &In8_position);
        if(gameRunning!=0)
            vidaP();
        if(gameRunning!=0 || vida!=0)
            atirador(bullet_vet, velobull, bullet3, bullet_frame, bullet_position, Background, Screen);
        //Atualiza a surface
        SDL_UpdateWindowSurface( window );
        //Delay de 2 segundos
        SDL_Delay(30);

    }
    if (gameRunning==0)
    {
        SDL_Delay(5000);
        opcao=0;
        Menu();
    }
    else
    {
        SDL_Delay(30);
        apareceGeral();
        aparecechefe();
        fase4();
    } 
}
void Menu()
{
    cursor_position.y=278;
    while(opcao!=1)         //Menu
    {
        Mix_PlayMusic( musica, -1 );
        while(opcao==0)    
        {
            SDL_BlitSurface(menu, NULL, Screen, NULL);
            SDL_BlitSurface(cursor, NULL, Screen, &cursor_position);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_1:
                            opcao=1;
                        break;
                        case SDLK_2:
                            opcao=2;
                        break;
                        case SDLK_3:
                            opcao=3;
                        break;
                        case SDLK_4:
                            opcao=4;
                        break;
                        case SDLK_5:
                            opcao=5;
                        break;
                        case SDLK_DOWN:
                            if(cursor_position.y!=434)
                                cursor_position.y+=39;
                            else
                                cursor_position.y=278;
                        break;
                        case SDLK_UP:
                            if(cursor_position.y!=278)
                                cursor_position.y-=39;
                            else
                                cursor_position.y=434;
                        break;
                        case SDLK_RETURN:
                            if(cursor_position.y==278)
                                opcao=1;
                            else if(cursor_position.y==317)
                                opcao=2;
                            else if(cursor_position.y==356)
                                opcao=3;
                            else if(cursor_position.y==395)
                                opcao=4;
                            else
                                opcao=5;
                        break;
                    }
                }
            }
        }
        
        while(opcao==3)     //Records
        {
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            leRecorde();
            ImprimeRecerde();
            //SDL_BlitSurface(records, NULL, janela_menu, NULL);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            opcao=0;
                        break;
                    }
                }
            }
        }
        while(opcao==2)      //Instrucoes
        {
            SDL_BlitSurface(instrucoes, NULL, Screen, NULL);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            opcao=0;
                        break;
                    }
                }
            }
        }
        while(opcao==4)     //Sobre
        {
            SDL_BlitSurface(creditos, NULL, Screen, NULL);
            SDL_UpdateWindowSurface( window );
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            opcao=0;
                        break;
                    }
                }
            }
        }
        while(opcao==5)  //Sair
        {
            //Liberar as imagens da memória
            SDL_FreeSurface(Background);
            SDL_FreeSurface(Player);
            SDL_FreeSurface(In1);
            SDL_FreeSurface(In2);
            SDL_FreeSurface(In3);
            SDL_FreeSurface(lose);
            SDL_FreeSurface(menu);
            SDL_FreeSurface(bullet);
            SDL_FreeSurface(creditos);
            SDL_FreeSurface(instrucoes);
            SDL_FreeSurface(Boss);
            SDL_FreeSurface(escrever);
            SDL_FreeSurface(Bos);
            SDL_FreeSurface(bullet2);
            SDL_FreeSurface(bullet3);
            SDL_FreeSurface(in4);
            //Destruir janela
            SDL_DestroyWindow( window );
            //Encerra o SDL
            SDL_Quit();
            exit(1);
        }
    }
  

    if(opcao==1)      //Condicao do menu relativa a jogar
    {
        apareceVagabundo();
        apareceVagabundo1();
        gameRunning=1;
        vida=5;
        player_frame.x = 0;
        player_frame.y = 0;
        player_position.x = (SCREEN_WIDTH/2);
        player_position.y = (SCREEN_HEIGHT/2);
        pont=0;
        SDL_Delay(500);//delay do menu para o jogo
        fase1();
    }
}
void apareceGeral()
{
    for(cont=0; cont<MAX_ENEMY; cont++)
    {
        vidaE[cont]=1;
        enemy_frame[cont].x = 0;
        enemy_frame[cont].y=0;
        enemy_frame[cont].w = in_frameW;
        enemy_frame[cont].h = in_frameH;
        if(cont%6==0)
        {
            enemy_position[cont].x=0;
            enemy_position[cont].y=SCREEN_HEIGHT/2;
        }
        else if(cont%6==1)
        {
            enemy_position[cont].x=0;
            enemy_position[cont].y=(SCREEN_HEIGHT/2)+100;
        }
        else if(cont%6==2)
        {
            enemy_position[cont].x=0;
            enemy_position[cont].y=(SCREEN_HEIGHT/2)+200;
        }
        if(cont%6==3)
        {
            enemy_position[cont].x=SCREEN_WIDTH-50;
            enemy_position[cont].y=SCREEN_HEIGHT/2;
        }
        else if(cont%6==4)
        {
            enemy_position[cont].x=SCREEN_WIDTH-50;
            enemy_position[cont].y=(SCREEN_HEIGHT/2)+100;
        }
        else if(cont%6==5)
        {
            enemy_position[cont].x=SCREEN_WIDTH-50;
            enemy_position[cont].y=(SCREEN_HEIGHT/2)+200;
        }
    }
}
void liberouGeral()
{
    for(cont=0; cont<MAX_ENEMY; cont++)
    {
        if(vidaE[cont]==1)
        {
        if(enemy_position[cont].x!=player_position.x && enemy_position[cont].y!=player_position.y)
        {
            if(enemy_position[cont].x>player_position.x)
            {
                if(enemy_position[cont].y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        enemy_position[cont].x -= j;
                        enemy_position[cont].y -=j;
                        enemy_frame[cont].x=53;
                        if(enemy_position[cont].x==player_position.x || enemy_position[cont].y==player_position.y)
                            j=2;
                    }
                }
                else if(enemy_position[cont].y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        enemy_position[cont].x -= j;
                        enemy_position[cont].y +=j;
                        enemy_frame[cont].x=159;
                        if(enemy_position[cont].x==player_position.x || enemy_position[cont].y==player_position.y)
                            j=2;
                    }
                }
            }
            else if (enemy_position[cont].x<player_position.x)
            {
                if(enemy_position[cont].y>player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        enemy_position[cont].x += j;
                        enemy_position[cont].y -=j;
                        enemy_frame[cont].x=371;
                        if(enemy_position[cont].x==player_position.x || enemy_position[cont].y==player_position.y)
                            j=2;
                    }
                }
                else if(enemy_position[cont].y<player_position.y)
                {
                    for(j=0.5; j<=velo; j+=0.5)
                    {
                        enemy_position[cont].x += j;
                        enemy_position[cont].y +=j;
                        enemy_frame[cont].x=265;
                        if(enemy_position[cont].x==player_position.x || enemy_position[cont].y==player_position.y)
                            j=2;
                    }
                }
            }
        }
        else if(enemy_position[cont].x!=player_position.x && enemy_position[cont].y==player_position.y)
        {
            
            if(enemy_position[cont].x>player_position.x)
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    enemy_position[cont].x -= j;
                    enemy_frame[cont].x=106;
                    if(enemy_position[cont].x==player_position.x)
                        j=2;
                } 
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                {
                    enemy_position[cont].x += j;
                    enemy_frame[cont].x=318;
                    if(enemy_position[cont].x==player_position.x)
                        j=2;
                } 
            }
        }
        else if(enemy_position[cont].x==player_position.x && enemy_position[cont].y!=player_position.y)
        {
            
            if(enemy_position[cont].y>player_position.y)
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        enemy_position[cont].y -= j;
                        enemy_frame[cont].x=0;
                        if(enemy_position[cont].y==player_position.y)
                            j=2;
                    }  
            }
            else
            {
                for(j=0.5; j<=velo; j+=0.5)
                    {
                        enemy_position[cont].y += j;
                        enemy_frame[cont].x=212;
                        if(enemy_position[cont].y==player_position.y)
                            j=2;
                    } 
            }
        }
        if(enemy_position[cont].x==player_position.x && enemy_position[cont].y==player_position.y)
        {
            vidaE[cont]=0;
            vida--;
        }
        SDL_BlitSurface(In1, &enemy_frame[cont], Screen, &enemy_position[cont]);
        SDL_BlitSurface(Boss, NULL, Screen, &chefe_position);
        SDL_BlitSurface(Bos, NULL, Screen, &chefe2_position);
        }
    }
}
void fase4()
{
    while(gameRunning==4)
    { 
        //Mix_PlayMusic(fase, 1 );
        //Checar se há eventos
        if(SDL_PollEvent(&event))
        {                   
            if(event.type == SDL_QUIT)
            {
                exit(1);
            }
            //Verifica se houve tecla pressionada
            if(event.type == SDL_KEYDOWN)
            {
                // Declarando uma variavel para teclado
                const Uint8 *keystates = SDL_GetKeyboardState(NULL);
                //definindo teclas
                int cima_pressionado = keystates[SDL_SCANCODE_UP];
                int baixo = keystates[SDL_SCANCODE_DOWN];
                int esquerda = keystates[SDL_SCANCODE_LEFT];
                int direita = keystates[SDL_SCANCODE_RIGHT];
                int tiro_pressionado = keystates[SDL_SCANCODE_SPACE];
                int pausar = keystates[SDL_SCANCODE_RETURN];
                int w=keystates[SDL_SCANCODE_W];
                int d=keystates[SDL_SCANCODE_D];
                int s=keystates[SDL_SCANCODE_S];
                int a=keystates[SDL_SCANCODE_A];
                // Executando movimentacoes
                if(pausar)
                {
                    if(Pause==0)
                        Pause=1;
                    else 
                        Pause=0;
                }
                if(Pause==1) 
                {
                //Principais
                    if (cima_pressionado)
                    {
                        if(velx<10 && vely<10)
                        {
                            velx+=2;
                            vely+=2;
                        }
                    }
                    else if (baixo)
                    {
                        velx-=2;
                        vely-=2;
                    }
                    else if (esquerda)
                    {
                        if(player_frame.x==350)
                            player_frame.x=0;
                        else
                            player_frame.x += player_frame.w;
                    }
                    else if (direita)
                    {
                        if(player_frame.x==0)
                            player_frame.x=350;
                        else
                            player_frame.x -= player_frame.w;
                    }
                    if(tiro_pressionado)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        if(player_frame.x==0)
                        {
                            bullet_vet[i].posi=1;
                            bullet_frame[i].x=0;
                        }      
                        else if(player_frame.x==50)
                        {
                            bullet_frame[i].x=50;
                            bullet_vet[i].posi=7;
                        }
                        else if(player_frame.x==100)
                        {
                            bullet_frame[i].x=100;
                            bullet_vet[i].posi=2;
                        }
                        else if(player_frame.x==150)
                        {
                            bullet_frame[i].x=150;
                            bullet_vet[i].posi=8;
                        }
                        else if(player_frame.x==200)
                        {
                            bullet_frame[i].x=200;
                            bullet_vet[i].posi=3;
                        }
                        else if(player_frame.x==250)
                        {
                            bullet_frame[i].x=250;
                            bullet_vet[i].posi=6;
                        }
                        else if(player_frame.x==300)
                        {
                            bullet_frame[i].x=300;
                            bullet_vet[i].posi=4;
                        }
                        else if(player_frame.x==350)
                        {
                            bullet_frame[i].x=350;
                            bullet_vet[i].posi=5;
                        }
                    }
                    //tiro
                    if(d && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=5;
                    }
                    else if(d && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                        {
                            i=0;
                        }
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=6;
                    }
                    else if(a && w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=7;
                    }
                    else if(a && s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=8;
                    }
                    else if(w)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=1;
                    }
                    else if(a)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=2;
                    }
                    else if(s)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=3;
                    }       
                    else if(d)
                    {
                        i++;
                        if(i == MAX_BULLETCOUNT)
                            i=0;
                        bullet_position[i].x = player_position.x;
                        bullet_position[i].y = player_position.y;
                        bullet_vet[i].tiro = 1;
                        bullet_vet[i].posi=4;
                    }
                }
            }
            if (event.type == SDL_KEYUP) // Se o usuário soltou um botão do teclado
            {
                // Verifica qual tecla foi solta
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(vely>2 && velx>2)
                        {
                            vely = 2;
                            velx = 2;
                        }
                    break;
                    case SDLK_DOWN:
                        vely = 2;
                        velx =2;
                    break;
                    default:
                    break;
                }
            }
        }
        if(Pause==1)
        {
            anda();
            //liberouGeral();
            Chora();
        }
        //Atualiza a tela de fundo
        SDL_BlitSurface(Background, NULL, Screen, NULL);
        sprintf(pontuacao, "                                                                 Pontos: %d", pont);
        escrever = TTF_RenderText_Solid(fonte, pontuacao, cor);
        SDL_BlitSurface(escrever, NULL, Screen, &dst_rect);
        if(Pause==0)
            SDL_BlitSurface(pausa, NULL, Screen, &pause_position);
        if(vidaC==0)
        {
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            SDL_BlitSurface(win, NULL, Screen, &lose_position);
            gameRunning=0;
            SDL_Delay(30);
        }
        if (vida<=0)
        {
            int j;
            for(cont=0; cont<MAX_ENEMY; cont++)
            {
                vidaE[cont]=0;   
            }
            for(j=0; j<MAX_BULLETCOUNT; j++)
            {
                bullet_vet[j].tiro = 0;
            }
            vidaC=0;
            SDL_BlitSurface(Background, NULL, Screen, NULL);
            SDL_BlitSurface(lose, NULL, Screen, &lose_position);
            gameRunning=0;
            SDL_Delay(30);
        }
        if(gameRunning==4 || vida!=0)
            SDL_BlitSurface(Player, &player_frame, Screen, &player_position);
        if(Pause==1)
        {
            liberouGeral();
        }
        if(vida>0)
            vidaP();
        if(gameRunning==4 || vida>0)
            atirador(bullet_vet, velobull, bullet3, bullet_frame, bullet_position, Background, Screen);
        //Atualiza a surface
        SDL_UpdateWindowSurface( window );
        //Delay de 2 segundos
        SDL_Delay(30);

    }
    SDL_Delay(5000);
    opcao=0;
    Menu(); 
}
void leRecorde()
{
    pe=fopen("rec.txt" , "r");
    for(e=0; e<5; e++)
    {
        fscanf(pe, "%d", &rec[e]);
        if(e==0)
        {
            sprintf(recordes1, "1:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes1, cor);
        }
        else if(e==1)
        {
            sprintf(recordes2, "2:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes2, cor);
        }
        else if(e==2)
        {
            sprintf(recordes3, "3:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes3, cor);
        }
        else if(e==3)
        {
            sprintf(recordes4, "4:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes4, cor);
        }
        else if(e==4)
        {
            sprintf(recordes5, "5:      %d", rec[e]);
            Recordes[e]= TTF_RenderText_Solid(fonte, recordes5, cor);
        }
    }
    fclose(pe);
}
void ImprimeRecerde()
{
    for(e=0; e<5; e++)
    {
        if(e==0)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec1);
        else if(e==1)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec2);
        else if(e==2)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec3);
        else if(e==3)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec4);
        else if(e==4)
            SDL_BlitSurface(Recordes[e], NULL, Screen, &rec5);
    }
}

void guardaRecorde()
{
    ps=fopen("rec.txt" , "w");
    for(e=0; e<5; e++)
    {
        if(pont>rec[e])
        {
            aux=rec[e];
            rec[e]=pont;
            pont=aux;
        }
    }
    for(e=0; e<5; e++)
    {
        fprintf(ps, "%d\n", rec[e]);
    }
    fclose(ps);

}