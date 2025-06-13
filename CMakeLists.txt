cmake_minimum_required(VERSION 3.31)
project(MyTinySTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyTinySTL main.cpp
        Algorithms/Algorithm.h

        Containers/Bitset.h
        Containers/Deque.h
        Containers/ForwardList.h
        Containers/List.h
        Containers/Map.h
        Containers/Pair.h
        Containers/PriorityQueue.h
        Containers/Queue.h
        Containers/Set.h
        Containers/Stack.h
        Containers/String.h
        Containers/String.cpp
        Containers/UnorderedMap.h
        Containers/UnorderedSet.h
        Containers/Vector.h


        DataStructures/AdjacencyList.h
        DataStructures/AdjacencyList.cpp
        DataStructures/AdjacencyMatrix.h
        DataStructures/AVL.cpp
        DataStructures/AVL.h
        DataStructures/BST.cpp
        DataStructures/BST.h
        DataStructures/HashTable.h
        DataStructures/Huffman_Tree.h
        DataStructures/Huffman_Tree.cpp
        DataStructures/RedBlackTree.h


        Memory/Memory.h
        Memory/SharedPtr.h
        Memory/UniquePtr.h
        Memory/WeakPtr.h


        OtherClasses/Allocator.h
        OtherClasses/Any.h
)
