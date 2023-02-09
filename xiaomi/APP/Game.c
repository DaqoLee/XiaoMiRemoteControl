#include "Game.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
Snake_t SnakeHand;
Food_t Food;
int FoodBuf[][2]=
{
  25,17,
  25,14,
  25,11,
  25,8,
  25,5,
  25,2,

  23,2,
  23,5,
  23,8,
  23,11,
  23,14,

  21,14,
  21,11,
  21,8,
  21,5,
  19,5,
  17,5,
  14,5,
  7,4,
  7,6,
  9,6,
  11,6,
  14,6,
  14,8,
  14,12,
  13,13,
  11,14,
  9,15,
  7,15,
  7,11,
  3,11,
  4,10,
  5,9,
  6,8,
  7,7
  
};

unsigned char GameMap[40][20]={0};

void GAME_SnakeTest(void)
{
//  static int j=0,N=3;
//   HAL_Delay(10);
//   if(j<101)
//   {
//  //  GAME_SnakeMoveTest(GameMap,&SnakeHand,N);  
//   } 
//   else
//   {
//    
//     Paint_DrawString_CN(21, 120,"关注＋三连" , &Font12CN,BLACK , WHITE);
//   }
//   j++;
//   if(j==6)
//    N=2;
//   else if(j==21)
//    N=1;
//   else if(j==23)
//    N=4;
//   else if(j==35)
//    N=1;
//   else if(j==37)
//    N=2;
//   else if(j==46)
//    N=1;
//   else if(j==53)
//    N=2;
//   else if(j==54)
//    N=1;
//   else if(j==61)
//    N=4;
//   else if(j==63)
//    N=3;
//   else if(j==70)
//    N=4;
//   else if(j==76)
//    N=1;
//   else if(j==77)
//    N=4;
//   else if(j==78)
//    N=1;
//   else if(j==80)
//    N=4;  
//   else if(j==81)
//    N=1; 
//   else if(j==83)
//    N=4;
//   else if(j==84)
//    N=1;
//   else if(j==86)
//    N=2;
//   else if(j==90)
//    N=1;
//   else if(j==94)
//    N=2;
//   else if(j==95)
//    N=3;
//   else if(j==96)
//    N=2;
//   else if(j==97)
//    N=3;
//   else if(j==98)
//    N=2;
//   else if(j==99)
//    N=3;
//   else if(j==100)
//    N=2;
//   else if(j==101)
//    N=3;
}
 

void GAME_SnakeFillInGameMap(unsigned char (*gamemap)[20],Snake_t *snake)
{
  Snake_t *p=snake; 
  while(p->next!=NULL)
  {
    gamemap[p->x][p->y]=1;
    p=p->next;
  }
}

