#include "mpi.h"
#include <iostream>
#include <vector>
#include "ingiro.h"

int main(int argc, char* argv[]) {
    
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_city = 10;
    int pop = 1000;
    Random rnd;
    Mappa Map(n_city, rnd);
    Genetica gene(n_city);
    
    rnd.initialize(rank);

    
/*
    vector<int> local_best_solution(n_city);
    vector<int> best_solution(n_city);

    int Ngen = 1000; // Number of generations
    int Nmigr = 1; // Number of migrations

    // Loop for genetic algorithm and migration
    for (int gen = 0; gen < Ngen; ++gen) {
        // Each process runs its own genetic algorithm for one generation
        local_best_solution = gene.Evoluzione(1, "length_cerchio.dat");

        // Exchange best solutions between processes after settled generations
        if ((gen + 1) % Nmigr == 0) {
            // Each process constructs a sending plan (permutation of ranks)
            std::vector<int> sending_plan(size);
            for (int i = 0; i < size; ++i) {
                sending_plan[i] = i;
            }
            std::random_shuffle(sending_plan.begin(), sending_plan.end());

            // Perform migration
            for (int i = 0; i < size; ++i) {
                int dest_rank = sending_plan[i];
                if (dest_rank != rank) {
                    // Send local best solution to the destination rank
                    MPI_Send(local_best_solution.data(), n_city, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
                    // Receive best solution from the destination rank
                    MPI_Recv(best_solution.data(), n_city, MPI_INT, dest_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    // Update local best solution if the received solution is better
                    for (int j = 0; j < n_city; ++j) {
                        if (best_solution[j] < local_best_solution[j]) {
                            local_best_solution[j] = best_solution[j];
                        }
                    }
                }
            }
        }

        // Gather all local best solutions
        MPI_Allreduce(local_best_solution.data(), best_solution.data(), n_city, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

        // Perform some logging or processing here if needed
        if (rank == 0) {
            std::cout << "Generation " << gen << ": Best solution found: ";
            for (int i = 0; i < n_city; ++i) {
                std::cout << best_solution[i] << " ";
            }
            std::cout << std::endl;
        }
    }
*/
    MPI_Finalize();
    return 0;
}
