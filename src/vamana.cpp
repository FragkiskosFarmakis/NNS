#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include "functions.h"





void showLoadingAnimation(int durationInSeconds) {
    const char* loadingFrames[] = {"creating vamana index  ", "creating vamana index.  ", "creating vamana index.. ", "creating vamana index..."};
    const int numFrames = 4;
    int frameIndex = 0;

    auto startTime = std::chrono::steady_clock::now();
    while (true) {
        // Print the current frame
        std::cout << "\r" << loadingFrames[frameIndex] << std::flush;

        // Move to the next frame
        frameIndex = (frameIndex + 1) % numFrames;

        // Pause for 250ms
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // Check if the duration has passed
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count() >= durationInSeconds) {
            break;
        }
    }

    // Clear the animation and print a completion message
    std::cout << "\rDone!             " << std::endl;
}


vector<int> error = {3,12,27,41,43,30,51,53,55,80,81,113,116,119,130};


vector<vector<double>> extract_data_from_file(const string& filename) {
    vector<vector<double>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        double value;

        // Determine delimiter based on your file format
        while (ss >> value) {
            row.push_back(value);
            if (ss.peek() == ',' || ss.peek() == ' ')
                ss.ignore();
        }

        data.push_back(row);
    }

    file.close();
    return data;
}



vector<vector<double>> dataset_setup(string filename){
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return {};
    }

    // Declare a 2D vector to store the data
    std::vector<std::vector<double>> matrix;
    
    std::string line;
    // Read the file line by line
    while (std::getline(inputFile, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        float value;

        // Read each value in the line and add it to the row vector
        while (ss >> value) {
            row.push_back(value);
        }

        // Add the row to the 2D matrix
        matrix.push_back(row);
    }

    inputFile.close();


    return matrix;

}

double recall(vector<int> L,vector<double> gt,vector<double> coordinates){

    double similarity = 0;
    for(long unsigned int i = 0; i < L.size();i++){
        for(size_t j = 0; j < gt.size();j++){
            if(L[i] == gt[j]){
                similarity += 1; 
                break;
            }
        }
    }
    
    return similarity/100;
}

 

void print_vectord(vector<double> vec){
     for (auto it = vec.begin(); it != vec.end(); it++)
        std::cout << *it << " ";
}


