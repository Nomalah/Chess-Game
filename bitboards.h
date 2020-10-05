#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <string>

namespace nmlh::chess{
	typedef uint64_t bitboard;
	void print(bitboard board){
		for(int y = 7; y >= 0; y--){
			for(int x = 0; x < 8; x++){
				std::cout << ((1ULL << (x + 8 * y)) & board ? "\033[42m1\033[0m" : "0");
			}
			std::cout << "\n";
		}
	}

	enum square {
		a1=0x1,b1=0x2,c1=0x4,d1=0x8,e1=0x10,f1=0x20,g1=0x40,h1=0x80,a2=0x100,b2=0x200,c2=0x400,d2=0x800,e2=0x1000,f2=0x2000,g2=0x4000,h2=0x8000,a3=0x10000,b3=0x20000,c3=0x40000,d3=0x80000,e3=0x100000,f3=0x200000,g3=0x400000,h3=0x800000,a4=0x1000000,b4=0x2000000,c4=0x4000000,d4=0x8000000,e4=0x10000000,f4=0x20000000,g4=0x40000000,h4=0x80000000,a5=0x100000000,b5=0x200000000,c5=0x400000000,d5=0x800000000,e5=0x1000000000,f5=0x2000000000,g5=0x4000000000,h5=0x8000000000,a6=0x10000000000,b6=0x20000000000,c6=0x40000000000,d6=0x80000000000,e6=0x100000000000,f6=0x200000000000,g6=0x400000000000,h6=0x800000000000,a7=0x1000000000000,b7=0x2000000000000,c7=0x4000000000000,d7=0x8000000000000,e7=0x10000000000000,f7=0x20000000000000,g7=0x40000000000000,h7=0x80000000000000,a8=0x100000000000000,b8=0x200000000000000,c8=0x400000000000000,d8=0x800000000000000,e8=0x1000000000000000,f8=0x2000000000000000,g8=0x4000000000000000,h8=0x8000000000000000
	};

	enum piece {
		all = 0,
		pawn = 1,
		knight = 2,
		bishop = 3,
		rook = 4,
		queen = 5,
		king = 6
	};

	enum turn {
		white = 0,
		black = 1 
	};

	namespace constants{
		constexpr std::array<const char*, 64> square {
			"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
			"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
			"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
			"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
			"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
			"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
			"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
			"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8" 
		};
		constexpr std::array<bitboard, 7> white_bitboards {0x000000000000FFFF|square::d3, 0x000000000000FF00|square::d3, 0x0|square::b1|square::g1, 0x0|square::c1|square::f1, 0x0|square::a1|square::h1, 0x0|square::d1, 0x0|square::e1};
		constexpr std::array<bitboard, 7>  black_bitboards {0xFFFF000000000000|square::e3, 0x00FF000000000000|square::e3, 0x0|square::b8|square::g8, 0x0|square::c8|square::f8, 0x0|square::a8|square::h8, 0x0|square::d8, 0x0|square::e8};

		constexpr std::array<bitboard, 64> knight_move_bitboards {0x20400,0x50800,0xa1100,0x142200,0x284400,0x508800,0xa01000,0x402000,0x2040004,0x5080008,0xa110011,0x14220022,0x28440044,0x50880088,0xa0100010,0x40200020,0x204000402,0x508000805,0xa1100110a,0x1422002214,0x2844004428,0x5088008850,0xa0100010a0,0x4020002040,0x20400040200,0x50800080500,0xa1100110a00,0x142200221400,0x284400442800,0x508800885000,0xa0100010a000,0x402000204000,0x2040004020000,0x5080008050000,0xa1100110a0000,0x14220022140000,0x28440044280000,0x50880088500000,0xa0100010a00000,0x40200020400000,0x204000402000000,0x508000805000000,0xa1100110a000000,0x1422002214000000,0x2844004428000000,0x5088008850000000,0xa0100010a0000000,0x4020002040000000,0x400040200000000,0x800080500000000,0x1100110a00000000,0x2200221400000000,0x4400442800000000,0x8800885000000000,0x100010a000000000,0x2000204000000000,0x4020000000000,0x8050000000000,0x110a0000000000,0x22140000000000,0x44280000000000,0x88500000000000,0x10a00000000000,0x20400000000000};

