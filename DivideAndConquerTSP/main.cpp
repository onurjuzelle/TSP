#include "city.h"
#include "algorithms.h"
#include <iostream>
#include <chrono>
#include <deque>

using namespace std;

int main(int argc, char * argv[])
{
    
    auto start = chrono::system_clock::now();
	
    srand(time(0));  
    
    tsp test(argv[1]);             
    test.divide_conquer();       
    
    auto end = chrono::system_clock::now();
	chrono::duration<double> elapsedSeconds = end - start;
    
    cout<< " --------------------------------------- "<< endl;
    cout<< "| Divide and Conquer Algorithm Solution | "<< endl;
    cout<< " --------------------------------------- "<< endl;
	cout<< endl;
    cout<<"Run time is: "<< elapsedSeconds.count() <<endl;
	
    ifstream f("sol.txt");
    if (f.is_open())
        cout << f.rdbuf();
		cout<< endl;
		cout<< endl;
    
    return 0;
}
