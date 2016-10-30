#include "catch.hpp"
#include "UTF8Encoder.hpp"
#include <sstream>

SCENARIO("UTF8Encoder its used to encode files to UTF-8", "") {
	GIVEN("An instance of UTF8Encoder and an input and output stream") {
		UTF8Encoder utf8enc;
		std::basic_stringstream<char32_t> input;
		std::basic_stringstream<char> output;
		WHEN("Converting hello") {
			input.put('h');
			input.put('e');
			input.put('l');
			input.put('l');
			input.put('o');
			utf8enc.encode(input, output);
			THEN("Output is the same") {
				char c = output.get();
				REQUIRE(c=='h');
				c = output.get();
				REQUIRE(c=='e');
				c = output.get();
				REQUIRE(c=='l');
				c = output.get();
				REQUIRE(c=='l');
				c = output.get();
				REQUIRE(c=='o');
			}
		}

		WHEN("Converting ñ") {
			input.put(char32_t(0xf1));
			utf8enc.encode(input, output);
			THEN("Output is 0xc3 0xb1") {
				char c = output.get();
				REQUIRE(c=='\xc3');
				c = output.get();
				REQUIRE(c=='\xb1');
			}
		}
	}
}
