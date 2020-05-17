#ifndef _algorithms_h
#define _algorithms_h
#include <deque>
#include <fstream>
#include "city.h"
#include <vector>
#include <signal.h>

using namespace std;

const char OUTPUT_FN[] = "sol.txt";

class tsp
{
    public:
        tsp(const char * filename); 
        tsp(tsp & source);
        ~tsp();
        int read_file(const char * filename); 
        void write_solution(const char * file_name);
        int brute_force_wrapper(); 
        int divide_conquer(); 
        int divide_conquer_basic(int start_index); 
        int two_change(); 
        int two_opt(); 
        int swap_two(int i, int k); 
        int get_solution_distance(); 
        void display_lists(); 
        void fix_positions(); 
        void rotate(int pos); 
    private:
        void brute_force(deque <city*> & best_path, int & min_distance, int cities_left); 
        deque <city*> original_list; 
        deque <city*> solution; 
        int num_cities; 
};

void copy_city_deque(deque <city*> & source, deque <city*> & dest); 
void end_opt(int signum); 
#endif
