#include <iostream>

void to_chinese_num(short num);
void to_heavenly_stems_num(short num);

void nomenclature(short position[100][4], short chain_length)
{
	bool from_left = true;
	short left = 0;
	short right = 0;

	bool has_double_bond = false;
	bool has_triple_bond = false;

	short double_bond_count = 0;
	short triple_bond_count = 0;

	short double_bond_positions[100]{};
	short triple_bond_positions[100]{};

	for (short x = 1; x < chain_length * 2 - 1; x += 2)
	{
		if (position[x][2] == 3)
		{
			has_double_bond = true;
			double_bond_positions[double_bond_count] = (x + 1) / 2;
			double_bond_count++;
		}
		else if (position[x][2] == 4)
		{
			has_triple_bond = true;
			triple_bond_positions[triple_bond_count] = (x + 1) / 2;
			triple_bond_count++;
		}
	}

	if (has_double_bond == true)
	{
		if (double_bond_positions[0] < chain_length - double_bond_positions[double_bond_count - 1])
		{
			from_left = true;
		}
		else if (double_bond_positions[0] > chain_length - double_bond_positions[double_bond_count - 1])
		{
			from_left = false;
		}
		else
		{
			for (short i = 0; i < double_bond_count; i++)
			{
				left += double_bond_positions[i];
				right += chain_length - double_bond_positions[i];
			}
			if (left < right)
			{
				from_left = true;
				left = 0;
				right = 0;
			}
			else if (left > right)
			{
				from_left = false;
				left = 0;
				right = 0;
			}
			else
			{
				if (has_triple_bond == true)
				{
					goto check_triple_bond;
				}
				else
				{
					from_left = true;
					left = 0;
					right = 0;
				}
			}
		}
	}
	else if (has_double_bond == false and has_triple_bond == true)
	{
		check_triple_bond:
		if (triple_bond_positions[0] < chain_length - triple_bond_positions[triple_bond_count - 1])
		{
			from_left = true;
		}
		else if (triple_bond_positions[0] > chain_length - triple_bond_positions[triple_bond_count - 1])
		{
			from_left = false;
		}
		else
		{
			for (short i = 0; i < triple_bond_count; i++)
			{
				left += triple_bond_positions[i];
				right += chain_length - triple_bond_positions[i];
			}
			if (left <= right)
			{
				from_left = true;
				left = 0;
				right = 0;
			}
			else
			{
				from_left = false;
				left = 0;
				right = 0;
			}
		}
	}
	else
	{
		for (short type = 6; type <= 15; type++)
		{
			bool has_group = false;
			short group_count = 0;
			short group_positions[100]{};

			for (short x = 0; x < chain_length * 2 - 1; x += 2)
			{
				for (short y = 1; y <= 3; y += 2)
				{
					if (position[x][y] == type)
					{
						has_group = true;
						group_positions[group_count] = x / 2 + 1;
						group_count++;
					}
				}
			}

			if (has_group = true)
			{
				if (group_positions[0] < chain_length - group_positions[group_count - 1] + 1)
				{
					from_left = true;
					goto name_part;
				}
				else if (group_positions[0] > chain_length - group_positions[group_count - 1] + 1)
				{
					from_left = false;
					goto name_part;
				}
			}
		}
	}

name_part:
	std::cout << "\n此有机化合物名称为：";

	bool out_ = false;

	for (short type = 6; type <= 15; type++)
	{
		bool name_has_group = false;
		short name_group_count = 0;
		short name_group_positions[100]{};

		for (short x = 0; x < chain_length * 2 - 1; x += 2)
		{
			for (short y = 1; y <= 3; y += 2)
			{
				if (position[x][y] == type)
				{
					name_has_group = true;
					name_group_positions[name_group_count] = x / 2 + 1;
					name_group_count++;
				}
			}
		}

		if (name_has_group == true)
		{
			if (out_ == false)
			{
				out_ = true;
			}
			else
			{
				std::cout << "-";
			}

			if (from_left == true)
			{
				for (short i = 0; i < name_group_count - 1; i++)
				{
					std::cout << name_group_positions[i] << ",";
				}
				std::cout << name_group_positions[name_group_count - 1] << "-";
			}
			else
			{
				for (short i = name_group_count - 1; i > 0; i--)
				{
					std::cout << chain_length - name_group_positions[i] + 1 << ",";
				}
				std::cout <<chain_length - name_group_positions[0] + 1 << "-";
			}

			to_heavenly_stems_num (type - 5);
			std::cout << "基";
		}
	}

	to_heavenly_stems_num(chain_length);

	if (has_double_bond == false and has_triple_bond == false)
	{
		std::cout << "烷";
	}
	if (has_double_bond == true)
	{
		if (chain_length > 3)
		{
			std::cout << "-";
			if (from_left == true)
			{
				for (short i = 0; i < double_bond_count - 1; i++)
				{
					std::cout << double_bond_positions[i] << ",";
				}
				std::cout << double_bond_positions[double_bond_count - 1] << "-";
			}
			else
			{
				for (short i = double_bond_count - 1; i > 0; i--)
				{
					std::cout << chain_length - double_bond_positions[i] << "-";
				}
				std::cout << chain_length - double_bond_positions[0] << "-";
			}
		}
		
		std::cout << "烯";
	}
	if (has_triple_bond == true)
	{
		if (chain_length > 3)
		{
			std::cout << "-";
			if (from_left == true)
			{
				for (short i = 0; i < triple_bond_count - 1; i++)
				{
					std::cout << triple_bond_positions[i] << ",";
				}
				std::cout << triple_bond_positions[triple_bond_count - 1] << "-";
			}
			else
			{
				for (short i = triple_bond_count - 1; i > 0; i--)
				{
					std::cout << chain_length - triple_bond_positions[i] << ",";
				}
				std::cout << chain_length - triple_bond_positions[0] << "-";
			}
		}

		std::cout << "炔";
	}
}