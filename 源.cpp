#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
int arr[20][20];//储存棋盘信息1为白2为黑
char score[2];//储存对局信息1为黑2为白
void playchess();
void drawscore()
{
	outtextxy(505, 175, L"玩家1:玩家2");
	outtextxy(505, 190, score[0]);
	outtextxy(515, 190, score[1]);
}
void drawmap()
{
	initgraph(600, 500);
	loadimage(NULL, L"1.jpg");
	int i;
	setlinecolor(BLACK);
	for (i = 0; i < 19; i++) {
		line(0, 25 + 25 * i, 500, 25 + 25 * i);
		line(25 + 25 * i, 0, 25 + 25 * i, 500);
	}
	setlinestyle(PS_SOLID, 2);//将线条设置为实线,2个像素宽度
	line(500, 0, 500, 500);
	line(0, 500, 500, 500);
	outtextxy(505, 20, L"黑棋:玩家1");//指定位置输出文字
	outtextxy(505, 50, L"白旗:玩家2");
}
void again()
{
	outtextxy(505, 300, L"是否再来一局");
	outtextxy(505, 320, L"再来一局");
	MOUSEMSG n;
	int location=0;//判断是否点中
	while (location == 0) {
		n = GetMouseMsg();
		if (n.uMsg == WM_LBUTTONDOWN) {
			if (n.x>505&&n.x<565&&n.y>320&&n.y<340) {
				playchess();
			}
			else {
				continue;
			}
		}
	}
}
int result(int i,int j,int chess)
{
	int same = 1;
	for (int m = i - 1; m>0; m--) {
		if (arr[m][j] == arr[i][j])same = same + 1;
		else break;
	}
	for (int m = i + 1; m<20; m++) {
		if (arr[m][j] == arr[i][j])same = same + 1;
		else break;
	}
	if (same<4)same = 1; //竖向排查 

	for (int m = j - 1; m>0; m -= 1) {
		if (arr[i][m] == arr[i][j])same = same + 1;
		else break;
	}
	for (int m = j + 1; m<20; m += 1) {
		if (arr[i][m] == arr[i][j])same = same + 1;
		else break;
	}
	if (same<4)same = 1;  //横向排查

	for (int m = 1; m<20; m++) {
		if (i - m == 0 || j -  m == 0)break;
		else if (arr[i - m][j -  m] == arr[i][j])same = same + 1;
		else break;
	}
	for (int m = 1; m<20; m++) {
		if (i + m == 20|| j +  m == 20)break;
		else if (arr[i + m][j +  m] == arr[i][j])same = same + 1;
		else break;
	}
	if (same<4)same = 1;  //左上右下排查

	for (int m = 1; m<20; m++) {
		if (i + m == 20 || j -  m == 0)break;
		else if (arr[i + m][j -  m] == arr[i][j])same = same + 1;
		else break;
	}
	for (int m = 1; m<20; m++) {
		if (i - m == 0 || j +  m == 20)break;
		if (arr[i - m][j + m] == arr[i][j]) same = same + 1;
		else  break; 
	}//左下右上排查
	if (same >= 4 && chess == 1) {
		outtextxy(505, 250, L"玩家1胜利");//指定位置输出结果
		score[0] += 1;
		return 1;
	}
	else if (same >= 4 && chess == 2) {
		outtextxy(505, 250, L"玩家2胜利");
		score[1] += 1;
		return 1;
	}
	else {
		return 0;
	}
}


void playchess()
{
	system("cls");
	drawmap();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			arr[i][j] = 0;
		}
	}
	MOUSEMSG m;
	int chess,end;
	chess = 2;
	end = 0;
	outtextxy(505, 100, L"现在黑棋落子");
	drawscore();
	while (end==0)
	{
		m = GetMouseMsg();//获取鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			int i, j, xx, yy;
			xx = 0;
			yy = 0;
			for (i = 0; i < 20; i++) {//下棋过程中能正常落子
				if (abs(m.x - i * 25) < 12) {
					xx = i;
				}
			}
			for (j = 0; j < 20; j++) {
				if (abs(m.y - j * 25)< 12) {
					yy = j;
				}
			}
			if (xx == 0 || yy == 0)continue;
			if (arr[xx][yy] == 0) {//更改棋盘信息
				arr[xx][yy] = chess % 2 + 1;
				end=result(xx,yy,chess%2+1);//检查结果
				if (arr[xx][yy] == 1) {
					setfillcolor(BLACK);
					solidcircle(xx * 25, yy * 25, 10);
					outtextxy(505, 100, L"现在白棋落子");

				}
				else if (arr[xx][yy] == 2) {
					setfillcolor(WHITE);
					solidcircle(xx * 25, yy * 25, 10);
					outtextxy(505, 100, L"现在黑棋落子");
				}
				chess = chess + 1;
			}
			continue;
		}
	}
	again();
}


int main()
{
	score[0] = '0';
	score[1] = '0';
	playchess();
	_getch();
	 return 0;
}
