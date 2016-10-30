#include "catch.hpp"
#include "UTF8Encoder.hpp"
#include <sstream>

SCENARIO("UTF8Encoder its used to encode files to UTF-8", "") {
	GIVEN("An instance of UTF8Encoder and an input and output stream") {
		UTF8Encoder utf8enc;
		std::basic_stringstream<char32_t> input;
		std::basic_stringstream<char> output;

		WHEN("Converting hello") {
			input << std::basic_string<char32_t> {'h','e','l','l','o'};
			utf8enc.encode(input, output);
			THEN("Output is the same") {
				std::string actual;
				output >> actual;
				REQUIRE(actual=="hello");
			}
		}

		WHEN("Converting 0xf1 0xf1 (ññ)") {
			input << std::basic_string<char32_t> {0xf1, 0xf1};
			utf8enc.encode(input, output);
			THEN("Output is ññ") {
				std::string actual;
				output >> actual;
				REQUIRE(actual=="\xc3\xb1\xc3\xb1");
			}
		}
	}
}
