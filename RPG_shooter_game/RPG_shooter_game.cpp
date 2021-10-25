#include <iostream>
#include <conio.h>
#include <string>
#include <list>
#include <Windows.h>
#include <vector>

const std::string main_menu[] = {
	"     * Play *",
	"* Quit the game *",
};

const std::string in_village[] = {
	"  * Fight *",
	" * Go shop *",
	"* Inventory *",
	"  * Exitt *"
};

const std::string in_inventory[] = {
	"         * Back *",
	"    * Change Weapon *",
};

const std::string ask_YesNo[] = {
	"      * Yes *",
	"      * Noo *"
};

int selected_button;
int max_buttons, min_buttons;
std::string YesNo;
std::string where_I;

std::string prev_where_I;
int prev_max_buttons;

bool gameActive;

HANDLE wndHandle = GetStdHandle(STD_OUTPUT_HANDLE);

struct Character
{
	int hp = 100;
	int armor = 0;
	int money = 0;
	int ammo = 10;
	std::string equiped_weapon = "Pistol";
	int equiped_weapon_damage = 10;
	int equiped_weapon_range = 10;
};

Character player;

std::vector<std::string> nameWeapon;
std::vector<int> damageWeapon, rangeWeapon;

void addWeapon(std::string name, int damage, int range)
{
	nameWeapon.push_back(name);
	damageWeapon.push_back(damage);
	rangeWeapon.push_back(range);
}

void initialize()
{
	selected_button = 0;
	max_buttons = 1;
	min_buttons = 0;
	where_I = "menu";
	gameActive = true;
}

void inventory()
{
	std::cout << "------Player statistic------\n";
	std::cout << "Health:   " << player.hp << "\n";
	std::cout << "Armor:    " << player.armor << "\n";
	std::cout << "Cash:     " << player.money << "\n";
	std::cout << "Ammo:     " << player.ammo << "\n";
	std::cout << "Equipped weapon: " << player.equiped_weapon << "\n";
	std::cout << "Damage: " << player.equiped_weapon_damage << " Range: " << player.equiped_weapon_range << "\n\n";
	std::cout << "----------Inventory---------\n";	
	if (nameWeapon.size() != 0)
	{
		std::cout << "\tDamage\tRange\n";
		for (int i = 0; i < nameWeapon.size(); i++)
		{
			std::cout << nameWeapon[i] << "\t " << damageWeapon[i] << "\t  " << rangeWeapon[i] << "\n";
		}
	}
	else
	{
		std::cout << "You don't have any weapon\n";
	}
	
	std::cout << "----------------------------\n";
}

void Shop()
{
	std::cout << "---Welcome to shop---\n\n";
	std::cout << "Выберете раздел магазина:\n";
	std::cout << "  [1]Броня и патроны\n";
	std::cout << "  [2]Оружие\n";

	std::cout << "Вы находитесь в разделе броня и патроны\n";
	std::cout << "---Вы находитесь в разделе оружие---\n";

	std::cout << "Не известная команда. Напиши номер раздела или 'exit' чтоб выйти из магазина.\n";
}

