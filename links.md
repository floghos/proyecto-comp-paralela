* Graph libraries:
https://softwarerecs.stackexchange.com/questions/30347/a-modernish-c-graph-representation-and-manipulation-library

* Intro to BoostGraph lib:
https://medium.com/@alinakipoglu/modelling-word-relationships-in-c-and-boost-graph-library-1115ecc14525

* On large graph representation:
https://www.quora.com/What-is-the-most-efficient-way-to-represent-a-graph-with-million-nodes

* C++ adjacency list graph implementation:
https://www.techiedelight.com/graph-implementation-using-stl/

* Graph visualizer & solver:
https://graphonline.ru/en/create_graph_by_matrix

* Random simple connected graph generation with given sparseness:
https://stackoverflow.com/questions/2041517/random-simple-connected-graph-generation-with-given-sparseness

* A* resources:
    * Wiki pseudocode: https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode
    * python & C++ implementation: https://www.redblobgames.com/pathfinding/a-star/implementation.html
    *

* Profiling with Valgrind :
https://developer.mantidproject.org/ProfilingWithValgrind.html
    1. Compile with the -g flag like: $ g++ -g source.cpp
    2. Run: $ valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes <executable> [args...]
        2.1 Note: Use the executable's path, like so: ./<executable>
    3. To visualize with kcachegrind just run: $ kcachegrind callgrind.out.xxxx

* Compiling with multiple files:
    Now that I've split the code into different files, remember to add all relevant .cpp 's as arguments for the compiler, like so:
    $ g++ main.cpp Graph.cpp

* Implementing min-heaps with decrease-key function.
    https://www.baeldung.com/cs/min-heaps-decrease-key
