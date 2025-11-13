#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
void to_chinese(short number);
void to_num(short number);

int main()
{
	short pointer = 0;
	short chain_length = 1;
	short position[100][2]{};
    position[0][1] = 2;

    bool esc = false;
    bool has_double_bond = false;
    bool has_triple_bond = false;
	short left = 0;
	short right = 0;
	short bond_count = 0;
    short bond_position[50][1]{};

    for (short i = 0; i < 100; i++)
    {
		std::cout << position[i][0] << "," << position[i][1] << std::endl;
    }

    while (esc == false)
    {
        system("cls");
        std::cout << "=====欢迎使用直链烃命名器=====\n";
        std::cout << "by TidalStarNan\n\n";
        std::cout << "A：左移        D：右移\nESC：退出程序  M：开始命名\n\n";
        std::cout << "Z：延长碳链    X：缩短碳链\nC：单键        V：双键      B：三键\n\n";
		std::cout << "当前碳链长度：" << chain_length << "\n\n";

        for (short i = 0; i < chain_length * 2 - 1; i++)
        {
            if (position[i][1] == 2)
            {
                std::cout << "\033[47m口\033[0m";
            }
            else if (position[i][1] == -1)
            {
                std::cout << "一";
            }
            else if (position[i][1] == -2)
            {
                std::cout << "二";
            }
            else if (position[i][1] == -3)
            {
                std::cout << "三";
            }
			else if (position[i][1] == 0)
            {
                std::cout << "　";
            }
            else
            {
                std::cout << "碳链值错误，请重新启动程序";
            }
        }
        std::cout << std::endl;
        for (short i = 0; i < pointer; i++)
        {
            std::cout << "　";
        }
        std::cout << "▲";
        std::cout << pointer;
		std::cout << std::endl << std::endl;
        
        int key = _getch();
        switch (key)
        {
        case 'a':
        case 'A':
            if (pointer > 0)
            {
				pointer--;
            }
            break;
        case 'd':
		case 'D':
            if (pointer < chain_length * 2 - 2 )
            {
                pointer++;
            }
            break;

        case 'z':
		case 'Z':
            if (chain_length < 50)
            {
                position[chain_length * 2 - 1][1] = -1;
                position[chain_length * 2][1] = 2;
				chain_length++;
            }
            else
            {
				std::cout << "碳链长度已达上限50，无法继续延长\n";
                Sleep(500);
            }
            break;
        case 'x':
		case 'X':
            if (chain_length > 1)
            {
                position[chain_length * 2 - 2][1] = 0;
                position[chain_length * 2 - 3][1] = 0;
                chain_length--;
            }
            else
            {
				std::cout << "碳链长度已达下限1，无法继续缩短\n";
                Sleep(500);
            }
            if (pointer > chain_length * 2 - 2)
            {
                pointer = chain_length * 2 - 2;
            }
            break;
        case 'c':
		case 'C':
            if (pointer % 2 == 1)
            {
                position[pointer][1] = -1;
            }
            break;
        case 'v':
		case 'V':
            if (pointer % 2 == 1 and position[pointer - 2][1] == -1 and position[pointer + 2][1] == -1)
            {
                position[pointer][1] = -2;
            }
            else if (pointer == 1 and position[3][1] == -1)
            {
                position[1][1] = -2;
            }
            else if (pointer == chain_length * 2 - 3 and position[chain_length * 2 - 5][1] == -1)
            {
                position[chain_length * 2 - 3][1] = -2;
            }
            else if (pointer == 1 and position[3][1] == 0)
            {
                position[1][1] = -2;
            }
            else
            {
				std::cout << "双键需位于两个单键之间，无法设置\n";
                Sleep(500);
            }
            break;
		case 'b':
        case 'B':
            if (pointer % 2 == 1 and position[pointer - 2][1] == -1 and position[pointer + 2][1] == -1)
            {
                position[pointer][1] = -3;
            }
            else if (pointer == 1 and position[3][1] == -1)
            {
                position[1][1] = -3;
            }
            else if (pointer == chain_length * 2 - 3 and position[chain_length * 2 - 5][1] == -1)
            {
                position[chain_length * 2 - 3][1] = -3;
            }
            else if (pointer == 1 and position[3][1] == 0)
            {
                position[1][1] = -3;
            }
            else
            {
				std::cout << "三键需位于两个单键之间，无法设置\n";
				Sleep(500);
            }
            break;
        case 'm':
        case 'M':
			has_double_bond = false;
			has_triple_bond = false;
            left = 0;
            right = 0;
			bond_count = 0;
            for (short i = 0; i < 50; i++)
            {
				bond_position[i][0] = 0;
            }

			std::cout << "此有机化合物名称为：";

            for (short i = 0; i < chain_length * 2 - 1; i++)
            {
                if (position[i][1] == -2)
                {
					has_double_bond = true;
                }
                if (position[i][1] == -3)
                {
					has_triple_bond = true;
                }
            }

            if (has_double_bond == false and has_triple_bond == false)
            {
				to_chinese(chain_length);
				std::cout << "烷\n";
            }
			else if (has_double_bond == true and has_triple_bond == false)
            {
                if (chain_length < 4)
                {
					to_chinese(chain_length);
                    std::cout << "烯\n";
                }
                else
                {
                    for (float i = 0; i < chain_length * 2 - 1; i++)
                    {
                        if (position[short(i)][1] == -2)
                        {
                            bond_position[bond_count][0] = short(i / 2) + 1;
                            bond_count++;
                        }
                    }
                    
                    if (bond_position[0][0] < chain_length - bond_position[bond_count - 1][0])
                    {
                        L2:for (short i = 0; i < bond_count - 1; i++)
                        {
							std::cout << bond_position[i][0] << ",";
                        }
						std::cout << bond_position[bond_count - 1][0] << "-";
						to_chinese(chain_length);
                        if (bond_count > 1)
                        {
                            to_num(bond_count);
                        }
                        std::cout << "烯\n";
                    }
                    else if (bond_position[0][0] > chain_length - bond_position[bond_count - 1][0])
                    {
                        R2:for (short i = bond_count - 1; i > 0; i--)
                        {
                            std::cout << chain_length - bond_position[i][0] << ",";
                        }
                        std::cout << chain_length - bond_position[0][0] << "-";
                        to_chinese(chain_length);
                        if (bond_count > 1)
                        {
                            to_num(bond_count);
                        }
                        std::cout << "烯\n";
                    }
                    else
                    {
                        for (short i = 0; i < bond_count; i++)
                        {
                            left = left + bond_position[i][0];
                            right = right + (chain_length - bond_position[i][0]);
                        }

                        if (left <= right)
                        {
                            goto L2;
                        }
                        else
                        {
                            goto R2;
                        }
                    }

                }
            }
            else if (has_double_bond == false and has_triple_bond == true)
            {
                if (chain_length < 4)
                {
                    to_chinese(chain_length);
                    std::cout << "炔\n";
                }
                else
                {
                    for (float i = 0; i < chain_length * 2 - 1; i++)
                    {
                        if (position[short(i)][1] == -3)
                        {
                            bond_position[bond_count][0] = short(i / 2) + 1;
                            bond_count++;
                        }
                    }

                    if (bond_position[0][0] < chain_length - bond_position[bond_count - 1][0])
                    {
                        L3:for (short i = 0; i < bond_count - 1; i++)
                        {
                            std::cout << bond_position[i][0] << ",";
                        }
                        std::cout << bond_position[bond_count - 1][0] << "-";
                        to_chinese(chain_length);
                        if (bond_count > 1)
                        {
                            to_num(bond_count);
                        }
                        std::cout << "炔\n";
                    }
                    else if (bond_position[0][0] > chain_length - bond_position[bond_count - 1][0])
                    {
                        R3:for (short i = bond_count - 1; i > 0; i--)
                        {
                            std::cout << chain_length - bond_position[i][0] << ",";
                        }
                        std::cout << chain_length - bond_position[0][0] << "-";
                        to_chinese(chain_length);
                        if (bond_count > 1)
                        {
                            to_num(bond_count);
                        }
                        std::cout << "炔\n";
                    }
                    else
                    {
                        for (short i = 0; i < bond_count; i++)
                        {
                            left = left + bond_position[i][0];
                            right = right + (chain_length - bond_position[i][0]);
                        }

                        if (left <= right)
                        {
                            goto L3;
                        }
                        else
                        {
                            goto R3;
                        }
                    }
                }
            }
            else
            {
                for (float i = 0; i < chain_length * 2 - 1; i++)
                {
                    if (position[short(i)][1] == -2)
                    {
                        bond_position[bond_count][0] = short(i / 2) + 1;
                        bond_count++;
                    }
                }

                if (bond_position[0][0] < chain_length - bond_position[bond_count - 1][0])
                {
                L23:for (short i = 0; i < bond_count - 1; i++)
                {
                    std::cout << bond_position[i][0] << ",";
                }
                std::cout << bond_position[bond_count - 1][0] << "-";
                to_chinese(chain_length);
                if (bond_count > 1)
                {
                    to_num(bond_count);
                }
                std::cout << "烯";

                std::cout << "-";
                left = 0;
                right = 0;
                bond_count = 0;
                for (short i = 0; i < 50; i++)
                {
                    bond_position[i][0] = 0;
                }

                for (float i = 0; i < chain_length * 2 - 1; i++)
                {
                    if (position[short(i)][1] == -3)
                    {
                        bond_position[bond_count][0] = short(i / 2) + 1;
                        bond_count++;
                    }
                }

                for (short i = 0; i < bond_count - 1; i++)
                {
                    std::cout << bond_position[i][0] << ",";
                }
                std::cout << bond_position[bond_count - 1][0] << "-";
                if (bond_count > 1)
                {
                    to_num(bond_count);
                }
                std::cout << "炔\n";

                }
                else if (bond_position[0][0] > chain_length - bond_position[bond_count - 1][0])
                {
                R23:for (short i = bond_count - 1; i > 0; i--)
                {
                    std::cout << chain_length - bond_position[i][0] << ",";
                }
                std::cout << chain_length - bond_position[0][0] << "-";
                to_chinese(chain_length);
                if (bond_count > 1)
                {
                    to_num(bond_count);
                }
                std::cout << "烯";

                std::cout << "-";
                left = 0;
                right = 0;
                bond_count = 0;
                for (short i = 0; i < 50; i++)
                {
                    bond_position[i][0] = 0;
                }

                for (float i = 0; i < chain_length * 2 - 1; i++)
                {
                    if (position[short(i)][1] == -3)
                    {
                        bond_position[bond_count][0] = short(i / 2) + 1;
                        bond_count++;
                    }
                }

                for (short i = bond_count - 1; i > 0; i--)
                {
                    std::cout << chain_length - bond_position[i][0] << ",";
                }
                std::cout << chain_length - bond_position[0][0] << "-";
                if (bond_count > 1)
                {
                    to_num(bond_count);
                }
                std::cout << "炔\n";
                }
                else
                {
                    for (short i = 0; i < bond_count; i++)
                    {
                        left = left + bond_position[i][0];
                        right = right + (chain_length - bond_position[i][0]);
                    }

                    if (left <= right)
                    {
                        goto L23;
                    }
                    else
                    {
                        goto R23;
                    }
                }
            }

			std::cout << "\n按任意键继续……";
			key = _getch();
			break;
        case 27:
            esc = true;
			break;
		default:
            break;
        }
    }

}