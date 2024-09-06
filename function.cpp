#include"game.h"

int Arr[3][WIDTH / 20][HEIGHT / 20];

System::System()
{
	for (int k = 0; k < MapNum; ++k)
	{
		for (int i = 1; i < WIDTH / 20 - 1; ++i)
		{
			for (int j = 1; j < HEIGHT / 20 - 1; ++j)
			{
				Arr[k][i][j] = 0;
			}
		}
		for (int i = 0; i < WIDTH / 20; ++i)
		{
			Arr[k][i][0] = 1;
			Arr[k][i][WIDTH / 20 - 1] = 1;
		}
		for (int i = 0; i < HEIGHT / 20; ++i)
		{
			Arr[k][0][i] = 1;
			Arr[k][HEIGHT / 20 - 1][i] = 1;
		}
	}
	
	initgraph(P_WIDTH, HEIGHT, 0);
}


void System::outtext(int k)
{
	TCHAR s[10] = { 0 };
	_stprintf_s(s, _T("%d"), k);
	outtextxy(10 * WIDTH / 20, 10, s);
}

void System::Init()
{
	srand((unsigned int)time(NULL));
	for (int i = 1; i < WIDTH / 20 - 1; ++i)
	{
		for (int j = 1; j < HEIGHT / 20 - 1; ++j)
		{
			Arr[0][i][j] = rand() % 8 + 1;
		}
	}
}
void System::bulidGrid()
{
	for (int i = 1; i < WIDTH / 20 - 1; ++i)
	{
		for (int j = 1; j < HEIGHT / 20 - 1; ++j)
		{
			TCHAR s1[10] = { 0 };
			_stprintf_s(s1, _T("%d"), Arr[0][i][j]);
			outtextxy(i *20+7 , j * 20+7 , s1);
//			fillrectangle(i * WIDTH / 20 + 1, j * HEIGHT / 20 + 1, i * WIDTH / 20 + 19,j * HEIGHT / 20 + 19);
		}
	}
}

void Queue::Push(Node node)
{
	data[rear].x = node.x;
	data[rear].y = node.y;

	if (rear == 0)  data[rear].pre = NULL;

	else data[rear].pre = &data[front];

	++rear;
}

inline int Queue::GetFront()
{
	return front;
}

inline int Queue::GetRear()
{
	return rear;
}

void Queue::ReSetPre()
{
	Node* s = &data[rear - 1];
	Node* p = s->pre;
	Node* r = NULL;

	while (1)
	{
		r = p->pre;
		p->pre = s;
		s = p;
		p = r;

		if (r == NULL) break;
	}
}
void Queue::PrintRoute()
{
	Node* s = data[0].pre;

	while (s != &data[rear - 1])
	{
		setfillstyle(BLUE);
		fillcircle(s->x * 20 + 10, s->y * 20 + 10, 6);
		Sleep(100);
		s = s->pre;
	}
}

void System::Demo()
{
	Queue qu;
	Node node;
	int zx[4] = { 1,0,-1,0 };
	int zy[4] = { 0,1,0,-1 };
	int find = 0;
	int x[4] = { 0 }, y[4] = { 0 };
	int X = 0, Y = 0;
	int k = 0;

	node.x = 5;
	node.y = 5;
	qu.Push(node);
	while (qu.GetFront() < qu.GetRear())
	{
		Arr[0][node.x][node.y] = 0;

		node.x = qu.visit(qu.GetFront()).x;
		node.y = qu.visit(qu.GetFront()).y;

		for (int i = 0; i < 4; ++i)
		{
			x[i] = node.x + zx[i];
			y[i] = node.y + zy[i];
			if (k <= Arr[0][x[i]][y[i]])
			{
				X = x[i], Y = y[i];
				k = Arr[0][x[i]][y[i]];
			}
			x[i] = 0;
			y[i] = 0;
		}
		node.x = X;
		node.y = Y;
		qu.Push(node);
		Arr[0][node.x][node.y] = 0;

		qu.Pop();
		++find;

		if (find == 1)
		{
			qu.ReSetPre();
			qu.PrintRoute();
			break;
		}
	}
}

Queue::Queue()
{
	data = new Node[MaxLength];
	front = 0;
	rear = 0;
}

Queue::~Queue()
{
	delete(data);
}

void Queue::Pop()
{
	++front;
}

Node Queue::visit(int i)
{
	return data[i];
}