#include "pch.h"
#include "CppUnitTest.h"
#include "../Graphs/Graphs.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphTests1
{
	TEST_CLASS(GraphTests1)
	{
	public:
		std::string firelink = "Firelink Shrine";
		std::string burg = "Undead Burg";
		std::string asylum = "Northern Undead Asylum";
		std::string catacombs = "Catacombs";

		TEST_METHOD(AddNodeGivesNoNeighbors)
		{
			Graph ds1 = Graph();
			ds1.addNode(asylum);
			Assert::IsTrue(ds1.getNeighbors(asylum).isEmpty());
		}


		TEST_METHOD(AddEdgeGivesNeighbor)
		{
			Graph ds1 = Graph();
			ds1.addEdge(firelink, catacombs, 55);
			Vertices hmm = ds1.getNeighbors(firelink);
			Assert::IsTrue(hmm.length() == 1);
			Assert::IsTrue(hmm.contains(catacombs));
			Assert::IsFalse(hmm.contains(asylum));
			// Assert::IsTrue(ds1.getNeighbors(asylum).isEmpty());
		}
	};
}
