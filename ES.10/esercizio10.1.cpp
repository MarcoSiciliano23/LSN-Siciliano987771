#include <mpi.h>
#include <iostream>
#include <vector>
#include "ingiro.h"

using namespace std;
// (!) SERVONO 90 GENERAZIONI SE SI USANO 8 PROCESSI

int main(int argc, char* argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_city = 34;
    int _N = 1000;
    int gen_stop = 90;
    int M = 10;
    Random rnd;
    Mappa Map(n_city, rnd);
    Genetica gene(n_city);

    rnd.initialize(rank);

    // crea la generazione iniziale
    auto generazione = gene.Prima_generazione(_N);
    gene.sort_by_length(generazione);

    int i = 0;

    while (i < gen_stop) { 
        // Create new generation maintaining the best path
        vector<vector<int>> new_generation = {generazione[0]};

        while (new_generation.size() < _N) {
            vector<int> parent1 = gene.selection(generazione);
            vector<int> parent2 = gene.selection(generazione);

            if (rnd.Rannyu() < 0.9) {
                auto crossover_result = gene.crossover(parent1, parent2);
                new_generation.push_back(crossover_result.first);
                new_generation.push_back(crossover_result.second);
            } else {
                new_generation.push_back(parent1);
                new_generation.push_back(parent2);
            }
        }

        // Apply mutations
        for (int j = 0; j < _N ; ++j) {
            int k = static_cast<int>(rnd.Rannyu(0., _N));
            if (rnd.Rannyu() < 0.075)
                gene.m_inverse(new_generation[k]);
            if (rnd.Rannyu() < 0.1)
                gene.shift(new_generation[k]);
            if (rnd.Rannyu() < 0.1)
                gene.m_perm(new_generation[k]);
            if (rnd.Rannyu() < 0.05)
                gene.pair_perm(new_generation[k]);
        }

        // Sort new generation by length
        gene.sort_by_length(new_generation);

        // Periodic synchronization to find global best solution
        if (i % M == 0) {
            vector<int> local_best_solution = new_generation[0];
            vector<int> global_best_solution(n_city);
            vector<int> all_solutions(size * n_city);

        
            MPI_Gather(local_best_solution.data(), n_city, MPI_INT, all_solutions.data(), n_city, MPI_INT, 0, MPI_COMM_WORLD);

            if (rank == 0) {
                vector<int> overall_best_solution = local_best_solution;

                for (int p = 1; p < size; ++p) {

                    int start_idx = p * n_city;
                    int end_idx = start_idx + n_city;
                    vector<int> tmp_solution(all_solutions.begin() + start_idx, all_solutions.begin() + end_idx);
                    if (Map.Get_length(tmp_solution) < Map.Get_length(overall_best_solution)) {
                        overall_best_solution = tmp_solution;
                    }
                }
                global_best_solution = overall_best_solution;
            }

            MPI_Bcast(global_best_solution.data(), n_city, MPI_INT, 0, MPI_COMM_WORLD);
            new_generation[0] = global_best_solution;

             
        }

        generazione = new_generation;  
        i++;
    }
    
    vector<int> local_best_solution = generazione[0];
    vector<int> global_best_solution(n_city);
    vector<int> all_solutions(size * n_city);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(local_best_solution.data(), n_city, MPI_INT, all_solutions.data(), n_city, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        vector<int> overall_best_solution = local_best_solution;
        for (int p = 1; p < size; ++p) {
            vector<int> tmp_solution(all_solutions.begin() + p * n_city, all_solutions.begin() + (p + 1) * n_city);
                if (Map.Get_length(tmp_solution) < Map.Get_length(overall_best_solution)) {
                    overall_best_solution = tmp_solution;
                }
        }
        global_best_solution = overall_best_solution;
    

            MPI_Bcast(global_best_solution.data(), n_city, MPI_INT, 0, MPI_COMM_WORLD);
            generazione[0] = global_best_solution;
        }

    vector<int> Final_solution = generazione[0];

    if (rank == 0) {
        cout << "Best path found:" << endl;
        for (int j = 0; j < n_city; j++) {
            cout << Final_solution[j] << "  ";
        }
        cout << endl;
        cout << Map.Get_length(Final_solution) << endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
