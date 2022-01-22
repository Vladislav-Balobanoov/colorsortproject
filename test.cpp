#include <gtest\gtest.h>
#include <vector>
#include <string>
#include "..\Sub.h"
#include "..\ASTest.h"

TEST(testSort, validRule) 
{
	std::vector<Sub<int>> vector;
	std::string rule = "rgb";
	generate(10, vector);
	ASSERT_TRUE(sortColors(vector, rule));

	rule = "rbg";
	generate(10, vector);
	ASSERT_TRUE(sortColors(vector, rule));

	rule = "bgr";
	generate(10, vector);
	ASSERT_TRUE(sortColors(vector, rule));

	rule = "brg";
	generate(10, vector);
	ASSERT_TRUE(sortColors(vector, rule));

	rule = "gbr";
	generate(10, vector);
	ASSERT_TRUE(sortColors(vector, rule));

	rule = "gbr";
	generate(10, vector); 
	ASSERT_TRUE(sortColors(vector, rule));
}

TEST(testSort, invalidRule)
{
	std::vector<Sub<int>> vector;
	std::string rule = "kgb";
	generate(10, vector);
	ASSERT_FALSE(sortColors(vector, rule));
	
	rule = "axe";
	generate(10, vector);
	ASSERT_FALSE(sortColors(vector, rule));

	rule = "rbb";
	generate(10, vector);
	ASSERT_FALSE(sortColors(vector, rule));

	rule = "bbb";
	generate(10, vector);
	ASSERT_FALSE(sortColors(vector, rule));

	rule = "ggg";
	generate(10, vector);
	ASSERT_FALSE(sortColors(vector, rule));

	rule = "rrr";
	generate(10, vector);
	ASSERT_FALSE(sortColors(vector, rule));
}

TEST(testSort, invalidSizeOfRule)
{
	std::vector<Sub<int>> vector;
	std::string rule = "rggg";
	generate(10, vector);
	EXPECT_FALSE(sortColors(vector, rule));

	rule = "bggr";
	generate(10, vector);
	EXPECT_FALSE(sortColors(vector, rule));

	rule = "rbbbgbrg";
	generate(10, vector);
	EXPECT_FALSE(sortColors(vector, rule));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}