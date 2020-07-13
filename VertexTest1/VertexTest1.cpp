#include "pch.h"
#include "CppUnitTest.h"
#include "../Graphs/Vertex.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VertexTest1
{
	TEST_CLASS(VertexTest1)
	{
	public:

		TEST_METHOD(EnqueueAndLength)
		{
			Vertices test = Vertices();
			test.enqueue("Pixel", 1);
			Assert::AreEqual(1, test.length());
		}


		TEST_METHOD(EnqueueAndLength2)
		{
			Vertices test = Vertices();
			test.addNode("Pixel", 1);
			test.addNode("XL", 1);
			test.enqueue("Telephone", 1);
			Assert::AreEqual(3, test.length());
		}

		TEST_METHOD(EnqueueAndLength3)
		{
			Vertices test = Vertices();
			test.enqueue("Pixel", 1);
			test.enqueue("XL", 1);
			test.enqueue("Telephone", 1);
			Assert::AreEqual(3, test.length());
		}

		TEST_METHOD(EnqueueAndPop2)
		{
			Vertices test = Vertices();
			std::string pixel = "Pixel";
			std::string xl = "XL";
			test.enqueue("Pixel", 1);
			test.enqueue("XL", 1);
			Vertex* pop1 = test.pop();
			Assert::AreEqual(pixel, pop1->name);
			Vertex* pop2 = test.pop();
			Assert::AreEqual(xl, pop2->name);
		}

		TEST_METHOD(EnqueueAndPop)
		{
			Vertices test = Vertices();
			test.addNode("Pixel", 1);
			test.addNode("XL", 1);
			test.enqueue("Telephone", 1);
			int count = 0;
			while (!test.isEmpty())
			{
				Vertex * elt = test.pop();
				++count;
			}
			Assert::AreEqual(3, count);
		}


		TEST_METHOD(Sanity)
		{
			Vertices test = Vertices();
			while (!test.isEmpty())
			{
				Vertex * elt = test.pop();
			}
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(Append1) 
		{
			Vertices as = Vertices();
			Vertices bs = Vertices();
			std::string apple = "Apple";
			std::string banana = "Banana";
			std::string peach = "Peach";
			std::string pear = "Pear";
			as.addNode(apple, 12);
			as.addNode(banana, 34);
			bs.addNode(peach, 56);
			bs.addNode(pear, 78);
			as.append(bs);
			Assert::AreEqual(4, as.length());
		}

		TEST_METHOD(Append2) 
		{
			Vertices as = Vertices();
			Vertices bs = Vertices();
			std::string apple = "Apple";
			std::string banana = "Banana";
			std::string peach = "Peach";
			std::string pear = "Pear";
			as.addNode(apple, 12);
			as.addNode(banana, 34); // as = | banana,34 | apple,12 |
			bs.addNode(peach, 56); // bs = | pear, 78 | peach, 56 |
			bs.addNode(pear, 78);
			as.append(bs); // | peach, 56 | pear, 78 | banana, 34 | apple,12 |
			Vertex * bananaHuh = as.pop();
			Vertex * appleHuh = as.pop();
			Vertex * peachHuh = as.pop();
			Vertex * pearHuh = as.pop();
			Assert::AreEqual(0, as.length());
		}

		TEST_METHOD(Append3)
		{
			Vertices as = Vertices();
			Vertices bs = Vertices();
			std::string apple = "Apple";
			std::string banana = "Banana";
			std::string peach = "Peach";
			std::string pear = "Pear";
			as.addNode(apple, 12);
			as.addNode(banana, 34); // as = | banana,34 | apple,12 |
			bs.addNode(peach, 56); // bs = | pear, 78 | peach, 56 |
			bs.addNode(pear, 78);
			as.append(bs); // | peach, 56 | pear, 78 | banana, 34 | apple,12 |
			Vertex* bananaHuh = as.pop();
			Vertex* appleHuh = as.pop();
			Vertex* pearHuh = as.pop();
			Vertex* peachHuh = as.pop();
			Assert::AreEqual(peach, peachHuh->name);
			Assert::AreEqual(56, peachHuh->weight);
		}

		TEST_METHOD(Append4)
		{
			Vertices as = Vertices();
			Vertices bs = Vertices();
			std::string apple = "Apple";
			std::string banana = "Banana";
			std::string peach = "Peach";
			std::string pear = "Pear";
			as.addNode(apple, 12);
			as.addNode(banana, 34); // as = | banana,34 | apple,12 |
			bs.addNode(peach, 56); // bs = | pear, 78 | peach, 56 |
			bs.addNode(pear, 78);
			as.append(bs); // | peach, 56 | pear, 78 | banana, 34 | apple,12 |
			Vertex* bananaHuh = as.pop();
			Vertex* appleHuh = as.pop();
			Vertex* pearHuh = as.pop();
			Vertex* peachHuh = as.pop();
			Assert::AreEqual(pear, pearHuh->name);
			Assert::AreEqual(78, pearHuh->weight);
		}


		TEST_METHOD(Append5)
		{
			Vertices as = Vertices();
			Vertices bs = Vertices();
			std::string apple = "Apple";
			std::string banana = "Banana";
			std::string peach = "Peach";
			std::string pear = "Pear";
			as.addNode(apple, 12);
			as.addNode(banana, 34); // as = | banana,34 | apple,12 |
			bs.addNode(peach, 56); // bs = | pear, 78 | peach, 56 |
			bs.addNode(pear, 78);
			as.append(bs); // | peach, 56 | pear, 78 | banana, 34 | apple,12 |
			Vertex* bananaHuh = as.pop();
			Vertex* appleHuh = as.pop();
			Vertex* pearHuh = as.pop();
			Vertex* peachHuh = as.pop();
			Assert::AreEqual(apple, appleHuh->name);
			Assert::AreEqual(12, appleHuh->weight);
		}

		TEST_METHOD(Append6)
		{
			Vertices as = Vertices();
			Vertices bs = Vertices();
			std::string apple = "Apple";
			std::string banana = "Banana";
			std::string peach = "Peach";
			std::string pear = "Pear";
			as.addNode(apple, 12);
			as.addNode(banana, 34); // as = | banana,34 | apple,12 |
			bs.addNode(peach, 56); // bs = | pear, 78 | peach, 56 |
			bs.addNode(pear, 78);
			as.append(bs); // | peach, 56 | pear, 78 | banana, 34 | apple,12 |
			Vertex* bananaHuh = as.pop();
			Vertex* appleHuh = as.pop();
			Vertex* peachHuh = as.pop();
			Vertex* pearHuh = as.pop();
			Assert::AreEqual(banana, bananaHuh->name);
			Assert::AreEqual(34, bananaHuh->weight);
		}
		TEST_METHOD(PopTest1)
		{
			Vertices test = Vertices();
			std::string honey = "Honey";
			test.addNode(honey, 122);
			Vertex * a = test.pop();
			Assert::AreEqual(honey, a->name);
			Assert::AreEqual(122, a->weight);
		}


		TEST_METHOD(PopTest2)
		{
			Vertices test = Vertices();
			std::string honey = "Honey";
			test.addNode(honey, 122);
			Vertex * a = test.pop();
			Assert::AreEqual(0, test.length());
		}


		TEST_METHOD(PopTest3)
		{
			Vertices test = Vertices();
			std::string honey = "Honey";
			std::string bbq = "BBQ";
			test.addNode(honey, 122);
			test.addNode(bbq, 65);
			Vertex * a = test.pop();
			Assert::AreEqual(65, a->weight);
			Assert::AreEqual(bbq, a->name);
		}

	
		TEST_METHOD(PopTest4)
		{
			Vertices test = Vertices();
			std::string honey = "Honey";
			std::string bbq = "BBQ";
			test.addNode(honey, 122);
			test.addNode(bbq, 65);
			Assert::AreEqual(2, test.length());
			Vertex * a = test.pop();
			Assert::AreEqual(1, test.length());
			Vertex * b = test.pop();
			Assert::AreEqual(0, test.length());
		}

		TEST_METHOD(PopTest5)
		{
			Vertices test = Vertices();
			std::string honey = "Honey";
			std::string bbq = "BBQ";
			test.addNode(honey, 122);
			test.addNode(bbq, 65);
			Vertex * a = test.pop(); // first pop returns the second element added
			Vertex * b = test.pop(); // second pop returns the first element added 
			Assert::AreEqual(122, b->weight);
			Assert::AreEqual(honey, b->name);
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
			fresh.addNode("water", 1);
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
			fresh.addNode("dog", 1);
			std::string dog = "dog";
			Assert::AreEqual(dog, fresh.peek());
			//Assert::IsTrue(fresh.contains("dog"));
		}


		TEST_METHOD(ContainsTest2)
		{
			Vertices fresh = Vertices();
			fresh.addNode("dog", 1);
			std::string dog = "dog";
			Assert::IsTrue(fresh.contains(dog));
		}

		TEST_METHOD(ContainsTest3)
		{
			Vertices fresh = Vertices();
			fresh.addNode("dog", 1);
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
			fresh.addNode("Seattle", 24);
			Assert::AreEqual(fresh.length(), 1);
		}


		TEST_METHOD(LengthTest3)
		{
			Vertices fresh = Vertices();
			fresh.addNode("Seattle", 24);
			fresh.addNode("Boise", 4);
			Assert::AreEqual(2, fresh.length());
		}

		TEST_METHOD(LengthTest4)
		{
			Vertices fresh = Vertices();
			fresh.addNode("Seattle", 24);
			fresh.addNode("Boise", 4);
			fresh.contains("Seattle");
			Assert::AreEqual(2, fresh.length());
		}
	};
}
