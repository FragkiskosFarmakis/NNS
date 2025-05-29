#include "functions.h"

//General utility functions
void print_vector(vector<int> vec){
     for (auto it = vec.begin(); it != vec.end(); it++)
        cout << *it << " ";
}





//Greedy Search utility functions
vector<int> set_diff(vector<int> L,vector<int> V){
    int size1 = L.size();
    int size2 = V.size();
    vector<int> res;
  

    for(int i = 0;i < size1;i++){
        int flag = 0;
        for(int j = 0; j < size2;j++){
           flag = 0;
           if(L[i] == V[j]){
                flag = 1;
                break;
           }
        }
        if(flag == 0){
            res.insert(res.end(),L.at(i));
        }       
    }
    return res;
}



double Euclid_dist(vector<double> point1,vector<double> point2){
    int size = point1.size();
    double distance = 0;
    for(int i = 0; i < size;i++){
        distance += (point1.at(i)-point2.at(i))*(point1.at(i)-point2.at(i));
    }
    //distance = sqrt(distance);
    return distance;
}
 



int exists(int table[],int item,int len){
    for(int i=0;i < len;i++){
        if(table[i] == item){
            return 1;
        }
    }
    return 0;
}

int intersection(int query_filter,int node_label,int query_type){
    
    if(query_type > 1 || query_type < 0){
        return -1;
    }

    if(query_type == 0){
        return 1;
    }


    return query_filter == node_label;
}



