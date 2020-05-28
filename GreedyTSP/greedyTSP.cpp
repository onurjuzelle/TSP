// CMP3004 - Formal Languages and Automata Theory Term Project by Onur Guzel
// TSP Greedy Algorithm Implementation

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <tuple>
#include <ctime>
using namespace std;


struct CityDistance{
	int city;
	int nextCity;
	int distanceToCity;
	CityDistance(){};
	CityDistance(int c, int nc, int dTC)
	{
		city = c;
		nextCity = nc;
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



CityDistancePQ loadGraphOfMapAsPriorityQueue(char* dataInputFileName)
{
	ifstream inputData1, inputData2;
	if(dataInputFileName == nullptr){
        cout << "\nMust enter file name when running program." << endl
             << "Type './greedyTSP file.txt' in command line," << endl
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
	CityDistancePQ graph;
	string line;

	
	int i = 0;
	bool cityCountEstablished = false;
	int cityCount = 0;
	do
	{
	    getline(inputData1, line);
        int startingCity, startingCityX, startingCityY;
        istringstream iss(line);
        iss >> startingCity >> startingCityX >> startingCityY;
		while(getline(inputData2, line))
        {
            int city, cityX, cityY;
            istringstream iss(line);
            iss >> city >> cityX >> cityY;
            int distanceToCity =
                static_cast<int>(round(sqrt(pow(static_cast<double>(cityX) - static_cast<double>(startingCityX), 2) +
                                             pow(static_cast<double>(cityY) - static_cast<double>(startingCityY), 2))));
            graph.push(CityDistance(startingCity, city, distanceToCity));
			if(!cityCountEstablished)
			{
				cityCount++;
			}
        }
		cityCountEstablished = true;
        inputData2.clear();
        inputData2.seekg(0, ios::beg);
        i++;
	} while(i < cityCount);
	inputData1.close();
	inputData2.close();

	return graph;
}


vector<vector<int>> loadGraphOfMapAsVectors(char* dataInputFileName)
{
	ifstream inputData1, inputData2;
	if(dataInputFileName == nullptr){
        cout << "\nMust enter file name when running program." << endl
             << "Type './greedyTSP file.txt' in command line," << endl
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


void printLoaded(vector<CityDistancePQ>& v)
{
	for(int i = 0; i < static_cast<int>(v.size()); i++)
	{
		while(!v[i].empty())
		{
			cout << v[i].top().city << " " << v[i].top().distanceToCity << endl;
			v[i].pop();
		}
	}
}


tuple<int, vector<int>> loadTour(CityDistancePQ& graph)
{
	int cityCount = sqrt(graph.size());
    tuple<int, vector<int>> tspTour;

	
	vector<tuple<bool, int, int>> cityTourPositionTracker;
	for(int i = 0; i < cityCount; i++)
	{
		cityTourPositionTracker.push_back(make_tuple(false, -1, -1));
	}

	int distance = 0;
    for(int i = 0; i < cityCount; i++)
    {
		bool edgeAdded = false;
		while(!edgeAdded)
		{
			
			while(get<0>(cityTourPositionTracker[graph.top().city]) == true ||
				  get<2>(cityTourPositionTracker[graph.top().nextCity]) != -1 ||
                  graph.top().city == graph.top().nextCity)
			{
				graph.pop();
			}
			
			int downstreamCity = graph.top().nextCity;
			bool edgeCreatesCycle = false;

            
			while(get<0>(cityTourPositionTracker[downstreamCity]) == true &&
					get<1>(cityTourPositionTracker[downstreamCity]) != -1 && i < cityCount - 1)
			{
				downstreamCity = get<1>(cityTourPositionTracker[downstreamCity]);
				if(downstreamCity == graph.top().city)
				{
					graph.pop();
					edgeCreatesCycle = true;
					break;
				}
			}

			if(!edgeCreatesCycle)
			{
				get<0>(cityTourPositionTracker[graph.top().city]) = true;
				get<1>(cityTourPositionTracker[graph.top().city]) = graph.top().nextCity;
				get<2>(cityTourPositionTracker[graph.top().nextCity]) = graph.top().city;
				distance += graph.top().distanceToCity;
				graph.pop();
				edgeAdded = true;
			}
		}
	}
	for(int i = 0, j = 0; i < cityCount; i++)
	{
		get<1>(tspTour).push_back(j);
		j = get<1>(cityTourPositionTracker[j]);
	}
	get<0>(tspTour) = distance;

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
	CityDistancePQ graph1 = loadGraphOfMapAsPriorityQueue(argv[1]);
	
	tuple<int, vector<int>> tspTour = loadTour(graph1);

	
	CityDistancePQ().swap(graph1);

	vector<vector<int>> graph2 = loadGraphOfMapAsVectors(argv[1]);
	twoOptImprove(tspTour, graph2);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<< " --------------------------- "<< endl;
    cout<< "| Greedy Algorithm Solution | "<< endl;
    cout<< " --------------------------- "<< endl;
    cout<<endl;
    cout<< "Run Time: " << elapsed_secs << endl;
    cout<<endl;
    cout<< "Shortest Path Distance: "<< get<0>(tspTour) << "\n" << endl;
    cout<< "Shortest Path is: "<< endl;
    
	cout<<endl;
    for(int i = 0; i < static_cast<int>(get<1>(tspTour).size()); i++)
    {
        cout<< get<1>(tspTour)[i] << "--";
    }
    
    cout<< endl;
    cout<< endl;    
}
