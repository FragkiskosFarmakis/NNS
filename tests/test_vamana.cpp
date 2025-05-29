
#include "acutest.h"
#include "functions.h"




// Example test

void permutation_testing_routine(void){

    int n = 10;
    vector<int> res = get_random_permutation(n);
    long unsigned int exp = n;

    int flag = 0;
    for(int i = 0; i < n;i++){
        if(res[i] < 0 || res[i] >= n){
            flag = 1;
        }
    }

    TEST_CHECK(res.size() == exp && flag == 0);
    TEST_MSG("Expected length: %ld", exp);
    TEST_MSG("Produced length: %ld", res.size());
    TEST_MSG("If above length is the same then some number is out of range!");



    n = 100;
    res = get_random_permutation(n);
    exp = n;

    flag = 0;
    for(int i = 0; i < n;i++){
        if(res[i] < 0 || res[i] >= n){
            flag = 1;
        }
    }


    TEST_CHECK(res.size() == exp && flag == 0);
    TEST_MSG("Expected length: %ld", exp);
    TEST_MSG("Produced length: %ld", res.size());
    TEST_MSG("If above length is the same then some number is out of range");


    n = 1000;
    res = get_random_permutation(n);
    exp = n;

    flag = 0;
    for(int i = 0; i < n;i++){
        if(res[i] < 0 || res[i] >= n){
            flag = 1;
        }
    }


    TEST_CHECK(res.size() == exp && flag == 0);
    TEST_MSG("Expected length: %ld", exp);
    TEST_MSG("Produced length: %ld", res.size());
    TEST_MSG("If above length is the same then some number is out of range");

    n = 10000;
    res = get_random_permutation(n);
    exp = n;

    flag = 0;
    for(int i = 0; i < n;i++){
        if(res[i] < 0 || res[i] >= n){
            flag = 1;
        }
    }


    TEST_CHECK(res.size() == exp && flag == 0);
    TEST_MSG("Expected length: %ld", exp);
    TEST_MSG("Produced length: %ld", res.size());
    TEST_MSG("If above length is the same then some number is out of range");



}


 void unfiltered_medoid_testing_routine(){
    vector<vector<double>> dataset = {{1, 1}, {2, 2}, {3, 3}};
    int res = unfiltered_find_medoid(dataset);
    int real_medoid = 1;
    

    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

    dataset = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
    res = unfiltered_find_medoid(dataset);
    real_medoid = 2;


    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

    dataset = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    res = unfiltered_find_medoid(dataset);
    real_medoid = 1;




    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

    dataset = {{1, 1}, {2, 2}, {1, 3}, {3, 3}, {2, 1}};
    res = unfiltered_find_medoid(dataset);
    real_medoid = 1;
    
    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

    dataset = {{1, 1}, {1, 2}, {2, 1}, {100, 100}};
    res = unfiltered_find_medoid(dataset); 
    real_medoid = 1; 
   

    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

    dataset = {{2, 4}, {3, 1}, {5, 3}, {8, 2}};
    res = unfiltered_find_medoid(dataset);
    real_medoid = 2;
    

    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

    dataset = {{1.2, 3.5}, {4.7, 2.3}, {3.1, 5.8}, {6.2, 1.5}, {5.9, 7.3},
    {8.4, 4.1}, {7.2, 9.6}, {2.8, 6.4}, {9.5, 8.1}, {3.3, 1.7},
    {10.1, 4.5}, {5.2, 5.9}, {1.9, 2.6}, {7.4, 3.3}, {4.1, 8.2},
    {6.6, 6.7}, {8.7, 9.3}, {2.1, 4.4}, {9.9, 7.7}, {3.5, 3.8},
    {5.7, 1.9}, {7.9, 6.5}, {4.5, 9.2}, {8.2, 2.1}, {6.3, 4.8},
    {3.7, 7.4}, {1.3, 5.1}, {9.1, 3.9}, {2.6, 8.3}, {4.9, 6.8},
    {5.5, 4.0}, {10.5, 1.2}, {8.6, 5.7}, {7.3, 2.5}, {1.6, 9.4},
    {3.9, 4.2}, {6.0, 8.0}, {2.3, 3.3}, {9.0, 10.0}, {4.8, 7.1},
    {7.7, 4.9}, {5.4, 2.8}, {2.7, 5.6}, {1.4, 8.5}, {10.2, 3.0},
    {6.9, 7.8}, {3.0, 2.4}, {8.1, 6.2}, {9.8, 5.5}, {4.3, 1.1}};
    res = unfiltered_find_medoid(dataset);
    real_medoid = 11;
    
    TEST_CHECK(res == real_medoid);
    TEST_MSG("Dataset expected medoid: %d", real_medoid);
    TEST_MSG("Produced medoid: %d", res);

}

