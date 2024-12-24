/*
*
* Filename      : graph.cpp
* Programmer(s) : Berat Yildizer
******************************************************************************/

#include "graph.h"

graph* graph::p = nullptr;

graph::graph(int v) : number_of_vertices{ v }, adj_matrix{ v, std::vector<int>(v,0) } { }

graph::graph(std::string& s) : adj_matrix{ 0, std::vector<int>(0,0) } {
	read_graph_file(s);
}

graph::~graph() {
	if (p != nullptr) {
		delete p;
	}
}

void graph::add_edge(int x, int y)
{
	if (x >= number_of_vertices || y >= number_of_vertices)
		throw my_exception{};

	adj_matrix[x][y] = 1;
	adj_matrix[y][x] = 1;
}

int graph::vertices_degree(int x)const
{
	if (x >= number_of_vertices)
		throw my_exception{};

	int count{};

	for (int i = 0; i < number_of_vertices; ++i) {
		if (adj_matrix[x][i] == 1)
			++count;
	}

	return count;
	
}

void graph::set_vertices_degree(unsigned int val)
{
	number_of_vertices = val;

	adj_matrix.resize(number_of_vertices);

	for (auto& s : adj_matrix) {
		s.resize(number_of_vertices);
	}

}

bool graph::check_neighboor(int x, int y)const
{
	if (x >= number_of_vertices || y >= number_of_vertices)
		throw my_exception{};

	return adj_matrix[x][y];
}

std::vector<std::vector<int>> graph::get_adj_matrix()const {
	return adj_matrix;
}

int graph::get_number_of_vertices(void)const
{
	return number_of_vertices;
}

void graph::read_graph_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == 'c') continue;

        std::istringstream iss(line);

        if (line[0] == 'p') {
            std::string tmp;
            int numEdges;
            iss >> tmp >> tmp >> number_of_vertices >> numEdges;
            adj_matrix.resize(number_of_vertices);  

			for (auto& s : adj_matrix) {
				s.resize(number_of_vertices);
			}
			
        }

       
        if (line[0] == 'e') {
            char e;
            int u, v;
            iss >> e >> u >> v;

			--u;
			--v;

            adj_matrix[u][v] = 1;
            adj_matrix[v][u] = 1;

			//std::cout << u << v << "\n";
        }
    }

    file.close();
}

graph* get_instance(void) {
	if (graph::p == nullptr) {
		graph::p =  new graph;
	}

	return graph::p;
}

graph* get_instance(int v) {
	if (graph::p == nullptr) {
		graph::p = new graph{v};
	}

	return graph::p;
}

graph* get_instance(std::string& s) {
	if (graph::p == nullptr) {
		graph::p = new graph{ s };
	}

	return graph::p;
}

std::vector<std::pair<int,color_list>> graph_colouring(const graph& r)
{

	using pair_type_v = std::pair<int, int>;
	using pair_type_c = std::pair<int, color_list>;

	std::vector<pair_type_v> vertices_degrees{};

	for (int i{}; i < r.number_of_vertices; ++i) {
		vertices_degrees.emplace_back( i, r.vertices_degree(i) );
	}

	std::sort(vertices_degrees.begin(), vertices_degrees.end(), [](const pair_type_v& x, const pair_type_v& y) {
		return x.second > y.second;
		});

	std::vector<pair_type_c> graph_color{};
	color_list color_counter{ white };

	for (auto i{ vertices_degrees.begin() }; i < vertices_degrees.end(); ++i) {

		if (std::find_if(graph_color.begin(), graph_color.end(), [&i](const pair_type_c& x) {return x.first == i->first; }) == graph_color.end()) {
			graph_color.emplace_back(i->first, color_counter);

			for (auto j = i + 1; j < vertices_degrees.end(); ++j) {
				if (r.check_neighboor(i->first, j->first) == false ) {
					if (std::find_if(graph_color.begin(), graph_color.end(), [&j](const pair_type_c& x) {return x.first == j->first; }) == graph_color.end())
						graph_color.emplace_back(j->first, color_counter);
				}
			}

			color_counter = static_cast<color_list>(static_cast<int>(color_counter) + 1u);
			
		}

		
	}

	return graph_color;

}