int main(int argc,char* argv[]){

    



    string datafilebin = "dummy-data.bin";
    string queryfilebin = "dummy-queries.bin";
    string datafile = "data.txt";
    string queryfile = "queries.txt";
    string ground_truth_file = "groundtruth.txt"; 
    double a = 1.5;
    int L = 150;
    int R = 21;

    if(argc > 1){
        if(argc >= 2){
            a =  stod(argv[1]);
        }
        if(argc >= 3){
            L = atoi(argv[2]);
        }
        if(argc >= 4){
            R = atoi(argv[3]);
        }
        if(argc >= 5){
            datafile = argv[4];
        }
        if(argc >= 6){
            queryfile = argv[5];
        }
        if(argc >= 7){
            ground_truth_file = argv[6];
        }

    }

    vector<vector<double>> ground_truth_unfiltered = dataset_setup("groundtruth_unfiltered.txt");
    vector<vector<double>> ground_truth = dataset_setup(ground_truth_file);
    vector<vector<double>> coordinates_nearly = dataset_setup(datafile);
    vector<vector<double>> table = dataset_setup(queryfile); 

    /* ector<vector<double>> ground_truth_unfiltered = dataset_setup("groundtruth_unfiltered.txt");
    vector<vector<double>> ground_truth = dataset_setup(ground_truth_file);
    vector<vector<double>> coordinates_nearly = extract_data_from_file(datafilebin);
    vector<vector<double>> table = extract_data_from_file(queryfilebin); */



    int file_flag = 0;
    string index_filename = "index.bin";
    ifstream file(index_filename);
    if(file.good()){
        file_flag = 1;
    }
    





    vector<vector<double>> coordinates_table = vector<vector<double>>(coordinates_nearly.size(),vector<double>((coordinates_nearly[0].size())-1,0));
    vector<vector<double>> stitched_coordinates = vector<vector<double>>(coordinates_nearly.size(),vector<double>((coordinates_nearly[0].size())-2,0));
    vector<int> stitched_labels(coordinates_nearly.size(),0);
    int scale = 100 - error.size();


    for(size_t i = 0; i < coordinates_nearly.size();i++){
        int z = 0;
        for(size_t j = 0; j < coordinates_nearly[i].size();j++){
            if(j == 1)
                continue;
            coordinates_table[i][z] = coordinates_nearly[i][j];
            z++;
        }
    }

    for(size_t i = 0; i < stitched_labels.size();i++){
        stitched_labels[i] = coordinates_nearly[i][0];
    }

    for(size_t i = 0; i < coordinates_nearly.size();i++){
        int z = 0;
        for(size_t j = 0; j < coordinates_nearly[i].size();j++){
            if(j == 1 || j == 0)
                continue;
            stitched_coordinates[i][z] = coordinates_nearly[i][j];
            z++;
        }
    }

    cout << "Menu: " << endl << "1)Filtered Vamana" << endl;
    cout << "2)Stiched Vamana" << endl;
    int choice = 0;
    cin >> choice;

    //showLoadingAnimation(10);

    
        
    //vamana.print();






    vector<int> where(150,0);
    int k = 0;
    for(long unsigned int i = 0; i < table.size();i++){
        if(table[i][0] == 1){
        where[k] = i;
        k++; 
        }
        if(k == 150){
        break;
        }
    }

    vector<vector<int>> matrix;
    double recall_avg = 0;
    auto start = std::chrono::high_resolution_clock::now();
    if(choice == 1){
        cout << "Running filtered vamana..." << endl;
        if(file_flag == 0){


            std::ofstream outputFile("index.bin", std::ios::binary | std::ios::app);
            if (!outputFile) {
                std::cerr << "Error: Cannot open or create file " << " index.bin!" << std::endl;
                return -77;
            }
            Graph generator = filtered_vamana_index_create(coordinates_table,a,L,R);
            matrix = generator.extract_adjacency_matrix();
            


            size_t sz = matrix.size();

            outputFile.write(reinterpret_cast<const char*>(&sz), sizeof(size_t));
            outputFile.write(reinterpret_cast<const char*>(&sz), sizeof(size_t));

            for (const auto& row : matrix) {
                outputFile.write(reinterpret_cast<const char*>(row.data()), sz * sizeof(int));
            }

            outputFile.close();
            cout << "Index succesfully writen to index.bin!" << endl;
    
        }
        
        else{
            //load adj_matrix get size then create graph
            std::ifstream inputFile("index.bin", std::ios::binary);
            if (!inputFile) {
                std::cerr << "Error: Cannot open file " << "index.bin" << std::endl;
                return -77;
            }

            size_t sz;
            inputFile.read(reinterpret_cast<char*>(&sz), sizeof(size_t));
            inputFile.read(reinterpret_cast<char*>(&sz), sizeof(size_t));

            std::vector<std::vector<int>> vec(sz, std::vector<int>(sz));

            // Read the data into the 2D vector
            for (size_t i = 0; i < sz; ++i) {
                inputFile.read(reinterpret_cast<char*>(vec[i].data()), sz * sizeof(int));
            }
            matrix = vec;

            inputFile.close();


        }
        auto stop = std::chrono::high_resolution_clock::now();
        cout << "Matrix size: " << matrix.size() << " n: " << coordinates_nearly[0].size() << endl;
        Graph vamana(coordinates_nearly.size(),coordinates_nearly[0].size()-2);
        vamana.insert_adjacency_matrix(coordinates_nearly.size(),matrix);
        vamana.insert_coordinates_table(stitched_coordinates.size(),stitched_coordinates);
        vamana.insert_label_table(stitched_labels.size(),stitched_labels);

        /* cout << "Printing matrix.... " << endl;
        for(size_t l = 0; l < matrix.size();l++){
            for(size_t b = 0; b < matrix[l].size();b++){
                cout << matrix[l][b];
            }
            cout << endl;
        } */




    
        cout << "vamana index construction done!!!" << endl;
        cout << "running some filtered queries..." << endl;
        for(int i=0; i < 100;i++){

            int exist = 0;
            for(size_t j = 0; j < error.size();j++){
                if(i == error[j]){
                    exist = 1;
                    break;
                }
            }

            if(exist == 1){
                continue;
            }



            vector<double> xq;
            for(size_t z = 4; z < table[where[i]].size();z++){
                xq.insert(xq.end(),table[where[i]][z]);
            }

            struct mpair p;
            double qlabel = table[where[i]][1];

            int starting = 0;
            for(size_t l = 0; l < coordinates_nearly.size();l++){
                if(coordinates_nearly[l][0] == qlabel){
                    starting = l;
                    break;
                }
            }
            p.L_k = vamana.GreedySearch({starting},xq,100,150,10000,qlabel,1).L_k;


            //vector<int> nei = vamana.get_neighbours(starting,10000);
        
            //cout << endl;
      
            //cout << "Greedy done!" << endl;
            vector<vector<double>> coordinates;



            for(size_t z=0; z < p.L_k.size();z++){
                coordinates.insert(coordinates.end(),vamana.get_coordinates(p.L_k[z]));
            }



            double recall_it  = recall(p.L_k,ground_truth[i],xq);
            recall_avg += recall_it;
            cout << "Recall " << i << ": " << recall_it<< endl; 
         
        }
        cout << "Filtered Average Recall: " << recall_avg/(scale+3)<< endl; //calculate recall rate



        k = 0;
        for(long unsigned int i = 0; i < table.size();i++){
            if(table[i][0] == 0){
                where[k] = i;
                k++; 
            }
            if(k == 150){
                break;
            }
        }




        recall_avg = 0;
        cout << "running some unfiltered queries..." << endl;
        for(int i=0; i < 100;i++){



            vector<double> xq;
            for(size_t z = 4; z < table[where[i]].size();z++){
                xq.insert(xq.end(),table[where[i]][z]);
            }

            struct mpair p;
            double qlabel = -1;


            p.L_k = vamana.GreedySearch({911},xq,100,150,10000,qlabel,0).L_k;

        //vector<int> nei = vamana.get_neighbours(starting,10000);
        //cout << endl;
      
        //cout << "Greedy done!" << endl;
            vector<vector<double>> coordinates;


            for(size_t z=0; z < p.L_k.size();z++){
                coordinates.insert(coordinates.end(),vamana.get_coordinates(p.L_k[z]));
            }




            double recall_it  = recall(p.L_k,ground_truth_unfiltered[i],xq);
            recall_avg += recall_it;
            cout << "Recall " << i << ": " << recall_it << endl; 
         
        }
        auto duration = chrono::duration_cast<std::chrono::seconds>(stop - start);
        cout << "Unfiltered Average Recall: " << recall_avg/scale << endl; //calculate recall rate
        cout << "Building index duration === " << duration.count() << endl;

        }
    else if(choice == 2){
        auto start = std::chrono::high_resolution_clock::now();
        if(file_flag == 0){


            std::ofstream outputFile("index.bin", std::ios::binary | std::ios::app);
            if (!outputFile) {
                std::cerr << "Error: Cannot open or create file " << " index.bin!" << std::endl;
                return -77;
            }
            Graph generator = Stitched_Vamana_Index_Create(stitched_coordinates,stitched_labels,a,L,R,R);
            matrix = generator.extract_adjacency_matrix();

            size_t sz = matrix.size();

            outputFile.write(reinterpret_cast<const char*>(&sz), sizeof(size_t));
            outputFile.write(reinterpret_cast<const char*>(&sz), sizeof(size_t));

            for (const auto& row : matrix) {
                outputFile.write(reinterpret_cast<const char*>(row.data()), sz * sizeof(int));
            }

            outputFile.close();
            cout << "Index succesfully written to index.bin!" << endl;
    
        }
        else{
            //load adj_matrix get size then create graph
            std::ifstream inputFile("index.bin", std::ios::binary);
            if (!inputFile) {
                std::cerr << "Error: Cannot open file " << "index.bin" << std::endl;
                return -77;
            }

            size_t sz;
            inputFile.read(reinterpret_cast<char*>(&sz), sizeof(size_t));
            inputFile.read(reinterpret_cast<char*>(&sz), sizeof(size_t));

            std::vector<std::vector<int>> vec(sz, std::vector<int>(sz));

            // Read the data into the 2D vector
            for (size_t i = 0; i < sz; ++i) {
                inputFile.read(reinterpret_cast<char*>(vec[i].data()), sz * sizeof(int));
            }
            matrix = vec;

            inputFile.close();


        }

        auto stop = std::chrono::high_resolution_clock::now();
        cout << "Matrix size: " << matrix.size() << " n: " << coordinates_nearly[0].size() << endl;
        Graph stiched_vamana(coordinates_nearly.size(),coordinates_nearly[0].size()-2);
        stiched_vamana.insert_adjacency_matrix(coordinates_nearly.size(),matrix);
        stiched_vamana.insert_coordinates_table(stitched_coordinates.size(),stitched_coordinates);
        stiched_vamana.insert_label_table(stitched_labels.size(),stitched_labels);





        recall_avg = 0;
        cout << "vamana stiched construction done!!!" << endl;
        cout << "running some filtered queries..." << endl;
        for(int i=0; i < 100;i++){

            int exist = 0;
            for(size_t j = 0; j < error.size();j++){
                if(i == error[j]){
                    exist = 1;
                    break;
                }
            }

            if(exist == 1){
                continue;
            }



            vector<double> xq;
            for(size_t z = 4; z < table[where[i]].size();z++){
                xq.insert(xq.end(),table[where[i]][z]);
            }

            struct mpair p;
            double qlabel = table[where[i]][1];

            int starting = 0;
            for(size_t l = 0; l < coordinates_nearly.size();l++){
                if(coordinates_nearly[l][0] == qlabel){
                    starting = l;
                    break;
                }
            }
            p.L_k = stiched_vamana.GreedySearch({starting},xq,100,150,10000,qlabel,1).L_k;


            vector<int> nei = stiched_vamana.get_neighbours(starting,10000);
        
            cout << endl;
      
            //cout << "Greedy done!" << endl;
            vector<vector<double>> coordinates;



            for(size_t z=0; z < p.L_k.size();z++){
                coordinates.insert(coordinates.end(),stiched_vamana.get_coordinates(p.L_k[z]));
            }



            double recall_it  = recall(p.L_k,ground_truth[i],xq);
            recall_avg += recall_it;
            cout << "Recall " << i << ": " << recall_it << endl; 
         
        }
        cout << "Filtered Average Recall: " << recall_avg/(scale+3) << endl; //calculate recall rate
 
        //Graph stiched_vamana = vamana_index_create(stitched_coordinates,1.5,150,21);
        recall_avg = 0;
        k = 0;
        for(long unsigned int i = 0; i < table.size();i++){
            if(table[i][0] == 0){
                where[k] = i;
                k++; 
            }
            if(k == 150){
                break;
            }
        }





        cout << "running some unfiltered queries..." << endl;
        for(int i=0; i < 100;i++){



            vector<double> xq;
            for(size_t z = 4; z < table[where[i]].size();z++){
                xq.insert(xq.end(),table[where[i]][z]);
            }

            struct mpair p;
            double qlabel = -1;


            p.L_k = stiched_vamana.GreedySearch({911},xq,100,150,10000,qlabel,0).L_k;

            //vector<int> nei = vamana.get_neighbours(starting,10000);
            //cout << endl;
      
            //cout << "Greedy done!" << endl;
            vector<vector<double>> coordinates;


            for(size_t z=0; z < p.L_k.size();z++){
                coordinates.insert(coordinates.end(),stiched_vamana.get_coordinates(p.L_k[z]));
            }




            double recall_it  = recall(p.L_k,ground_truth_unfiltered[i],xq);
            recall_avg += recall_it;
            cout << "Recall " << i << ": " << recall_it << endl; 
         
        } 
        auto duration = chrono::duration_cast<std::chrono::seconds>(stop - start);
        cout << "Unfiltered Average Recall: " << recall_avg/scale << endl; //calculate recall rate
        cout << "Building index duration === " << duration.count() << endl;

        }

    return 0;
}