vector<int> random_bit_vector(int R,int n,int offset){
    vector<int> bit_vec(n,0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0,n-1); 
    vector<int> table;

    int err_table[ERROR_TOL]; //error table
    int err_it = 0;

    
    for(int i = 0;i < R;i++){


        int random_number = distrib(gen);
        while(exists(err_table,random_number,err_it) || random_number == offset){ //the random number is unique
            random_number = distrib(gen);
        }


        table.push_back(random_number);
        err_table[err_it] = random_number;
        err_it++;
    }

    for(int i = 0; i < R;i++){
        bit_vec.at(table[i]) = 1;
    }


    return bit_vec;
}







    Graph::Graph(int n,int dimension){
        adj_matrix = vector<vector<int>>(n,vector<int>(n,0));
        coordinates_table = vector<vector<double>>(n,vector<double>(dimension,0));
        label_table = vector<int>(n,0);
    }
    void Graph::add_edge(int u,int v){
        adj_matrix[u][v] = 1;
    }

    void Graph::print()
    {
        // Get the number of vertices
        cout << "Adjacency Matrix for the Graph: " << endl;
        int n = adj_matrix.size();
        for (int i = 0; i < n; i++) {  
            for (int j = 0; j < n; j++) {
                cout << adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void Graph::custom_graph(vector<vector<int>> custom){
        for(long unsigned int i = 0; i < custom.size();i++){
            adj_matrix[i] = custom[i];
        }
    }



    vector<double> Graph::get_coordinates(int node){
        return coordinates_table[node];
    }


    //used in choosing the k closest values given a list

    bool Graph::compareByEuclidValue(const Euclid_pair& a, const Euclid_pair& b) {//ovveride std::sort function
        return a.euclid_value < b.euclid_value;
    }
 
    vector<int> Graph::sort_euclid(vector<int> L,int k,vector<double> xq){
        vector<int> result_nodes;
        int size = L.size();
        vector<struct Euclid_pair> e(size);

        for(int i = 0; i < size;i++){//load values in e
            e[i].node = L[i];
            e[i].euclid_value = Euclid_dist(coordinates_table[e[i].node],xq);
        }
        sort(e.begin(),e.end(),compareByEuclidValue);

        

        for(int i = 0; i < k;i++){ 
            result_nodes.insert(result_nodes.end(),e[i].node);
        }

        return result_nodes;
    }
  
    void Graph::print_coordinates(int dimension){
        // Get the number of vertices
        cout << "Coordinates Table for the Graph: " << endl;
        int n = coordinates_table.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < dimension; j++) {
                cout << coordinates_table[i][j] << " ";
            }
            cout << endl;
        }
    }

    void Graph::print_labels(int label_size){
        // Get the number of vertices
        cout << "Label Table for the Graph: " << endl;
        int n = label_table.size();
        for (int i = 0; i < n; i++) {
            cout << label_table[i] << " ";
        }
    }



    void Graph::construct_random_graph(int R,int n){
        for(int i = 0;i < n;i++){
            adj_matrix.at(i) = random_bit_vector(R,n,i); 
        }
    }

    
    void Graph::custom_coordinates(int n,const vector<vector<double>>& table){
        for(int i = 0; i < n;i++){
            coordinates_table.at(i) = table.at(i);
        }
    }

    void Graph::insert_adjacency_matrix(int n,const vector<vector<int>>& table){
        for(int i = 0; i < n;i++){
            adj_matrix.at(i) = table.at(i);
        }
    }

    void Graph::insert_coordinates_table(int n,const vector<vector<double>>& table){
        for(int i = 0; i < n;i++){
            coordinates_table.at(i) = table.at(i);
        }
    }

    void Graph::insert_label_table(int n,const vector<int> table){
        for(int i = 0; i < n;i++){
            label_table.at(i) = table.at(i);
        }
    }



    vector<vector<int>> Graph::extract_adjacency_matrix(){
        vector<vector<int>> table = vector<vector<int>>(adj_matrix.size(),vector<int>(adj_matrix.size(),0));
        for(size_t i = 0; i < adj_matrix.size();i++){
            table.at(i) = adj_matrix.at(i);
        }
        return table;
    }

    vector<vector<double>> Graph::extract_coordinates_table(){
        vector<vector<double>> table = vector<vector<double>>(coordinates_table.size(),vector<double>(coordinates_table.size(),0));
        for(size_t i = 0; i < coordinates_table.size();i++){
            table.at(i) = coordinates_table.at(i);
        }
        return table;
    }

    vector<int> Graph::extract_label_table(){
        vector<int> table(label_table.size(),0);
        for(size_t i = 0; i < adj_matrix.size();i++){
            table.at(i) = label_table.at(i);
        }
        return table;
    }





    void Graph::custom_label(int n,const vector<int>& table){
        for(int i = 0; i < n;i++){
            label_table[i] = table[i];
        }
    }




    void Graph::get_random_coordinates(int n,int dimension){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0,100);
        vector<vector<double>> dum;
        for(int i = 0; i < n;i++){
            for(int j= 0; j < dimension;j++){
                coordinates_table[i][j] = distrib(gen);
            }
        }
    }

    vector<vector<int>> Graph::get_adjacency_matrix(){
        return adj_matrix;
    }




    void Graph::get_random_label(int n,int label_size){//1 if node has label i else 0
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0,1);
        vector<vector<double>> dum;
        for(int i = 0; i < n;i++){
            label_table[i] = distrib(gen);
        }
    }








    vector<int> Graph::get_neighbours(int node,int n){
        vector<int> vec = adj_matrix[node];
        vector<int> neighbours;
        for(int i = 0; i < n;i++){
            if(vec[i] == 1){
                neighbours.insert(neighbours.end(),i);
            }
        }
        return neighbours;
    } 
   
    int Graph::get_label(int node){
        return label_table[node];
    }





    //Greedy Search
    mpair Graph::GreedySearch(vector<int> s,vector<double> x_q,int k,int list_size,int n,int query_filter,int query_type){//maybe private 
        vector<int> L;
        vector<int> V;
        L.insert(L.end(),s[0]); //initialize with s



        if(L.size() == 0){
            cout << "Error:Starting set doesn't exist or incorrect." << endl;
        }


        vector<int> set_minus = L;
        while(set_minus.size() != 0){
            

            double min = Euclid_dist(x_q,coordinates_table[set_minus[0]]);
            int size = set_minus.size();
            int p = set_minus[0];
            for(int i = 1;i < size;i++){
                double val = Euclid_dist(x_q,coordinates_table[set_minus[i]]);
                if(min > val){
                    min = val;
                    p = set_minus[i];
                }
            }

            V.push_back(p);


          
            vector<int> p_neighbours =  get_neighbours(p,n);
            vector<int> p_neighbour_star;
            //filter the neigbours with labels
            for(long unsigned int i = 0; i  < p_neighbours.size();i++){

                int already_visited = 0;// p' not in V
                for(long unsigned int k = 0; k < V.size();k++){
                    if(p_neighbours[i] == V[k]){
                        already_visited = 1;
                        break;
                    }
                }
                if(intersection(label_table[p_neighbours[i]],query_filter,query_type) != 0 && already_visited == 0){//critical point 1
                    p_neighbour_star.insert(p_neighbour_star.end(),p_neighbours[i]);
                }

            }
            
            L.insert(L.end(), p_neighbour_star.begin(),p_neighbour_star.end());
            sort(L.begin(),L.end());
            auto last = unique(L.begin(),L.end());
            L.erase(last, L.end()); 

            sort(V.begin(),V.end());
            auto lastV = unique(V.begin(),V.end());
            V.erase(lastV,V.end());

            //dont allow to put the query point in L
            for(long unsigned int i = 0; i < L.size();i++){ //is the query point in the dataset ?
                if(coordinates_table[L[i]] == x_q){
                    L.erase(L.begin() + i);
                    break;
                }
            }
            for(long unsigned int i = 0; i < V.size();i++){
                if(coordinates_table[V[i]] == x_q){
                    V.erase(V.begin() + i);
                    break;
                }
            }
            int s = L.size();
            if(s > list_size){           
                L = sort_euclid(L,k,x_q);
                                       
            }

            set_minus = (set_diff(L,V));//renew the L-V
            
        }


        struct mpair returnStruct;
        returnStruct.V = V;

        for(int i = 0;i < k;i++){
            returnStruct.L_k.push_back(L[i]);
        } 
        
        return returnStruct;
    }
    //robust prune and testing
    void Graph::filtered_robust_prune(int node,vector<int> V,float a,int R,int n,int query_type){
        
        

        int size = V.size(); // initialize V
        for(int i = 0; i < size;i++){
            if(V[i] == node){
                V.erase(V.begin() + i);
                break;
            }
        }

        vector<int> p_neighbours = get_neighbours(node,n);
        V.insert(V.end(), p_neighbours.begin(),p_neighbours.end());


        sort(V.begin(),V.end());
        auto last = unique(V.begin(),V.end());
        V.erase(last, V.end()); 

      


        for(int i = 0; i < n;i++){
            adj_matrix[node][i] = 0; //delete all neighbors
        }
        //print V.size
        while(V.size() != 0){
            size = V.size();
            double min = Euclid_dist(coordinates_table[node],coordinates_table[V[0]]);//find min from V
            int p = V[0];
            for(int i = 1;i < size;i++){
                double val = Euclid_dist(coordinates_table[node],coordinates_table[V[i]]);
                if(min > val){
                    min = val;
                    p = V[i]; //p
                }
            }

            adj_matrix[node][p] = 1; //add to neighbours


            int neighbours = 0;

            for(int i=0; i<n; i++){
                if(adj_matrix[node][i] == 1){
                    neighbours++;
                }
            }


            if(neighbours == R){
                break;
            }
            int i = 0;
            while(i < size){

                double dist1 = Euclid_dist(coordinates_table[p],coordinates_table[V[i]]);
                double dist2 = Euclid_dist(coordinates_table[node],coordinates_table[V[i]]);


                if(query_type != 0){ // V[i] = p', node = p ,p = p*
                    if((label_table[V[i]] == label_table[node] && label_table[V[i]] != label_table[p])){
                        i++;
                        continue;
                    }
                }
                else if(label_table[V[i]] != label_table[p]){
                    i++;
                    continue;
                }



                if(a*dist1 <= dist2){
                    
                    V.erase(V.begin() + i);     
                    i--;
                    size--;   
                }
                
                i++;
            }
    



        }

    }

    void Graph::run_test_case(int node, std::vector<int> V, float a, int R, int n, const std::vector<int> expected_edges) {
       

        filtered_robust_prune(node, V, a, R, n,0);
   

        int actual_edges = 0;
        for (int i = 0; i < n; ++i) {
            if (adj_matrix[node][i] == 1) {
                actual_edges++;
            }
        }

        if((long unsigned int)actual_edges == expected_edges.size()){
             // Print in green
            cout << "\033[32m[ PASSED ROBUST PRUNE TEST ]\033[0m" << endl << endl;  // Green
        } 
        else {
            // Print in red
            cout << "\033[31m[ FAILED ROBUST PRUNE TEST ]\033[0m" << endl << endl;  // Red
        }
         
    }

    //vamana index creation


    int unfiltered_find_medoid(vector<vector<double>> dataset){

        double min = -1;
        int pos = 1;
        int sz = dataset.size();
        vector<vector<double>> Dynamic_Euclid = vector<vector<double>>(sz,vector<double>(sz,0));
        for(long unsigned int i = 0; i < dataset.size();i++){
            double avg = 0;
            
            for(long unsigned int j = 0; j < dataset.size();j++){
                if(Dynamic_Euclid[i][j] == 0 && Dynamic_Euclid[j][i] == 0){
                    Dynamic_Euclid[i][j] = Euclid_dist(dataset[i],dataset[j]);
                    avg += Dynamic_Euclid[i][j];
                }
                else{
                    if(Dynamic_Euclid[i][j] != 0){
                        avg += Dynamic_Euclid[i][j];
                    }
                    else{
                        avg += Dynamic_Euclid[j][i];
                    }
                }
            }
            
            avg = avg/dataset.size();
            if(i == 1){
                min = avg; 
            }
            else{
                if(min > avg){
                    min = avg;
                    pos = i;
                }
            }


        }
        return pos;
    }

    vector<int> FindMedoid(vector<vector<double>> dataset,int threshold){//one filter return only one label 
        int n = dataset.size();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0,n);
        vector<int> starting_nodes;

        vector<int> labels;
        for(size_t i = 0; i < dataset.size();i++){
            int temp_label = dataset[i][0];
            int exist = 0;
            for(size_t j = 0; j < labels.size();j++){
                if(labels[j] == temp_label){
                    exist = 1;
                }
            }
            if(exist == 0){
                labels.insert(labels.end(),temp_label);
            }
        }

        if(threshold > n){
            threshold = n;
        }

        for(size_t i = 0; i < labels.size();i++){
            int min = n+1;
            //cout << i << endl;
            vector<int> sample;
            for(int j = 0; j < threshold;j++){ //sample t items from dataset
                int node = distrib(gen);

                if(dataset[node][0] != labels[i]){
                    sample.insert(sample.end(),node);
                    if(node < min){
                        min = node;
                    }
                }
                else{
                    j--;
                }
            }
            starting_nodes.insert(starting_nodes.end(),min);
        }
        return starting_nodes;//maybe the one with smallest id ? 
    }








    vector<int> get_random_permutation(int n){
        vector<int> list;
        for(int i = 0; i < n;i++){
            list.insert(list.end(),i);
        }
        random_device rd;
        mt19937 gen(rd());


        vector<int> perm;
        for(int i = 0; i < n;i++){
            int size = list.size();
            uniform_int_distribution<> distrib(0,size-1);
            int random_number = distrib(gen);
            perm.insert(perm.end(),list[random_number]);
            list.erase(list.begin() + random_number);
        }

        return perm;
    } 


     Graph vamana_index_create(vector<vector<double>> dataset,double a,int L,int R){
        int n = dataset.size();
        long unsigned int dimension = dataset[0].size();
        Graph vamana(n,dimension);

        cout << "n " << n << endl;

        if(n < R){
            R = n-2;
        }
        vamana.construct_random_graph(R,n);

        cout << "construct R-random graph" << endl;

        vamana.custom_coordinates(n,dataset);
        

        cout << "find the medoid of dataset s" << endl;
        
        int s = unfiltered_find_medoid(dataset);
        cout << "create random permutation σ(i)..." << endl;
        vector<int> sigma = get_random_permutation(n);
        
        for(int i = 0; i < n;i++){
            cout << "node: " << i << endl;
            struct mpair res = vamana.GreedySearch({s},dataset[sigma[i]],1,L,n,-1,0);//perform greedy search to σ(i)
            

    

            vamana.filtered_robust_prune(sigma[i],res.V,a,R,n,0); //robust prune to update all out-neighbours


            vector<int> sigmaNeighbours = vamana.get_neighbours(sigma[i],n);//Nout(sigma[i])
                
            for(long unsigned int j = 0; j < (vamana.get_neighbours(sigma[i],n)).size();j++){
                //ensure that sigma[i] isnt already a neigbour of j
                vector<int> j_neighbours = vamana.get_neighbours(sigmaNeighbours[j],n);//Nout(j)
                
            
                int exist = 0;
                int offset = 1;
                for(long unsigned int z = 0; z < j_neighbours.size();z++){//sigma[i] already exists in the neighbours of j no need to add
                    if(j_neighbours[z] == sigma[i]){
                        exist = 1;
                        break;
                    }
                }
                
                if(exist == 1){
                    offset = 0;
                }
                
                
                if((vamana.get_neighbours(sigmaNeighbours[j],n)).size()+offset > (long unsigned int)R){



                    if(exist == 0){    
                        j_neighbours.insert(j_neighbours.end(),sigma[i]);
                    }    

                    vamana.filtered_robust_prune(sigmaNeighbours[j],j_neighbours,a,R,n,0);
                }
                else{
                    vamana.add_edge(sigmaNeighbours[j],sigma[i]);
                }

            }
        }

        
        
        return vamana;


};













    Graph filtered_vamana_index_create(vector<vector<double>> dataset,double a,int L,int R){
        long unsigned int n = dataset.size();
        long unsigned int dimension = dataset[0].size();
        Graph vamana(n,dimension);

        vector<int> temp;//initialize the label table
        for(size_t k = 0; k < dataset.size();k++){
            temp.insert(temp.end(),dataset[k][0]);
        }
        vamana.custom_label(n,temp);


        cout << "n " << n << endl;
        vector<vector<int>> zeroes = vector<vector<int>>(n,vector<int>(n,0));

        cout << "construct empty graph" << endl;
        //vamana.custom_graph(zeroes);
        vamana.construct_random_graph(50,n);
        vector<vector<double>> transit = vector<vector<double>>(n,vector<double>(dimension-1,0));
        for(size_t i = 0; i < n; i++){
            for(size_t j = 2; j < dimension;j++){
                transit[i][j-1] = dataset[i][j];
            }
        }
        dimension = transit[0].size();
        cout << "n x dim == " << transit.size() << " x " << transit[0].size() << endl;


        vamana.custom_coordinates(n,transit);


        cout << "find the medoid of dataset s" << endl;
        int threshold = 10;
        vector<int> medoid;
        medoid = FindMedoid(dataset,threshold);
        cout << "filtered medoid done" << endl;
        int s = unfiltered_find_medoid(transit);
        cout << "medoid = " << s << endl;

        cout << "create random permutation σ(i)..." << endl;
        vector<int> sigma = get_random_permutation(n);
        




        
        for(long unsigned int i = 0; i < n;i++){
            cout << "node: " << i << endl;
            //find specific medoid for σ(i) label
            int label = vamana.get_label(sigma[i]);
            int query_type = 1;
            if(label == -1){
                cout << "Returning -1 as error code and cutting execution !!!!!" << endl;
                query_type = 0;
                return vamana;
            }
            else{
                for(size_t k = 0; k < medoid.size();k++){
                    if(label == vamana.get_label(medoid[k])){
                        s = medoid[k];
                        break;
                    }
                }
            }

            struct mpair res = vamana.GreedySearch({s},vamana.get_coordinates(sigma[i]),0,L,n,label,query_type);//perform greedy search to σ(i)
            cout << "Greedy done" <<endl;
    

            vamana.filtered_robust_prune(sigma[i],res.V,a,R,n,query_type); //robust prune to update all out-neighbours
            cout << "Robust prune done" << endl;

            vector<int> sigmaNeighbours = vamana.get_neighbours(sigma[i],n);//Nout(sigma[i])
                
            for(long unsigned int j = 0; j < (vamana.get_neighbours(sigma[i],n)).size();j++){
                //ensure that sigma[i] isnt already a neigbour of j
                vector<int> j_neighbours = vamana.get_neighbours(sigmaNeighbours[j],n);//Nout(j)
                
            
                int exist = 0;
                int offset = 1;
                for(long unsigned int z = 0; z < j_neighbours.size();z++){//sigma[i] already exists in the neighbours of j no need to add
                    if(j_neighbours[z] == sigma[i]){
                        exist = 1;
                        break;
                    }   
                }
                
                if(exist == 1){
                    offset = 0;
                }
                
                
                vamana.add_edge(sigmaNeighbours[j],sigma[i]);
                if((vamana.get_neighbours(sigmaNeighbours[j],n)).size()+offset > (long unsigned int)R){

                    if(exist == 0){    
                        j_neighbours.insert(j_neighbours.end(),sigma[i]);
                    }    

                    vamana.filtered_robust_prune(sigmaNeighbours[j],j_neighbours,a,R,n,query_type);
                }

            }
            
        }
    
        
        return vamana;


}

