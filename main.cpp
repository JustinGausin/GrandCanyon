#include <iostream>
#include <cstdlib>
#include <random>
#include <list>
#include <ctime>
#include <fstream>
#include <queue>
#include <cstdlib>

#include "basepolygon.h"
int main()
{
    ///initialize
    default_random_engine *engine;
    engine = new default_random_engine(time(NULL));
    list<triangle> Cliff1;
    list<triangle> Cliff2;
    list <triangle> Slope;
    list <triangle> Ridgeline;
    list <triangle> Connector;
    list <triangle> Connector1;
    list <triangle> Connector2;
    list <triangle> GrandCanyon;
    Points ASlope,  BSlope, ACliff, BCliff,CCliff,DCliff;
    int counter = 0;

    ///functions
    makeSlope(Slope,  counter, ASlope, BSlope);
    MakeCliff(Cliff1, Cliff2,  counter, 2, ACliff,BCliff,CCliff,DCliff);
    SlopeCliffConnector(Connector2, Cliff2, Slope, counter);
    MakeRidge(Ridgeline);
    RidgeConnector(Ridgeline,Slope, Connector1,  counter);
    MakeCliff(Cliff1, Cliff2,  counter,1, ACliff,BCliff,CCliff,DCliff);
    RidgeCliffConnector(Ridgeline, Cliff1,Connector, counter);
    GraftBase( Cliff1,Cliff2,Slope,Ridgeline,Connector,Connector1,Connector2, GrandCanyon);
    Refine(GrandCanyon);
    setEdges(GrandCanyon, ASlope, BSlope,ACliff , BCliff, CCliff, DCliff);
    MakeRiver(GrandCanyon);
    display(GrandCanyon);
    dijkstraAlgorith(GrandCanyon,  engine);

    ////plots the grand canyon to gnuplot
    system("gnuplot command.txt");

    return 0;

}

