#include <doctest.h>

#include "Core/Settings.h"

// Macro's
#define NULL_KEY "null"
#define STRINGS_KEY "string"
#define INTEGERS_KEY "integer"
#define FLOATS_KEY "float"
#define BOOLS_KEY "bools"
#define XML_KEY "xml"

TEST_SUITE("Settings"){
    //Single instance
    auto settings = GolfEngine::Core::Settings{};

    TEST_CASE("getType() on invalid key returns Null"){
        CHECK_EQ(settings.getType(NULL_KEY), GolfEngine::Core::SettingsTypes::Null);
    }

    TEST_CASE("Strings"){
        SUBCASE("Can set/get values"){
            settings.setString(STRINGS_KEY, "true");
            CHECK(settings.hasString(STRINGS_KEY));
            CHECK_EQ(settings.getString(STRINGS_KEY), "true");
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(settings.hasString(NULL_KEY));
            CHECK_THROWS(settings.getString(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            settings.setBool(STRINGS_KEY, true);
            CHECK_FALSE(settings.hasString(STRINGS_KEY));
            CHECK_THROWS(settings.getString(STRINGS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            settings.setString("", "test");
            CHECK_FALSE(settings.hasString(""));
        }
        SUBCASE("getType() returns String"){
            settings.setString(STRINGS_KEY, "true");
            CHECK_EQ(settings.getType(STRINGS_KEY), GolfEngine::Core::SettingsTypes::String);
        }
    }

    TEST_CASE("Integers"){
        SUBCASE("Can set/get values"){
            settings.setInteger(INTEGERS_KEY, 1);
            CHECK(settings.hasInteger(INTEGERS_KEY));
            CHECK_EQ(settings.getInteger(INTEGERS_KEY), 1);
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(settings.hasInteger(NULL_KEY));
            CHECK_THROWS(settings.getInteger(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            settings.setString(INTEGERS_KEY, "");
            CHECK_FALSE(settings.hasInteger(INTEGERS_KEY));
            CHECK_THROWS(settings.getInteger(INTEGERS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            settings.setInteger("", 1);
            CHECK_FALSE(settings.hasInteger(""));
        }
        SUBCASE("getType() returns Integer"){
            settings.setInteger(INTEGERS_KEY, 1);
            CHECK_EQ(settings.getType(INTEGERS_KEY), GolfEngine::Core::SettingsTypes::Integer);
        }
    }

    TEST_CASE("Floats"){
        SUBCASE("Can set/get values"){
            settings.setFloat(FLOATS_KEY, 1.0f);
            CHECK(settings.hasFloat(FLOATS_KEY));
            CHECK_EQ(settings.getFloat(FLOATS_KEY), 1.0f);
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(settings.hasFloat(NULL_KEY));
            CHECK_THROWS(settings.getFloat(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            settings.setInteger(FLOATS_KEY, 1);
            CHECK_FALSE(settings.hasFloat(FLOATS_KEY));
            CHECK_THROWS(settings.getFloat(FLOATS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            settings.setFloat("", 1.0f);
            CHECK_FALSE(settings.hasFloat(""));
        }
        SUBCASE("getType() returns Float"){
            settings.setFloat(FLOATS_KEY, 1.0f);
            CHECK_EQ(settings.getType(FLOATS_KEY), GolfEngine::Core::SettingsTypes::Float);
        }
    }

    TEST_CASE("Booleans"){
        SUBCASE("Can set/get values"){
            settings.setBool(BOOLS_KEY, true);
            CHECK(settings.hasBool(BOOLS_KEY));
            CHECK_EQ(settings.getBool(BOOLS_KEY), true);
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(settings.hasBool(NULL_KEY));
            CHECK_THROWS(settings.getBool(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            settings.setFloat(BOOLS_KEY, 1.0f);
            CHECK_FALSE(settings.hasBool(BOOLS_KEY));
            CHECK_THROWS(settings.getBool(BOOLS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            settings.setBool("", true);
            CHECK_FALSE(settings.hasBool(""));
        }
        SUBCASE("getType() returns Bool"){
            settings.setBool(BOOLS_KEY, true);
            CHECK_EQ(settings.getType(BOOLS_KEY), GolfEngine::Core::SettingsTypes::Boolean);
        }
    }

    TEST_CASE("Serialization"){
        SUBCASE("fromXml() sucessfully loads former state"){
            //Arrange
            settings.setBool(XML_KEY, true);

            //Act
            auto xmlResult = settings.toXml();

            //Assert
            CHECK(settings.getBool(XML_KEY));
            settings.setBool(XML_KEY, false);
            CHECK_FALSE(settings.getBool(XML_KEY));
            settings.fromXml(xmlResult);
            CHECK(settings.getBool(XML_KEY));
        }
        SUBCASE("fromXml() throws on invalid XML"){
            CHECK_THROWS(settings.fromXml("INVALID XML STRING"));
        }
    }
}
