#ifndef RANDOM_TSP_H
#define RANDOM_TSP_H

#include <vector>
#include <map>
#include <limits>

#include "solver.h"

#include <ctime>

#include "utils.h"

using std::map;
using std::vector;


class RandomTSP : public Solver {
 public:
  RandomTSP(const Graph * g)
  : Solver(g),
    generator( time(NULL) )
  {}

  void solve()
  {
    Solution *s = nullptr;
    do
    {
        vector<const Vertex *> random_vertices;
        long v = G->get_vertices().size();
        uniform_int_distribution<uint32_t> vert_gen(0, v - 1);

        vector< uint32_t > inserted;
        uint32_t i = 0;
        do
        {
            uint32_t rn = vert_gen(generator);
            if( find( inserted.begin(), inserted.end(), rn ) == inserted.end() )
            {
                inserted.push_back( rn );
                random_vertices.push_back( G->get_vertices()[ rn ] );
                i++;
            }
        }while( i < v);
        random_vertices.push_back( random_vertices[0] );

        s = new Solution(random_vertices, G);

    }while( !s->is_feasible() );
    best_solution = s;
  }


  Solution* get_solution()
  {
      return best_solution;
  }

 private:
  Solution* best_solution;
  mt19937_64 generator;
};

#endif