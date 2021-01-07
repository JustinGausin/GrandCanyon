#include "basepolygon.h"
void dijkstraAlgorith(list <triangle> &GrandCanyon,  default_random_engine *engine)
{


    list <triangle > Solution;
    list <triangle *>::iterator Itr;
    list <triangle >::iterator LItr;
    list <triangle >::iterator MItr;

    ///sorting algorithm for the PQ
    auto cmp = [](triangle * left, triangle * right) { return (left->getCost() > right->getCost());};
    priority_queue<triangle *,vector<triangle *>, decltype(cmp)> PQ(cmp);

    list <triangle>::iterator Mitr;




    triangle tri;
    ///triangle *droppoint;

    int sizeofMtn = GrandCanyon.size();
    int locationofdrop = 0;
    cout << "Size of the Mountain: " << sizeofMtn<<endl;

    uniform_int_distribution <int> Distro (0, sizeofMtn);
    bool flag = false;
    while(flag != true)
    {

    locationofdrop = Distro(*engine);


    cout << "landing on the triangle with the ID: " <<  locationofdrop << endl; ;

    cout << "Drooooooping............" <<endl;
    Mitr= GrandCanyon.begin();

    while(Mitr != GrandCanyon.end())
    {
        if(Mitr->getID() == locationofdrop)
        {
            ///droppoint = &(*Mitr);
            ////cout << droppoint->getID() << endl;
            if(Mitr->getUsability() ==true)
            {
               Solution.push_back((*Mitr));
               flag = true;
               break;
            }
            else
            {
                cout << "restarting the dropping again...landing point is not usable " << endl;
            }
        }
        Mitr++;

    }
    }


    LItr = Solution.begin();
    double currcost;

    ///retrieve cost of the last element of the solutions
    currcost = (LItr)->getCost();
    ///retrieve destination from current source and push to PQ
    bool found = false;

    list <triangle*>::iterator Ione;
    list <triangle*>::iterator Itwo;
    (LItr)->getEdges(Ione,Itwo);
    while(Ione!=Itwo)
    {
      if((*Ione)!=NULL)
        {

            if((*Ione)->getUsability() ==true)
            {
                    (*Ione)->addCost(currcost);
                    PQ.push((*Ione));
                    cout << "edge " << (*Ione)->getID() << " is usable with cost: " << (*Ione)->getCost() <<  endl;
                    /// cout << (*Ione)->getID() << "   ";
            }
            else
            {
                cout << "this drop point edge " << (*Ione)->getID() << " is not usable" << endl;
            }

        }
       else
       {
           cout << "NULL" << endl;
           found = true;
           cout << "Solution already found before the iterator begins" << endl;
       }
        Ione++;
    }
    cout << endl;




    ///if found by ending the list of PQ or finding a unull
    cout<<"entering djikstra's algorithm, nList, Solution and PQ initialized"<<endl;
    ///algorithm begin
        int Bao =0;

    while(found == false && !PQ.empty())
    {
        bool repeat = false;
        ///looking if the triangle is in the solution
        LItr = Solution.begin();
        cout << endl;
        while(LItr!=Solution.end())
        {
            if((LItr)->getID() == PQ.top()->getID())
            {
                cout << "The triangle is part of the solution already...removing from the PQ" << endl;
                ///cout << PQ.top()->getID() <<endl;
                PQ.pop();
                MItr = Solution.end();
                --MItr;
                currcost = (MItr)->getCost();
                PQ.top()->addCost(currcost);
              cout << "This is the new top :  " << PQ.top()->getID() << " with the cost of " << PQ.top()->getCost() << endl;
                ///cout << "size of PQ" << PQ.size() << endl;
               repeat = true;
                break;
            }
            else
               {
               /// cout << endl;
               /// cout << PQ.top()->getID() << " is not equal to this value of the solutions" << endl;
               }
            LItr++;
        }

            ///add top of the PQ to the solution list


        if(repeat ==false)
        {

        tri = *(PQ.top());
        cout << "removing " << PQ.top()->getID() << " to the solution list "  << endl;
        PQ.pop();
        cout << "New top is " << PQ.top()->getID() << endl;
        cout << "adding " << tri.getID() << " to the triangle of solutions" << endl;

        Solution.push_back(tri);


          cout << "What in the solution?  { ";
        LItr= Solution.begin();
        while(LItr!=Solution.end())
        {
            cout << (LItr)->getID() << "  ";
            LItr++;
        }
        cout << " } ";
        cout << endl <<endl;

        ///adding last cost to the current one
        cout << "This is at the end of the solution " << Solution.back().getID() << endl;
        LItr = Solution.end();
        --LItr;
        currcost = (LItr)->getCost();


            tri.getEdges(Ione,Itwo);

            ///if the neighbor listed size is less than three than the triangle is not usable
            cout<< "Current triangle has neighbors being added to the PQ: [ " ;
            while(Ione!=Itwo)
                {


                    if((*Ione)!=NULL)
                    {
                        if((*Ione)->getUsability() ==true)
                        {
                            /// cout << "currcost: " << currcost << endl;
                            ///   cout << "  costbefore: " << (*Ione)->getCost() << " ";
                            (*Ione)->addCost(currcost);
                            PQ.push((*Ione));
                            cout << "ID " << (*Ione)->getID() << ":cost " << (*Ione)->getCost()
                            << "  /  ";
                        }
                    }
                    else
                    {
                       cout << "NULLedge "; ///crashes during this
                       found = true;
                      //  PQ.push(NULL);
                    }
                Ione++;

                }
                cout << " ] " << endl;



            /*Bao++;

            if(Bao ==4)
            {
             cout << " ~~~~~~~~~~~~~~~~~~~~ERROR CHECKING~~~~~~~~~~~~~~~`" << endl;
            int q = PQ.size();
            cout << "size is: " << q <<endl;
            while(PQ.size()!=0)
                {
                    cout << PQ.top()->getID() << " cost is: " << PQ.top()->getCost() << endl;
                    PQ.pop();
                }
             cout << " ~~~~~~~~~~~~~~~~~~~~ERROR CHECKING~~~~~~~~~~~~~~~`" << endl;

            }*/




        }
    }
    cout << "This is the end of the path...." << endl <<endl;

    fstream fpath;
    fpath.open("Solutionpath.txt", ios::out);

    LItr = Solution.begin();
    while(LItr!=Solution.end())
    {
        LItr->displayCenter(fpath);
        LItr++;
    }

    LItr = Solution.end();
    --LItr;
    if(LItr->getPointA().z == 0)
    {
          fpath << (LItr->getPointA().x) << " " << (LItr->getPointA().y) << " " << "0" << endl;
    }
    else if(LItr->getPointB().z == 0 )
    {
        fpath << (LItr->getPointB().x) << " " << (LItr->getPointB().y) << " " << "0" << endl;
    }
    else
    {
        fpath << (LItr->getPeak().x) << " " << (LItr->getPeak().y) << " " << "0" << endl;

    }





    fpath << endl << endl;
    fpath.close();






}


