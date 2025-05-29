#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;

#define ERROR_TOL 10000 // Error tolerance for random graph creation

// General utility function declarations
void print_vector(const vector<int> vec);
vector<int> set_diff(const vector<int> L, const vector<int> V);
double Euclid_dist(const vector<double> point1, const vector<double> point2);
int exists(const int table[], int item, int len);
int intersection(int query_filter, int node_label, int query_type);
vector<int> random_bit_vector(int R, int n, int offset = 0);

// Struct declarations
struct mpair {
    vector<int> L_k;
    vector<int> V;
};

struct Euclid_pair {
    int node;
    double euclid_value;
};

// Class declarations
class Graph {
    vector<vector<int>> adj_matrix;
    vector<vector<double>> coordinates_table;
    vector<int> label_table;

public:
    Graph(int n, int dimension);
    void add_edge(int u, int v);
    void print();
    vector<double> get_coordinates(int node);
    static bool compareByEuclidValue(const Euclid_pair& a, const Euclid_pair& b);
    vector<int> sort_euclid(vector<int> L, int k, vector<double> xq);
    void print_coordinates(int dimension);
    void print_labels(int label_size);
    void construct_random_graph(int R, int n);
    void custom_coordinates(int n, const vector<vector<double>>& table);
    void custom_label(int n, const vector<int>& table);
    void insert_adjacency_matrix(int n,const vector<vector<int>>& table);
    void insert_coordinates_table(int n,const vector<vector<double>>& table);
    void insert_label_table(int n ,const vector<int> table);
    vector<vector<int>> extract_adjacency_matrix();
    vector<vector<double>> extract_coordinates_table();
    vector<int> extract_label_table();
    void get_random_coordinates(int n, int dimension);
    void get_random_label(int n, int label_size);
    vector<int> get_neighbours(int node, int n);
    mpair GreedySearch(vector<int> s, vector<double> x_q, int k, int list_size, int n, int query_filter, int query_type);
    void filtered_robust_prune(int node, vector<int> V, float a, int R, int n, int query_type);
    void run_test_case(int node, vector<int> V, float a, int R, int n, const vector<int> expected_edges);
    void custom_graph(vector<vector<int>> custom);
    int get_label(int node);
    vector<vector<int>> get_adjacency_matrix();
};

// Utility functions for medoid and random permutations
int unfiltered_find_medoid(const vector<vector<double>> dataset);
vector<int> FindMedoid(const vector<vector<double>> dataset, int threshold);
vector<int> get_random_permutation(int n);

// Vamana index creation
Graph vamana_index_create(vector<vector<double>> dataset, double a, int L, int R);
Graph filtered_vamana_index_create(vector<vector<double>> dataset, double a, int L, int R);
Graph Stitched_Vamana_Index_Create(vector<vector<double>> dataset,vector<int> labels,double a,int L_small,int R_small,int R_stitched);

