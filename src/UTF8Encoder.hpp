#ifndef UTF8_ENCODER_HPP_GUARD
#define UTF8_ENCODER_HPP_GUARD

#include <istream>
#include <ostream>

class UTF8Encoder
{
	public:
		static constexpr char32_t lower_6_bits   = 0b0011'1111UL;
		static constexpr char32_t continuation_byte = 0b1000'0000UL;
		static constexpr char32_t two_bytes_preamble   = 0b1100'0000UL;
		static constexpr char32_t three_bytes_preamble = 0b1110'0000UL;
		static constexpr char32_t four_bytes_preamble  = 0b1111'0000UL;

		std::string encode(char32_t c) {
			if(c<0x80)
				return std::string{static_cast<char>(c)};
			if(c<0x0800) {
				std::string to_return{0,2};
				to_return[1] = (c     & lower_6_bits) + continuation_byte;
				to_return[0] = (c>>6) + two_bytes_preamble;
				return to_return;
			}
			if(c<0x10000) {
				std::string to_return{0,3};
				to_return[2] = (c     & lower_6_bits) + continuation_byte;
				to_return[1] = (c>>6  & lower_6_bits) + continuation_byte;
				to_return[0] = (c>>12) + three_bytes_preamble;
				return to_return;
			}
			if(c<0x110000) {
				std::string to_return{0,4};
				to_return[3] = (c     & lower_6_bits) + continuation_byte;
				to_return[2] = (c>>6  & lower_6_bits) + continuation_byte;
				to_return[1] = (c>>12 & lower_6_bits) + continuation_byte;
				to_return[0] = (c>>18 & lower_6_bits) + four_bytes_preamble;
				return to_return;
			}
			return "";
		}

		void encode(std::basic_istream<char32_t> &input, std::basic_ostream<char> &output)  {
			while(input.good()) {
				std::string converted = encode(input.get());
				output << converted;
			}
		}
};

#endif //UTF8_ENCODER_HPP_GUARD
