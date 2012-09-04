#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "memory.h"
#include "stdio.h"
extern "C" {
#include "mj_evaluator.h"
}

TEST_GROUP(evaluator)
{

};

TEST(evaluator, evaluate_array) {
	tile_t tiles[1] = {C(1)};
	mahjong_evaluator_handle_t * e = LIB_create_evaluator();
	LIB_evaluator_evaluate_array(e, tiles, 1);
	delete e;
}
