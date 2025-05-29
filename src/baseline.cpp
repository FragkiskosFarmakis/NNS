/**
 *  Example code using sampling to find KNN.
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include "io.h"
#include <iterator>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

double Euclid_dist(vector<double> point1,vector<double> point2){
    int size = point1.size();
    double distance = 0;
    for(int i = 0; i < size;i++){
        distance += (point1.at(i)-point2.at(i))*(point1.at(i)-point2.at(i));
    }
    //distance = sqrt(distance);
    return distance;
}
struct Euclid_pair {
    int node;
    double euclid_value;
};

bool compareByEuclidValue(const Euclid_pair& a, const Euclid_pair& b) {//ovveride std::sort function
        return a.euclid_value < b.euclid_value;
    }

vector<int> sort_euclid(vector<int> L,int k,vector<double> xq,vector<vector<double>> coordinates_table){
        vector<int> result_nodes;
        int size = L.size();
        vector<struct Euclid_pair> e(size);

        for(int i = 0; i < size;i++){//load values in e
            e[i].node = L[i];
            e[i].euclid_value = Euclid_dist(coordinates_table[i],xq);
        }
        sort(e.begin(),e.end(),compareByEuclidValue);

        

        for(int i = 0; i < k;i++){ 
            result_nodes.insert(result_nodes.end(),e[i].node);
        }

        return result_nodes;
    }


vector<int> brute_force_groundtruth(vector<vector<float>> data,vector<float> query,int cut){
    int label = query[1];
    vector<double> euclid;
    vector<double> coordinates;
    vector<vector<double>> coordinates_table;
    vector<int> nodes;
cout << endl << "TEST 4" << endl << endl;
    for(size_t j = 4; j < query.size();j++){
        coordinates.insert(coordinates.end(),query[j]);
    }
    for(size_t i = 0; i < data.size();i++){
      if(data[i][0] == label || label == -1){
        nodes.push_back(i);

        vector<double> temp;
        for(size_t z = 2; z < data[i].size();z++){
          temp.push_back(data[i][z]);
        }
      
        coordinates_table.push_back(temp);
      }
 
    }



      cout << endl << "TEST 6" << endl << endl;

    vector<int> res =  sort_euclid(nodes,cut,coordinates,coordinates_table);
    cout << endl << "TEST 7" << endl << endl;
    
    return res;
}










float compare_with_id(const std::vector<float>& a, const std::vector<float>& b) {
  float sum = 0.0;
  // Skip the first 2 dimensions
  for (size_t i = 2; i < a.size(); ++i) {
    float diff = a[i] - b[i];
    sum += diff * diff;
  }
  return sum;
}


int main(int argc, char **argv) {
  string source_path = "dummy-data.bin";
  string query_path = "dummy-queries.bin";
  string knn_save_path = "output.bin";

  // Also accept other path for source data
  if (argc > 1) {
    source_path = string(argv[1]);
  }

  uint32_t num_data_dimensions = 102;
  float sample_proportion = 0.001;

  // Read data points
  vector <vector<float>> nodes;
  ReadBin(source_path, num_data_dimensions, nodes);
  cout<<nodes.size()<<"\n";
  // Read queries
  uint32_t num_query_dimensions = num_data_dimensions + 2;
  vector <vector<float>> queries;
  ReadBin(query_path, num_query_dimensions, queries);

  vector <vector<uint32_t>> knn_results; // for saving knn results

  uint32_t n = nodes.size();
  uint32_t d = nodes[0].size();
  uint32_t nq = queries.size();
  uint32_t sn = uint32_t(sample_proportion * n);

  cout<<"# data points:  " << n<<"\n";
  cout<<"# data point dim:  " << d<<"\n";
  cout<<"# queries:      " << nq<<"\n";




  std::ofstream outFile("queries.txt");

    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Write the 2D vector to the file
    for (const auto& row : queries) {
        for (const auto& elem : row) {
            outFile << elem << " "; // Write each element followed by a space
        }
        outFile << "\n"; // New line after each row
    }

    // Close the file
    outFile.close();





 std::ofstream outFile2("data.txt");

    if (!outFile2) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Write the 2D vector to the file
    for (const auto& row : nodes) {
        for (const auto& elem : row) {
            outFile2 << elem << " "; // Write each element followed by a space
        }
        outFile2 << "\n"; // New line after each row
    }

    // Close the file
    outFile2.close();

  cout << endl << "TEST 0" << endl << endl;

  //find the 100 first queries with query type 1
  vector<int> where(150,0) ;
  int k = 0;
  for(long unsigned int i = 0; i < queries.size();i++){
    cout << queries[i][0] << endl;
    if(queries[i][0] == 1){
      where[k] = i;
      k++; 
    }
    if(k == 150){
      break;
    }
  }


  cout << "where" << endl;
  for(size_t i = 0; i < k ;i++){
    cout << where[i] << " ";
  }
  cout << endl;





  cout << endl << "TEST 1" << endl << endl;
  std::ofstream outFile3("groundtruth.txt");
  vector<vector<int>> groundtruth;
  //vector<vector<double>> groundtruth = vector<vector<double>>(2,vector<double>(10000,0));
  vector<vector<int>> res = vector<vector<int>>(k,vector<int>(k,0));
  cout << endl << "TEST 2" << endl << endl;
  for(size_t i = 0; i < k; i++){
    res[i] = brute_force_groundtruth(nodes,queries[where[i]],100);
    groundtruth.insert(groundtruth.end(),res[i]);
  }




    if (!outFile3) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Write the 2D vector to the file
    for (const auto& row : groundtruth) {
        for (const auto& elem : row) {
            outFile3 << elem << " "; // Write each element followed by a space
        }
        outFile3 << "\n"; // New line after each row
    }

    // Close the file
    outFile3.close();


  k = 0;
  for(long unsigned int i = 0; i < queries.size();i++){
    cout << queries[i][0] << endl;
    if(queries[i][0] == 0){
      where[k] = i;
      k++; 
    }
    if(k == 150){
      break;
    }
  }




  std::ofstream outFile4("groundtruth_unfiltered.txt");
  vector<vector<int>> groundtruth_unfiltered;
  //vector<vector<double>> groundtruth = vector<vector<double>>(2,vector<double>(10000,0));
  vector<vector<int>> res2 = vector<vector<int>>(k,vector<int>(k,0));
  cout << endl << "TEST 2" << endl << endl;
  for(size_t i = 0; i < k; i++){
    res2[i] = brute_force_groundtruth(nodes,queries[where[i]],100);
    groundtruth_unfiltered.insert(groundtruth_unfiltered.end(),res2[i]);
  }




    if (!outFile4) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Write the 2D vector to the file
    for (const auto& row : groundtruth_unfiltered) {
        for (const auto& elem : row) {
            outFile4 << elem << " "; // Write each element followed by a space
        }
        outFile4 << "\n"; // New line after each row
    }

    // Close the file
    outFile4.close();

















  /** A basic method to compute the KNN results using sampling  **/
  const int K = 100;    // To find 100-NN

  for(uint i = 0; i < nq; i++){
    uint32_t query_type = queries[i][0];
    int32_t v = queries[i][1];
    float l = queries[i][2];
    float r = queries[i][3];
    vector<float> query_vec;

    // first push_back 2 zeros for aligning with dataset
    query_vec.push_back(0);
    query_vec.push_back(0);
    for(uint j = 4; j < queries[i].size(); j++)
      query_vec.push_back(queries[i][j]);

    vector<uint32_t> knn; // candidate knn

    // Handling 4 types of queries
    if(query_type == 0){  // only ANN
        for(uint32_t j = 0; j < sn; j++){
            knn.push_back(j);
        }
    }
    else if(query_type == 1){ // equal + ANN
        for(uint32_t j = 0; j < sn; j++){
            if(nodes[j][0] == v){
                knn.push_back(j);
            }
        }
    }
    else if(query_type == 2){ // range + ANN
      for(uint32_t j = 0; j < sn; j++){
        if(nodes[j][1] >= l && nodes[j][1] <= r)
          knn.push_back(j);
      }
    }
    else if(query_type == 3){ // equal + range + ANN
      for(uint32_t j = 0; j < sn; j++){
        if(nodes[j][0] == v && nodes[j][1] >= l && nodes[j][1] <= r)
          knn.push_back(j);
      }
    }

    // If the number of knn in the sampled data is less than K, then fill the rest with the last few nodes
    if(knn.size() < K){
      uint32_t s = 1;
      while(knn.size() < K) {
        knn.push_back(n - s);
        s = s + 1;
      }
    }

    // build another vec to store the distance between knn[i] and query_vec
    vector<float> dists;
    dists.resize(knn.size());
    for(uint32_t j = 0; j < knn.size(); j++)
      dists[j] = compare_with_id(nodes[knn[j]], query_vec);

    vector<uint32_t > ids;
    ids.resize(knn.size());
    std::iota(ids.begin(), ids.end(), 0);
    // sort ids based on dists
    std::sort(ids.begin(), ids.end(), [&](uint32_t a, uint32_t b){
        return dists[a] < dists[b];
    });
    vector<uint32_t> knn_sorted;
    knn_sorted.resize(K);
    for(uint32_t j = 0; j < K; j++){
      knn_sorted[j] = knn[ids[j]];
    }
    knn_results.push_back(knn_sorted);
  }

  // save the results
  SaveKNN(knn_results, knn_save_path);
  return 0;
}