# Magic-Number-Generation

# V1
Generates magic numbers for rooks and bishops. I am trying to make it fast by making everything I can constexpr. I still have more to make constexpr.

# V2
I made the bishop generation into a constexpr array.

# V3 
I changed the random number generator to do less calculation speeding up the magic number generation. compiled with the command "g++ -std=c++23 -O3 main.cpp -o main.exe"

# V4
<<<<<<< HEAD
threaded generation. the other 4v was a failure -__-.
=======
unrolled some loops to make use of more constexpr values. I have not verified if this works. Its suspiciously fast
>>>>>>> fc6dc0d829b206e49284c27d5af64fd04f847a71
