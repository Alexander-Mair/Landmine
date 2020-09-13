#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <thread>
#include <chrono>
#include <exception>
#include <iterator>

class Game
{
	struct Position
	{
		int x = 0;
		int y = 0;
	};
	struct InvalidDirectionException : public std::exception {
		const char * what() const throw () {
			return "InvalidDirectionException";
		}
	};
public:


	static void PlayGame();
private:
	static void PlayerPosition(Position&);
	static void Move(std::string, Position&);
	static void FileReader(std::string);
	static void Detonate(std::string, Position&);
	
};

