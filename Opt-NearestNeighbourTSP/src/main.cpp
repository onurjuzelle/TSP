#include "header/axisgoal.h"
#include "header/tsp.h"
#include <iostream>

#define result "sol.txt"


using namespace std;

int main(int argc, char const *argv[])
{
    
	auto start = chrono::system_clock::now();

	mtsp m_tsp;
	if (argc >= 2 && argc <= 3){
		AxisGoal ag1(argv[1]);
		m_tsp.add_axisgoal(&ag1);
	 
		if (argc == 3){
			int limit = atoi(argv[2]);
			do {
				m_tsp.two_opt(ag1);
			} while (m_tsp.getSolutionCost(0) >= limit);
		} else {
			m_tsp.two_opt(ag1);
		}
		m_tsp.write_outfile(result);
	
	}
     auto end = chrono::system_clock::now();
     chrono::duration<double> elapsedSeconds = end - start;
     

    cout<< " ------------------------------------------- "<< endl;
    cout<< "| Nearest Neigbour Algorithm Exact Solution | "<< endl;
    cout<< " ------------------------------------------- "<< endl;
	cout<< endl;
    cout<<"Run time is: "<< elapsedSeconds.count() <<endl;
	cout<< endl;
    ifstream f("sol.txt");
    if (f.is_open())
        cout << f.rdbuf();
		cout<< endl;
		cout<< endl;
}