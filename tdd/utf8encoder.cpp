#include "catch.hpp"
#include "UTF8Encoder.hpp"

SCENARIO("UTF8Encoder its used to encode utf8", "") {
	GIVEN("An instance of UTF8Encoder") {
		UTF8Encoder utf8enc;

		WHEN("Encoding an 'a' (0x61) unicode code point") {
			auto encoded = utf8enc.encode(0x61);
			THEN("You get an 'a'") {
				REQUIRE(encoded[0] == 0x61);
			}
		}

		WHEN("Encoding a DELETE (7f) unicode code point") {
			auto encoded = utf8enc.encode(0x7f);
			THEN("You get the same 7f") {
				REQUIRE(encoded[0] == 0x7f);
			}
		}

		WHEN("Encoding a 'ñ' (0xf1) unicode code point") {
			auto encoded = utf8enc.encode(0xf1);
			THEN("You get an 0xc3 0xb1") {
				REQUIRE(encoded[0] == '\xc3');
				REQUIRE(encoded[1] == '\xb1');
			}
		}

		WHEN("Encoding the bigger two byte number") {
			auto encoded = utf8enc.encode(0x07ff);
			THEN("You get an 0xDF 0xBF") {
				REQUIRE(encoded[0] == '\xdf');
				REQUIRE(encoded[1] == '\xbf');
			}
		}

		WHEN("Encoding a 0x0DA3 unicode code point") {
			auto encoded = utf8enc.encode(0x0DA3);
			THEN("You get 0xE0 0xB6 0xA3") {
				REQUIRE(encoded[0] == '\xe0');
				REQUIRE(encoded[1] == '\xb6');
				REQUIRE(encoded[2] == '\xa3');
			}
		}

		WHEN("Encoding the bigger three byte number") {
			auto encoded = utf8enc.encode(0x0ffff);
			THEN("You get an EF BF BF") {
				REQUIRE(encoded[0] == '\xef');
				REQUIRE(encoded[1] == '\xbf');
				REQUIRE(encoded[2] == '\xbf');
			}
		}

		WHEN("Encoding a 0x10082") {
			auto encoded = utf8enc.encode( 0x10082 );
			THEN("You get 0xF0 0x90 0x82 0x82") {
				REQUIRE(encoded[0] == '\xf0');
				REQUIRE(encoded[1] == '\x90');
				REQUIRE(encoded[2] == '\x82');
				REQUIRE(encoded[3] == '\x82');
			}
		}

		WHEN("Encoding biggest Unicode code point") {
			auto encoded = utf8enc.encode( 0x10ffff );
			THEN("You get F4 8F BF BF") {
				REQUIRE(encoded[0] == '\xf4');
				REQUIRE(encoded[1] == '\x8f');
				REQUIRE(encoded[2] == '\xbf');
				REQUIRE(encoded[3] == '\xbf');
			}
		}
	}
}

/*
TODO:
*/
