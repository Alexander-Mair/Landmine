#include "stdafx.h"
#include "Game.h"
int triggers;
enum class Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};
std::vector<std::vector<bool>> easy = {
	{false, false, false},
	{ false, true, false },
	{ true, false, true },
	{false,false, true},
	{true, false, false},
	{false, false, false}
};
std::vector<std::vector<bool>> hard = {
	{ false, true, true },
	{ true, true, false},
	{ true, false, true },
	{false, false, false},
	{true, true, true},
	{false, false, false}
};

std::vector<std::vector<bool>>minefield;
void Game::PlayGame()
{
	Position p;
	std::string direction;

	FileReader("welcome");


	std::this_thread::sleep_for(std::chrono::seconds(2));

	FileReader("intro and rules");
	std::string level;
	while (level != "easy" && level != "hard")
	{


		std::cout << "Would you like to play the easy level or the hard level?" << std::endl;
		std::cout << "Level: " + level << std::endl;
		std::getline(std::cin, level);
		std::cout << "Level: " + level << std::endl;

		if (level == "easy")
		{
			std::cout << "You've chosen the easy option" << std::endl;
			minefield = easy;
			triggers = 5;
		}
		else if (level == "hard")
		{
			std::cout << "You've chosen the hard option" << std::endl;
			minefield = hard;
			triggers = 3;
		}
		else {
			std::cout << level + " is not a valid option" << std::endl;
		}
	}
	try
	{
		while (true)
		{
			PlayerPosition(p);
			//FileReader("which_way");
			std::cout << "What's your next move" << std::endl;
			getline(std::cin, direction);

			std::istringstream iss(direction);
			std::vector<std::string> command(std::istream_iterator<std::string>{iss},
				std::istream_iterator<std::string>());

			if (command[0] == "detonate" || command[0] == "det")
			{
				if (triggers == 0)
				{
					std::cout << "Sorry you're out of detonators" << std::endl;
				}
				else
				{
					try {
						Detonate(command[1], p);
					}
					catch (InvalidDirectionException ide)
					{
						std::cout << direction + " is not a valid option" << std::endl;
					}
					;
				}
			}
			else
			{


				try {
					Move(direction, p);
				}
				catch (InvalidDirectionException ide)
				{
					std::cout << direction + " is not a valid option" << std::endl;
				}
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << "Game Over" << std::endl;
	}
}

void Game::PlayerPosition(Position &p)
{
	if (p.x == minefield.size() - 1)
	{
		FileReader("win");
		throw std::exception();
	}
	else if (minefield[p.x][p.y])
	{
		std::cout << "you stepped on a mine! BANG!" << std::endl;
		throw std::exception();

	}
	else
	{
		std::cout << "Not dead yet!" << std::endl;
	}

}
void Game::Move(std::string input, Position &p)
{
	Direction direction;

	if (input == "north" || input == "n")
	{
		direction = Direction::NORTH;
	}
	else if (input == "south" || input == "s")
	{
		direction = Direction::SOUTH;
	}
	else if (input == "east" || input == "e")
	{
		direction = Direction::EAST;
	}
	else if (input == "west" || input == "w")
	{
		direction = Direction::WEST;
	}

	else
	{
		throw InvalidDirectionException();

	}

	switch (direction)
	{
	case Direction::NORTH:
		p.x++;
		break;
	case Direction::SOUTH:
		if (p.x - 1 < 0) {
			std::cout << "You can't go back. Go forward." << std::endl;
		}


		else
		{
			p.x--;
		}
		break;
	case Direction::EAST:
		if (p.y + 1 == minefield[p.x].size()) {
			p.y = 0;
		}


		else
		{
			p.y++;
		}
		break;
	case Direction::WEST:
		if (p.y - 1 < 0) {
			p.y = 0;
		}

		else
		{
			p.y--;
		}
		break;
	default:

		break;
	}

}

void Game::Detonate(std::string input, Position &p)
{
	Direction direction;
	if (input == "north" || input == "n")
	{
		direction = Direction::NORTH;
	}
	else if (input == "south" || input == "s")
	{
		direction = Direction::SOUTH;
	}
	else if (input == "east" || input == "e")
	{
		direction = Direction::EAST;
	}
	else if (input == "west" || input == "w")
	{
		direction = Direction::WEST;
	}

	else
	{
		throw InvalidDirectionException();
	}
	switch (direction)
	{
	case Direction::NORTH:
		if (p.x + 1 == minefield.size()) {
			std::cout << "You can't detonate at the edge of the minefield" << std::endl;
		}


		else if (minefield[p.x + 1][p.y])
		{
			minefield[p.x + 1][p.y] = false;
			std::cout << "Well done! You exploded a landmine!" << std::endl;
			triggers--;
		}
		else
		{
			triggers--;
			std::cout << "Oops! You've just wasted one of your detonators. You have " + std::to_string(triggers) + " left." << std::endl;

		}
		break;
	case Direction::SOUTH:
		if (p.x - 1 < 0) {
			std::cout << "You can't detonate at the edge of the minefield" << std::endl;
		}
		else if (minefield[p.x - 1][p.y])
		{
			minefield[p.x - 1][p.y] = false;
			std::cout << "Well done! You exploded a landmine!" << std::endl;
			triggers--;
		}
		else
		{
			triggers--;
			std::cout << "Oops! You've just wasted one of your detonators. You have " + std::to_string(triggers) + " left." << std::endl;

		}


		break;
	case Direction::EAST:
		if (p.y + 1 == minefield[p.x].size()) {
			std::cout << "You can't detonate at the edge of the minefield" << std::endl;
		}


		else if (minefield[p.x][p.y + 1])
		{
			minefield[p.x][p.y + 1] = false;
			std::cout << "Well done! You exploded a landmine!" << std::endl;
			triggers--;
		}
		else
		{
			triggers--;
			std::cout << "Oops! You've just wasted one of your detonators. You have " + std::to_string(triggers) + " left." << std::endl;

		}
		break;
	case Direction::WEST:
		if (p.y - 1 < 0) {
			std::cout << "You can't detonate at the edge of the minefield" << std::endl;
		}
		else if (minefield[p.x][p.y - 1])
		{
			minefield[p.x][p.y - 1] = false;
			std::cout << "Well done! You exploded a landmine!" << std::endl;
			triggers--;
		}
		else
		{
			triggers--;
			std::cout << "Oops! You've just wasted one of your detonators. You have " + std::to_string(triggers) + " left." << std::endl;

		}
		break;
	default:

		break;
	}

}
void Game::FileReader(std::string filename)
{
	std::string filepath = "../text/" + filename + ".txt";
	std::ifstream file(filepath);
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
}