void input_In_menu()
{
	switch (_getch())
	{
	case 72:
		if (selected_button > min_buttons)
		{
			selected_button--;
		}
		break;
	case 80:
		if (selected_button < max_buttons)
		{
			selected_button++;
		}
		break;
	case 32:
		if (where_I == "menu")
		{
			if (selected_button == 0)  // play
			{
				where_I = "village";
				max_buttons = 3;
				prev_max_buttons = max_buttons;
			}
			else if (selected_button == 1)  //exit
			{
				where_I = "exit";
				max_buttons = 1;
			}
			prev_where_I = "menu";
		}
		else if (where_I == "village")
		{
			if (selected_button == 0)
			{

			}
			else if (selected_button == 1)
			{

			}
			else if (selected_button == 2)
			{
				where_I = "inventory";
				max_buttons = 1;
			}
			else if (selected_button == 3)
			{
				where_I = "exit";
				max_buttons = 1;
			}
			prev_where_I = "village";
		}
		else if (where_I == "inventory")
		{
			if (selected_button == 0)
			{
				where_I = prev_where_I;
				max_buttons = prev_max_buttons;
			}
			else if (selected_button == 1)
			{
				where_I = "inventory_weapon";
				prev_where_I = "inventory";
				prev_max_buttons = 3;
			}			
		}
		else if (where_I == "inventory_weapon")
		{
			if (selected_button == 0)
			{
				where_I = prev_where_I;
				prev_where_I = "village";
				max_buttons = 1;
			}
			else
			{
				for (int i = 0; i < nameWeapon.size(); i++)
				{
					if (selected_button == i + 1)
					{
						nameWeapon.push_back(player.equiped_weapon);
						damageWeapon.push_back(player.equiped_weapon_damage);
						rangeWeapon.push_back(player.equiped_weapon_range);

						player.equiped_weapon = nameWeapon[i];
						player.equiped_weapon_damage = damageWeapon[i];
						player.equiped_weapon_range = rangeWeapon[i];

						nameWeapon.erase(nameWeapon.cbegin() + i);
						damageWeapon.erase(damageWeapon.cbegin() + i);
						rangeWeapon.erase(rangeWeapon.cbegin() + i);
					}
				}
			}
		}
		else if (where_I == "exit")
		{
			if (selected_button == 0)
			{
				gameActive = false;
			}
			else if (selected_button == 1)
			{
				where_I = prev_where_I;
				max_buttons = prev_max_buttons;
			}
		}	
		selected_button = 0;
		break;
	default:
		break;
	}
}

void render_menu()
{
	system("cls");

	std::string tempLine;

	if (where_I == "inventory")
	{
		inventory();
	}
	else if (where_I == "inventory_weapon")
	{
		max_buttons = nameWeapon.size();
		std::cout << "-------Change Weapon-------\n";
		std::cout << "Selected weapon: " << player.equiped_weapon << "\n";
		std::cout << "Damage: " << player.equiped_weapon_damage << " | Range: " << player.equiped_weapon_range << "\n";
		if (selected_button == 0)
		{
			std::cout << "          > Back <\n\n";
		}
		else
		{
			std::cout << "            Back\n\n";
		}
		if (nameWeapon.size() != 0)
		{
			std::cout << "\tDamage\tRange\n";
			for (int i = 0; i < max_buttons; i++)
			{
				if (selected_button == i + 1)
				{
					std::cout << ">";
				}
				else
				{
					std::cout << " ";
				}
				std::cout << nameWeapon[i] << "\t " << damageWeapon[i] << "\t  " << rangeWeapon[i] << "\n";
			}
		}
		else
		{
			std::cout << "You don't have any weapon\n";
		}
		std::cout << "---------------------------\n";
		return;
	}
	else if (where_I == "exit")
	{
		std::cout << "Are you sure about that?\n";
	}

	for (int i = 0; i < max_buttons + 1; i++)
	{
		if (where_I == "menu")
		{
			tempLine = main_menu[i];
		}
		else if (where_I == "village")
		{
			tempLine = in_village[i];
		}
		else if (where_I == "inventory")
		{
			tempLine = in_inventory[i];
		}
		else if (where_I == "exit")
		{
			tempLine = ask_YesNo[i];
		}

		if (selected_button == i)
		{
			int nextSymbol = 0;
			for (int j = 0; j < tempLine.size(); j++)
			{
				if (tempLine[j] == '*' && !nextSymbol)
				{
					tempLine[j] = '>';
					nextSymbol++;
				}
				if (tempLine[j] == '*' && nextSymbol)
				{
					tempLine[j] = '<';
				}
			}
		}
		else
		{
			for (int j = 0; j < tempLine.size(); j++)
			{
				if (tempLine[j] == '*')
				{
					tempLine[j] = ' ';
				}
			}
		}
		std::cout << tempLine << "\n";
	}
}

int main()
{
	addWeapon("AWM", 100, 100);
	addWeapon("AK47", 30, 15);
	addWeapon("Deagle", 50, 18);
	addWeapon("MP5", 30, 20);
	addWeapon("FAL", 40, 24);
	addWeapon("HK416", 30, 25);

	initialize();

	while (gameActive)
	{
		render_menu();
		input_In_menu();
	}
}