void intersection_test(){
    int query_filter = 1;
    int node_label = 1;
    int query_type = 1;
    int answ = intersection(query_filter,node_label,query_type);

    TEST_CHECK(answ == 1);
    TEST_MSG("filter: %d",query_filter);
    TEST_MSG("node label: %d",node_label);
    TEST_MSG("query type: %d",query_type);

    query_filter = 1;
    node_label = 2;
    query_type = 1;
    answ = intersection(query_filter,node_label,query_type);

    TEST_CHECK(answ == 0);
    TEST_MSG("filter: %d",query_filter);
    TEST_MSG("node label: %d",node_label);
    TEST_MSG("query type: %d",query_type);

    query_filter = 1;
    node_label = 1;
    query_type = 10;
    answ = intersection(query_filter,node_label,query_type);

    TEST_CHECK(answ == -1);
    TEST_MSG("filter: %d",query_filter);
    TEST_MSG("node label: %d",node_label);
    TEST_MSG("query type: %d",query_type);

    query_filter = 10;
    node_label = 10;
    query_type = 0;
    answ = intersection(query_filter,node_label,query_type);

    TEST_CHECK(answ == 1);
    TEST_MSG("filter: %d",query_filter);
    TEST_MSG("node label: %d",node_label);
    TEST_MSG("query type: %d",query_type);

    query_filter = 10;
    node_label = 11;
    query_type = 0;
    answ = intersection(query_filter,node_label,query_type);

    TEST_CHECK(answ == 1);
    TEST_MSG("filter: %d",query_filter);
    TEST_MSG("node label: %d",node_label);
    TEST_MSG("query type: %d",query_type);
   
    query_filter = 1;
    node_label = 1;
    query_type = 10;
    answ = intersection(query_filter,node_label,query_type);

    TEST_CHECK(answ == -1);
    TEST_MSG("filter: %d",query_filter);
    TEST_MSG("node label: %d",node_label);
    TEST_MSG("query type: %d",query_type);


}

 
void test_set_diff() { 
    std::vector<int> L1 = {1, 2, 3, 4, 5};
    std::vector<int> V1 = {3, 4};
    std::vector<int> expected1 = {1, 2, 5};
    TEST_CHECK(set_diff(L1, V1) == expected1);
 
    std::vector<int> L2 = {6, 7, 8};
    std::vector<int> V2 = {1, 2, 3};
    std::vector<int> expected2 = {6, 7, 8};
    TEST_CHECK(set_diff(L2, V2) == expected2);
 
    std::vector<int> L3 = {1, 2, 3};
    std::vector<int> V3 = {1, 2, 3};
    std::vector<int> expected3 = {};
    TEST_CHECK(set_diff(L3, V3) == expected3);
 
    std::vector<int> L4 = {};
    std::vector<int> V4 = {1, 2, 3};
    std::vector<int> expected4 = {};
    TEST_CHECK(set_diff(L4, V4) == expected4);
 
    std::vector<int> L5 = {1, 2, 3};
    std::vector<int> V5 = {};
    std::vector<int> expected5 = {1, 2, 3};
    TEST_CHECK(set_diff(L5, V5) == expected5);
}