void display(list<triangle> &GrandCanyon)
{

    list<triangle>::iterator mitr;

    fstream fout;
    fout.open("GrandCanyon.txt",ios::out);

    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        mitr->displaypoints(fout);
        mitr++;
        cout << endl;
    }
    fout<<endl;
    fout.close();
    fout.close();
}

void setEdges(list <triangle> &GrandCanyon, Points ASlope, Points BSlope, Points ACliff, Points BCliff,Points CCliff, Points DCliff)
{
    list <triangle>::iterator ritr;
    ritr=GrandCanyon.begin();
    int counter = 0;
    while(ritr!=GrandCanyon.end())
    {
        ritr->setID(counter);
        counter++;
        ritr++;
    }

    list <triangle>::iterator mitr;
    /**
                    THIS IS JUST FOR ACOUNTING THE TRIANGLES TO THE EDGE OF THE SLOPE
    **/
    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {

        if(mitr->getPointB() == ASlope && mitr->getPointA() ==BSlope)
        {

           /* cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

            idnum = mitr->getID();
            cout << idnum << endl;
            cout << ACliff.x <<  " " <<  ACliff.y << " " <<  ACliff.z << endl << endl;
            cout << mitr->getPointB().x <<  " " <<  mitr->getPointB().y << " " <<  mitr->getPointB().z << endl;
            cout << BCliff.x <<  " " <<  BCliff.y << " " <<  BCliff.z << endl;
            cout << mitr->getPointA().x <<  " " <<  mitr->getPointA().y << " " <<  mitr->getPointA().z << endl;

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        */

            ritr = GrandCanyon.begin();
            while(ritr!=GrandCanyon.end())
            {
                 if(mitr->getCenter() == ritr->getCenter() || ritr->getID()==mitr->getID())
                    {
                       ///cout << mitr->getPeak().x <<  " " <<  mitr->getPeak().y << " " <<  mitr->getPeak().z << endl;
                       ritr++;
                    }
                else
                {
                   ///cout << ritr->getID() << endl;

                    if( ritr->getPointB() >= ASlope && BSlope>= ritr->getPointA() )
                    {
                        mitr->addedges(&(*ritr));
                        ritr->addedges(&(*mitr));
                    }
                    ritr++;
                }
                ///ritr++;
            }

        }
        mitr++;
    }

    /**

                    THIS IS JUST FOR ACOUNTING THE TRIANGLES TO THE EDGE OF THE CLIFF 1
    **/

    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        if(mitr->getPointB() == ACliff && mitr->getPointA() ==BCliff)
        {

            ritr = GrandCanyon.begin();
            while(ritr!=GrandCanyon.end())
            {
                 if(mitr->getCenter() == ritr->getCenter() || ritr->getID()==mitr->getID())
                    {
                       ///cout << mitr->getPeak().x <<  " " <<  mitr->getPeak().y << " " <<  mitr->getPeak().z << endl;
                       ritr++;
                    }
                else
                {
                   ///cout << ritr->getID() << endl;

                    if( ritr->getPointB() >= ACliff && BCliff >= ritr->getPointA() )
                    {
                        mitr->addedges(&(*ritr));
                        ritr->addedges(&(*mitr));
                    }
                    ritr++;
                }
                ///ritr++;
            }

        }
        mitr++;
    }


    /**
                    THIS IS JUST FOR ACOUNTING THE TRIANGLES TO THE EDGE OF THE CLIFF 1
    **/


    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        if(mitr->getPointB() == CCliff && mitr->getPointA() ==DCliff)
        {

            ritr = GrandCanyon.begin();
            while(ritr!=GrandCanyon.end())
            {
                 if(mitr->getCenter() == ritr->getCenter() || ritr->getID()==mitr->getID())
                    {
                       ///cout << mitr->getPeak().x <<  " " <<  mitr->getPeak().y << " " <<  mitr->getPeak().z << endl;
                       ritr++;
                    }
                else
                {
                   ///cout << ritr->getID() << endl;

                    if( ritr->getPointB() >= CCliff && DCliff >= ritr->getPointA() )
                    {
                        mitr->addedges(&(*ritr));
                        ritr->addedges(&(*mitr));
                    }
                    ritr++;
                }
                ///ritr++;
            }

        }
        mitr++;
    }





    /**
                    CHECKS IF THE EDGES ARE THE SAME..
                    CHECKS A->B or B->A && A->Peak or Peak->A && B->Peak or Peak->B
    **/
    list <triangle>::iterator otheritr;
    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        otheritr = GrandCanyon.begin();
        while(otheritr!=GrandCanyon.end())
        {
            ///check if its the same triangle
            if(mitr->getCenter() == otheritr->getCenter())
            {
               /// cout << mitr->getCenter().x << "  " << mitr->getCenter().y  << " " <<  mitr->getCenter().z << endl;
                ///cout << otheritr->getCenter().x << "  " << otheritr->getCenter().y  << " " <<  otheritr->getCenter().z << endl << endl<< endl;
                otheritr++;
            }
            else
            {

                ///do i have one point in common?
                if(mitr->getPointA() == otheritr->getPointA() ||mitr->getPointA() == otheritr->getPointB() || mitr->getPointA() == otheritr->getPeak())
                {
                    ///set the edge
                    ///if i do have a common point... check if my other point is equal to him ///check hte second point
                    if(mitr->getPointB() == otheritr->getPointA() ||mitr->getPointB() == otheritr->getPointB() || mitr->getPointB() == otheritr->getPeak())/// ||mitr->getPeak() == otheritr->getPointA() ||mitr->getPeak() == otheritr->getPointB() || mitr->getPeak() == otheritr->getPeak())
                    {
                        ///if u do have another point then its an edge
                        ///addd it
                        mitr->addedges(&(*otheritr));

                        otheritr++;

                    }

                    else
                    {
                        otheritr++;

                    }
                }
                else
                    otheritr++;
            }
        }
        mitr++;
    }

    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        otheritr = GrandCanyon.begin();
        while(otheritr!=GrandCanyon.end())
        {
            ///check if its the same triangle
            if(mitr->getCenter() == otheritr->getCenter())
            {
                ///cout << mitr->getCenter().x << "  " << mitr->getCenter().y  << " " <<  mitr->getCenter().z << endl;
                ///cout << otheritr->getCenter().x << "  " << otheritr->getCenter().y  << " " <<  otheritr->getCenter().z << endl << endl<< endl;
                otheritr++;
            }
            else
            {

                ///do i have one point in common?
                if(mitr->getPointB() == otheritr->getPointA() ||mitr->getPointB() == otheritr->getPointB() || mitr->getPointB() == otheritr->getPeak())
                {
                    ///set the edge
                    ///if i do have a common point... check if my other point is equal to him ///check hte second point
                    if(mitr->getPeak() == otheritr->getPointA() ||mitr->getPeak() == otheritr->getPointB() || mitr->getPeak() == otheritr->getPeak())/// ||mitr->getPeak() == otheritr->getPointA() ||mitr->getPeak() == otheritr->getPointB() || mitr->getPeak() == otheritr->getPeak())
                    {
                        ///if u do have another point then its an edge
                        ///addd it
                        mitr->addedges(&(*otheritr));

                        otheritr++;
                    }

                    else
                    {
                        otheritr++;
                    }
                }
                else
                    otheritr++;
            }
        }
        mitr++;
    }

  mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        otheritr = GrandCanyon.begin();
        while(otheritr!=GrandCanyon.end())
        {
            ///check if its the same triangle
            if(mitr->getCenter() == otheritr->getCenter())
            {
                ///cout << mitr->getCenter().x << "  " << mitr->getCenter().y  << " " <<  mitr->getCenter().z << endl;
                ///cout << otheritr->getCenter().x << "  " << otheritr->getCenter().y  << " " <<  otheritr->getCenter().z << endl << endl<< endl;
                otheritr++;
            }
            else
            {
                ///do i have one point in common?
                if(mitr->getPeak() == otheritr->getPointA() ||mitr->getPeak() == otheritr->getPointB() || mitr->getPeak() == otheritr->getPeak())
                {
                    ///set the edge
                    ///if i do have a common point... check if my other point is equal to him ///check hte second point
                    if(mitr->getPointA() == otheritr->getPointA() ||mitr->getPointA() == otheritr->getPointB() || mitr->getPointA() == otheritr->getPeak())/// ||mitr->getPeak() == otheritr->getPointA() ||mitr->getPeak() == otheritr->getPointB() || mitr->getPeak() == otheritr->getPeak())
                    {
                        ///if u do have another point then its an edge
                        ///addd it
                        mitr->addedges(&(*otheritr));

                        otheritr++;
                    }

                    else
                    {
                        otheritr++;
                    }
                }
                else
                    otheritr++;
            }
        }
        mitr++;
    }



    ///sets the null edges...the ones that are in the bottom of the Polygon
    mitr = GrandCanyon.begin();
    while(mitr != GrandCanyon.end())
    {
        ///adds null to the bottom triangles
        mitr->addNULL();
        mitr++;
    }


}
void GraftBase( list<triangle> &Cliff1,list<triangle> &Cliff2,list <triangle> &Slope,list <triangle> &Ridgeline,list <triangle>& Connector,list <triangle> &Connector1, list <triangle> &Connector2, list <triangle> &GrandCanyon)
{

    list <triangle>::iterator mitr;
    while(Slope.size()!=0)
    {

        mitr = Slope.begin();
        GrandCanyon.push_back((*mitr));
        Slope.pop_front();
    }

    while(Cliff1.size()!=0)
    {

        mitr = Cliff1.begin();
        GrandCanyon.push_back((*mitr));
        Cliff1.pop_front();
    }

    while(Cliff2.size()!=0)
    {
        mitr = Cliff2.begin();
        GrandCanyon.push_back((*mitr));
        Cliff2.pop_front();
    }



     while(Connector2.size()!=0)
    {

        mitr = Connector2.begin();
        GrandCanyon.push_back((*mitr));
        Connector2.pop_front();
    }



    mitr = Ridgeline.begin();
    while(mitr!=Ridgeline.end())
    {
        GrandCanyon.push_back((*mitr));
        mitr++;
    }


    ///putting the slope into the original

    while(Connector1.size()!=0)
    {
        mitr = Connector1.begin();
        GrandCanyon.push_back((*mitr));
        Connector1.pop_front();
    }
    while(Connector.size()!=0)
    {
        mitr = Connector.begin();
        GrandCanyon.push_back((*mitr));
        Connector.pop_front();
    }




}
void Refine(list <triangle> &GrandCanyon)
{
     int refine;
     int counter = 0;
    double AspectRatio;
    Points peak, B, newCen;
    Points A;
    triangle base;
    triangle *temp;
    triangle *temp2;
    triangle *temp3;

default_random_engine gen(time(NULL));

    double   dx, dy, dz;
    list <triangle>::iterator Mitr;
    cout << "How many refinements would you like? " << endl;
    cin >> refine;

    /// Refinement of the mountain
    for(int i=0; i<refine; i++)
    {

        double lmin = 0;
        Mitr = GrandCanyon.begin();
        AspectRatio = Mitr->calculateAspRatio(lmin);


        //cout << "Aspect Ratio : "<<  AspectRatio << endl;


        ///can only limit the triangle to a certain aspect ratio
        if(AspectRatio < 10)
        {
        ///L = Mitr->calculateLength();
        ////cout << "Length of one point to the center: " << L << endl << endl;
        ///sd = L/30;

        ///cout << "maximum deviation " << sd << endl << endl ;
        normal_distribution<double> Sdist(lmin/60,lmin/20);
        dx = Sdist(gen);
        dy = Sdist(gen);
        dz = Sdist(gen);
      ///  cout << "dx, dy, and dz:: " <<  dx << "  "  << dy << "  "  << dz << endl;
        A = Mitr->getPointA();
        B = Mitr->getPointB();
        peak = Mitr->getPeak();

        ///cout << A.x << A.y << A.z << endl;

        ///this is the new of the triangles peak
        newCen = Mitr->getCenter();
       /// cout << "Centroid of triangle  :" << newCen.x << ", " << newCen.y << ", " << newCen.z << endl;

        newCen.x = newCen.x +dx;
        newCen.y = newCen.y +dy;
        newCen.z = newCen.z +dz;


        ///  cout << "New Centroid of triangle" << newCen.x << ", " << newCen.y << ", " << newCen.z << endl;
       /// cout << " this is teh temporary ones " << endl;
        temp = new triangle(A,B, newCen, counter);
          ///  temp->displaypoints(fout);

        temp2 = new triangle(B, peak, newCen, counter);
              ///  temp2->displaypoints(fout);

        temp3 = new triangle(peak, A, newCen, counter);
               /// temp3->displaypoints(fout);
              ///  cout << endl << endl;



        GrandCanyon.push_back(*temp);
        GrandCanyon.push_back(*temp2);
        GrandCanyon.push_back(*temp3);
        GrandCanyon.pop_front();

        }
        else
        {
            cout << "ignoring triangle as it fails the aspect ratio" << endl;
        }

    }







}

