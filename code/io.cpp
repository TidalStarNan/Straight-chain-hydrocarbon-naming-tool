#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>

void out(short position[100][4], short chain_length)
{
	srand(time(0));
	const char* replace_char[] = {"a", "b", "c", "d", "e", "f"};
	const char* random_chars[] = {"z", "y", "x", "w", "v", "u", "t", "s", "r", "q", "p", "o", "n", "m", "l", "k", "j", "i", "h", "g"};
	short random_chars_count = std::size(random_chars);
	std::string out_string = "=";
	int checksum = 0;

	if (chain_length < 10)
	{
		out_string += "0";
	}
	out_string += std::to_string(chain_length);
	checksum += chain_length;

	for (short x = 0; x < chain_length * 2 - 1; x++)
	{
		for (short y = 1; y <= 3; y++)
		{
			checksum += position[x][y];

			if (position[x][y] == 0)
			{
				out_string += random_chars[rand() % random_chars_count];
			}
			else if (position[x][y] >= 1 and position[x][y] <= 9)
			{
				out_string += std::to_string(position[x][y]);
			}
			else if (position[x][y] >= 10 and position[x][y] <= 15)
			{
				out_string += replace_char[position[x][y] - 10];
			}
			else
			{
				std::string error = "碳链值错误\n错误值：" + std::to_string(position[x][y]);
				throw std::out_of_range(error);
			}
		}
	}
	out_string += std::to_string((checksum + 8) % 100);
	out_string += "=";

	std::cout << "\n选择导出方式：\n1. 文本文件\n2. 控制台\n\n";
	short out_choice = _getch();
	switch (out_choice)
	{
	case '1':
	{
		std::ofstream out_file("output.txt", std::ios::app);
		if (out_file)
		{
			out_file << out_string << "\n\n";
			out_file.close();

			char fullpath[MAX_PATH];
			DWORD length = GetFullPathNameA("output.txt", MAX_PATH, fullpath, nullptr);
			if (length == 0)
			{
				std::cout << "无法获取文件位置，可能已经保存了。来自Windows的错误代码: " << GetLastError();
			}
			else
			{
				std::cout << "已保存到: " << fullpath;
			}
		}
		else
		{
			std::cout << "无法打开或创建输出文件，也许你需要管理员权限";
		}
		break;
	}
	case '2':
		std::cout << out_string;
		break;
	}

	std::cout << "\n\n按任意键继续……";
	(void)_getch();
}