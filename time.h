#pragma once

#include <iostream>
#include <chrono>

class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
public:
    Timer() {
        time_start();
    }

    ~Timer() {
        time_end();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
		if((duration / 1000) > 1000){
        	std::cout << "Elapsed time: " << (duration /= 1000)  << " ms" << std::endl;
		}
		else{
			std::cout << "Elapsed time: " << duration << " mc" << std::endl;
		}
        
    }

    void time_start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void time_end() {
        end_time = std::chrono::high_resolution_clock::now();
    }
};