///OVERLOADED FUNCTIONS
bool operator==(Points lhs, Points rhs)
{
    if(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
        return true;
    else
        return false;
}
bool operator>=(Points lhs, Points rhs)
{
     ///cout << " { " << lhs.x << "| " << rhs.x << " ---  "  << lhs.y  << "| " << rhs.y << " ---" << lhs.z << "| "  << rhs.z << " }" << endl;

    if((lhs.x == rhs.x) && (lhs.y >= rhs.y) && (lhs.z == rhs.z))
    {
                ///cout <<  lhs.x << "| " << rhs.x << " ---  "  << lhs.y  << "| " << rhs.y << " ---" << lhs.z << "| "  << rhs.z << endl;
       /// cout <<  lhs.x << "| "  << lhs.y  << "| " <<  lhs.z << endl;

        return true;
    }
    else
        return false;
}
bool compare(Points lhs, Points rhs)
{
    return(lhs.y == rhs.y && lhs.x == rhs.x);

}

void MakeCliff(list <triangle> &Cliff1, list<triangle> &Cliff2, int counter, int type, Points& ACliff, Points& BCliff,Points& CCliff, Points& DCliff)
{

    counter = 0;
    list <triangle> Cliff;
    default_random_engine gen(time(NULL));
    normal_distribution<double> mrand(0,.1);
    normal_distribution<double> Rdist(0,.1);
    normal_distribution<double> Zdist(0,.1);


    list<triangle>::iterator mitr;


    triangle * tptr1;


    double tempx, tempy, tempz;
    double x,y,z;
    Points temp, temp2, temp3, temp4, temp5, temp6, temp7, temp8;


    int xtemp, ytemp;
    if(type == 1)
    {
        xtemp = 100, ytemp= 150;
    }
    else if(type == 2)
    {
        xtemp=100; ytemp=-350;
    }



    list<Points> R;
    list<Points> C;
    C.clear();
    R.clear();
    list<Points>::iterator ptitr;
    list<Points>::iterator ptitr2;
    list<Points>::iterator ptitr3;

    Points * ptptr;

    for(int i=0; i<6; i++)
       {
           tempx= 0; //Rdist(gen);
           x = xtemp+tempx;

           tempy= 0; //Rdist(gen);
           y = ytemp+(i*20)+tempy;
           z = 0;
           ptptr = new Points (x,y,z);

           R.push_back(*ptptr);

           ///tempx=Rdist(gen);
           tempx = 0;
           x = 80+tempx;
           y = ytemp+(i*20)+tempx;
           /// tempz=Zdist(gen);
           tempz = 0;
           z = 60+tempz;
           ptptr = new Points(x,y,z);
           C.push_back(*ptptr);

       }
        ///cout<<"rivers edge"<<endl;
        int s = R.size();
       /// cout<<"R ["<<s<<"]"<<endl;


    list<Points>::iterator titr = prev(C.end());

    ///side view of the cliffs
    ptitr = R.begin();
    ptitr2= C.begin();
    if(type == 1)
    {
         ACliff = *(C.begin());
         BCliff = *(titr);


        list<Points>::iterator enditr4 = R.end();
        --enditr4;
        list<Points>::iterator enditr5 = C.end();
        --enditr5;

        temp4 = *enditr4; ///point c for
        temp5 = *enditr5;///point c basically
        temp3 = {0, temp5.y, temp5.z}; ///point a
        temp6 = {0 , temp4.y, temp4.z}; ///point b

        tptr1 = new triangle {temp3, temp4, temp5, counter};
        Cliff.push_back(*tptr1);
        counter++;

        tptr1 = new triangle {temp3, temp4, temp6, counter};
        Cliff.push_back(*tptr1);
        counter++;



    }
    else if(type ==2)
    {
        CCliff = *(C.begin());
        DCliff = *(titr);


        temp4 = *ptitr; ///point c for
        temp5 = *ptitr2;///point c basically
        temp3 = {0, temp5.y, temp5.z}; ///point a
        temp6 = {0 , temp4.y, temp4.z}; ///point b

        tptr1 = new triangle {temp3, temp4, temp5, counter};
        Cliff.push_back(*tptr1);
        counter++;

        tptr1 = new triangle {temp3, temp4, temp6, counter};
        Cliff.push_back(*tptr1);
        counter++;


    }
    else{cout << " None here " << endl;}


    ///back of the cliffs
    ptitr = R.begin();
    ptitr2= C.begin();
    list<Points>::iterator enditrCliff = C.end();
    --enditrCliff;
    list<Points>::iterator enditrRiver = R.end();
    --enditrRiver;
    temp = {0 , enditrRiver->y , 0}; ///a
    temp2 = {0 , enditrCliff->y, enditrCliff->z};  ///c
    temp3 = {0, ptitr2->y, ptitr2->z}; ///b
    temp4 = {0, ptitr->y ,0};  ///c

    tptr1 = new triangle (temp, temp3, temp2, counter);
    Cliff.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp, temp3, temp4, counter);
    Cliff.push_back(*tptr1);
    counter++;


    ///the rest of the triangles
    ptitr = R.begin();
    ptitr2= C.begin();


    ///main ones
    for(int i=0; i<s-1; i++)
    {
    tptr1 = new triangle;
    tptr1->setA(*ptitr);
    ptitr++;
    tptr1->setB(*ptitr);
    tptr1->setC(*ptitr2);
    tptr1->setID(counter);
    Cliff.push_back(*tptr1);
    counter++;

    tptr1 = new triangle;
    tptr1->setA(*ptitr);
    tptr1->setB(*ptitr2);
    ptitr2++;
    tptr1->setC(*ptitr2);
    tptr1->setID(counter);
    Cliff.push_back(*tptr1);
    counter++;
    }




    list<Points>::iterator ptitr4 = C.end();
    --ptitr4;
    list<Points>::iterator ptitr5 = R.end();
    --ptitr5;

    ptitr = R.begin();
    ptitr2= C.begin();

    ///top
    tptr1 = new triangle;    ///ABC1
    temp = {0, ptitr2->y , ptitr2->z};
    tptr1->setC(*ptitr2);
    tptr1->setA(temp);
    tptr1->setB(*ptitr4);
    tptr1->setID(counter);
    Cliff.push_back(*tptr1);
    counter++;

    tptr1 = new triangle;
    temp2 = {0, ptitr4->y , ptitr4->z};
    tptr1->setC(temp2);
    tptr1->setA(temp);
    tptr1->setB(*ptitr4);
    tptr1->setID(counter);
    Cliff.push_back(*tptr1);
    counter++;





    if(type == 1)
    {
        while(Cliff.size()!=0)
        {
        mitr = Cliff.begin();
        Cliff1.push_back((*mitr));  ///puts it in cliff 1
        Cliff.pop_front();
        }

    }
    else if(type == 2)
    {

        while(Cliff.size()!=0)
        {
            mitr = Cliff.begin();
            Cliff2.push_back((*mitr));  ///puts it in cliff 2
            Cliff.pop_front();
        }

    }
    else
        cout << "Error" << endl;

}
///makes the river
void MakeRiver(list <triangle> GrandCanyon)
{

    fstream riverout;
    riverout.open("River_dat.txt", ios::out);
    list <triangle>::iterator mitr;
    mitr=GrandCanyon.begin();
    list<Points> RiverBottom;
    list<Points> RiverTop;
    list<Points>::iterator pitr;
    list<Points>::iterator qitr;
    list<Points>::iterator nextitr;
    list<triangle> ColoradoRiver;
    list<triangle>::iterator ritr;

    triangle * tptr1;
    int counter = 0;


    Points river;
    int bank = 50;
    mitr=GrandCanyon.begin();
    while(mitr!=GrandCanyon.end())
    {
        ///Does the points have a z that is equal to 0?
        ///is there really a point tho
        if(mitr->istherePoint() == true)
        {
            river  = mitr->returnZPoint();
            river.x = bank + river.x;
            RiverBottom.push_back(river);
        }

        mitr++;
    }


    ///I NEED TO ORDER THE POINTS BASED ON THE X AXIS FIRST
    Points ptemp, ptemp2;
    Points *ptemp3;
    double Len;
    RiverBottom.sort([](Points lhs, Points rhs) {return lhs.y < rhs.y;});
   RiverBottom.unique(compare);
    for(int i = 0; i < 40; i++)
    {
        pitr = RiverBottom.begin();
        nextitr = RiverBottom.begin();
        ++nextitr;
        ptemp = *(pitr);
        ptemp2 = *(nextitr);
        Len = sqrt(pow(ptemp.x-ptemp2.x,2.0)+pow(ptemp.y-ptemp2.y,2.0));

        if(Len > 30 && Len < 500)
        {
            ptemp3 = new Points{ (ptemp.x+ptemp2.x)/2, (ptemp.y+ptemp2.y)/2, 0};
            RiverBottom.push_back(*pitr);
            RiverBottom.push_back(*ptemp3);
            RiverBottom.pop_front();
        }
        else
        {
            RiverBottom.push_back(*pitr);
            RiverBottom.pop_front();
        }

    }





    RiverBottom.sort([](Points lhs, Points rhs) {return lhs.y < rhs.y;});

    pitr = RiverBottom.begin();
    double widthriver =60;
    while(pitr!=RiverBottom.end())
    {
        ptemp = {pitr->x +widthriver, pitr->y, pitr->z};
        RiverTop.push_back(ptemp);
        pitr++;
    }


    int s = RiverBottom.size();
   /// cout<<"River bottom ["<<s<<"]"<<endl;


    ///the rest of the triangles
    pitr = RiverBottom.begin();
    qitr= RiverTop.begin();


    ///main ones
    for(int i=0; i<s-1; i++)
    {
    tptr1 = new triangle;
    tptr1->setA(*pitr);
    pitr++;
    tptr1->setB(*pitr);
    tptr1->setC(*qitr);
    tptr1->setID(counter);
    ColoradoRiver.push_back(*tptr1);
    counter++;

    tptr1 = new triangle;
    tptr1->setA(*pitr);
    tptr1->setB(*qitr);
    qitr++;
    tptr1->setC(*qitr);
    tptr1->setID(counter);
    ColoradoRiver.push_back(*tptr1);
    counter++;
    }
    mitr = ColoradoRiver.begin();
    while(mitr!=ColoradoRiver.end())
    {
        mitr->displaypoints(riverout);
        mitr++;
    }
    riverout <<endl <<endl;
    riverout.close();


}
///connector3
void SlopeCliffConnector(list<triangle> &Connector2, list <triangle> Cliff2, list <triangle> Slope,int counter)
{

    list<triangle>::iterator mitr;
    counter=0;
    triangle tri, tri1, tri2, tri3;
    triangle * tptr1;


    Points temp, temp2, temp3, temp4, temp5, temp6, temp7, temp8;


    list<triangle>::iterator enditrCliff = Cliff2.end();
    advance(enditrCliff, -1);

    list<triangle>::iterator thirdlastCliff = Cliff2.end();
    advance(thirdlastCliff, -3);

    list<triangle>::iterator penumitr = Slope.end();
    advance(penumitr, -2);

    list<triangle>::iterator firstitr = Slope.begin();
    advance(firstitr, 2);

    temp = enditrCliff->getPeak(); ///cliff point c
    temp2 = enditrCliff->getPointB(); ///cliff point B

    temp3 = penumitr->getPointA(); ///slope point A
    temp4 = penumitr->getPeak();   ///slope point C

    temp5 = thirdlastCliff->getPointA(); ///cliff bottom point
    temp6 =firstitr->getPointA();



    ///Top connectors
    tptr1 = new triangle (temp2, temp3, temp , counter);
    Connector2.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp2, temp3, temp4 , counter);
    Connector2.push_back(*tptr1);
    counter++;

    ///Front Bottom Connectors
    /*tptr1 = new triangle (temp2, temp6, temp4 , counter);
    Connector2.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp2, temp6, temp5 , counter);
    Connector2.push_back(*tptr1);
    counter++;*/
    //
    ///orrrrrrr
    tptr1 = new triangle (temp5, temp4, temp2 , counter);
    Connector2.push_back(*tptr1);
    counter++;
    tptr1 = new triangle (temp5, temp4, temp6 , counter);
    Connector2.push_back(*tptr1);
    counter++;

    ///backside
    temp7 = {0, temp.y, 0};
    temp8 = {0, temp3.y, 0};
    tptr1 = new triangle (temp7, temp3, temp , counter);
    Connector2.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp7, temp3, temp8 , counter);
    Connector2.push_back(*tptr1);
    counter++;





}


