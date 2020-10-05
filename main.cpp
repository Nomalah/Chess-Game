#include <iostream>
#include "chess_board.hpp"

int main() {
	nmlh::chess::board main_board;
	std::cout << main_board.ascii() << std::endl;
	for(const auto& move : main_board.moves()){
		std::cout << "from " << nmlh::chess::constants::square[move.from] << " to: " << nmlh::chess::constants::square[move.to] << " flags " << (int)move.flags << std::endl;
	}
	
}