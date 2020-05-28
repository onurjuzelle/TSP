// CMP3004 - Formal Languages and Automata Theory Term Project by Onur Guzel
// TSP Greedy Algorithm Implementation

#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <tuple>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std; 

struct CityDistance{
	int city;
	int distanceToCity;
	CityDistance(int c, int dTC)
	{
		city = c;
		distanceToCity = dTC;
	}
};


class myComparator
{
public:
    int operator() (const CityDistance& c1, const CityDistance& c2)
    {
        return c1.distanceToCity > c2.distanceToCity;
    }
};

typedef priority_queue<CityDistance, vector<CityDistance>, myComparator> CityDistancePQ;


vector<CityDistancePQ> loadGraphOfMapAsMinHeaps(char* dataInputFileName)
{
	ifstream inputData1, inputData2;
	if(dataInputFileName == nullptr){
        cout << "\nMust enter file name when running program." << endl
             << "Type './nearestNeighborTSP [filename]' in command line," << endl
             << "replacing 'file.txt' with the name of your file.\n" << endl;
        exit(1);
    }
    try{
        inputData1.open(dataInputFileName);
        inputData1.exceptions (ifstream::failbit | ifstream::badbit);
    }
    catch(ifstream::failure e){
        cerr << "\nFile cannot be found or opened.\n" << endl;
        exit(1);
    }
    inputData2.open(dataInputFileName);
	vector<CityDistancePQ> graph;
	string line;

	
	int i = 0;
	do
	{
	    getline(inputData1, line);
        int startingCity, startingCityX, startingCityY;
        istringstream iss(line);
        iss >> startingCity >> startingCityX >> startingCityY;
        CityDistancePQ pq;
        while(getline(inputData2, line))
        {
            int city, cityX, cityY;
            istringstream iss(line);
            iss >> city >> cityX >> cityY;
            int distanceToCity =
                static_cast<int>(round(sqrt(pow(static_cast<double>(cityX) - static_cast<double>(startingCityX), 2) +
                                             pow(static_cast<double>(cityY) - static_cast<double>(startingCityY), 2))));
            pq.push(CityDistance(city, distanceToCity));
        }
        graph.push_back(pq);
        inputData2.clear();
        inputData2.seekg(0, ios::beg);
        i++;
	} while(i < static_cast<int>(graph[0].size()));
	inputData1.close();
	inputData2.close();

	return graph;
}


vector<vector<int>> loadGraphOfMapAsVectors(char* dataInputFileName)
{
	ifstream inputData1, inputData2;
	if(dataInputFileName == nullptr){
        cout << "\nMust enter file name when running program." << endl
             << "c" << endl
             << "replacing '[filename]' with the name of your file.\n" << endl;
        exit(1);
    }
    try{
        inputData1.open(dataInputFileName);
        inputData1.exceptions (ifstream::failbit | ifstream::badbit);
    }
    catch(ifstream::failure e){
        cerr << "\nFile cannot be found or opened.\n" << endl;
        exit(1);
    }
    inputData2.open(dataInputFileName);
	vector<vector<int>> graph;
	string line;

	
	int i = 0;
	do
	{
	    getline(inputData1, line);
        int startingCity, startingCityX, startingCityY;
        istringstream iss(line);
        iss >> startingCity >> startingCityX >> startingCityY;
        vector<int> v;
        while(getline(inputData2, line))
        {
            int city, cityX, cityY;
            istringstream iss(line);
            iss >> city >> cityX >> cityY;
            int distanceToCity =
                static_cast<int>(round(sqrt(pow(static_cast<double>(cityX) - static_cast<double>(startingCityX), 2) +
                                             pow(static_cast<double>(cityY) - static_cast<double>(startingCityY), 2))));
            v.push_back(distanceToCity);
        }
        graph.push_back(v);
        inputData2.clear();
        inputData2.seekg(0, ios::beg);
        i++;
	} while(i < static_cast<int>(graph[0].size()));
	inputData1.close();
	inputData2.close();

	return graph;
}