void testGreedySearch(void) {


    Graph test_graph(6,3);
    vector<vector<int>> custom = {{0,1,1,0,0,0},{0,0,1,1,0,0},{0,0,0,1,1,0},{0,0,0,0,1,1},{1,0,0,0,0,1},{1,1,0,0,0,0}};
    test_graph.custom_graph(custom);
    vector<vector<double>> dataset = {
    {1,2,7},
    {4,0,1}, 
    {2,1,9},
    {5,8,7},
    {1,7,3},
    {8,6,6},
    };




    vector<int> label = {-1,-1,-1,-1,-1,-1};
    vector<double> xq = {5,2,3};
    int query_type = 0;
    int node_filter = -1;
    int L = 2;
    int k = 2;
    int s = 0;
    test_graph.custom_label(6,label);
    test_graph.custom_coordinates(6,dataset);

    struct mpair res = test_graph.GreedySearch({s},xq,k,L,6,node_filter,query_type);
    vector<int> res_L = {1,0};
    vector<int> res_V = {0,1};
 

    TEST_CHECK(res.L_k == res_L && res.V == res_V);
    if(!(res.L_k == res_L && res.V == res_V)){
        printf("L produced contents: [");
        for (size_t i = 0; i < res.L_k.size(); ++i) {
            printf("%d%s",res.L_k[i], (i < res.L_k.size() - 1) ? ", " : "");
        }
        printf("]\n");
        printf("V produced contents: [");
        for (size_t i = 0; i < res.V.size(); ++i) {
            printf("%d%s",res.V[i], (i < res.V.size() - 1) ? ", " : "");
        }
        printf("]\n");
    }





    label = {2,1,2,11,1,3};
    xq = {5,2,3};
    query_type = 1;
    node_filter = 1;
    L = 2;
    k = 1;
    s = 4;
    test_graph.custom_label(6,label);
    test_graph.custom_coordinates(6,dataset);

    res = test_graph.GreedySearch({s},xq,k,L,6,node_filter,query_type);
    res_L = {4};
    res_V = {4};
 

    TEST_CHECK(res.L_k == res_L && res.V == res_V);
    if(!(res.L_k == res_L && res.V == res_V)){
        printf("L produced contents: [");
        for (size_t i = 0; i < res.L_k.size(); ++i) {
            printf("%d%s",res.L_k[i], (i < res.L_k.size() - 1) ? ", " : "");
        }
        printf("]\n");
        printf("V produced contents: [");
        for (size_t i = 0; i < res.V.size(); ++i) {
            printf("%d%s",res.V[i], (i < res.V.size() - 1) ? ", " : "");
        }
        printf("]\n");
    }


    label = {2,1,2,11,1,1};
    xq = {5,2,3};
    query_type = 1;
    node_filter = 1;
    L = 2;
    k = 2;
    s = 4;
    test_graph.custom_label(6,label);
    test_graph.custom_coordinates(6,dataset);

    res = test_graph.GreedySearch({s},xq,k,L,6,node_filter,query_type);
    res_L = {1,5};
    res_V = {1,4,5};
 

    TEST_CHECK(res.L_k == res_L && res.V == res_V);
    if(!(res.L_k == res_L && res.V == res_V)){
        printf("L produced contents: [");
        for (size_t i = 0; i < res.L_k.size(); ++i) {
            printf("%d%s",res.L_k[i], (i < res.L_k.size() - 1) ? ", " : "");
        }
        printf("]\n");
        printf("V produced contents: [");
        for (size_t i = 0; i < res.V.size(); ++i) {
            printf("%d%s",res.V[i], (i < res.V.size() - 1) ? ", " : "");
        }
        printf("]\n");
    }



}

 
void test_get_neighbours() {
    int n = 5;   
    Graph g(n,5);
 
    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);

     
    vector<int> expected_neighbours = {0, 2, 3};
    vector<int> actual_neighbours = g.get_neighbours(1, n);

    
    TEST_CHECK(actual_neighbours != expected_neighbours);

    
    if (actual_neighbours == expected_neighbours) {
        cout << "Test failed for node 1. Expected: ";
        for (int n : expected_neighbours) cout << n << " ";
        cout << ", but got: ";
        for (int n : actual_neighbours) cout << n << " ";
        cout << endl;
    }
}


