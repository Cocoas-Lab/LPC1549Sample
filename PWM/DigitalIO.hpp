/*
 * gpio.hpp
 *
 *  Created on: 2017/03/07
 *      Author: Keita
 */

#ifndef DRIVER_DIGITALIO_HPP_
#define DRIVER_DIGITALIO_HPP_

#include <chip.hpp>
#include <stdint.h>
#include <vector>


namespace Driver{

	using port_t = uint8_t;
	using pin_t = uint8_t;
	using module_t = uint8_t;
	using id_t = uint8_t;

	namespace GPIO{
		enum class Direction: bool{
			Out = true,
			In = false,
		};

		enum class Option: uint32_t{
			Func0 = IOCON_FUNC0,
			Func1 = IOCON_FUNC1,
			Func2 = IOCON_FUNC2,
			InAct = IOCON_MODE_INACT,
			PullDown = IOCON_MODE_PULLDOWN,
			PullUp = IOCON_MODE_PULLUP,
			Repeater = IOCON_MODE_REPEATER,
			Hysteresis = IOCON_HYS_EN,
			Invert = IOCON_INV_EN,
			Analog = IOCON_ADMODE_EN,
			Digital = IOCON_DIGMODE_EN,
			SFI2C = IOCON_SFI2C_EN,
			StdI2C = IOCON_STDI2C_EN,
			FastI2C = IOCON_FASTI2C_EN,
			OpenDrain = IOCON_OPENDRAIN_EN,
			Filter0Clk = IOCON_S_MODE_0CLK,
			Filter1Clk = IOCON_S_MODE_1CLK,
			Filter2Clk = IOCON_S_MODE_2CLK,
			Filter3Clk = IOCON_S_MODE_3CLK,
			ClkDivNone = IOCON_CLKDIV(0),
			ClkDiv2 = IOCON_CLKDIV(1),
			ClkDiv4 = IOCON_CLKDIV(2),
			ClkDiv8 = IOCON_CLKDIV(3),
			ClkDiv16 = IOCON_CLKDIV(4),
			ClkDiv32 = IOCON_CLKDIV(5),
			ClkDiv64 = IOCON_CLKDIV(6),

		};

		class Digital{
		public:
			port_t port;
			pin_t pin;

			Digital() = default;
			Digital(const uint8_t _port, const uint8_t _pin);
			Digital(const Digital&) = default;
			void Toggle()const;
			uint8_t port_()const;
			uint8_t pin_()const;
			const Digital& Open()const;
			const Digital& operator()(const bool)const;
			void operator<<(const bool)const;
			bool operator()()const;
			void operator>>(bool&)const;
			const Digital& operator()(const Direction)const;
			const Digital& operator()(const CHIP_SWM_PIN_MOVABLE_T)const;
			const Digital& operator()(const CHIP_SWM_PIN_FIXED_T)const;
			const Digital& operator()(const std::vector<Option>)const;
			//設定用関数
		};
	}
}



#endif /* DRIVER_DIGITALIO_HPP_ */
