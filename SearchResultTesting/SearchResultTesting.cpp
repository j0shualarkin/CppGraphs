#include "pch.h"
#include "CppUnitTest.h"
#include "../Graphs/SearchResult.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SearchResultTesting
{
	TEST_CLASS(SearchResultTesting)
	{
	public:
		
		TEST_METHOD(AddToPath_1)
		{
			SearchResult test = SearchResult();
			Assert::IsTrue(test.getPath().length() == 0);
			test.addToPath("Seattle", 20);
			Assert::IsTrue(test.getPath().length() == 1);
		}
	};
}
