#include "catch.hpp"

class UTF8Encoder
{
  public:
  	 std::string encode(char32_t c) {
  	 	if(c<0x7f)
  	 		return std::string{static_cast<char>(c)};
  	 	std::string to_return{0,2};
  	 	to_return[0] = (c>>6 & 0b0001'1111) + 0b1100'0000;
  	 	to_return[1] = (c    & 0b0011'1111) + 0b1000'0000;
  	 	return to_return;
  	 }
};

SCENARIO("UTF8Encoder its used to encode utf8", "") {
	GIVEN("An instance of UTF8Encoder") {
		UTF8Encoder utf8enc;

		WHEN("Encoding an 'a'") {
			auto encoded = utf8enc.encode(0x61);
			THEN("You get an 'a'") {
				REQUIRE(encoded[0] == 0x61);
			}
		}

		WHEN("Encoding an 'ñ'") {
			auto encoded = utf8enc.encode(0xf1);
			THEN("You get an 0xc3 0xb1") {
				REQUIRE(encoded[0] == '\xc3');
				REQUIRE(encoded[1] == '\xb1');
			}
		}
	}
}
