
double ArbInsert(uint start){   //Takes in a value for the arbitrary start location i, usually 0
    partial_tour.push_back(start); //insert starting point into mst vector
    uint initial_index = 0;
    uint stop_index = 0;
    double total_weight=0;
    double min = std::numeric_limits<double>::max(); // Highest value for comparison
    for (uint i = 0; i < num_vertices; ++i) //Get minimum distance to point j to build partial tour (i,j) from all nodes/vertices
    {
        if(i == start)//Skip start
            continue;
        if (vertices[0].edge_length(vertices[i],MST_flag)< min)
        {
            min = vertices[0].edge_length(vertices[i],MST_flag);
            initial_index = i;
        }
    }
    total_weight += 2 * min;    //add two of min weight for underestimate
    partial_tour.push_back(initial_index);
    partial_tour.push_back(0);
    
    //Find the edge{i, j}, belonging to the partial tour, that minimizes cik +ckj −cij.  Insert kbetween i and j
    for (uint possible_stops = 1; possible_stops < num_vertices; ++possible_stops){
        min = std::numeric_limits<double>::max();
        if(possible_stops == initial_index || possible_stops == start){
            continue;
        }
        for(uint tour_stop = 0; tour_stop < partial_tour.size()-1; ++tour_stop){
            double temp_weight = vertices[partial_tour[tour_stop]].edge_length(vertices[possible_stops],MST_flag)   //Calculates length of cik
            + vertices[partial_tour[tour_stop+1]].edge_length(vertices[possible_stops],MST_flag)    //Calculates length of ckj
            - vertices[partial_tour[tour_stop]].edge_length(vertices[partial_tour[tour_stop+1]],MST_flag);
            if(temp_weight < min){
                min = temp_weight;
                stop_index = tour_stop;
            }
        }
        total_weight+=min;
        partial_tour.insert(partial_tour.begin()+stop_index+1,1,possible_stops); //insert the vertex into the partial at the specified position
        
    }
    partial_tour.pop_back();// to prevent recounting start location
   
    cout << std::fixed<< std::setprecision(2) << total_weight << '\n';
    //Always show 2 decimal places
    for(uint i = 0; i < partial_tour.size(); ++i){ //print list
        cout << partial_tour[i] << " ";
        }
    
    return 0;
}//ArbInsert(uint start)
`
