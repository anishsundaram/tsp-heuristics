double nearest_neighbour(uint start){ 
    partial_tour.push_back(start);// Start with a partial tour with just one city i, randomly chosen
    double total_weight=0;
    unordered_set<int> visited;
    visited.insert(start);
    //Let (1,...,k) be the current partial tour (k < n).  Find city k+ 1 that is not yet in the tour and that is closer to k.
    int k = start;
    int closest_node = 0;
    for (uint vertex = 0; vertex < num_vertices-1; ++vertex){
        double min = std::numeric_limits<double>::max(); // Highest value for comparison
        closest_node = 0;
        for(uint neighbour = 0; neighbour < num_vertices; ++neighbour){
            if(visited.find(neighbour) != visited.end()){
                continue;
            }
            if(vertices[k].get_edge_length_MST(vertices[neighbour],MST_flag)< min){
                closest_node = neighbour;
                min = vertices[k].get_edge_length_MST(vertices[neighbour],MST_flag);
            }
        }
        partial_tour.push_back(closest_node);
        k = closest_node;
        visited.insert(closest_node);
        total_weight+=min;
    }
    partial_tour.push_back(closest_node);
    total_weight+=vertices[k].get_edge_length_MST(vertices[start],MST_flag);
    
  std::cout << std::fixed<< std::setprecision(2) << total_weight << '\n';
    //Always show 2 decimal places
    for(uint i = 0; i < partial_tour.size()-1; ++i){ //print list
        std::cout << partial_tour[i] << " ";
        }
    
    return 0;
}//nearest_neighbour(uint start)