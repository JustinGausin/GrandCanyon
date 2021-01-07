#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <list>

#include <vector>
#include <algorithm>
using namespace std;
struct Points
{
    double x,y,z;
    Points(){};
    Points(double x1, double y1, double z1):x(x1),y(y1), z(z1){};
    inline void display(fstream &fout )
    {
       /// cout << "Point: ( " << x << " , " << y << " , " << z << " )" << endl;
        fout  << fixed << setprecision(2) <<  x << " " << y << " " << z << endl;

    }

};
class triangle
{

    public:
        triangle(){};
        virtual ~triangle(){};
        triangle(Points &A1, Points &B1, Points &newPeak, int i)
            {
                A = A1;
                B = B1;
                Peak = newPeak;
                usability = false;
                ID = i;

            }



        ///returns the z point
        Points returnZPoint()
        {
            if(A.z ==0)
            {
                return A;
            }
            else if(B.z==0)
            {
                return B;
            }
            else if(Peak.z ==0)
            {
                return Peak;
            }
            else
                return Center;
        }

        ///bool to check if the point is valid to be used when creating  the river
        bool istherePoint()
        {
            if(A.z ==0 || B.z == 0 || Peak.z ==0)
            {
                if(A.x > 50 || B.x > 50)
               {
                  return true;
               }
               else
                return false;
            }
            else
                return false;
        }

        ///displays the points to the fstream
        void displaypoints(fstream &fout)
        {
            ///cout << "The center of the triangle is: ";
            calculateCenter();
            //Center.display(fout);
             cout << endl;

            cout << "the id is : " << ID << endl;
            fout << endl;
            A.display(fout);
            B.display(fout);
            fout << endl;

            B.display(fout);
            Peak.display(fout);

            fout << endl;
            Peak.display(fout);
            A.display(fout);
            fout << endl;

        calculateUsabilityandCost();

        cout << "Edges are ";
        displayEdges();

        cout << boolalpha <<  "Usable? : " << usability << "     Cost: [" << cost <<  " units]" << endl;



        }

        ///drop point for the parachuter
        void displaystartingpoints()
        {
            ///We are using the triangle center rather than its edges
            cout << "Parachuter has dropped at the location with elevation of " << Center.z << " feet from sea level" <<  endl;
            cout << "The triangle id is : " << ID << endl;
        }

        ///calculates the center of the triangle
        void calculateCenter()
        {
            double CX = (A.x+B.x+Peak.x)/3;
            double CY = (A.y+B.y+Peak.y)/3;
            double CZ = (A.z+B.z+Peak.z)/3;
            Center ={CX,CY,CZ};
            ///cout<<"Centroid(G) (X1,Y1) = ("<<CX<<","<<CY << "," << CZ<<")" << endl;
        }


        ///calculates the length of the sides
        double calculateLength()
        {
            calculateCenter();
            int L;
            L = sqrt(pow(A.x-Center.x,2.0)+pow(A.y-Center.y,2.0) + pow(A.z-Center.z,2.0));
            return L;
        }

        ///calculates the aspect ratio using a vector...the lengthmin is also passed back for the
        ///uniform distribution on the changes if x y z
        double calculateAspRatio(double &lengthmin)
        {
            /*Aspect ratio formula:
             h/l1 where h=l2*sin(acos((x1-x0)(x2-x0)+(y1-y0)(y2-y0)+(z1-z0)(z2-z0))),
             l2 is the other edge and l1 is the longest edge.
             To find length of edge is sqrt((x1-x0)^2+(y1-y0)^2+(z1-z0)^2)
             where (x1,y1,z1) is the second point of edge and (x0,y0,z0)
              is the first point.
            */
            ///calculate the edges first:
            ///calculate edge Length from A-B, B-P, P-A
            double edge1, edge2, edge3, Ratio;
            ///A->B
            edge1 = sqrt(pow(B.x-A.x,2.0)+pow(B.y-A.y,2.0) + pow(B.z-A.z,2.0));
            ///B->P
            edge2 = sqrt(pow(Peak.x-B.x,2.0)+pow(Peak.y-B.y,2.0) + pow(Peak.z-B.z,2.0));
            ///P->A
            edge3 = sqrt(pow(A.x-Peak.x,2.0)+pow(A.y-Peak.y,2.0) + pow(A.z-Peak.z,2.0));

            vector<double> edgeLength {edge1, edge2, edge3};
            sort(edgeLength.begin(), edgeLength.end());
           /* cout << "edge 1:" <<  edgeLength[0] << endl;
            cout  << "edge 2:"<< edgeLength[1] << endl;
            cout  << "edge 3:"<< edgeLength[2] << endl;*/

            lengthmin = edgeLength[0];
            ///Aspect Ratio is Aspect = Longest Edge/Shortest Edge
            ///Figure out which edge is bigger and the smallest
            Ratio = edgeLength[2]/edgeLength[0];
            return Ratio;

        }

