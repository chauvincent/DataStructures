#ifndef evacH
#define evacH

#include "EvacRunner.h"

class CityInfo
{
    public:
      
      bool known, deadEnd, evacuatedCity;
  
      int *edgeID; 
  
      int maxPeople;
  
      int evacPeople;
  
      char numEdges;
  
      int depth;
  
      bool visited;
  
      CityInfo():known(false), deadEnd(true), evacuatedCity(false), evacPeople(0), visited(false) {}
}; 

class RoadEdge
{
    public:
      
      int destCityID;
      
      int weight;
      
      int used;
  
      RoadEdge():used(0) {}

}; 

class EvacInfo
{
    public:
      
      int ID;
  
      float ratio;

}; 


class Evac
{
  
    CityInfo *cities;
    
    RoadEdge *edge;

    EvacInfo *evacCities;

    int numCities;
  
    int hour;
  
    int *evacQ, back, front;
  
    int *visitedIDs, visitedSize;
  
    int *usedRoads, usedCount;
  
    public:
  
        int dfs(int cityID, int needed, int sourceCityID);
  
        Evac(City *cities, int numCities, int numRoads);
  
        void evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes, int &routeCount); 

}; 



#endif
