#pragma once

#include "bitboards.h"
#include <cstring>
#include <vector>
#include <cstdint>

namespace nmlh::bit::tools{
#if defined(_MSC_VER)
	
#elif defined(__GNUC__) || defined(__clang__)
#define ctz64(x) __builtin_ctzll(x)
#else

#endif
}



namespace nmlh::chess{
	struct move{
		uint8_t from;
		uint8_t to;
		uint8_t flags;
		bool castle(){
			return flags & 128;
		}
		bool enpassant(){
			return flags & 64;
		}

		piece res_piece(){
			return piece(flags & 7);
		}
	};

	class board{
		public:
			bool operator==(const board& other){			
				return this->bitboards[turn::white] == other.bitboards[turn::white] &&
					this->bitboards[turn::black] == other.bitboards[turn::black];
			}

			std::string ascii(){
				std::string res = " +--------+\n";
				for(int y = 7; y >= 0; y--){
					res += (char)(y + 49);
					res += "|";
					for(int x = 0; x < 8; x++){
						if(bitboards[turn::white][piece::pawn] & (1ULL << (x + 8 * y))){
							res += "P";
						} else if(bitboards[turn::white][piece::knight] & (1ULL << (x + 8 * y))){
							res += "N";
						} else if(bitboards[turn::white][piece::rook] & (1ULL << (x + 8 * y))){
							res += "R";
						} else if(bitboards[turn::white][piece::queen] & (1ULL << (x + 8 * y))){
							res += "Q";
						} else if(bitboards[turn::white][piece::bishop] & (1ULL << (x + 8 * y))){
							res += "B";
						} else if(bitboards[turn::white][piece::king] & (1ULL << (x + 8 * y))){
							res += "K";
						} else if(bitboards[turn::black][piece::pawn] & (1ULL << (x + 8 * y))){
							res += "p";
						} else if(bitboards[turn::black][piece::knight] & (1ULL << (x + 8 * y))){
							res += "n";
						} else if(bitboards[turn::black][piece::rook] & (1ULL << (x + 8 * y))){
							res += "r";
						} else if(bitboards[turn::black][piece::queen] & (1ULL << (x + 8 * y))){
							res += "q";
						} else if(bitboards[turn::black][piece::bishop] & (1ULL << (x + 8 * y))){
							res += "b";
						} else if(bitboards[turn::black][piece::king] & (1ULL << (x + 8 * y))){
							res += "k";
						} else {
							res += "*";
						}
					}
					res += "|\n";
				}
				res += " +--------+\n  ABCDEFGH";
				return res;
			}

			std::vector<move> moves(){
				std::vector<move> legal_moves;
				
				//std::cout << (long long)pawn_turn(256) << "\n";
				// Knight Moves
				{
					bitboard remaining_knights = bitboards[game_turn][piece::knight];
					while(remaining_knights){
						uint8_t square_from = ctz64(remaining_knights);

						bitboard attacked_squares = constants::knight_move_bitboards[square_from] & ~bitboards[game_turn][piece::all];
						while(attacked_squares){
							uint8_t square_to = ctz64(attacked_squares);
							
							legal_moves.push_back({square_from, square_to, 0x2});
							attacked_squares ^= (1ULL << square_to);
						}
						remaining_knights ^= (1ULL << square_from);
					}
				}

				// Pawn Moves
				{
					auto pawn_turn = game_turn == turn::white ? [](bitboard a){return (a & 0xFF0000) << 8;} : [](bitboard a){return (a & 0xFF0000000000) >> 8;};
					bitboard remaining_pawns = bitboards[game_turn][piece::pawn];
					while(remaining_pawns){
						uint8_t square_from = ctz64(remaining_pawns);

						bitboard valid_squares = (constants::white_pawn_capture_bitboards[square_from] & bitboards[!game_turn][piece::all]) | (constants::white_pawn_push_bitboards[square_from] & ~(bitboards[!game_turn][piece::all] | bitboards[game_turn][piece::all]) & ~pawn_turn((bitboards[!game_turn][piece::all] | bitboards[game_turn][piece::all]) ^ (1ULL << square_from)));
						
						while(valid_squares){
							uint8_t square_to = ctz64(valid_squares);
							if(square_to > 55){
								legal_moves.push_back({square_from, square_to, 0x2});
								legal_moves.push_back({square_from, square_to, 0x3});
								legal_moves.push_back({square_from, square_to, 0x4});
								legal_moves.push_back({square_from, square_to, 0x5});
							}else{
								legal_moves.push_back({square_from, square_to, 0x1});
							}
							
							valid_squares ^= (1ULL << square_to);
						}
						remaining_pawns ^= (1ULL << square_from);
					}

					// King Moves
					{
						uint8_t square_from = ctz64(bitboards[game_turn][piece::king]);

						bitboard valid_squares = constants::king_move_bitboards[square_from] &  ~bitboards[game_turn][piece::all];
						
						while(valid_squares){
							uint8_t square_to = ctz64(valid_squares);
							legal_moves.push_back({square_from, square_to, 0x6 });
							
							valid_squares ^= (1ULL << square_to);
						}
					}
				}
				return legal_moves;
			}
			
		private:
			std::array<std::array<bitboard, 7>, 2> bitboards = {constants::white_bitboards, constants::black_bitboards};

			turn game_turn = turn::white;

			
	};
}