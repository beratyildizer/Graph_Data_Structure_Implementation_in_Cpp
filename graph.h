/*
*
* Filename      : graph.h
* Programmer(s) : Berat Yildizer
******************************************************************************/

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
#include <exception> 

enum color_list : unsigned int {
	white = 0,
	yellow,
	blue,
	red,
	green,
	brown,
	black,
	wheat,
	hotPink,
	pink,
	gray,
	silver,
	orange,
	royalBlue,
	olive,
	golden,
	color_1,
	color_2,
	color_3,
	color_4,
	color_5,
	color_6,
	color_7,
	color_8,
	color_9,
	color_10,
	color_11,
	color_12,
	color_13,
	color_14,
	color_15,
	color_16,
	color_17,
	color_18,
	color_19,
	color_20,
	color_21,
	color_22,
	color_23,
	color_24,
	color_25,
	color_26,
	color_27,
	color_28,
	color_29,
	color_30
};

class graph {
public:
	graph(const graph&) = delete;
	graph& operator=(const graph&) = delete;
	~graph();

	void add_edge(int x, int y);
	int vertices_degree(int x)const;
	void set_vertices_degree(unsigned int x);
	bool check_neighboor(int x, int y)const;
	std::vector<std::vector<int>> get_adj_matrix(void)const;
	int get_number_of_vertices(void)const;
	void read_graph_file(const std::string& filename);


private:
	graph() = default;
	graph(int v);
	graph(std::string&);
	int number_of_vertices = 0;
	std::vector<std::vector<int>> adj_matrix;
	std::string file_name;

	static graph* p;
	friend graph* get_instance(void);
	friend graph* get_instance(int v);
	friend graph* get_instance(std::string& s);
	friend std::vector<std::pair<int, color_list>> graph_colouring(const graph& r);
};

graph* get_instance(void);
graph* get_instance(int v);
graph* get_instance(std::string& s);
std::vector<std::pair<int, color_list>> graph_colouring(const graph& r);

class my_exception : public std::exception {
public:
	virtual const char* what()const noexcept override {
		return "Undefined Behaviour!!!";
	}
};






