///connector 0
void RidgeCliffConnector(list<triangle> Ridgeline, list <triangle> Cliff1,  list <triangle> &Connector, int counter)
{
    list<triangle>::iterator mitr;
    triangle tri, tri1, tri2, tri3;
    triangle * tptr1;
    Points temp, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;

    counter = 21;

    list<triangle>::iterator RidgeFront = Ridgeline.begin();
    list<triangle>::iterator RidgeEnd = Ridgeline.end();
    --RidgeEnd;
    list<triangle>::iterator penum = Cliff1.end();
    advance(penum, -2);
    list<triangle>::iterator CliffFront = Cliff1.begin();
    advance(CliffFront, 4);


    temp = RidgeFront->getPeak(); ///peak1
    temp2 = RidgeEnd->getPeak(); ///peak2
    temp3 = penum->getPointA(); ///ned to be point c
    temp4 = penum->getPeak(); ///need to be point b
    ///temp5 = CliffFront->getPeak();  ///z =60..will need to point b
    temp6 = CliffFront->getPointA(); ///z= 0...will be point c
    temp7 = RidgeEnd->getPointB(); /// this will need to be a
    ///   cout << "XXXXXXXXXXXXXXXXXXXXXXXXx" << endl;
   /// cout << temp5.z << endl << endl << endl;
   /// cout << "XXXXXXXXXXXXXXXXXXXXXXXXx" << endl;


    ///top
    tptr1 = new triangle (temp, temp4, temp3, counter);
    Connector.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp, temp4, temp2, counter);
    Connector.push_back(*tptr1);
    counter++;

    ///bottom
   tptr1 = new triangle (temp7, temp4, temp2, counter);
    Connector.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp7, temp4, temp6, counter);
    Connector.push_back(*tptr1);
    counter++;

    ///backside
    temp5 = {0, temp3.y, 0};
    temp9 = RidgeFront->getPointA();


    tptr1 = new triangle (temp9, temp3, temp, counter);
    Connector.push_back(*tptr1);
    counter++;
    tptr1 = new triangle (temp9, temp3, temp5, counter);
    Connector.push_back(*tptr1);



}