void GAME_SnakePixel(int x,int y,UWORD col)
{
  for(int i=0;i<6;i++)
  {
    for(int j=0;j<6;j++)
    {
      Paint_DrawPoint(6*y+j, 6*x+i, col, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    }
  }
}



void GAME_NewFood(unsigned char (*gamemap)[20],Food_t *food)
{
  while(1)
  {    
//    food->x = random(24); 
//    food->y = random(18); 
    if(gamemap[food->x][food->y]==0&&food->x>6&&food->y>6)
    {
      gamemap[food->x][food->y]=2;
      GAME_SnakePixel(food->x,food->y,BLACK);
      break;
    }
  }
}

void GAME_SnakeAddNode(Snake_t *snake,int x,int y)
{
  Snake_t *node,*p;
  p=snake;
  
  node=(Snake_t *)malloc(sizeof(Snake_t));
  
  if(node==NULL)
  {
     
  }
  node->x=x;
  node->y=y;
  node->next=NULL;

  p->prev=node;
  
  while(p->next!=NULL)
  {
    p =p->next;
  }
  node->prev=p;
  p->next=node;
  GAME_SnakeFillInGameMap(GameMap ,snake);
}

void GAME_NewSnake(Snake_t *snake)
{
  int x=5,y=5;
  
  snake->x=x;
  snake->y=y;
  snake->prev=NULL;
  snake->next=NULL;
  
  for(int i=0;i<5;i++)
  {
    GAME_SnakeAddNode(snake,x+i,y);
  }
  GAME_NewFood(GameMap,&Food);
  
  GAME_SnakeFillInGameMap(GameMap ,snake);
}




void GAME_SnakeRun(unsigned char (*gamemap)[20],Snake_t *snake)
{
  Snake_t *h=snake,*n=snake->prev;
 // Paint_DrawPoint(n->y,n->x, WHITE, DOT_PIXEL_4X4, DOT_STYLE_DFT);
  GAME_SnakePixel(n->x,n->y,WHITE);
  GAME_SnakePixel(h->x,h->y,BLACK);
  gamemap[n->x][n->y]=0;
}

unsigned char GAME_SnakeMove(unsigned char (*gamemap)[20],Snake_t *snake,int dir) 
{
  Snake_t *p,*h;
  unsigned char val;
//  static int temp=1;
  
  h=snake;
  p=snake->prev;
  while(p!=snake)
  {
    p->x=p->prev->x;
    p->y=p->prev->y;
    p=p->prev;
  }
  switch(dir)
  {
    case 1:
      h->x--;     
    break;
    case 2:
      h->y--;
    break;
    case 3:
      h->x++;
    break;
    case 4:
      h->y++;
    break;
    default:
      h->y++;
      break;
  
  }
  
  val=gamemap[h->x][h->y];

  switch(val)
  {
    case 0:       
      break;
    case 1:

         return 0;
//      break;
    case 2:
        GAME_SnakeAddNode(snake,h->x,h->y);
        GAME_NewFood(gamemap,&Food);   
      break;
    default:
      break;
  }
  GAME_SnakeRun(gamemap,snake);
  GAME_SnakeFillInGameMap(gamemap,snake);
  return 1;
}



void GAME_SnakeFreeNode(Snake_t *snake)
{
  Snake_t *p,*q;
  p=snake->next;

  while(p)
  {
    q=p->next;
    free(p);
    p=q;  
  }
  snake->next=NULL;
}

void GAME_SnakeInit(Snake_t *snake,unsigned char (*gamemap)[20])
{
  Snake_t *p;
  for(int i=0;i<40;i++)
  {
    for(int j=0;j<20;j++)
    {
      GameMap[i][j]=0;
    }  
  }
  GAME_NewSnake(snake);
  p=snake;
  
  while(p->next!=NULL)
  {
    GAME_SnakePixel(p->x,p->y,BLACK);
    p=p->next;
  }  
  for(int i=0;i<=27;i++)
  {
    for(int j=0;j<=19;j++)
    {
      if(i==0||i==27||j==0||j==19)
      {       
        GAME_SnakePixel(i,j,BLACK); 
        gamemap[i][j]=1;   
      //  Paint_DrawPoint(j, i, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);   
      }
    }
  
  } 
}

int GAME_Over(int n)
{
  static int num=0;
  num++;
  if(num==1)
  {
     Paint_ClearWindows(15, 80, 15 + Font12CN.Width*6, 100 + Font12CN.Height, WHITE);
     Paint_DrawString_CN(15, 80,"投币再来" , &Font12CN,WHITE , BLACK);
     Paint_DrawString_CN(80, 82,"▲" , &Font12CN,BLACK , WHITE);
     Paint_DrawString_CN(15, 100,"下次一定" , &Font12CN,BLACK , WHITE);

     return 15;
  }
  else if(num==2)
  {

    HAL_Delay(1000);
     Paint_ClearWindows(15, 80, 15 + Font12CN.Width*6, 100 + Font12CN.Height, WHITE);
     Paint_DrawString_CN(15, 80,"投币再来" , &Font12CN,BLACK , WHITE);
     Paint_DrawString_CN(80, 102,"▲" , &Font12CN,BLACK , WHITE);
     Paint_DrawString_CN(15, 100,"下次一定" , &Font12CN,WHITE , BLACK);
     return 15;
  }
  else if(num==3)
  {
     HAL_Delay(1000);
     Paint_ClearWindows(15, 80, 15 + Font12CN.Width*6, 100 + Font12CN.Height, WHITE);
     Paint_DrawString_CN(20, 80,"投币成功！" , &Font12CN,BLACK , WHITE);

     return 15; 
  }
  else if(num==4)
  {
     HAL_Delay(1000);
     return 4; 
  }
   return 0; 
}


