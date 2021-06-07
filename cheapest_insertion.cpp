double cheapest_insertion(uint start){
    partial_tour.push_back(start);
    unordered_set<int> visited;
    visited.insert(start);
    partial_tour.push_back(start);//Start with a partial tour with just one city i, randomly chosen.
    uint stop_index = 0;
    double total_weight=0;
    
    for(uint k = 0; k < vertices.size();++k){
        double min_tour = std::numeric_limits<double>::max();
        if(visited.find(k) != visited.end()){
            continue;
        }
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