///this is a separate list not the actually orignial polygon
void makeSlope(list <triangle> &Slope, int counter, Points  &ACliff, Points &BCliff)
{

    counter = 0;
    default_random_engine gen(time(NULL));
    normal_distribution<double> mrand(0,.1);
    normal_distribution<double> Rdist(0,.1);
    normal_distribution<double> Zdist(0,.1);
    list<triangle>::iterator mitr;



    triangle * tptr1;



    double tempx, tempy, tempz;


    double x,y,z;
    Points temp, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    int xtemp=200, ytemp=-150;
    list<Points> R;
    list<Points> C;
    C.clear();
    R.clear();
    list<Points>::iterator ptitr;
    list<Points>::iterator ptitr2;
    list<Points>::iterator ptitr3;

    Points * ptptr;

       for(int i=0; i<6; i++)
       {
           tempx=Rdist(gen);
           x = xtemp+tempx;

           tempy=Rdist(gen);
           y = ytemp+(i*20)+tempy;
           z = 0;
           /*ptptr->x = x;
           ptptr->y = y;
           ptptr->z = z;*/

           ptptr = new Points (x,y,z);

           R.push_back(*ptptr);

            tempx= 0;
           x = 50+tempx; /// change this to change plateue
           y = ytemp+(i*20)+tempx;
           tempz = 0;
           z = 60+tempz;
           ptptr = new Points(x,y,z);
           C.push_back(*ptptr);

       }
        ///cout<<"rivers edge"<<endl;
    int s = R.size();
       /// cout<<"R ["<<s<<"]"<<endl;


    list<Points>::iterator titr = prev(C.end());
    ACliff = *(C.begin());
    BCliff = *(titr);
   //// cout << ACliff.x << "  " << ACliff.y << " " << ACliff.z;



     ///back of the cliffs
    ptitr = R.begin();
    ptitr2= C.begin();
    list<Points>::iterator enditrCliff = C.end();
    --enditrCliff;
    list<Points>::iterator enditrRiver = R.end();
    --enditrRiver;
    temp = {0 , enditrRiver->y , 0}; ///a
    temp2 = {0 , enditrCliff->y, enditrCliff->z};  ///c
    temp3 = {0, ptitr2->y, ptitr2->z}; ///b
    temp4 = {0, ptitr->y ,0};  ///c

    tptr1 = new triangle (temp, temp3, temp2, counter);
    Slope.push_back(*tptr1);
    counter++;

    tptr1 = new triangle (temp, temp3, temp4, counter);
    Slope.push_back(*tptr1);
    counter++;


    ///main

    ptitr = R.begin();
    ptitr2= C.begin();

   list<triangle>::iterator enditr = Slope.end();
    list<triangle>::iterator enditr2 = Slope.end();
    for(int i=0; i<s-1; i++)
    {
    tptr1 = new triangle;    ///ABC1
    tptr1->setA(*ptitr);
    ptitr++;
    tptr1->setB(*ptitr);
    tptr1->setC(*ptitr2);
    tptr1->setID(counter);
    Slope.push_back(*tptr1);
    counter++;

    tptr1 = new triangle;
    tptr1->setA(*ptitr);
    tptr1->setB(*ptitr2);
    ptitr2++;
    tptr1->setC(*ptitr2);
    tptr1->setID(counter);
    Slope.push_back(*tptr1);

    counter++;
    }






    list<Points>::iterator ptitr4 = C.end();
    --ptitr4;
    list<Points>::iterator ptitr5 = R.end();
    --ptitr5;

    ptitr = R.begin();
    ptitr2= C.begin();


    ///top
    tptr1 = new triangle;
    temp = {0, ptitr2->y , ptitr2->z};
    tptr1->setC(*ptitr2);
    tptr1->setA(temp);
    tptr1->setB(*ptitr4);
    tptr1->setID(counter);
    Slope.push_back(*tptr1);
    counter++;

    tptr1 = new triangle;
    temp2 = {0, ptitr4->y , ptitr4->z};
    tptr1->setC(temp2);
    tptr1->setA(temp);
    tptr1->setB(*ptitr4);
    tptr1->setID(counter);
    Slope.push_back(*tptr1);
    counter++;


}


