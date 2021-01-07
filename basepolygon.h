#ifndef BASEPOLYGON_H_INCLUDED
#define BASEPOLYGON_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <random>
#include <list>
#include <ctime>
#include <fstream>
#include <queue>
#include <cstdlib>
using namespace std;
#include "triangle.h"

///function to refine the given based polygon
void Refine(list <triangle> &GrandCanyon);
///grafts all the standard shapes to each other to one list (GrandCanyon List)
void GraftBase( list<triangle> &Cliff1,list<triangle> &Cliff2,list <triangle> &Slope,list <triangle> &Ridgeline,list <triangle>& Connector,list <triangle> &Connector1, list <triangle> &Connector2, list <triangle> &GrandCanyon);

///makes the ridge base
void MakeRidge(list<triangle> &Ridgeline);

///makes the cliff base... either the type 1 on the left and type 2 on the right
void MakeCliff(list <triangle> &Cliff1, list<triangle> &Cliff2, int counter, int type, Points& ACliff, Points& BCliff,Points& CCliff, Points& DCliff);


///display the list of the Grandcayon and output the file to the text doc
void display(list<triangle> &GrandCanyon);

///makes the general base of the slope
void makeSlope(list <triangle> &Slope, int counter, Points  &ASlope, Points &BSlope);

///Base Connectors of the slope and cliff
void SlopeCliffConnector(list<triangle> &Connector2, list <triangle> Cliff2, list <triangle> Slope,int counter);

///Base Connector from the Ridge to the Slope
void RidgeConnector(list <triangle> Ridgeline, list <triangle> Slope,  list <triangle> &Connector1, int counter);

///Connect the Ridge to the Cliff
void RidgeCliffConnector(list<triangle> Ridgeline, list <triangle> Cliff1,  list <triangle> &Connector, int counter);

///creates a river using the base points of the grandcanyon
void MakeRiver(list <triangle> GrandCanyon);

///sets up the neighbors using two points that triangles shares with
void setEdges(list <triangle> &GrandCanyon, Points ASlope, Points BSlope, Points ACliff, Points BCliff,Points CCliff, Points DCliff);


///overloaded functions for comparison
bool compare(Points lhs, Points rhs);
bool operator>=(Points lhs, Points rhs);
bool operator==(Points lhs, Points rhs);

///Dijksras Algorthm.. to find the shortest path down
void dijkstraAlgorith(list <triangle> &GrandCanyon,  default_random_engine *engine);


#endif // BASEPOLYGON_H_INCLUDED
