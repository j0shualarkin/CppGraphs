#include "pch.h"
#include "CppUnitTest.h"
#include "../Graphs/Vertex.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VertexTest1
{
	TEST_CLASS(VertexTest1)
	{
	public:


		TEST_METHOD(PopFront1) 
		{
			Vertices test = Vertices();
			test.addNodeBack

		}
		// 1. Make sure isEmpty holds only for a new instance of Vertices
		TEST_METHOD(IsEmptyTest1)
		{
			Vertices fresh = Vertices();
			Assert::IsTrue(fresh.isEmpty());
		}

		TEST_METHOD(IsEmptyTest2)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("water", 1);
			Assert::IsFalse(fresh.isEmpty());
		}

		TEST_METHOD(ContainsTest1)
		{
			Vertices fresh = Vertices();
			Assert::IsFalse(fresh.contains("dog"));
		}

		TEST_METHOD(AddNodeThenPeek)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("dog", 1);
			std::string dog = "dog";
			Assert::AreEqual(dog, fresh.peek());
			//Assert::IsTrue(fresh.contains("dog"));
		}


		TEST_METHOD(ContainsTest2)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("dog", 1);
			std::string dog = "dog";
			Assert::IsTrue(fresh.contains(dog));
		}

		TEST_METHOD(ContainsTest3)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("dog", 1);
			Assert::IsTrue(fresh.contains("dog"));
			Assert::IsFalse(fresh.isEmpty());
			Assert::IsTrue(fresh.contains("dog")); // see if it works a second time 
		}

		TEST_METHOD(LengthTest1)
		{
			Vertices fresh = Vertices();
			Assert::AreEqual(fresh.length(), 0);
		}


		TEST_METHOD(LengthTest2)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("Seattle", 24);
			Assert::AreEqual(fresh.length(), 1);
		}


		TEST_METHOD(LengthTest3)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("Seattle", 24);
			fresh.addNodeFront("Boise", 4);
			Assert::AreEqual(2, fresh.length());
		}

		TEST_METHOD(LengthTest4)
		{
			Vertices fresh = Vertices();
			fresh.addNodeFront("Seattle", 24);
			fresh.addNodeFront("Boise", 4);
			fresh.contains("Seattle");
			Assert::AreEqual(2, fresh.length());
		}
	};
}