///connector1
void RidgeConnector(list <triangle> Ridgeline, list <triangle> Slope,  list <triangle> &Connector1, int counter)
{
    triangle tri, tri1, tri2, tri3;
    triangle * tptr1;

    counter=0;

    Points temp, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    list<triangle>::iterator enditr = Slope.end();
    advance(enditr, -3);
    list<triangle>::iterator mitr;


    tri = Ridgeline.back();
    tri1 = Slope.back();
    tri2 = Ridgeline.front();

    temp = tri1.getPointB(); ///slope:::point b of the last elemt
    temp2= tri1.getPeak(); ///slope:::point c of the back
    temp3 = tri2.getPeak();///rideline peak 1
    temp4 = tri.getPeak(); ///ridgeline peak2
    temp5 = enditr->getPointA();
    temp6 = tri.getPointA(); ///ridgeline, last element .. point a of it

    ///creating the connector between the slope and the ridge

    ///top
    tptr1 = new triangle (temp, temp3, temp2, counter);
    Connector1.push_back(*tptr1);
    counter++;

    tptr1 = new triangle(temp, temp3, temp4, counter);
    Connector1.push_back(*tptr1);
    counter++;


    ///this is the bottom of the list

    ///this one connect to enditr-2 of the slope
    tptr1 = new triangle(temp, temp6, temp5, counter);
    Connector1.push_back(*tptr1);
    counter++;

    tptr1 = new triangle(temp, temp6, temp4, counter);
    Connector1.push_back(*tptr1);
    counter++;

    ///backside
    temp7={0 , temp2.y, 0};
    temp8 = Ridgeline.front().getPointB();

    tptr1 = new triangle(temp8 , temp2, temp7, counter);
    Connector1.push_back(*tptr1);
    counter++;

    tptr1 = new triangle(temp8 , temp2, temp3, counter);
    Connector1.push_back(*tptr1);
    counter++;








}



