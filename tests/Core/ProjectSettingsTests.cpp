#include <doctest.h>

#include "Core/ProjectSettings.h"

// Macro's
#define NULL_KEY "null"
#define STRINGS_KEY "string"
#define INTEGERS_KEY "integer"
#define FLOATS_KEY "float"
#define BOOLS_KEY "bools"
#define XML_KEY "xml"

TEST_SUITE("ProjectSettings"){
    //Single instance
    auto& projectSettings = GolfEngine::Core::ProjectSettings::getInstance();

    TEST_CASE("Is a singleton"){
        auto& i1 = GolfEngine::Core::ProjectSettings::getInstance();
        auto& i2 = GolfEngine::Core::ProjectSettings::getInstance();

        CHECK_EQ(&i1, &i2);
    }

    TEST_CASE("getType() on invalid key returns Null"){
        CHECK_EQ(projectSettings.getType(NULL_KEY), GolfEngine::Core::ProjectSettingsTypes::Null);
    }

    TEST_CASE("Strings"){
        SUBCASE("Can set/get values"){
            projectSettings.setString(STRINGS_KEY, "true");
            CHECK(projectSettings.hasString(STRINGS_KEY));
            CHECK_EQ(projectSettings.getString(STRINGS_KEY), "true");
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(projectSettings.hasString(NULL_KEY));
            CHECK_THROWS(projectSettings.getString(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            projectSettings.setBool(STRINGS_KEY, true);
            CHECK_FALSE(projectSettings.hasString(STRINGS_KEY));
            CHECK_THROWS(projectSettings.getString(STRINGS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            projectSettings.setString("", "test");
            CHECK_FALSE(projectSettings.hasString(""));
        }
        SUBCASE("getType() returns String"){
            projectSettings.setString(STRINGS_KEY, "true");
            CHECK_EQ(projectSettings.getType(STRINGS_KEY), GolfEngine::Core::ProjectSettingsTypes::String);
        }
    }

    TEST_CASE("Integers"){
        SUBCASE("Can set/get values"){
            projectSettings.setInteger(INTEGERS_KEY, 1);
            CHECK(projectSettings.hasInteger(INTEGERS_KEY));
            CHECK_EQ(projectSettings.getInteger(INTEGERS_KEY), 1);
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(projectSettings.hasInteger(NULL_KEY));
            CHECK_THROWS(projectSettings.getInteger(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            projectSettings.setString(INTEGERS_KEY, "");
            CHECK_FALSE(projectSettings.hasInteger(INTEGERS_KEY));
            CHECK_THROWS(projectSettings.getInteger(INTEGERS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            projectSettings.setInteger("", 1);
            CHECK_FALSE(projectSettings.hasInteger(""));
        }
        SUBCASE("getType() returns Integer"){
            projectSettings.setInteger(INTEGERS_KEY, 1);
            CHECK_EQ(projectSettings.getType(INTEGERS_KEY), GolfEngine::Core::ProjectSettingsTypes::Integer);
        }
    }

    TEST_CASE("Floats"){
        SUBCASE("Can set/get values"){
            projectSettings.setFloat(FLOATS_KEY, 1.0f);
            CHECK(projectSettings.hasFloat(FLOATS_KEY));
            CHECK_EQ(projectSettings.getFloat(FLOATS_KEY), 1.0f);
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(projectSettings.hasFloat(NULL_KEY));
            CHECK_THROWS(projectSettings.getFloat(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            projectSettings.setInteger(FLOATS_KEY, 1);
            CHECK_FALSE(projectSettings.hasFloat(FLOATS_KEY));
            CHECK_THROWS(projectSettings.getFloat(FLOATS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            projectSettings.setFloat("", 1.0f);
            CHECK_FALSE(projectSettings.hasFloat(""));
        }
        SUBCASE("getType() returns Float"){
            projectSettings.setFloat(FLOATS_KEY, 1.0f);
            CHECK_EQ(projectSettings.getType(FLOATS_KEY), GolfEngine::Core::ProjectSettingsTypes::Float);
        }
    }

    TEST_CASE("Booleans"){
        SUBCASE("Can set/get values"){
            projectSettings.setBool(BOOLS_KEY, true);
            CHECK(projectSettings.hasBool(BOOLS_KEY));
            CHECK_EQ(projectSettings.getBool(BOOLS_KEY), true);
        }
        SUBCASE("Throws exception when using an invalid key"){
            CHECK_FALSE(projectSettings.hasBool(NULL_KEY));
            CHECK_THROWS(projectSettings.getBool(NULL_KEY));
        }
        SUBCASE("Throws exception when different type is instantiated"){
            projectSettings.setFloat(BOOLS_KEY, 1.0f);
            CHECK_FALSE(projectSettings.hasBool(BOOLS_KEY));
            CHECK_THROWS(projectSettings.getBool(BOOLS_KEY));
        }
        SUBCASE("Doesn't add anything on an empty key"){
            projectSettings.setBool("", true);
            CHECK_FALSE(projectSettings.hasBool(""));
        }
        SUBCASE("getType() returns Bool"){
            projectSettings.setBool(BOOLS_KEY, true);
            CHECK_EQ(projectSettings.getType(BOOLS_KEY), GolfEngine::Core::ProjectSettingsTypes::Boolean);
        }
    }

    TEST_CASE("Serialization"){
        SUBCASE("fromXml() sucessfully loads former state"){
            //Arrange
            projectSettings.setBool(XML_KEY, true);

            //Act
            auto xmlResult = projectSettings.toXml();

            //Assert
            CHECK(projectSettings.getBool(XML_KEY));
            projectSettings.setBool(XML_KEY, false);
            CHECK_FALSE(projectSettings.getBool(XML_KEY));
            projectSettings.fromXml(xmlResult);
            CHECK(projectSettings.getBool(XML_KEY));
        }
        SUBCASE("fromXml() throws on invalid XML"){
            CHECK_THROWS(projectSettings.fromXml("INVALID XML STRING"));
        }
    }
}
