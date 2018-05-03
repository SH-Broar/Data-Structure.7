#include <stdio.h>
#include <Windows.h>

void movexy(int x,int y)
{
	COORD s = { (x-1)*2,y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), s);
}

void drawUi()
{
	movexy(1, 1);
	printf("┌ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┐\n");
	for (int i = 0; i < 17; i++)
	{
		printf("├ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┤\n");
	}
	printf("└ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┴ ┘\n");
}

int main()
{
	
	int getX = -1, getY = -1;
	int p1 = 0,p2 = 0;
	int turnofwho = 0;
	int table[19][19] = { 0 };

	int nBlack = 0, nWhite = 0;
	int Maximum[2] = { 0 };
	int SavedMaximum[2] = { 0 };
	bool isSamestone[2] = { false };

	int startingMax[2] = { 0 };

	drawUi();

	while(1)
	{
		movexy(30, 25);
		printf("p1 : %d , p2 : %d", p1, p2);
		movexy(30, 20);

		scanf("%d %d", &getX, &getY);
		
		if (getX <= 0 || getX > 19 || getY <= 0 || getY > 19)
		{
			movexy(30, 24);
			printf("Don't be rude!");
			movexy(30, 20);
			printf("                   "); //지우기
			movexy(30, 20);
			rewind(stdin);
			getX = -1, getY = -1;
			continue;
		}
		
		if (table[getX - 1][getY - 1] == 0 && turnofwho == 0)
		{
			movexy(getX, getY);
			printf("★");
			movexy(30, 24);
			printf("                   "); //지우기
			movexy(30, 20);
			printf("                   "); //지우기
			movexy(30, 20);
			table[getX - 1][getY - 1] = 1;
			turnofwho = 1;//턴 변경
			p1++;
			getX = -1, getY = -1;
		}
		else if (table[getX - 1][getY - 1] == 0 && turnofwho == 1)
		{
			movexy(getX, getY);
			printf("☆");
			movexy(30, 24);
			printf("                   "); //지우기
			movexy(30, 20);
			printf("                   "); //지우기
			movexy(30, 20);
			table[getX - 1][getY - 1] = 2;
			turnofwho = 0;//턴 변경
			p2++;
			getX = -1, getY = -1;
		}
		else if (table[getX - 1][getY - 1] == 1 || table[getX - 1][getY - 1] == 2)
		{
			movexy(30, 20);
			printf("                    "); //지우기
			movexy(30, 24);
			printf("Don't pile!");
			movexy(1, 20);
			rewind(stdin);
			getX = -1, getY = -1;
		}
		/////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < 19; i++)
		{
			nBlack = 0;
			nWhite = 0;
			for (int j = 0; j < 19; j++)
			{
				if (table[j][i] == 1)
				{
					nBlack++;
				}
				else if (table[j][i] == 2)
				{
					nWhite++;
				}
				
			}
			movexy(20, i + 1);
			printf("b %d w %d", nBlack, nWhite);
			
		}
		for (int i = 0; i < 19; i++)
		{
			nBlack = 0;
			nWhite = 0;
			for (int j = 0; j < 19; j++)
			{
				if (table[i][j] == 1)
				{
					nBlack++;
				}
				else if (table[i][j] == 2)
				{
					nWhite++;
				}

			}
			movexy(i+1, 20);
			printf("b");
			movexy(i + 1, 21);
			printf("%d", nBlack);
			movexy(i + 1, 22);
			printf("w");
			movexy(i + 1, 23);
			printf("%d",nWhite);

		}
		/////////////////////////////////////////////////////////////////////

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (table[j][i] == 1)
				{
					movexy(j + 1, i + 1);
					printf("★");
				}
				else if (table[j][i] == 2)
				{
					movexy(j + 1, i + 1);
					printf("☆");
				}
			}
		}
		//가로
		Maximum[0] = 0;
		Maximum[1] = 0;

		for (int i = 0; i < 19; i++)
		{
			Maximum[0] = 0;
			Maximum[1] = 0;
			SavedMaximum[0] = 0;
			SavedMaximum[1] = 0;
			startingMax[0] = 0;
			startingMax[1] = 0;

			for (int j = 0; j < 19; j++)
			{
				if (table[j][i] == 1 && Maximum[0] == 0) //검은돌이고 처음나온친구
				{
					Maximum[0]++;

					if (SavedMaximum[0] < Maximum[0])
						SavedMaximum[0] = Maximum[0];

					isSamestone[0] = true;
					isSamestone[1] = false;
				}
				else if (table[j][i] == 2 && Maximum[1] == 0) //흰돌이고 처음나온친구
				{
					Maximum[1]++;

					if (SavedMaximum[1] < Maximum[1])
						SavedMaximum[1] = Maximum[1];

					isSamestone[0] = false;
					isSamestone[1] = true;
				}
				else if (table[j][i] == 1 && isSamestone[0] == true)
				{
					Maximum[0]++;
					if (SavedMaximum[0] < Maximum[0])
					{
						SavedMaximum[0] = Maximum[0];
						if (SavedMaximum[0] == 2)
							startingMax[0] = j;
					}
				}
				else if (table[j][i] == 2 && isSamestone[1] == true)
				{
					Maximum[1]++;
					if (SavedMaximum[1] < Maximum[1])
					{
						SavedMaximum[1] = Maximum[1];
						if (SavedMaximum[1] == 2)
							startingMax[1] = j;
					}
				}
				else
				{
					Maximum[0] = 0;
					Maximum[1] = 0;
					isSamestone[0] = false;
					isSamestone[1] = false;
				}
			}

			movexy(25, i + 1);
			if (SavedMaximum[0] > SavedMaximum[1])
			{
				printf("b %d", SavedMaximum[0]);
				if (startingMax[0] > 0)
				{
					movexy(startingMax[0], i+1);
					for (int k = 0; k < SavedMaximum[0]; k++)
					{
						printf("※");
					}
				}
				
			}
			else if (SavedMaximum[0] < SavedMaximum[1])
			{
				printf("w %d", SavedMaximum[1]);
				if (startingMax[1] > 0)
				{
					movexy(startingMax[1], i + 1);
					for (int k = 0; k < SavedMaximum[1]; k++)
					{
						printf("※");
					}
				}
			}
			else
			{
				printf("= %d", SavedMaximum[0]);
				if (startingMax[0] > 0 && startingMax[1] > 0)
				{
					movexy(startingMax[0], i + 1);
					for (int k = 0; k < SavedMaximum[0]; k++)
					{
						printf("※");
					}
					movexy(startingMax[1], i + 1);
					for (int k = 0; k < SavedMaximum[1]; k++)
					{
						printf("※");
					}
				}
			}
		}
		
		//////////////////////////////////////////////////////////////////////////////
		//세로
		Maximum[0] = 0;
		Maximum[1] = 0;

		for (int i = 0; i < 19; i++)
		{
			Maximum[0] = 0;
			Maximum[1] = 0;
			SavedMaximum[0] = 0;
			SavedMaximum[1] = 0;

			for (int j = 0; j < 19; j++)
			{
				if (table[i][j] == 1 && Maximum[0] == 0) //검은돌이고 처음나온친구
				{
					Maximum[0]++;

					if (SavedMaximum[0] < Maximum[0])
						SavedMaximum[0] = Maximum[0];

					isSamestone[0] = true;
					isSamestone[1] = false;
				}
				else if (table[i][j] == 2 && Maximum[1] == 0) //흰돌이고 처음나온친구
				{
					Maximum[1]++;

					if (SavedMaximum[1] < Maximum[1])
						SavedMaximum[1] = Maximum[1];

					isSamestone[0] = false;
					isSamestone[1] = true;
				}
				else if (table[i][j] == 1 && isSamestone[0] == true)
				{
					Maximum[0]++;
					if (SavedMaximum[0] < Maximum[0])
					{
						SavedMaximum[0] = Maximum[0];
					}
				}
				else if (table[i][j] == 2 && isSamestone[1] == true)
				{
					Maximum[1]++;
					if (SavedMaximum[1] < Maximum[1])
					{
						SavedMaximum[1] = Maximum[1];
					}
				}
				else
				{
					Maximum[0] = 0;
					Maximum[1] = 0;
					isSamestone[0] = false;
					isSamestone[1] = false;
				}
			}

			movexy(i+1, 25);
			if (SavedMaximum[0] > SavedMaximum[1])
			{
				printf("b");
				movexy(i + 1, 26);
				printf("%d", SavedMaximum[0]);
			}
			else if (SavedMaximum[0] < SavedMaximum[1])
			{
				printf("w");
				movexy(i + 1, 26);
				printf("%d", SavedMaximum[1]);
			}
			else
			{
				printf("=");
				movexy(i + 1, 26);
				printf("%d", SavedMaximum[0]);
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		//우하단 대각
		Maximum[0] = 0;
		Maximum[1] = 0;

		for (int i = -18; i < 19; i++)
		{
			Maximum[0] = 0;
			Maximum[1] = 0;
			SavedMaximum[0] = 0;
			SavedMaximum[1] = 0;

			for (int j = 0; j < 19; j++)
			{
				if (i + j < 0 || i + j >= 19)
					continue;
				if (table[j][i+j] == 1 && Maximum[0] == 0) //검은돌이고 처음나온친구
				{
					Maximum[0]++;

					if (SavedMaximum[0] < Maximum[0])
						SavedMaximum[0] = Maximum[0];

					isSamestone[0] = true;
					isSamestone[1] = false;
				}
				else if (table[j][i + j] == 2 && Maximum[1] == 0) //흰돌이고 처음나온친구
				{
					Maximum[1]++;

					if (SavedMaximum[1] < Maximum[1])
						SavedMaximum[1] = Maximum[1];

					isSamestone[0] = false;
					isSamestone[1] = true;
				}
				else if (table[j][i + j] == 1 && isSamestone[0] == true)
				{
					Maximum[0]++;
					if (SavedMaximum[0] < Maximum[0])
					{
						SavedMaximum[0] = Maximum[0];
					}
				}
				else if (table[j][i + j] == 2 && isSamestone[1] == true)
				{
					Maximum[1]++;
					if (SavedMaximum[1] < Maximum[1])
					{
						SavedMaximum[1] = Maximum[1];
					}
				}
				else
				{
					Maximum[0] = 0;
					Maximum[1] = 0;
					isSamestone[0] = false;
					isSamestone[1] = false;
				}
			}

			movexy(1, i + 46);
			if (SavedMaximum[0] > SavedMaximum[1])
			{
				printf("b %d", SavedMaximum[0]);
			}
			else if (SavedMaximum[0] < SavedMaximum[1])
			{
				printf("w %d", SavedMaximum[1]);
			}
			else
			{
				printf("= %d", SavedMaximum[0]);
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		//우상단 대각
		Maximum[0] = 0;
		Maximum[1] = 0;

		for (int i = 0; i < 37; i++)
		{
			Maximum[0] = 0;
			Maximum[1] = 0;
			SavedMaximum[0] = 0;
			SavedMaximum[1] = 0;

			for (int j = 0; j < 19; j++)
			{
				if (i - j < 0 || i - j >= 19)
					continue;
				if (table[j][i - j] == 1 && Maximum[0] == 0) //검은돌이고 처음나온친구
				{
					Maximum[0]++;

					if (SavedMaximum[0] < Maximum[0])
						SavedMaximum[0] = Maximum[0];

					isSamestone[0] = true;
					isSamestone[1] = false;
				}
				else if (table[j][i - j] == 2 && Maximum[1] == 0) //흰돌이고 처음나온친구
				{
					Maximum[1]++;

					if (SavedMaximum[1] < Maximum[1])
						SavedMaximum[1] = Maximum[1];

					isSamestone[0] = false;
					isSamestone[1] = true;
				}
				else if (table[j][i - j] == 1 && isSamestone[0] == true)
				{
					Maximum[0]++;
					if (SavedMaximum[0] < Maximum[0])
					{
						SavedMaximum[0] = Maximum[0];
					}
				}
				else if (table[j][i - j] == 2 && isSamestone[1] == true)
				{
					Maximum[1]++;
					if (SavedMaximum[1] < Maximum[1])
					{
						SavedMaximum[1] = Maximum[1];
					}
				}
				else
				{
					Maximum[0] = 0;
					Maximum[1] = 0;
					isSamestone[0] = false;
					isSamestone[1] = false;
				}
			}

			movexy(5, i + 28);
			if (SavedMaximum[0] > SavedMaximum[1])
			{
				printf("b %d", SavedMaximum[0]);
			}
			else if (SavedMaximum[0] < SavedMaximum[1])
			{
				printf("w %d", SavedMaximum[1]);
			}
			else
			{
				printf("= %d", SavedMaximum[0]);
			}
		}
	} 
	
}