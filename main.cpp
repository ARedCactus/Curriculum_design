#include"game.h"

int main()
{
	System system;
	system.Init();
	while (1)
	{
//		BeginBatchDraw();

		system.bulidGrid();
		system.Demo();
		if (_getch())
		{
			break;
		}
//		FlushBatchDraw();
	}
	return 0;
}
