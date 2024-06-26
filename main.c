#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>//��������� ��� ������� ����� � 2 �������

#define MAX_X 30
#define MAX_Y 15

int dir=2,game=1;//���������� ����� - dir - �����������, game - ���� ���������� ������
int level=0,delay=1000,pause=1;


typedef struct tail_t{
	int x;
	int y;
} tail_t;

typedef struct snake_t{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
}  snake_t;
// --> x
// || Y
// \/
// @**
//������ ���
tail_t*initFood(){
    tail_t*food=(tail_t*)malloc(sizeof(tail_t));
    food->x=rand()%MAX_X;
    food->y=rand()%MAX_Y;
    return food;
}

struct snake_t initSnake(int x, int y, size_t tsize){
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);//������� ������ ��� �����
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
	}
	return snake;
}

//�������� ������� ������ (1 ��������� ��� � 1 �������).
//��� ���������� ���� ��������� ��������� ���������
void printLevel(){
    printf("Level: %d",level);
}

// @**
void printSnake(struct snake_t snake,tail_t*food){
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i){
        for (int j = 0; j < MAX_Y; ++j)
        {
            matrix[i][j] = ' ';
        }
    }

    if(game){
        if(pause){
            matrix[snake.x][snake.y] = '@';
            for (int i = 0; i < snake.tsize; ++i){
                matrix[snake.tail[i].x][snake.tail[i].y] = '*';
            }
            matrix[food->x][food->y]='*';

        }else{
            matrix[14][8]='P';//������� �����
            matrix[15][8]='A';
            matrix[16][8]='U';
            matrix[17][8]='S';
            matrix[18][8]='E';
        }
    }else{
        matrix[11][8]='G';//������� ���� ����
        matrix[12][8]='A';
        matrix[13][8]='M';
        matrix[14][8]='E';
        matrix[15][8]=' ';
        matrix[16][8]='O';
        matrix[17][8]='V';
        matrix[18][8]='E';
        matrix[19][8]='R';
    }
    for (int j = 0; j < MAX_Y; ++j){
        for (int i = 0; i < MAX_X; ++i)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
    printLevel();
}

// <--  @** tsize = 2
//     @**

//  @**      @***
//    * <--     *
//  ***        **
snake_t ifEat(snake_t snake,tail_t*food){ //�������� ����������� �� �� � ����
    if((snake.x==food->x)&&(snake.y==food->y)){
        snake.tsize++;
        food->x=rand()%MAX_X;
        food->y=rand()%MAX_Y;
        level++;
        if(delay>0){
            delay-=100;
        }
    }
    return snake;
}

snake_t moveLeft(snake_t snake){//�����
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
    }
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;

	snake.x = snake.x - 1;
	if (snake.x < 0){
		snake.x = MAX_X - 1;
		}
	return snake;
}

snake_t moveRight(snake_t snake){//������
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
    }
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;

	snake.x = snake.x + 1;
	if (snake.x > (MAX_X-1)){
		snake.x = 0;
    }
	return snake;
}

snake_t moveUp(snake_t snake){//�����
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
    }
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;

	snake.y = snake.y - 1;
	if (snake.y < 0){
		snake.y = MAX_Y-1;
    }
	return snake;
}

snake_t moveDown(snake_t snake){//����
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
    }
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;

	snake.y = snake.y + 1;
	if (snake.y > (MAX_Y-1)){
		snake.y = 0;
    }
	return snake;
}

int checkDirection(snake_t* snake){//� �� ���� ��������� � ���� ������� �������� key, ���j����, �� ������ � ����������� �����-�� ����������, �� � �������� windows.h
    if((snake->tail[1].x == snake->x)&&(snake->tail[1].y == snake->y)){
        return 1;
    }
    return 0;
}

int checkCollision(snake_t* snake){//��� ������� �������� �� ������� ������ � ��������� ������ - ����� ������������� ��� checkDirection.����� �����������: � main **���������������, ***����������������
    for (int i = 0;i<snake->tsize;i++){
		if((snake->x==snake->tail[i].x)&&(snake->y==snake->tail[i].y)){
            return 0;
		}
    }
    return 1;
}

DWORD CALLBACK myFunc(LPVOID p){//�-�� ������
    int temp=0;
    while(game){
        switch(getch()){
            case'W':
            case'w':dir=1;break;//��������� ������� � ������� � ������ ��������
            case'S':
            case's':dir=2;break;
            case'D':
            case'd':dir=3;break;
            case'A':
            case'a':dir=4;break;
            case'Q':
            case'q':game=0;break;
            case'P':
            case'p':pause^=1;break;
        }
    }
}

int main(){
    HANDLE myThread=CreateThread(NULL,0,myFunc,0,0,NULL);//������ 2-��� ������
    srand(time(NULL));
	struct snake_t snake = initSnake( 10, 5, 2);
	tail_t*food=initFood();
	printSnake(snake,food);
	while(game)//for( int i = 0; i < 8; ++i)
	{
	    if(pause){
            snake=ifEat(snake,food);
            switch(dir){//�������� � ����������� �� �����������
                case 1:snake=moveUp(snake);break;//�������� ������ �-��
                case 2:snake=moveDown(snake);break;
                case 3:snake=moveRight(snake);break;
                case 4:snake = moveLeft(snake);break;
            }

            if(checkCollision(&snake)==0){//�������� �������� � ��������� ������ ***
                game=0;//���������� ����
            }
	    }
		Sleep(delay);
		system("cls");
		printSnake(snake,food);
	}
	free(snake.tail);

	return 0;
}
