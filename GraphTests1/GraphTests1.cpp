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
		std::string parish = "Undead Parish";
		std::string garden = "Darkroot Garden";
		std::string anor = "Anor Londo";
		std::string tomb = "Tomb of the Giants";
		std::string valley = "Valley of the Drakes";
		std::string londo = "New Londo Ruins";
		std::string blight = "Blighttown";
		std::string depths = "Depths";
		std::string sens = "Sen's Fortress";

		TEST_METHOD(MakingDS1)
		{
			Graph ds1 = Graph();
			ds1.addEdge(firelink, catacombs, 50);
			ds1.addEdge(firelink, parish, 20);
			ds1.addEdge(firelink, depths, 30);
			ds1.addEdge(firelink, londo, 10);
			ds1.addEdge(firelink, burg, 1);

			ds1.addEdge(burg, parish, 20);
			ds1.addEdge(burg, depths, 20);

			ds1.addEdge(catacombs, tomb, 15);

			ds1.addEdge(valley, londo, 10);
			ds1.addEdge(valley, blight, 5);

			ds1.addEdge(londo, garden, 30);
			ds1.addEdge(depths, blight, 15);

			ds1.addEdge(parish, sens, 2);
			ds1.addEdge(parish, garden, 5);

			ds1.addEdge(sens, anor, 50);
			ds1.addNode(asylum);

			Assert::AreEqual(5, ds1.neighborCount(firelink));
			Assert::AreEqual(2, ds1.neighborCount(catacombs));
			Assert::AreEqual(1, ds1.neighborCount(tomb));
			Assert::AreEqual(2, ds1.neighborCount(valley));
			Assert::AreEqual(3, ds1.neighborCount(burg));
			Assert::AreEqual(0, ds1.neighborCount(asylum));
		}

		TEST_METHOD(StoopidDFS1) 
		{
			Graph testGraph = Graph();
			testGraph.addEdge("Start", "B", 9);
			testGraph.addEdge("Start", "A", 7);
			testGraph.addEdge("B", "E", 10);
			testGraph.addEdge("A", "C", 3);
			testGraph.addEdge("C", "D", 8);
			testGraph.addEdge("E", "D", 5);
			SearchResult test = testGraph.DFSDriver("Start", "E");
			Assert::IsTrue(test.getBool());
			Assert::AreEqual(5, test.getPath().length());
		}

		/* The above and below examples show how DFS can under perform compared to BFS
			Above, the path follows the line through all nodes to get to E.
			Below, we can't get to E from D, so we find it by following B.
			A BFS would do this without exhausting the A side;  proof coming soon!
		*/
		TEST_METHOD(StoopidDFS2) 
		{
			Graph testGraph = Graph();
			testGraph.addEdge("Start", "B", 9);
			testGraph.addEdge("Start", "A", 7);
			testGraph.addEdge("B", "E", 10);
			testGraph.addEdge("A", "C", 3);
			testGraph.addEdge("C", "D", 8);
			SearchResult test = testGraph.DFSDriver("Start", "E");
			Assert::IsTrue(test.getBool());
			Assert::AreEqual(3, test.getPath().length());
		}
		TEST_METHOD(DFSTestWithDS)
		{
			Graph ds1 = Graph();
			ds1.addEdge(firelink, catacombs, 50);
			ds1.addEdge(firelink, parish, 20);
			ds1.addEdge(firelink, depths, 30);
			ds1.addEdge(firelink, londo, 10);
			ds1.addEdge(firelink, burg, 1);

			ds1.addEdge(burg, parish, 20);
			ds1.addEdge(burg, depths, 20);

			ds1.addEdge(catacombs, tomb, 15);

			ds1.addEdge(valley, londo, 10);
			ds1.addEdge(valley, blight, 5);

			ds1.addEdge(londo, garden, 30);
			ds1.addEdge(depths, blight, 15);

			ds1.addEdge(parish, sens, 2);
			ds1.addEdge(parish, garden, 5);

			ds1.addEdge(sens, anor, 50);
		
			ds1.addNode(asylum);
			SearchResult res = ds1.DFS(firelink, sens, Vertices(), SearchResult());
			Assert::IsTrue(res.getBool());
			Vertices path = res.getPath();
			Assert::IsTrue(0 < path.length()); 
		}

		TEST_METHOD(DFSTestWithDS2)
		{
			Graph ds1 = Graph();
			ds1.addEdge(firelink, catacombs, 50);
			ds1.addEdge(firelink, parish, 20);
			ds1.addEdge(firelink, depths, 30);
			ds1.addEdge(firelink, londo, 10);
			ds1.addEdge(firelink, burg, 1);

			ds1.addEdge(burg, parish, 20);
			ds1.addEdge(burg, depths, 20);

			ds1.addEdge(catacombs, tomb, 15);

			ds1.addEdge(valley, londo, 10);
			ds1.addEdge(valley, blight, 5);

			ds1.addEdge(londo, garden, 30);
			ds1.addEdge(depths, blight, 15);

			ds1.addEdge(parish, sens, 2);
			ds1.addEdge(parish, garden, 5);

			ds1.addEdge(sens, anor, 50);
		
			ds1.addNode(asylum);
			
			SearchResult res = ds1.DFS(firelink, asylum, Vertices(), SearchResult());
			Assert::IsFalse(res.getBool());
		}

		TEST_METHOD(AddNodeGivesNoNeighbors)
		{
			Graph test = Graph();
			test.addNode(asylum);
			Assert::IsTrue(test.getNeighbors(asylum).isEmpty());
		}


		TEST_METHOD(Add1EdgeGivesLen1)
		{
			Graph test = Graph();
			test.addEdge(firelink, catacombs, 55);
			Assert::AreEqual(1, test.neighborCount(firelink));
		}

		TEST_METHOD(Add1EdgeContainsEdge)
		{
			Graph test = Graph();
			test.addEdge(firelink, catacombs, 55);
			Assert::IsTrue(test.getNeighbors(firelink).contains(catacombs));
		}

		TEST_METHOD(Add1EdgeDoesntContainDiffNode)
		{
			Graph test = Graph();
			test.addEdge(firelink, catacombs, 55);
			Assert::IsFalse(test.getNeighbors(firelink).contains(asylum));
		}

		TEST_METHOD(GetNoNeighbors)
		{
			Graph test = Graph();
			Assert::IsTrue(test.getNeighbors("unknown").isEmpty());
		}
	};
}