		constexpr std::array<bitboard, 64> white_pawn_push_bitboards {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1010000,0x2020000,0x4040000,0x8080000,0x10100000,0x20200000,0x40400000,0x80800000,0x1000000,0x2000000,0x4000000,0x8000000,0x10000000,0x20000000,0x40000000,0x80000000,0x100000000,0x200000000,0x400000000,0x800000000,0x1000000000,0x2000000000,0x4000000000,0x8000000000,0x10000000000,0x20000000000,0x40000000000,0x80000000000,0x100000000000,0x200000000000,0x400000000000,0x800000000000,0x1000000000000,0x2000000000000,0x4000000000000,0x8000000000000,0x10000000000000,0x20000000000000,0x40000000000000,0x80000000000000,0x100000000000000,0x200000000000000,0x400000000000000,0x800000000000000,0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
		constexpr std::array<bitboard, 64> black_pawn_push_bitboards {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100,0x200,0x400,0x800,0x1000,0x2000,0x4000,0x8000,0x10000,0x20000,0x40000,0x80000,0x100000,0x200000,0x400000,0x800000,0x1000000,0x2000000,0x4000000,0x8000000,0x10000000,0x20000000,0x40000000,0x80000000,0x100000000,0x200000000,0x400000000,0x800000000,0x1000000000,0x2000000000,0x4000000000,0x8000000000,0x10100000000,0x20200000000,0x40400000000,0x80800000000,0x101000000000,0x202000000000,0x404000000000,0x808000000000,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
		constexpr std::array<bitboard, 64> white_pawn_capture_bitboards {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20000,0x50000,0xa0000,0x140000,0x280000,0x500000,0xa00000,0x400000,0x2000000,0x5000000,0xa000000,0x14000000,0x28000000,0x50000000,0xa0000000,0x40000000,0x200000000,0x500000000,0xa00000000,0x1400000000,0x2800000000,0x5000000000,0xa000000000,0x4000000000,0x20000000000,0x50000000000,0xa0000000000,0x140000000000,0x280000000000,0x500000000000,0xa00000000000,0x400000000000,0x2000000000000,0x5000000000000,0xa000000000000,0x14000000000000,0x28000000000000,0x50000000000000,0xa0000000000000,0x40000000000000,0x200000000000000,0x500000000000000,0xa00000000000000,0x1400000000000000,0x2800000000000000,0x5000000000000000,0xa000000000000000,0x4000000000000000,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
		constexpr std::array<bitboard, 64> black_pawn_capture_bitboards {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x5,0xa,0x14,0x28,0x50,0xa0,0x40,0x200,0x500,0xa00,0x1400,0x2800,0x5000,0xa000,0x4000,0x20000,0x50000,0xa0000,0x140000,0x280000,0x500000,0xa00000,0x400000,0x2000000,0x5000000,0xa000000,0x14000000,0x28000000,0x50000000,0xa0000000,0x40000000,0x200000000,0x500000000,0xa00000000,0x1400000000,0x2800000000,0x5000000000,0xa000000000,0x4000000000,0x20000000000,0x50000000000,0xa0000000000,0x140000000000,0x280000000000,0x500000000000,0xa00000000000,0x400000000000,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
		constexpr std::array<bitboard, 64> king_move_bitboards {0x302,0x705,0xe0a,0x1c14,0x3828,0x7050,0xe0a0,0xc040,0x30203,0x70507,0xe0a0e,0x1c141c,0x382838,0x705070,0xe0a0e0,0xc040c0,0x3020300,0x7050700,0xe0a0e00,0x1c141c00,0x38283800,0x70507000,0xe0a0e000,0xc040c000,0x302030000,0x705070000,0xe0a0e0000,0x1c141c0000,0x3828380000,0x7050700000,0xe0a0e00000,0xc040c00000,0x30203000000,0x70507000000,0xe0a0e000000,0x1c141c000000,0x382838000000,0x705070000000,0xe0a0e0000000,0xc040c0000000,0x3020300000000,0x7050700000000,0xe0a0e00000000,0x1c141c00000000,0x38283800000000,0x70507000000000,0xe0a0e000000000,0xc040c000000000,0x302030000000000,0x705070000000000,0xe0a0e0000000000,0x1c141c0000000000,0x3828380000000000,0x7050700000000000,0xe0a0e00000000000,0xc040c00000000000,0x203000000000000,0x507000000000000,0xa0e000000000000,0x141c000000000000,0x2838000000000000,0x5070000000000000,0xa0e0000000000000,0x40c0000000000000};
	}

	
}