tuple<int, vector<int>> loadTour(vector<CityDistancePQ>& graph)
{
    tuple<int, vector<int>> tspTour;
    int distance = 0;
    vector<int> tspTourCities;
    int i, j;
    for(i = 0, j = 0; j < static_cast<int>(graph.size()); j++)
    {
		
        while(find(tspTourCities.begin(), tspTourCities.end(),
                   graph[i].top().city) != tspTourCities.end())
        {
            graph[i].pop();
        }
		
        tspTourCities.push_back(graph[i].top().city);
        distance += graph[i].top().distanceToCity;
        
		i = graph[i].top().city;
    }

    
    while(graph[0].top().city != i)
    {
        graph[0].pop();
    }
    get<0>(tspTour) = distance + graph[0].top().distanceToCity;     
    get<1>(tspTour) = tspTourCities;

    return tspTour;

}


void twoOptImprove(tuple<int, vector<int>> &tspTour,
                   vector<vector<int>> &graph)
{
	
	bool breakOutToOptimize;
	bool nExceeds2500;
	bool improved;
	if(get<1>(tspTour).size() > 2500)
	{
		nExceeds2500 = true;
	}
	else
	{
		nExceeds2500 = false;
	}

    do
    {
		improved = false;
		breakOutToOptimize = false;
	
        for(int i = 1; i < static_cast<int>(get<1>(tspTour).size()) - 2 &&
				breakOutToOptimize == false; i++)		
        {	
            for(int j = i, k = i + 1; k < static_cast<int>(get<1>(tspTour).size()) &&
					breakOutToOptimize == false; k++)					
            {		
				
				if(k - j == 1)
				{
					continue;
				}
			
				
				if(graph[get<1>(tspTour)[j]][get<1>(tspTour)[k - 1]] +
				   graph[get<1>(tspTour)[j + 1]][get<1>(tspTour)[k]] <
				   graph[get<1>(tspTour)[j]][get<1>(tspTour)[j + 1]] +
				   graph[get<1>(tspTour)[k - 1]][get<1>(tspTour)[k]])
				{
					    
					
					get<0>(tspTour) -=  (graph[get<1>(tspTour)[j]][get<1>(tspTour)[j + 1]] +
										 graph[get<1>(tspTour)[k - 1]][get<1>(tspTour)[k]]) -
										(graph[get<1>(tspTour)[j]][get<1>(tspTour)[k - 1]] +
										 graph[get<1>(tspTour)[j + 1]][get<1>(tspTour)[k]]);
					
					improved = true;
					
					for(int l = j + 1, m = k - 1; l < m; l++, m--)
					{	
						int temp = get<1>(tspTour)[l];
						get<1>(tspTour)[l] = get<1>(tspTour)[m];
						get<1>(tspTour)[m] = temp;
					}
					
					if(!nExceeds2500)
					{
						breakOutToOptimize = true;
					}
				}
            }
        }
    }while(improved);
}

int main(int argc, char *argv[])
{
	clock_t begin = clock();
	vector<CityDistancePQ> graph1 = loadGraphOfMapAsMinHeaps(argv[1]);

	tuple<int, vector<int>> tspTour = loadTour(graph1);
	
	
	vector<CityDistancePQ>().swap(graph1);		
	
	vector<vector<int>> graph2 = loadGraphOfMapAsVectors(argv[1]);
	twoOptImprove(tspTour, graph2);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<< " -------------------------------------- "<< endl;
    cout<< "| Nearest Neighbour Algorithm Solution | "<< endl;
    cout<< " -------------------------------------- "<< endl;
    cout<<endl;
    cout<< "Run Time: " << elapsed_secs << endl;
    cout<<endl;
    cout<< "Shortest Path Distance: "<< get<0>(tspTour) << "\n" << endl;
    cout<< "Shortest Path is: "<< endl;
    
	cout<<endl;
    for(int i = 0; i < static_cast<int>(get<1>(tspTour).size()); i++)
    {
        cout << get<1>(tspTour)[i] << "--";
    }
    
    cout<<endl;
    cout<<endl;     
	
	return 0;
}
