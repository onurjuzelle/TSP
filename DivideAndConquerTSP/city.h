#ifndef _city_h
#define _city_h

#include "math.h"
#include <fstream>
#include <vector>
#include <deque>


using namespace std;

class city
{
    public:
        city(int idin, int xin, int yin, int posin, bool visitedin);
        city(city & source);
        ~city();
        int dist(city * city_in); 
        int get_x(); 
        int get_y(); 
        int get_id(); 
        int get_pos(); 
        int get_nl_size(); 
        city *& get_list(int index); 
        int get_list_pos(int index); 
        void set_pos(int pos_in); 
        void display_coords(); 
        void output_id(ostream & output); 
        int write_out(ofstream & write); 
        int copy_city(city * city_in); 
        int compare(const city * city_in); 
        void build_list(deque <city*> & cities, int num_cities); 
        void push_to_list(city *& to_add); 
        bool nl_is_empty(); 
        void display_list(); 
    private:
        int id;
        int x;
        int y;
        int pos;
        bool visited;
        deque <city*> x_list; 
};

#endif
