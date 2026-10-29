#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CITIES = 20;
const int INF = 1000000000;

class ShortestPathFinder {
private:
    string cities[MAX_CITIES];
    int distanceMatrix[MAX_CITIES][MAX_CITIES];
    int cityCount;

    int findCityIndex(const string& cityName) const {
        for (int i = 0; i < cityCount; i++) {
            if (cities[i] == cityName) {
                return i;
            }
        }
        return -1;
    }

public:
    ShortestPathFinder() {
        cityCount = 0;
        for (int i = 0; i < MAX_CITIES; i++) {
            for (int j = 0; j < MAX_CITIES; j++) {
                distanceMatrix[i][j] = (i == j) ? 0 : INF;
            }
        }
    }

    void addCity() {
        if (cityCount >= MAX_CITIES) {
            cout << "City limit reached. Maximum is " << MAX_CITIES << ".\n";
            return;
        }

        string name;
        cout << "Enter city name (no duplicate names): ";
        getline(cin >> ws, name);

        if (name.empty()) {
            cout << "City name cannot be empty.\n";
            return;
        }
        if (findCityIndex(name) != -1) {
            cout << "This city already exists.\n";
            return;
        }

        cities[cityCount] = name;
        cityCount++;
        cout << "City added successfully.\n";
    }

