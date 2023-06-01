#include "graph.hpp"
#include <sstream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>

using namespace std;

/*
//customType for custom Type testing
struct customType {
    int m1;
    int m2;
    std::string m3;

    std::string id() const {
        std::stringstream ss;
        ss << m1 << m2 << m3;
        return ss.str();
    }

    customType() : m1(0), m2(0), m3("A") {}
    customType(int i1, int i2, std::string i3) : m1(i1), m2(i2), m3(i3) {}
    customType(const customType& other) : m1(other.m1), m2(other.m2), m3(other.m3) {}
    customType(customType& other) noexcept : m1(other.m1), m2(other.m2), m3(other.m3) {}
    customType& operator=(const customType& other) {
        if (this != &other) {
            m1 = other.m1;
            m2 = other.m2;
            m3 = other.m3;
        }
        return *this;
    }

    bool operator==(const customType& e2) const {
        return (id() == e2.id());
    }

    bool operator<(const customType& e2) const {
        return (id() < e2.id());
    }
};




//stream insertion overrider for customType
std::ostream& operator<<(std::ostream& os, const customType& obj) {
    os << obj.id();
    return os;
}
*/
/*

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
*/


//Constructor Tests
TEST(ConstructorTest, DefaultConstructor){
    Graph<int> G;
    EXPECT_EQ(0,G.size());
}

TEST(ConstructorTest, EmptyParameterizedConstructor){
    Graph<int> G = Graph<int>({},{});
    EXPECT_EQ(0,G.size());
}

TEST(ConstructorTest, NoEdgesParameterizedConstructor){
    Graph<int> G = Graph<int>({1,2,3},{});
    EXPECT_EQ(3,G.size());
}

TEST(ConstructorTest, NoVerticesParameterizedConstructor){
    Graph<int> G = Graph<int>({},{Edge<int>(1,2)});
    EXPECT_EQ(0,G.size());
}

TEST(ConstructorTest, ParameterizedConstructor){
    Graph<int> G = Graph<int>({1,2,3}, {Edge<int>(1,2),Edge<int>(2,1)});
    EXPECT_EQ(3,G.size());
}


//addVertex Tests
TEST(AddVertexTest, emptyGraph){
    Graph<int> G;
    G.addVertex(1);
    EXPECT_EQ(1,G.size());
}

TEST(AddVertexTest, nonEmptyGraph){
    Graph<int> G = Graph<int>({1},{});
    G.addVertex(2);
    EXPECT_EQ(2,G.size());
}

TEST(AddVertexTest, addDuplicate){
    Graph<int> G = Graph<int>({1},{});
    G.addVertex(1);
    EXPECT_EQ(1,G.size());
}



//addEdge Tests
TEST(AddEdgeTest, emptyGraph){
    Graph<int> G;
    G.addEdge(Edge<int>(1,2));
    EXPECT_EQ(0,G.getEdges().size());
}

TEST(AddEdgeTest, nonEmptyGraph){
    Graph<int> G = Graph<int>({1,2,3},{Edge<int>(2,1)});
    G.addEdge(Edge<int>(1,3));

    EXPECT_EQ(2,G.getEdges().size());
}

TEST(AddEdgeTest, addDuplicateEdge){
    Graph<int> G = Graph<int>({1,2,3},{Edge<int>(2,1)});
    G.addEdge(Edge<int>(2,1));
    EXPECT_EQ(1,G.getEdges().size());
}

TEST(AddEdgeTest, noMatchingVertices){
    Graph<int> G = Graph<int>({1,2,3},{Edge<int>(2,1)});
    G.addEdge(Edge<int>(4,5));
    EXPECT_EQ(1,G.getEdges().size());
}

TEST(AddEdgeTest, onlyOneVertex){
    Graph<int> G = Graph<int>({1},{});
    G.addEdge(Edge<int>(1,2));
    EXPECT_EQ(0,G.getEdges().size());
}


//removeVertex Tests
TEST(RemoveVertexTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(false,G.removeVertex(1));
}

TEST(RemoveVertexTest, nonEmptyGraph){
    Graph<int> G = Graph<int>({1,2,3,4},{Edge<int>(1,4)});
    EXPECT_EQ(true,G.removeVertex(1));
}

TEST(RemoveVertexTest, noMatchingVertex){
    Graph<int> G = Graph<int>({1,2,3,4}, {Edge<int>(1,4)});
    EXPECT_EQ(false,G.removeVertex(0));
}

TEST(RemoveVertexTest, noMatchingEdges){
    Graph<int> G = Graph<int>({1,2,3,4}, {Edge<int>(4,3)});
    G.removeVertex(1);
    EXPECT_EQ(1, G.getEdges().size());
}

TEST(RemoveVertexTest, matchingEdges){
    Graph<int> G = Graph<int>({1,2,3,4},{Edge<int>(4,3)});
    G.removeVertex(4);
    EXPECT_EQ(0,G.getEdges().size());
}



//removeEdge Tests
TEST(RemoveEdgeTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(false, G.removeEdge(Edge<int>(5,4)));
}

TEST(RemoveEdgeTest, emptyEdgeSet){
    Graph<int> G = Graph<int>({1,2,3,4}, {});
    EXPECT_EQ(false, G.removeEdge(Edge<int>(4,1)));
}

TEST(RemoveEdgeTest, matchingEdges){
    Graph<int> G = Graph<int>({1,2},{Edge<int>(1,2)});
    EXPECT_EQ(true, G.removeEdge(Edge<int>(2,1)));
    EXPECT_EQ(0,G.getEdges().size());
}

