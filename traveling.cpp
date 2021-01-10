//Rehan Javaid, rj3dxu, 11/17/2020, traveling.cpp

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include "middleearth.h"

float computeDistance(MiddleEarth &me, const string& start, vector<string> dests);
void printRoute(const string& start, const vector<string>& dests);

int main(int argc, char** argv) {
    // check the number of parameters
    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }

    // we'll assume the parameters are all well-formed
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    int num_cities = stoi(argv[3]);
    int rand_seed = stoi(argv[4]);
    int cities_to_visit = stoi(argv[5]);

    // create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);

    unordered_map<float, vector<string>> data1;
    vector<float> v1; 

    v1.push_back(100.00); 
   
    //format obtained from example of using next_permutation in while loop

    sort(dests.begin()+1, dests.end()-1);

    do {
      float num1 = computeDistance(me, dests[0], dests);
      if (num1 < v1[0]){
	v1[0] = num1;
	data1.insert(pair<float, vector<string>> (num1, dests));
      }
    } while(next_permutation(dests.begin(), dests.end()));

    float minDis = *min_element(v1.begin(), v1.end());

    cout << "Minimum path has distance " << minDis << ": ";
    printRoute(data1[minDis][0],data1[minDis]); 
    
    return 0;
}

// This method will compute the full distance of the cycle that starts
// at the 'start' parameter, goes to each of the cities in the dests
// vector IN ORDER, and ends back at the 'start' parameter.
float computeDistance(MiddleEarth &me, const string& start, vector<string> dests) {
  float distanceTraveled = 0.00;
  for (int i = 0; i < dests.size(); i++){
    if (i+1 < dests.size()){
      float d1 = me.getDistance(dests[i], dests[i+1]);
      distanceTraveled += d1;
    }
  }
  distanceTraveled += me.getDistance(dests[dests.size()-1], start);
  return distanceTraveled;
}

// This method will print the entire route, starting and ending at the
// 'start' parameter.
// The output should be similar to:
// Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
void printRoute(const string& start, const vector<string>& dests) {
  for(int i = 0; i < dests.size(); i++){
    cout << dests[i] << " -> ";
  }
  cout << start << endl; 
}
