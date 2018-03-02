/*
 * uart.hpp
 *
 *  Created on: 2017/03/21
 *      Author: Keita
 */

#ifndef DRIVER_COMM_UART_HPP_
#define DRIVER_COMM_UART_HPP_

#include <string>
#include <stdint.h>
#include <cstring>
#include <vector>
#include <utility>
#include <array>
#include "DigitalIO.hpp"
#include "text.hpp"
#include "type.hpp"

namespace Driver{
	class Serial{
	public:
		static constexpr uint8_t UartChNum = 3;
		static constexpr size_t TxSize = 128, RxSize = 128; //バッファーのサイズ
        static RINGBUFF_T TxBuf[UartChNum], RxBuf[UartChNum];
		static char TxRaw[UartChNum][TxSize], RxRaw[UartChNum][RxSize];
		static LPC_USART_T* UartBase[UartChNum];
		static std::array<Util::CallBack, UartChNum> Callback;
		Driver::GPIO::Digital tx, rx;
		uint32_t baud;
		uint8_t id;
	public:
		Serial() = default;
		Serial(const std::pair<uint8_t, uint8_t> _tx, const std::pair<uint8_t, uint8_t> _rx, const uint32_t _id, const uint32_t _baud = 115200);
		Serial(const Serial&) = default;
		virtual ~Serial() = default;

		void Write(const char _c);
		void Write(const uint8_t* _data, size_t _sz);
		void Write(const char* _str);
		void Write(const std::vector<uint8_t>& _data);
		void WriteLine();
		void WriteLine(const std::string& line);
		void WriteLine(const char* line);
		void WriteLine(const std::vector<uint8_t>& bytes);
		void Write(const std::string& _text);
		char ReadByte();
		std::string Read(const size_t _sz);
		std::string Read();
		std::string ReadLine();
		bool IsEmpty();
		bool IsFull();
		void Claer();
		bool IsBusy();
		bool IsExist(const char _c);
		bool IsLine(){
			return IsExist('\r');
		}
		void setBaud(const uint32_t _baud);
		void SetCallback(const Util::CallBackRef _callback);
		void SetCallback(const Util::CallBackRRef _callback);
		static void IRQHandler(uint32_t _id){
			auto isReceive = ((Chip_UART_GetStatus(Serial::UartBase[_id]) & UART_STAT_RXRDY) != 0);

			Chip_UART_IRQRBHandler(Serial::UartBase[_id], &Serial::RxBuf[_id], &Serial::TxBuf[_id]);

			if((Callback[_id] != nullptr) &&  isReceive){
				auto& func = Callback[_id];
				func();
			}
		}
		void operator<<(const std::string& _str){
			Write(_str);
		}

		void operator<<(char _c){
			Write(_c);
		}

		void operator<<(const std::vector<uint8_t>& _data){
			Write(_data);
		}

		void operator<<(const char* _str){
			Write(_str);
		}

		void operator<<(const int _d){
			Write(Util::ToStr(_d));
		}

		void operator<<(const long _ld){
			Write(Util::ToStr(_ld));
		}

		void operator<<(const float _f){
			Write(Util::ToStrF(_f));
		}

		void operator<<(Serial& _serial){
			Write(_serial.Read());
		}

		void operator>>(char& _c){
			_c = ReadByte();
		}

		void operator>>(std::string& str){
			str = ReadLine();
		}

		void operator>>(int& _d){
			_d = Util::ToInt32(std::string{ReadByte()});
		}

		void operator>>(long& _ld){
			_ld = Util::ToInt64(std::string{ReadByte()});
		}

		void operator>>(float& _f){
			Util::ToFloat(std::string{ReadByte()});
		}

		void operator>>(Serial& _serial){
			_serial.Write(Read());
		}
	};
}


#endif /* DRIVER_COMM_UART_HPP_ */
