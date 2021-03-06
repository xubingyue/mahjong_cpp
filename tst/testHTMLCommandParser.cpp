#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include <typeinfo>
#include "mocks.h"

TEST_GROUP(HTMLCommandParser) {
	MockHTMLMahjongGameServer server;
	HTMLCommandParser *parser;
	MahjongCommand *cmd;
	void setup() {
		cmd = NULL;
		parser = new HTMLCommandParser(&server);
	}
	void teardown() {
		delete cmd;
		delete parser;
	}
};

TEST(HTMLCommandParser, parse_start_new) {
	cmd = parser->parse("/game", "");
	STRCMP_EQUAL(typeid(MJCommandStartNew).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, parse_bye) {
	cmd = parser->parse("/bye", "");
	STRCMP_EQUAL(typeid(MJCommandQuitGame).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, parse_shutdown) {
	cmd = parser->parse("/shutdown", "");
	STRCMP_EQUAL(typeid(MJCommandShutdownServer).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, restart) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/start", "3000");
	STRCMP_EQUAL(typeid(MJCommandRestart).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, game_does_not_exist) {
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 4).andReturnValue((void *)NULL);
	cmd = parser->parse("/start", "4000");
	STRCMP_EQUAL(typeid(MJCommandDoesNotExist).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandDiscard) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/throw", "3005");
	STRCMP_EQUAL(typeid(MJCommandDiscard).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandPick) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/pick", "3000");
	STRCMP_EQUAL(typeid(MJCommandPick).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandChow) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/chow", "3002");
	STRCMP_EQUAL(typeid(MJCommandChow).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandPong) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/pong", "3000");
	STRCMP_EQUAL(typeid(MJCommandPong).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandKong) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/kong", "3002");
	STRCMP_EQUAL(typeid(MJCommandKong).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandWin) {
	UserPerspective game;
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/win", "3000");
	STRCMP_EQUAL(typeid(MJCommandWin).name(), typeid(*cmd).name());
}