    void addRoad() {
        if (cityCount < 2) {
            cout << "Please add at least two cities first.\n";
            return;
        }

        string from, to;
        int km;
        cout << "Enter starting city: ";
        getline(cin >> ws, from);
        cout << "Enter destination city: ";
        getline(cin >> ws, to);

        int u = findCityIndex(from);
        int v = findCityIndex(to);

        if (u == -1 || v == -1) {
            cout << "One or both cities were not found. Check spelling.\n";
            return;
        }
        if (u == v) {
            cout << "A road must connect two different cities.\n";
            return;
        }

        cout << "Enter distance in km (positive number): ";
        if (!(cin >> km) || km <= 0) {
            cout << "Invalid distance. Please enter a positive integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        cin.ignore(10000, '\n');

        // Roads are assumed to be two-way, so store both directions.
        distanceMatrix[u][v] = km;
        distanceMatrix[v][u] = km;
        cout << "Road added/updated successfully.\n";
    }

    void displayCitiesAndRoads() const {
        if (cityCount == 0) {
            cout << "No cities have been added yet.\n";
            return;
        }

        cout << "\n--- Cities ---\n";
        for (int i = 0; i < cityCount; i++) {
            cout << i + 1 << ". " << cities[i] << '\n';
        }

        cout << "\n--- Roads (two-way) ---\n";
        bool foundRoad = false;
        for (int i = 0; i < cityCount; i++) {
            for (int j = i + 1; j < cityCount; j++) {
                if (distanceMatrix[i][j] != INF) {
                    cout << cities[i] << " <--> " << cities[j]
                         << " : " << distanceMatrix[i][j] << " km\n";
                    foundRoad = true;
                }
            }
        }
        if (!foundRoad) {
            cout << "No roads have been added yet.\n";
        }
    }

    void findShortestPath() const {
        if (cityCount < 2) {
            cout << "Please add at least two cities first.\n";
            return;
        }

        string sourceName, destinationName;
        cout << "Enter source city: ";
        getline(cin >> ws, sourceName);
        cout << "Enter destination city: ";
        getline(cin >> ws, destinationName);

        int source = findCityIndex(sourceName);
        int destination = findCityIndex(destinationName);

        if (source == -1 || destination == -1) {
            cout << "One or both cities were not found. Check spelling.\n";
            return;
        }

        int dist[MAX_CITIES];
        int parent[MAX_CITIES];
        bool visited[MAX_CITIES];

        for (int i = 0; i < cityCount; i++) {
            dist[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }
        dist[source] = 0;

        // Dijkstra's algorithm: repeatedly select the nearest unvisited city.
        for (int count = 0; count < cityCount; count++) {
            int u = -1;
            int bestDistance = INF;

            for (int i = 0; i < cityCount; i++) {
                if (!visited[i] && dist[i] < bestDistance) {
                    bestDistance = dist[i];
                    u = i;
                }
            }

            if (u == -1) {
                break; // Remaining cities cannot be reached from the source.
            }

            visited[u] = true;

            for (int v = 0; v < cityCount; v++) {
                if (!visited[v] && distanceMatrix[u][v] != INF &&
                    dist[u] + distanceMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + distanceMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        if (dist[destination] == INF) {
            cout << "No route exists between " << sourceName
                 << " and " << destinationName << ".\n";
            return;
        }

        int path[MAX_CITIES];
        int pathLength = 0;
        int current = destination;
        while (current != -1 && pathLength < MAX_CITIES) {
            path[pathLength++] = current;
            current = parent[current];
        }

        cout << "\nShortest route: ";
        for (int i = pathLength - 1; i >= 0; i--) {
            cout << cities[path[i]];
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << "\nTotal distance: " << dist[destination] << " km\n";
    }

    void loadSampleData() {
        if (cityCount != 0) {
            cout << "Sample data can only be loaded into an empty project.\n";
            return;
        }

        string sampleCities[] = {"Pune", "Mumbai", "Nashik", "Surat", "Thane"};
        int sampleCount = 5;
        for (int i = 0; i < sampleCount; i++) {
            cities[cityCount++] = sampleCities[i];
        }

        // Illustrative distances for demonstration only.
        int roads[][3] = {
            {0, 1, 150}, // Pune - Mumbai
            {0, 2, 200}, // Pune - Nashik
            {1, 2, 100}, // Mumbai - Nashik
            {1, 3, 250}, // Mumbai - Surat
            {2, 3, 150}, // Nashik - Surat
            {1, 4, 25},  // Mumbai - Thane
            {4, 2, 140}  // Thane - Nashik
        };

        int roadCount = sizeof(roads) / sizeof(roads[0]);
        for (int i = 0; i < roadCount; i++) {
            int u = roads[i][0];
            int v = roads[i][1];
            int km = roads[i][2];
            distanceMatrix[u][v] = km;
            distanceMatrix[v][u] = km;
        }

        cout << "Sample cities and roads loaded successfully.\n";
        cout << "Note: all sample distances are illustrative, not live road distances.\n";
    }
};

int main() {
    ShortestPathFinder app;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       SHORTEST PATH FINDER\n";
        cout << "====================================\n";
        cout << "1. Add City\n";
        cout << "2. Add Road and Distance\n";
        cout << "3. Display Cities and Roads\n";
        cout << "4. Find Shortest Path\n";
        cout << "5. Load Sample Data (demo)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        switch (choice) {
            case 1:
                app.addCity();
                break;
            case 2:
                app.addRoad();
                break;
            case 3:
                app.displayCitiesAndRoads();
                break;
            case 4:
                app.findShortestPath();
                break;
            case 5:
                app.loadSampleData();
                break;
            case 6:
                cout << "Thank you for using Shortest Path Finder!\n";
                break;
            default:
                cout << "Invalid choice. Select 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}

/*
PS C:\Girase Pratiksha> cd "c:\Girase Pratiksha\" ; if ($?) { g++ path_finder_using_graphs.cpp -o path_finder_using_graphs } ; if ($?) { .\path_finder_using_graphs }

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 1
Enter city name (no duplicate names): Mumbai
City added successfully.

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 1
Enter city name (no duplicate names): Nashik
City added successfully.

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 1
Enter city name (no duplicate names): Pune
City added successfully.

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 2
Enter starting city: Mumbai
Enter destination city: Pune
Enter distance in km (positive number): 360
Road added/updated successfully.

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 3

--- Cities ---
1. Mumbai
2. Nashik
3. Pune

--- Roads (two-way) ---
Mumbai <--> Pune : 360 km

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 4
Enter source city: Mumbai
Enter destination city: Pune

Shortest route: Mumbai -> Pune
Total distance: 360 km

====================================
       SHORTEST PATH FINDER
====================================
1. Add City
2. Add Road and Distance
3. Display Cities and Roads
4. Find Shortest Path
5. Load Sample Data (demo)
6. Exit
Enter your choice: 5
Sample data can only be loaded into an empty project.

*/