TEST(RemoveEdgeTest, nonMatchingEdges){
    Graph<int> G = Graph<int>({1,2,3},{Edge<int>(1,2)});
    EXPECT_EQ(false,G.removeEdge(Edge<int>(2,3)));
    EXPECT_EQ(1,G.getEdges().size());
}

//getNeighbours Tests
TEST(GetNeighboursTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(vector<int>(),G.getNeighbours(1));
}

TEST(GetNeighboursTest, emptyNeighbourList){
    Graph<int> G = Graph<int>({1,2,3,4}, {Edge<int>(2,4)});
    EXPECT_EQ(0,G.getNeighbours(1).size());
}


TEST(GetNeighboursTest, nonEmptyNeighbourList){
    Graph<int> G = Graph<int>({1,2,3,4}, {Edge<int>(2,4)});
    EXPECT_EQ(1,G.getNeighbours(2).size());
    EXPECT_EQ(1,G.getNeighbours(4).size());
}

//getVertices Tests
TEST(GetVerticesTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(0,G.getVertices().size());
}

TEST(GetVerticesTest, nonEmptyGraph){
    Graph<int> G = Graph<int>({1,2,3,4}, {Edge<int>(2,4)});
    EXPECT_EQ(4,G.getVertices().size());
}

//hasEdge Tests
TEST(hasEdgeTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(false, G.hasEdge(Edge<int>(1,2)));
}

TEST(hasEdgeTest, matchingEdges){
    Graph<int> G = Graph<int>({1,2,3},{Edge<int>(1,2)});
    EXPECT_EQ(true,G.hasEdge(Edge<int>(1,2)));
    EXPECT_EQ(true,G.hasEdge(Edge<int>(2,1)));
}

TEST(hasEdgeTest, nonMatchingEdges){
    Graph<int> G = Graph<int>({1,2,3},{Edge<int>(1,2)});
    EXPECT_EQ(false,G.hasEdge(Edge<int>(2,3)));
    EXPECT_EQ(false,G.hasEdge(Edge<int>(3,2)));
}


//getEdges
TEST(getEdgesTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(0,G.getEdges().size());
}
TEST(getEdgesTest, nonEmptyGraph){
    Graph<int> G = Graph<int>({1,2,3,4}, {Edge<int>(2,4),Edge<int>(2,1),Edge<int>(2,3),Edge<int>(1,4)});
    
    EXPECT_EQ(4,G.getEdges().size());
}        



//directed add Edge
TEST(DirectedAddEdgeTest, emptyGraph){
    DirectedGraph<int> G;
    G.addEdge(Edge<int>(1,2));
    EXPECT_EQ(0,G.getEdges().size());
}

TEST(DirectedAddEdgeTest, nonEmptyGraph){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3},{Edge<int>(2,1)});
    G.addEdge(Edge<int>(1,3));
    G.addEdge(Edge<int>(3,1));
    EXPECT_EQ(3,G.getEdges().size());
}

TEST(DirectedAddEdgeTest, addDuplicateEdge){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3},{Edge<int>(2,1)});
    G.addEdge(Edge<int>(2,1));
    EXPECT_EQ(1,G.getEdges().size());
}

TEST(DirectedAddEdgeTest, noMatchingVertices){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3},{Edge<int>(2,1)});
    G.addEdge(Edge<int>(4,5));
    EXPECT_EQ(1,G.getEdges().size());
}

TEST(DirectedAddEdgeTest, onlyOneVertex){
    DirectedGraph<int> G = DirectedGraph<int>({1},{});
    G.addEdge(Edge<int>(1,2));
    EXPECT_EQ(0,G.getEdges().size());
}


//directed remove Edge
TEST(DirectedRemoveEdgeTest, emptyGraph){
    DirectedGraph<int> G = DirectedGraph<int>();
    EXPECT_EQ(false, G.removeEdge(Edge<int>(5,4)));
}

TEST(DirectedRemoveEdgeTest, emptyEdgeSet){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3,4}, {});
    EXPECT_EQ(false, G.removeEdge(Edge<int>(4,1)));
}

TEST(DirectedRemoveEdgeTest, matchingEdges){
    DirectedGraph<int> G = DirectedGraph<int>({1,2},{Edge<int>(1,2)});
    EXPECT_EQ(true, G.removeEdge(Edge<int>(1,2)));
    EXPECT_EQ(0,G.getEdges().size());
}

TEST(DirectedRemoveEdgeTest, nonMatchingEdges){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3},{Edge<int>(1,2)});
    EXPECT_EQ(false,G.removeEdge(Edge<int>(2,3)));
    EXPECT_EQ(1,G.getEdges().size());
}

TEST(DirectedRemoveEdgeTest, ConverseMatchingEdges){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3},{Edge<int>(1,2)});
    EXPECT_EQ(false,G.removeEdge(Edge<int>(2,1)));
    EXPECT_EQ(1,G.getEdges().size());
}

//directed get Edges
TEST(DirectedGetEdgesTest, emptyGraph){
    Graph<int> G = Graph<int>();
    EXPECT_EQ(0,G.getEdges().size());
}
TEST(DirectedGetEdgesTest, nonEmptyGraph){
    DirectedGraph<int> G = DirectedGraph<int>({1,2,3,4}, {
        Edge<int>(2,4),
        Edge<int>(2,1),
        Edge<int>(2,3),
        Edge<int>(1,4),
        Edge<int>(4,2),
        Edge<int>(1,2),
        Edge<int>(3,2),
        Edge<int>(4,1)});
    EXPECT_EQ(8,G.getEdges().size());
}        




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}