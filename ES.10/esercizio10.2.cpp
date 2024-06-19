#include <mpi.h>
#include <iostream>
#include <vector>
#include "ingiro.h"

using namespace std;

int main(int argc, char* argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_city = 110;
    int _N = 2500;
    int gen_stop = 2000;
    int M = 10;

    string italia = "cap_prov_ita.dat";

    Mappa Map(n_city, italia);
    Genetica gene(n_city, italia);

    Random rnd;
    rnd.initialize(rank);

    // Creare la generazione iniziale
    auto generazione = gene.Prima_generazione(_N);
    gene.sort_by_length(generazione);

    int i = 0;

    ofstream out("Best_process0.dat"); // Crea un file di output per salvare i risultati del processo 0

    while (i < gen_stop) {
        // Creare una nuova generazione mantenendo il percorso migliore
        vector<vector<int>> new_generation = {generazione[0]};

        while (new_generation.size() < _N) {
            vector<int> parent1 = gene.selection(generazione);
            vector<int> parent2 = gene.selection(generazione);

            if (rnd.Rannyu() < 0.95) {
                auto crossover_result = gene.crossover(parent1, parent2);
                new_generation.push_back(crossover_result.first);
                new_generation.push_back(crossover_result.second);
            } else {
                new_generation.push_back(parent1);
                new_generation.push_back(parent2);
            }
        }

        // Applicare le mutazioni
        for (int j = 0; j < _N; ++j) {
            int k = static_cast<int>(rnd.Rannyu(0., _N));

            if (rnd.Rannyu() < 0.10)
                gene.m_inverse(new_generation[k]);
            if (rnd.Rannyu() < 0.12)
                gene.shift(new_generation[k]);
            if (rnd.Rannyu() < 0.10)
                gene.m_perm(new_generation[k]);
            if (rnd.Rannyu() < 0.10)
                gene.pair_perm(new_generation[k]);
        }

        // Ordinare la nuova generazione per lunghezza
        gene.sort_by_length(new_generation);
        //Aggiornamento frequenza di migrazioni
        if (i > 200) M = 20;
        if (i > 300) M = 40;
        if (i > 400) M = 50;

        // Sincronizzazione periodica per trovare la soluzione globale migliore
        if (i % M == 0) {
            vector<int> local_best_solution = new_generation[0];
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

                new_generation[0] = overall_best_solution;
            }

            MPI_Bcast(new_generation[0].data(), n_city, MPI_INT, 0, MPI_COMM_WORLD);
        }

        generazione = new_generation;

        if (rank == 0) {
            double best_length = Map.Get_length(generazione[0]);
            cout << i << "   " << best_length << endl;

            // Salva su file
            out << i + 1 << "  " << best_length << endl;
        }
        i++;
    }
    out.close();

    // Assicurarsi che non siano state trovate soluzioni migliori
    vector<int> local_best_solution = generazione[0];
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
        generazione[0] = overall_best_solution;
    }

    MPI_Bcast(generazione[0].data(), n_city, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Best path found:" << endl;
        for (int i = 0; i < n_city; i++) {
            cout << generazione[0][i] << "  ";
        }
        cout << endl;
        cout << "Length: " << Map.Get_length(generazione[0]) << endl;

        ofstream open("percorso_italia.dat");
    if (!open.is_open()) {
        cerr << "Errore nell'apertura del file: percorso_italia.dat" << endl;
        return 1;
    }

    // Scrittura del percorso migliore nel file
    for (size_t i = 0; i < generazione[0].size(); ++i) {
        open<< generazione[0][i] << endl;
    }
    open.close();
    cout << "Dati salvati correttamente nel file: percorso_italia.dat" << endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