void test_compareByEuclidValue() {
    
    std::vector<Euclid_pair> pairs = {
        {1, 3.5},
        {2, 1.2},
        {3, 4.8},
        {4, 2.9}
    };

    
    std::vector<Euclid_pair> expected = {
        {2, 1.2},
        {4, 2.9},
        {1, 3.5},
        {3, 4.8}
    };

     
    std::sort(pairs.begin(), pairs.end(), Graph::compareByEuclidValue);

    
    TEST_CHECK(pairs.size() == expected.size());
    for (size_t i = 0; i < pairs.size(); ++i) {
        TEST_CHECK(pairs[i].node == expected[i].node);
        TEST_CHECK(pairs[i].euclid_value == expected[i].euclid_value);

    }

}


// Test case for `filtered_robust_prune`
void test_filtered_robust_prune(void) {
    // Setup: Create a test graph
    int n = 5; // Number of nodes
    int dimension = 2; // Dimensionality of coordinates
    int R = 2; // Maximum number of neighbors
    float alpha = 1.2; // Pruning parameter

    Graph graph(n, dimension);

    // Custom coordinates for the graph
    graph.custom_coordinates(n, {
        {0.0, 0.0}, 
        {1.0, 0.0},
        {0.0, 1.0}, 
        {1.0, 1.0},
        {2.0, 2.0} 
    });

    // Custom adjacency matrix
    graph.custom_graph({
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0} 
    });

    // Custom labels
    graph.custom_label(n, {0, 0, 1, 1, 2});

    // Run filtered robust prune on node 0
    vector<int> neighbors = graph.get_neighbours(0, n); // Get initial neighbors
    graph.filtered_robust_prune(0, neighbors, alpha, R, n, 0);

    // Check adjacency matrix after pruning
    vector<int> pruned_neighbors = graph.get_neighbours(0, n);

    // Expected neighbors for node 0 (after pruning): {1, 2}
    vector<int> expected_neighbors = {1, 2};

    TEST_CHECK(pruned_neighbors.size() == expected_neighbors.size());
    for (size_t i = 0; i < expected_neighbors.size(); i++) {
        TEST_CHECK(pruned_neighbors[i] == expected_neighbors[i]);
    }
}


// Test cases for Graph::sort_euclid
void test_sort_euclid() {
    // Initialize the graph
    Graph g(6, 3);

    // Custom adjacency matrix (not used directly but reflects structure)
    vector<vector<int>> custom = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0}
    };
    g.custom_graph(custom);

    // Coordinates dataset
    vector<vector<double>> dataset = {
        {1, 2, 7},
        {4, 0, 1},
        {2, 1, 9},
        {5, 8, 7},
        {1, 7, 3},
        {8, 6, 6}
    };

    // Test Case 1: Basic case with 3 nodes
    vector<int> L1 = {0, 1, 2};
    vector<double> xq1 = {0, 0, 0};
    int k1 = 2;
    vector<int> expected1 = {1, 0}; // Closest nodes based on Euclidean distance
    TEST_CHECK(g.sort_euclid(L1, k1, xq1) != expected1);

    // Test Case 2: Including a node at a greater distance
    vector<int> L2 = {1, 3, 4};
    vector<double> xq2 = {0, 0, 0};
    int k2 = 2;
    vector<int> expected2 = {1, 4}; // Closest nodes based on Euclidean distance
    TEST_CHECK(g.sort_euclid(L2, k2, xq2) != expected2);

    // Test Case 3: All nodes, higher k value
    vector<int> L3 = {0, 1, 2, 3, 4, 5};
    vector<double> xq3 = {1, 2, 3};
    int k3 = 4;
    vector<int> expected3 = {0, 2, 1, 4}; // Closest nodes based on Euclidean distance
    TEST_CHECK(g.sort_euclid(L3, k3, xq3) != expected3);
}

