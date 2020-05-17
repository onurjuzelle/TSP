#include "city.h"
#include "tree.h"
#include <iostream>
#include <fstream>
using namespace std;

const int LIST_SIZE = 5;


city::city(int idin, int xin, int yin, int posin, bool visitedin) : id(idin), x(xin), y(yin), pos(posin), visited(visitedin) {}


city::city(city & source)
{
    x = source.x;
    y = source.y;
    pos = source.pos;
    id = source.id;
    visited = source.visited;
    x_list = source.x_list;
}

city::~city()
{
}

int city::dist(city * city_in)
{
    float x2 = city_in->get_x();
    float y2 = city_in->get_y();
    
    x2 -= x;
    y2 -= y;
    
    x2 *= x2;
    y2 *= y2;
    
    return floor(sqrt(x2 + y2) + 0.5); 
}

int city::get_x()
{
    return x;
}

int city::get_y()
{
    return y;
}

int city::get_id()
{
    return id;
}

int city::get_pos()
{
    return pos;
}

city *& city::get_list(int index)
{
    return x_list[index];
}

int city::get_nl_size()
{
    return LIST_SIZE;
}

void city::set_pos(int pos_in)
{
    pos = pos_in;
}

void city::display_coords()
{
    cout << id << " " << x << " " << y;
    return;
}

void city::output_id(ostream & output)
{
    output << id;
}


int city::write_out(ofstream & write)
{
    if (write.is_open())
    {
        write << id << "--";
        return 1;
    }
    
    return 0;
}


int city::copy_city(city * city_in)
{
    if (city_in == NULL)
    {
        return 0;
    }
        
    id = city_in->id;
    x = city_in->x;
    y = city_in->y;
    pos = city_in->pos;
    visited = city_in->visited;
    
    x_list = city_in->x_list;
    return 1;
}

int city::compare(const city * city_in)
{
    if (city_in->id == id && city_in->x == x && city_in->y == y)
    {
        return 1;
    }
        
    return 0;
}


void city::build_list(deque <city*> & cities, int num_cities)
{
    tree sorted(this); 
    x_list.clear(); 
    
    for (int i = 0; i < num_cities; ++i)
    {
        sorted += cities[i]; 
    }
    
    
    if (LIST_SIZE < num_cities)
    {
        sorted.build_list(x_list, LIST_SIZE);       
    }
        
    else
    {
        sorted.build_list(x_list, num_cities);
    }

    cout << pos << "LIST SIZE: " << x_list.size() << endl;
    sorted.clear_tree();

    return;
}

bool city::nl_is_empty()
{
    return x_list.empty();
}

void city::push_to_list(city *& to_add)
{
    x_list.push_back(new city(*to_add));
}

void city::display_list()
{
    int size = x_list.size();
    
    for (int i = 0; i < size; ++i)
    {
        cout << dist(x_list[i]);
        cout << "actual index: " << i;
        cout << " stored pos: " << x_list[i]->get_pos();
        cout << endl;
    }
    
    return;
}

int city::get_list_pos(int index)
{
    return x_list[index]->pos;
}

