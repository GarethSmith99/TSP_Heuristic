#include <iostream>
#include <fstream>
#include "utils.h"
#include "argparser.h"
#include "solver.h"
#include "randomTSP.h"

using std::cout;
using std::endl;
using std::fixed;

int main(int argc, char *argv[]) {

 // LOAD DATA
 //------------------------------------------------------------------
 std::ifstream i("TSP10.json");  // Read data  //TSP20.33.json  //TSP10.json
 json data;
 i >> data;
 Graph* G = new Graph(data); // Save data into graph
 // We now have  a full graph with arcs that contains vertices.


 // MAKE INITIAL FEASIBLE SOLUTIONS
 //------------------------------------------------------------------
  RandomTSP* solver = new RandomTSP(G); // Instantiating a class object with input of graph G
  vector< Solution* > my_solutions;     // Vector of type Solution called my_solution. Solution type is a class. mysolution is therefore a vector list of of Solution objects
                                        // Solution(const vector<const Vertex *> & sol, const Graph * g) Solution holds vectors of vertices that makes up graph G
  for( int i = 0; i < 10; i++ )
  {
      solver->solve();                  // Call the whole TSP
      my_solutions.push_back(  solver->get_solution() );
  }
 // PRINT INITIAL FEASIBLE SOLUTIONS
 //------------------------------------------------------------------
  for( int i = 0; i < 10; i++ )
  {
      Solution* sol = my_solutions[i];
      //G->print_vertices(sol->get_solution());
      cout << "Distance: " << sol->get_objective() << endl; //<< endl;
  }

 // Lets see if I can accomplish the task of comparing the initial my_solutions
 double Temp_best_obj =9e350;
 int best_pos =-1;
 for(int i=0;i<10;i++)
 {
     if(my_solutions[i]->get_objective() < Temp_best_obj)
     {
         Temp_best_obj =my_solutions[i]->get_objective();
         best_pos=i;
     }
     //cout<<Temp_best_obj<<endl;
 }
 cout<<"Best initial solution distance:"<<my_solutions[best_pos]->get_objective()<<endl;
 cout<<"Best initial path is at index "<<best_pos<<endl<<endl;
 G->print_vertices(my_solutions[best_pos]->get_solution());
  //---------------------------------------------------------------------------------------------------------------------
  // TABU SEARCH
  //---------------------------------------------------------------------------------------------------------------------
  cout<< "\n\n======================TABU SEARCH======================"<<endl;
  vector< Solution* > Current_best;
  Current_best.push_back(my_solutions[best_pos]);
  G->print_vertices(Current_best[0]->get_solution());
  cout<<""<<endl<<endl;

  //Create candidates
  vector< Solution* > Candidate;
  double Temp_obj=0;
  double Temp_best_obj_Tabu= 9e350;                        //Stores the best solution for this Tabu iteration
  double Best_obj =Current_best[0]->get_objective();       //Stores the best possible at all times
  int looper =0;
  int i_best = -1;
  int j_best = -1;
  int looper_best = -1;

  for(int i=0;i<10;i++)
  {
      // Try to figure out how to swap vertices
      for(int j=0;j<10;j++)
      {
          Candidate.push_back(Current_best.front());        //Copy
          Candidate.at(looper)->swap_vertices(i,j);         //Swap
          if(Candidate.at(looper)->is_feasible()==1)
          {
              Temp_obj =Candidate[looper]->get_objective();
              //cout<<"Loop objective value: "<< Temp_obj<<endl;
              if(Temp_obj <Temp_best_obj_Tabu)
              {
                  i_best=i;
                  j_best=j;
                  looper_best=looper;
                  Temp_best_obj_Tabu=Temp_obj;
                  cout<<"NEW BEST::  i: "<<i_best;
                  cout<<"  j: "<<j_best;
                  cout<<"  looper_best: "<<j_best<<endl;;
                  cout<<"CANDIDATE distance::   "<<Candidate.at(looper_best)->get_objective()<<endl;
                  cout<<"Feasibility "<<Candidate.at(looper_best)->is_feasible()<<endl;
                  G->print_vertices(Candidate.at(looper_best)->get_solution());
                  cout<<""<<endl;

              }
              //cout<<"Loop: "<<looper;
          }
          else{
                cout<<"";
            //cout<<"####### NOT FEASIBLE #######"<<endl;
          }
          looper++;
      }
  }

  cout<<"Candidate size : "<<Candidate.size()<<endl<<endl;

  cout<<"Best solution after searching without tabu after swapping aka 1 iteration: "<< Candidate[looper_best]->get_objective()<<endl;
  cout<<"After swapping i: "<<i_best<<"and j: "<<j_best<<"  looper_best:"<<looper_best<<endl;
  cout<<"Exact solution gives us 4318468 which is equal to 4.3e6"<<endl;

  // Update function
  if( Candidate[looper_best]< Current_best[0])
  {
      Current_best.clear();
      Current_best.push_back(Candidate[looper_best]);

  }
  // Now work further from  Current best
  cout<<"Current best distance"<<Current_best[0]->get_objective()<<endl;

  // Die fout le by die begin en eindnode wat nie altyd dieselfde is na n swap nie.

  Candidate.clear();



    //---------------------------------------------------------------------------------------------------------------------
    // TABU SEARCH
    //---------------------------------------------------------------------------------------------------------------------

    //We have our initial 10 solutions stored in my_solutions

  delete solver;

  return 0;
}