Graph Stitched_Vamana_Index_Create(vector<vector<double>> dataset,vector<int> labels,double a,int L_small,int R_small,int R_stitched){
    int n = dataset.size();
    int dimension = dataset[0].size();    
    Graph stitched_vamana(n,dimension);

    stitched_vamana.custom_label(n,labels);

    cout << "n " << n << endl;
    vector<vector<int>> zeroes = vector<vector<int>>(n,vector<int>(n,0));

    cout << "construct empty graph" << endl;
    //stitched_vamana.custom_graph(zeroes);
    stitched_vamana.construct_random_graph(R_small,n);

    vector<int> label_table;//find out the labels
    for(size_t i = 0; i < labels.size();i++){
        int exists = 0;
        for(size_t j = 0; j < label_table.size();j++){
            if(label_table[j] == labels[i]){
                exists = 1;
                break;
            }
        }
        if(exists == 0){
            label_table.push_back(labels[i]);
        }
    }
    vector<int> label_times(label_table.size(),0);
    for(size_t i = 0; i < labels.size();i++){//find out how many nodes have each label
        for(size_t j = 0; j < label_table.size();j++){
            if(label_table[j] == labels[i]){
                label_times[j]++;
                break;
            }
        }
    }




    vector<Graph> Subgraphs;
    vector<vector<int>> rebuild_table;
    for(size_t i = 0; i < label_table.size();i++){
        vector<vector<double>> P_f;
        rebuild_table.push_back({});
        int p_f_count = 0;
        for(size_t k = 0; k < labels.size();k++){
            if(labels[k] == label_table[i]  && label_times[i] > 1){//if the labels match

                

                P_f.push_back({});//add the coordinates of the point in P_f
                for(size_t z = 0; z < dataset[k].size();z++){
                    P_f[p_f_count].push_back(dataset[k][z]);
                }
                p_f_count++;
                rebuild_table[i].push_back(k);
            }
            else if(label_times[i] <= 1 && labels[k] == label_table[i]){
                rebuild_table[i].push_back(0);
            }
            
        }
                
        cout << "building vamana" << endl;
        if(P_f.size() < 2){
            Graph dummy(10,10);
            Subgraphs.push_back(dummy);
            continue;
        }
        Subgraphs.push_back(vamana_index_create(P_f,a,L_small,R_stitched));
        cout << "vamana i constructed" << endl;
    }
    

    for(size_t i = 0; i < label_table.size();i++){
        if(label_times[i] < 2){
            continue;
        }

        vector<vector<int>> matrix = Subgraphs[i].get_adjacency_matrix();//take the adjacency matrix of each subgraph
        for(size_t k = 0; k < matrix.size();k++){
            for(size_t z = 0; z < matrix[k].size();z++){//if in the subrgraph they connect translate into the big graph and add the edge
            cout << " k :" << k << " z: " << z << " i:" << i << endl;
                if(matrix[k][z] == 1){
                    stitched_vamana.add_edge(rebuild_table[i][k],rebuild_table[i][z]);
                }    
            }
        }
    }


    return stitched_vamana;
}