        Points getPointA(){return A;}
        Points getPointB(){return B;}
        Points getPeak(){return Peak;}
        Points getCenter(){ calculateCenter(); return Center;}

        ///Sets the edges
        void setA(Points Ax)
        {
            A = Ax;
        }

        void setB(Points Bx)
        {
            B = Bx;
        }
        void setC(Points Cx)
        {
            Peak = Cx;
        }

        ///returns id
        int getID()
        {
            return ID;
        }

        ///set the id
        void setID(int IDx)
        {
            ID = IDx;
        }

        ///displays the id
        void whatstheid()
        {
            ///cout << "the id is: " << ID << endl;
        }


        ///add neighbors to a list
        void addedges(triangle * c)
        {
            list<triangle*>::iterator itr;
            itr= edges.begin();
           /* bool flag = false;
            while(itr!=edges.end())
            {
                if((*itr)->getID() == c->getID());
                {
                  flag = true;
                }
                itr++;
            }
            if(flag == true)
            {
                cout << "Duplicate" << endl;
            }
            else*/
            edges.push_back((c));


        }

        ///returns the edges using the beginner iterator and end iterator
        void getEdges(list<triangle *>::iterator &Ione, list<triangle*>::iterator &Itwo)
        {
            Ione = edges.begin();
            Itwo = edges.end();
            return;
        }

        ///display edges if the curr triagnle
        void displayEdges()
        {
            list<triangle*>::iterator Ione;
           /// list<triangle*>::iterator Itwo;
          /// edges.unique();
           Ione = edges.begin();
            while(Ione!=edges.end())
            {
                if((*Ione)!=NULL)
                {
                    cout << (*Ione)->getID() << " ";
                }
                else{
                    cout << " NULL";
                    }
                Ione++;
            }
            cout <<endl;

        }

        ///calculates whether it is usable or not....Formula that was shown in class did not work for even if taken the absolute value of the unit normal
        void calculateUsabilityandCost()
        {

            double alpha = (B.x - A.x);
                ///cout << "alpha: " << B.x - A.x << endl;
            double beta = (B.y - A.y);
                ///cout << "beta: " << (B.y - A.y) <<endl;
            double delta =(Peak.x - A.x);
                ///  cout << "delta: " << Peak.x - A.x << endl;
            double epsilon = (Peak.y - A.y);
                /// cout << " epsilon"  << (Peak.y - A.y) <<endl;
            double phi = (B.z - A.z);
            double theta = (Peak.z-A.z);
                ///double unitnormal = ((alpha*epsilon)-(beta*delta));
                /// double normalize = sqrt()
            double unitnormal =((alpha*epsilon)- (beta*delta));
            double inormal = (beta*theta)- (phi*epsilon);
            double jnormal = (phi*delta) - (alpha*phi);
                ///cout << inormal << "   " << jnormal <<endl;
            double normalize = sqrt(pow(inormal, 2)+ pow(jnormal, 2) +pow(unitnormal, 2));
                /// cout << "first unit normal: " << unitnormal << endl;
                /// cout << "normalize: [ " << normalize << " ] "<< endl;
                /// cout << " LAB : " << LengthAB << "   LAC:  " << LengthAC << endl;
                /// cout << ID << "alpha: " << alpha << "  beta: " << beta << "   delta: " << delta << " epsilon: " << epsilon << endl;

            unitnormal = abs(unitnormal/normalize);
            cout << "Unit Normal {" << unitnormal << "}" << endl;
            if((unitnormal) > .6)
            {
                usability = true;
                cost  =  (1 - unitnormal);
                    ///the program works way too well that it would just go around the top of the mountain than go down
                    /*if(cost < .1)
                    {
                        cost = cost * 2;

                    }*/
            }
            else
            {
                usability = false;
                cost  =  (1 - unitnormal);
            }
        }

        bool getUsability()
        {
            return usability;
        }

        void addNULL()
        {
            if(edges.size() < 3)
            {
                edges.push_back(NULL);
            }
        }
        double getCost()
        {
            return cost;
        }

        ///Adds cost of the current solution to its neighbors going to the PQ list
        void addCost(double n)
        {
            cost = cost +n;
        }

        ///This is the solution  path using the center as the line
        void displayCenter(fstream &fout)
        {
            getCenter();
            fout << Center.x << " " << Center.y << " " << Center.z << endl;
            cout << "The cost of the path is: " << cost << endl;
        }
    protected:
    private:
        Points A;
        Points B;
        Points Peak;
        Points Center;
        list <triangle*> edges;

        int ID;
        double cost;
        bool usability;

};

#endif // TRIANGLE_H