void MakeRidge(list<triangle> &Ridgeline)
{
///for the ridge. This way I can specify its width height and length
///without really hardcoding it... use the peak1 and peak 2 to determine the xyz of all other points
    Points peak1, peak2;
    Points tempA, tempB, tempC, tempD, tempE, cent1, cent2;
    list <triangle>::iterator Mitr;
    list <triangle>::iterator Mitr2;
    list <triangle>::iterator Mitr3;
    list <triangle>::iterator Mitr4;




    uniform_int_distribution<int> Idist(1,100);
    uniform_int_distribution<int> Pdist(2,4);


    triangle *temp1;
  ///  double x1,y1,z1;
    ///for now we can set the peak 1 and peak 2 to some hard code..for refinement

    peak1 = {0,50,50};
    peak2= {300,50,50};

    ///get all the points first
    tempA = {peak1.x, 0 , 0};
    tempD = {peak1.x, peak1.y+50,0};

    tempB = {peak2.x, 0 , 0};
    tempC = {peak2.x, peak2.y+50, 0};

    ///A, B, P1 and P2
    cent1.x = (tempA.x+tempB.x+peak1.x+peak2.x)/4.0;
    cent1.y= (tempA.y+tempB.y+peak1.y+peak2.y)/4.0;
    cent1.z = (tempA.z+tempB.z+peak1.z+peak2.z)/4.0;

    ///C, D, P1, P2
    cent2.x = (tempC.x+tempD.x+peak1.x+peak2.x)/4.0;
    cent2.y= (tempC.y+tempD.y+peak1.y+peak2.y)/4.0;
    cent2.z = (tempC.z+tempD.z+peak1.z+peak2.z)/4.0;
   // cout << "Center: ( " << cent1.x << " , " << cent1.y << " , " << cent1.z << " )" << endl;
    ///cout << "Center: ( " << cent2.x << " , " << cent2.y << " , " << cent2.z << " )" << endl;

    ///set base polygon ///counterclockwise
    int ID = 0;
    ///triangle 0
    temp1 = new triangle(tempD, tempA, peak1, ID);
    Ridgeline.push_back(*temp1);


    ///triangle 5
    ID ++;
    temp1 = new triangle(tempB, tempC, peak2, ID);
    Ridgeline.push_back(*temp1);

}

