/*
 * bit.hpp
 *
 *  Created on: 2017/03/21
 *      Author: Keita
 */

#ifndef UTIL_BIT_HPP_
#define UTIL_BIT_HPP_

#include <stdint.h>

namespace Util {
	//bit処理をする。
	static inline constexpr auto Bit(auto _s) {
		return 1 << _s;
	}

	static inline constexpr bool Mand(auto _target, auto _cmp) {
		return (_target & _cmp) == _cmp;
	}

	//指定されたビット数で表現できる最大値
	constexpr auto BitMax(uint32_t _bit){
		return (1 << (_bit - 1)) - 1;
	}

	//指定されたビット数で表現できる最小値
	constexpr auto BitMin(uint32_t _bit){
		return -(1 << (_bit - 1));
	}


	//立っているビットを数える
	constexpr uint32_t BitCount(uint32_t _bits) {
		_bits = (_bits & 0x55555555) + (_bits >> 1 & 0x55555555);
		_bits = (_bits & 0x33333333) + (_bits >> 2 & 0x33333333);
		_bits = (_bits & 0x0f0f0f0f) + (_bits >> 4 & 0x0f0f0f0f);
		_bits = (_bits & 0x00ff00ff) + (_bits >> 8 & 0x00ff00ff);
		return (_bits & 0x0000ffff) + (_bits >> 16 & 0x0000ffff);

	}

	//
	static inline constexpr bool BitMask(auto _cmp, auto num){
		return Mand(_cmp, Bit(_num));
	}

}



#endif /* UTIL_BIT_HPP_ */