// Test cases for the Euclid_dist function
void test_Euclid_dist() {
    // Test Case 1: Simple 2D points
    std::vector<double> point1_1 = {0, 0};
    std::vector<double> point2_1 = {3, 4};
    double expected1 = 25.0; // (3^2 + 4^2)
    TEST_CHECK(Euclid_dist(point1_1, point2_1) == expected1);

    // Test Case 2: Identical points
    std::vector<double> point1_2 = {1, 1};
    std::vector<double> point2_2 = {1, 1};
    double expected2 = 0.0; // Distance between identical points
    TEST_CHECK(Euclid_dist(point1_2, point2_2) == expected2);

    // Test Case 3: 3D points
    std::vector<double> point1_3 = {1, 2, 3};
    std::vector<double> point2_3 = {4, 5, 6};
    double expected3 = 27.0; // (3^2 + 3^2 + 3^2)
    TEST_CHECK(Euclid_dist(point1_3, point2_3) == expected3);
}

// Register tests
TEST_LIST = {
    {"permutation", permutation_testing_routine},
    {"set diff", test_set_diff},
    {"unfiltered_medoid",unfiltered_medoid_testing_routine},
    {"intersection",intersection_test},
    {"Euclid dist", test_Euclid_dist},
    {"greedy search",testGreedySearch},
    {"filtered robust prune", test_filtered_robust_prune},
    {"sort euclid", test_sort_euclid},
    {"get neighbours", test_get_neighbours},
    {"set diff", test_set_diff},
    {NULL, NULL} // Sentinel to mark the end of the list
};



/* 
void testRobustPrune(int node, std::vector<int> V, float a,int dimension, int n, int R,vector<vector<double>> table,const std::vector<int> &expected_edges){

    dimension = 2; 
    n = 4;
    R = 2;
    Graph test_graph(dimension,n,10);
    test_graph.construct_random_graph(R,n);
    test_graph.custom_coordinates(n,table);
    test_graph.run_test_case(node, V, a, R, n, expected_edges);
    
}

 


 void vamana_index_test(){
    vector<vector<double>> dataset = {
    {0.0, 0.0},
    {1.0, 2.0},
    {3.0, 4.0},
    {5.0, 6.0},
    {7.0, 8.0},
    {9.0, 10.0}
    };

    int a = 2;
    int L = 3;
    int R = 3;
    cout << "hello" << endl;
    Graph vamanaGraph = vamana_index_create(dataset, a, L, R);

    cout << "Vamana Graph Results...." << endl;
    print_vector(vamanaGraph.GreedySearch({0},{7.0,8.0},2,3,6,{},0).L_k);
    cout << endl;
    vamanaGraph.print();

}  */





/* void test_example(){
    //int R =4;
    //int dimension = 3;

    //intersection_test();
    //medoid_testing_routine();
    
    //permutation_testing_routine();


    //vamana_index_test();

    //testGreedySearch(n,{4},{9.0,10.0},R,dimension);
    // testGreedySearch(n,{1},{1,1,0},R,dimension);
    // testGreedySearch(n,{2},{1,80,15},R,dimension);
    // testGreedySearch(n,{3},{2,2,4},R,dimension);
    // testGreedySearch(n,{4},{45,10,900},R,dimension);
    // testGreedySearch(n,{5},{69,312,920},R,dimension);
 
}


int main(void){
    
    test_example();

}
 */
