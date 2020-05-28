# Traveling Salesman Problem

 A solution to the TSP using different heuristic algorithms.
 
 - Input format is, identifier of the location and 2D Coordinates of the locations
 
 Example:
 

     1 4379, 6392
     2 5848, 2012
     3 2048, 2910
     .   .    .
     .   .    .
     .   .    .
     .   .    . `


- ##  Nearest Neigbor Algorithm

Open a new terminal 

- Make sure cmake is installed, navigate to the folder which contains the source code 

```cd [Path to the folder]```

- Use the command ```make``` to compile the code 

- Use the command ```./nearestNeighbourTSP Input.txt``` to run the code

```./[Program_Name] [Input_File_Name]```

- ## Opt-Nearest Neigbor Algorithm

This algorithm is the optimized version of the Nearest Neigbor Algorithm in order to find the shortest path possible. It takes the shortest path distance from the user as a parameter and generates tours until the distance is smaller than the distance provided by the user 

Open a new terminal 

- Make sure cmake is installed, navigate to the folder which contains the source code 

```cd [Path to the folder]```

- Use the command ```make all``` to compile the code 

- Use the command ```./tsp Input.txt 33250``` to run the code

```./[Program_Name] [Input_File_Name] [Shortest_Tour_Number]```

- ##  Greedy Algorithm

Open a new terminal 

- Make sure cmake is installed, navigate to the folder which contains the source code 

```cd [Path to the folder]```

- Use the command ```make``` to compile the code 

- Use the command ```./GreedyTSP Input.txt``` to run the code

```./[Program_Name] [Input_File_Name]```

- ##  Tour Visualization

Tour visualization is implemented separately using ```python``` and ```OpenCV``` 

To visualize the tour follow the steps below, 

- Fill in the ```x_axis=[]``` with the coordinate on the x axis as shown; ```x_axis = [0,8,37,30,43,17......]```

- Fill in the ```y_axis=[]``` with the coordinate on the y axis as shown; ```y_axis = [10,18,7,3,41,72......]```

- After filling the coordinates on the x-y axis insert the tour path to the one of the tour variables as shown ```tour# = [0,2,1,3,4,5,6.....]```

- Add the tours thta you want to visualize you can add multiple tours for comparison or add only one for checking the path as shown, ```tours = [tour#, tour# ......]```

- Depending the number of tours change the number parameter in the ```plot(tours, point, 1)``` 

- Finally use the command ```python plot.py``` to run the code 

Example Output: 

- #### Single Tour  

<img src="https://github.com/onurjuzelle/TSP/blob/master/Tour%20Visualization/neartour_.jpg" width="320" height="300"/>

- #### Multiple Tour

<img 
src="https://github.com/onurjuzelle/TSP/blob/master/Tour%20Visualization/tourcomp_.jpg" width="320" height="300"/>

