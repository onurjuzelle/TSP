#include "algorithms.h"
#include <iostream>
#include <deque>
#include <fstream>
#include <cstdlib>

using namespace std;

int done = 0;

tsp::tsp(const char * filename)
{
    num_cities = read_file(filename);
}

tsp::tsp(tsp & source)
{
    int size = source.original_list.size();
    for (int i = 0; i < size; ++i) 
    {
        original_list.push_back(new city(*source.original_list[i]));
    }

    size = source.solution.size();

    for (int i = 0; i < size; ++i) 
    {
        solution.push_back(new city(*source.solution[i]));
    }

    num_cities = source.num_cities;
}

tsp::~tsp()
{
    original_list.clear();
    solution.clear();
}

int tsp::read_file(const char * filename)
{
    int added = 0;
    int id_read = 0;
    int x_read = 0;
    int y_read = 0;

    original_list.clear();
    ifstream read(filename); 

    if (!read)
    {
        cout << "error";
        return 0; 
    }

    while (read>>id_read>>x_read>>y_read) 
    {
        original_list.push_back(new city(id_read, x_read, y_read, id_read, false));
        ++added;
    }

    read.close();
    return added;
}

int tsp::brute_force_wrapper()
{
    int distance = 0;
    int min_distance = 9999999;
    deque <city*> best_path;

    if (solution.empty())
        divide_conquer_basic(0);

    brute_force(best_path, min_distance, num_cities);
    copy_city_deque(best_path, solution); 

    distance = get_solution_distance();
    write_solution("bruteforce.txt");
    return distance;
}

void tsp::brute_force(deque <city*> & best_path, int & min_distance, int cities_left)
{
    int current_dist = 0;

    signal(SIGTERM, end_opt);
    for (int i = 0; !done && i < cities_left; ++i)
    {
        rotate(cities_left-1);
        current_dist = get_solution_distance();
        if (current_dist < min_distance)
        {
            min_distance = current_dist;
            cout << min_distance << endl;
            copy_city_deque(solution, best_path);
        }

        brute_force(best_path, min_distance, cities_left - 1); // shift ending position of rotation left 1 in each recursion

    }

   return;
}

void tsp::rotate(int pos)
{
    solution.push_front(solution[pos]);
    solution.erase(solution.begin() + pos+1);

    return;
}

int tsp::divide_conquer()
{
    solution.clear();
    int total_dist = 0;
    int best_start_distance = 9999999;
    int last_run = 0;

    for (int i = 0; !done && i < num_cities; ++i)
    {
        divide_conquer_basic(i);
        last_run = two_change();
        if (last_run < best_start_distance)
        {
            best_start_distance = last_run;
            write_solution(OUTPUT_FN);  
        }
    }

    total_dist = get_solution_distance();
    if (best_start_distance <= total_dist)
        return best_start_distance;     

    else
    {
        
        write_solution(OUTPUT_FN);       
        return best_start_distance;
    }
}

int tsp::divide_conquer_basic(int start_index)
{
    int cities_added = 0;
    int closest = 9999999;
    int total_dist = 0;
    int current_dist = 0;
    int closest_index = 0;
    int current_num = num_cities;
    deque <city*> temp;
    copy_city_deque(original_list, temp);      

    solution.clear();
    solution.push_back(original_list[start_index]);    
    original_list.erase(original_list.begin() + start_index);    
    --current_num;       
    ++cities_added;     
    while(current_num != 0)      
    {
        closest = 9999999;  
        for (int i = 0; i < current_num; ++i)
        {
            current_dist = original_list[i]->dist(solution[cities_added-1]);
            if (current_dist < closest)
            {
                closest_index = i;
                closest = current_dist;
            }
        }

        total_dist += closest;
        solution.push_back(original_list[closest_index]);
        original_list.erase(original_list.begin() + closest_index);

        --current_num;
        ++cities_added;
    }

    copy_city_deque(temp, original_list);       
    return total_dist + solution[0]->dist(solution[cities_added-1]);
}


int tsp::two_change()
{
    deque <city*> new_path;
    int min_distance = get_solution_distance();
    bool start_over = false;

    signal(SIGTERM, end_opt);  
    while(!done)
    {
        start_over = false;
        for (int i = 1; i < num_cities && !start_over; ++i)
        {
            for (int j = i+1; j < num_cities-1 && !start_over; ++j)
            {
                
                if (solution[i-1]->dist(solution[j]) + solution[i]->dist(solution[j+1]) < solution[i-1]->dist(solution[i]) + solution[j]->dist(solution[j+1]))
                {
                    swap_two(i, j);
                    min_distance = get_solution_distance();
                    start_over = true;
                }

                else
                    start_over = false;
            }
         }

         if (!start_over)
            break;
    }
    return min_distance;
}

int tsp::swap_two(int i, int k)
{
    deque <city*> temp;
    int count = 0;

    for (int x = k; x >= i; --x)
    {
        temp.push_back(solution[x]);
    }

    for (int x = i; x <= k; ++x)
    {
        solution[x] = temp[count];
        ++count;
    }
    temp.clear();
    
    return 1;
}


int tsp::get_solution_distance()
{
    int total_dist = 0;
    for (int i = 0; i < num_cities - 1; ++i)
    {
        total_dist += solution[i]->dist(solution[i+1]);
    }

    total_dist += solution[0]->dist(solution[num_cities-1]);
    return total_dist;
}


void tsp::write_solution(const char * file_name)
{
    int distance = get_solution_distance();
    ofstream write(file_name);
    if (write.is_open())
    {
        write << '\n';
        write << "Shortest Path Distance: ";
        write << distance << '\n';
        write << '\n';
        write <<"Shortest Path is: " <<'\n';
        write << '\n';
    }

    for (int i = 0; i < num_cities; ++i)
    {
        solution[i]->write_out(write);
    }

    write.close();

    return;
}


void tsp::display_lists()
{
    for (int i = 0; i < num_cities; ++i)
    {
        cout << "LIST " << i << endl;
        solution[i]->display_list();
    }

    return;
}


void tsp::fix_positions()
{
    for (int i = 0; i < num_cities; ++i)
    {
        solution[i]->set_pos(i);
    }
}


void copy_city_deque(deque <city*> & source, deque <city*> & dest)
{
    int length = source.size();
    dest.clear();
    for (int i = 0; i < length; ++i)
    {
        dest.push_back(new city(*source[i]));
    }
}

void end_opt(int signum)
{
    cout << "\nOut of time\n";
    done = 1;
}
