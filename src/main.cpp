#include <iostream>
#include <Windows.h>
#include <conio.h>

void render(short pos[100][4], short len, short poi[1][2]);
void nomenclature(short pos[100][4], short len);
static void notice()
{
	Sleep(500);
	while (_kbhit()) { (void)_getch(); }
}


int main()
{
	short position[100][4]{};
	position[0][2] = 1;
	for (short x = 0; x < 100; x++)
	{
		position[x][0] = x;
	}

	short pointer[1][2]{};
	short chain_length = 1;
	bool esc = false;

	try
	{
		while (esc == false)
		{
			render(position, chain_length, pointer);

			int key = _getch();
			switch (key)
			{
			case 27:
				esc = true;
				break;

			case 'm':
			case 'M':
				nomenclature(position, chain_length);

				std::cout << "\n\n按任意键继续……";
				key = _getch();
				break;

			case 'w':
			case 'W':
				if (pointer[0][1] > -1 and pointer[0][0] % 2 == 0)
				{
					pointer[0][1]--;
				}
				break;

			case 's':
			case 'S':
				if (pointer[0][1] < 1 and pointer[0][0] % 2 == 0)
				{
					pointer[0][1]++;
				}
				break;

			case 'a':
			case 'A':
				if (pointer[0][0] > 0)
				{
					if (pointer[0][1] == 0)
					{
						pointer[0][0]--;
					}
					else if (pointer[0][1] == -1 or pointer[0][1] == 1)
					{
						pointer[0][0] = pointer[0][0] - 2;
					}
				}
				break;

			case 'd':
			case 'D':
				if (pointer[0][0] < chain_length * 2 - 2)
				{
					if (pointer[0][1] == 0)
					{
						pointer[0][0]++;
					}
					else if (pointer[0][1] == -1 or pointer[0][1] == 1)
					{
						pointer[0][0] = pointer[0][0] + 2;
					}
				}
				break;

			case 'z':
			case 'Z':
				if (chain_length < 50)
				{
					position[chain_length * 2 - 1][2] = 2;
					position[chain_length * 2][2] = 1;
					chain_length++;
				}
				else
				{
					std::cout << "碳链长度已达上限50，无法继续延长\n";
					notice();
				}
				break;

			case 'x':
			case 'X':
				if (chain_length > 1)
				{
					if (position[chain_length * 2 - 2][1] == 0 and position[chain_length * 2 - 2][3] == 0)
					{
						for (short i = chain_length * 2 - 4; i >= 0; i -= 2)
						{
							if (position[i][1] - 5 < chain_length - (i / 2 + 1) and position[i][3] - 5 < chain_length - (i / 2 + 1))
							{
								//可以缩短碳链
							}
							else
							{
								std::cout << "无法缩短碳链，从取代基计算的链长不可长于主链长\n";
								std::cout << "位置：第" << i / 2 + 1 << "个碳\n";
								notice();
								goto x_end;
							}
						}

						position[chain_length * 2 - 2][2] = 0;
						position[chain_length * 2 - 3][2] = 0;
						chain_length--;

						if (pointer[0][0] > chain_length * 2 - 2)
						{
							pointer[0][0] = chain_length * 2 - 2;
						}
					}
					else
					{
						std::cout << "无法缩短碳链，从取代基计算的链长不可长于主链长2\n";
						notice();
					}
				}
				else
				{
					std::cout << "碳链长度已达下限1，无法继续缩短\n";
					notice();
				}
				x_end:break;

			case 'c':
			case 'C':
				if (pointer[0][0] % 2 == 1 and pointer[0][1] == 0)
				{
					position[pointer[0][0]][2] = 2;
				}
				else
				{
					std::cout << "单键需位于两个碳之间\n";
					notice();
				}
				break;

			case 'v':
			case 'V':
				if (pointer[0][1] == 0)
				{
					if (pointer[0][0] % 2 == 1 and position[pointer[0][0] - 2][2] == 2 and position[pointer[0][0] + 2][2] == 2)
					{
						if ((position[pointer[0][0] - 1][1] != 0 and position[pointer[0][0] - 1][3] != 0) or (position[pointer[0][0] + 1][1] != 0 and position[pointer[0][0] + 1][3] != 0))
						{
							std::cout << "双键任意侧的碳原子上不能有两个取代基\n";
							notice();
						}
						else
						{
							position[pointer[0][0]][2] = 3;
						}
					}
					else if (pointer[0][0] == 1 and position[3][2] == 0)
					{
						position[1][2] = 3;
					}
					else if (pointer[0][0] == 1 and position[3][2] == 2)
					{
						if (position[2][1] != 0 and position[2][3] != 0)
						{
							std::cout << "双键右侧的碳原子上不能有两个取代基\n";
							notice();
						}
						else
						{
							position[1][2] = 3;
						}
					}
					else if (pointer[0][0] == chain_length * 2 - 3 and position[chain_length * 2 - 5][2] == 2)
					{
						if (position[chain_length * 2 - 4][1] != 0 and position[chain_length * 2 - 4][3] != 0)
						{
							std::cout << "双键左侧的碳原子上不能有两个取代基\n";
							notice();
						}
						else
						{
							position[chain_length * 2 - 3][2] = 3;
						}
					}
					else
					{
						std::cout << "双键需位于两个单键碳之间\n";
						notice();
					}
				}
				else
				{
					std::cout << "双键需位于两个单键碳之间\n";
					notice();
				}
				break;

			case 'b':
			case 'B':
				if (pointer[0][1] == 0)
				{
					if (pointer[0][0] % 2 == 1 and position[pointer[0][0] - 2][2] == 2 and position[pointer[0][0] + 2][2] == 2)
					{
						if (position[pointer[0][0] - 1][1] != 0 or position[pointer[0][0] - 1][3] != 0 or position[pointer[0][0] + 1][1] != 0 or position[pointer[0][0] + 1][3] != 0)
						{
							std::cout << "三键任意侧的碳原子上不能有取代基\n";
							notice();
						}
						else
						{
							position[pointer[0][0]][2] = 4;
						}
					}
					else if (pointer[0][0] == 1 and position[3][2] == 0)
					{
						position[1][2] = 4;
					}
					else if (pointer[0][0] == 1 and position[3][2] == 2)
					{
						if (position[2][1] != 0 or position[2][3] != 0)
						{
							std::cout << "三键右侧的碳原子上不能有取代基\n";
							notice();
						}
						else
						{
							position[1][2] = 4;
						}
					}
					else if (pointer[0][0] == chain_length * 2 - 3 and position[chain_length * 2 - 5][2] == 2)
					{
						if (position[chain_length * 2 - 4][1] != 0 or position[chain_length * 2 - 4][3] != 0)
						{
							std::cout << "三键左侧的碳原子上不能有取代基\n";
							notice();
						}
						else
						{
							position[chain_length * 2 - 3][2] = 4;
						}
					}
					else
					{
						std::cout << "三键需位于两个单键碳之间\n";
						notice();
					}
				}
				else
				{
					std::cout << "三键需位于两个单键碳之间\n";
					notice();
				}
				break;

			case 'e':
			case 'E':
				if (pointer[0][1] == 1 or pointer[0][1] == -1)
				{
					if (pointer[0][0] % 2 == 0)
					{
						position[pointer[0][0]][pointer[0][1] + 2] = 0;
					}
				}
				else
				{
					std::cout << "你只能删除取代基 QAQ\n";
					notice();
				}
				break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if ((pointer[0][1] == 1 or pointer[0][1] == -1) and pointer[0][0] % 2 == 0)
				{
					if (position[pointer[0][0] - 1][2] == 4 or position[pointer[0][0] + 1][2] == 4)
					{
						std::cout << "取代基不能位于三键碳上\n";
						notice();
					}
					else if (position[pointer[0][0] - 1][2] == 3 or position[pointer[0][0] + 1][2] == 3)
					{
						if (pointer[0][1] == -1)
						{
							if (position[pointer[0][0]][3] != 0)
							{
								std::cout << "双键碳上不能存在两个取代基\n";
								notice();
							}
							else
							{
								goto next_check;
							}
						}
						else if (pointer[0][1] == 1)
						{
							if (position[pointer[0][0]][1] != 0)
							{
								std::cout << "双键碳上不能存在两个取代基\n";
								notice();
							}
							else
							{
								goto next_check;
							}
						}
					}
					else
					{
						next_check:if (key - 48 <= (chain_length - 1) / 2)
						{
							if (pointer[0][0] / 2 + 1 > key - 48 and chain_length - (pointer[0][0] / 2) > key - 48)
							{
								position[pointer[0][0]][pointer[0][1] + 2] = key - 43;
							}
							else
							{
								std::cout << "从取代基计算的链长不可长于主链长";
								notice();
							}
						}
						else
						{
							std::cout << "主链太短而取代基太长\n";
							notice();
						}
					}
				}
				else
				{
					std::cout << "取代基需位于主链碳上\n";
					notice();
				}
				break;

			case '0':
				throw std::runtime_error("手动触发错误退出程序");
			}
		}
	}
	catch (const std::exception& error)
	{
		std::cout << "发生错误，程序即将退出\n错误信息：" << error.what() << "\n";
		std::cout << "\n按任意键继续……";
		(void)_getch();
		std::exit(EXIT_FAILURE);
	}
}