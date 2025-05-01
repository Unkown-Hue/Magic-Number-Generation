# Magic-Number-Generation

# V1
Generates magic numbers for rooks and bishops. I am trying to make it fast by making everything I can constexpr. I still have more to make constexpr.

# V2
I made the bishop generation into a constexpr array.

# V3 
I changed the random number generator to do less calculation speeding up the magic number generation. compiled with the command "g++ -std=c++23 -O3 main.cpp -o main.exe"

# V4
threaded generation. the other 4v was a failure -__-.

# V5 
better candidate number generation and few tweeks