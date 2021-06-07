double arbitrary_insertion(uint start){//Takes in a value for the arbitrary start location i, usually 0
    partial_tour.push_back(start);
    unordered_set<int> visited;
    visited.insert(start);
    uint initial_index = 0;
    uint stop_index = 0;
    double total_weight=0;
    double min_tour = std::numeric_limits<double>::max();
    for (uint i = 0; i < num_vertices; ++i)//Get minimum distance to point j to build minimum partial tour (i,j,i) from all nodes/vertices
    {
        if(i == start)
            continue;
        if (vertices[0].get_edge_length_MST(vertices[i],MST_flag)< min_tour)
        {
            min_tour = vertices[0].get_edge_length_MST(vertices[i],MST_flag);
            initial_index = i;
        }
    }
    total_weight += 2 * min_tour;
    visited.insert(initial_index);
    partial_tour.push_back(initial_index); //Add J to partial tour (i,j,i)
    partial_tour.push_back(start);
    
    double min_ckj=0;
    uint k = 0;
    while(visited.size() != num_vertices){
        //Find cities k and j (j belonging to the partial tour and k not belonging) for which ckj is minimized
        k = rand() % num_vertices; //Arbitrary value to insert nearest to a value in subtour
        while(visited.find(k)!=visited.end()){
            k = rand() % num_vertices;
        }
        min_ckj = std::numeric_limits<double>::max();
        min_tour = std::numeric_limits<double>::max();
        for(uint tour_stop = 0; tour_stop < partial_tour.size()-1; ++tour_stop){ //Finding i
            double temp_weight = vertices[partial_tour[tour_stop]].get_edge_length_MST(vertices[k],MST_flag)   //Calculates length of cik
            + vertices[partial_tour[tour_stop+1]].get_edge_length_MST(vertices[k],MST_flag)    //Calculates length of ckj
            - vertices[partial_tour[tour_stop]].get_edge_length_MST(vertices[partial_tour[tour_stop+1]],MST_flag); //Calculates length of cij
            
            if(temp_weight < min_tour){
                min_tour = temp_weight;
                stop_index = tour_stop;
            }
        }
        total_weight+=min_tour;
        partial_tour.insert(partial_tour.begin()+stop_index+1,1,k);
        visited.insert(k);
    }
    partial_tour.pop_back();// to prevent recounting start location
   
    std::cout << std::fixed<< std::setprecision(2) << total_weight << '\n';
    //Always show 2 decimal places
    for(uint i = 0; i < partial_tour.size(); ++i){ //print list
        std::cout << partial_tour[i] << " ";
        }
    
    return 0;
}//nearest_insertion(uint start)