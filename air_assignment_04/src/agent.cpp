/*
* Daniel Vázquez
* Aritifiacial Intelligence for Robots
* MAS SS 2016
* Assignment 3
*
* modified by Maximilian Mensing, Torsten Jandt
*
* agent.cpp
* */

#include "agent.hpp"

#include <iostream>
#include <stack>

#include <chrono>
#include <thread>

#include <queue>
#include <stack>

using namespace std;

Agent::Agent(vector<vector<string> > map, const pair<int, int> initial_pos,
    int number_of_goals, int search_option) :
    map(map), initial_pos(initial_pos), number_of_goals(number_of_goals), search_option(
        search_option), number_of_stored_nodes(0), number_of_visited_nodes(
            0) {

            }

            Agent::~Agent() {

            }

            void Agent::run() {

                if (search_option == 1) {
                    cout << "Running BFS " << endl;
                    cout << "Number of goals " << number_of_goals << endl;
                    bfs();
                } else {
                    cout << "Running DFS " << endl;
                    cout << "Number of goals " << number_of_goals << endl;
                    dfs();
                }

            }

            void Agent::print_map() {
                system("clear");

                for (int row = 0; row < map_rows; row++) {
                    for (int col = 0; col < map_cols; col++) {
                        cout << map[row][col];
                    }
                    cout << endl;
                }

                this_thread::sleep_for(chrono::milliseconds(10));

            }

            void Agent::bfs() {
                queue<pair<int, int> > nodes_queue;
                pair<int, int> current_node;

                nodes_queue.push(make_pair(initial_pos.first, initial_pos.second));
                number_of_stored_nodes++;

                while (nodes_queue.size() > 0) {
                    current_node = nodes_queue.front();
                    nodes_queue.pop();

                    int row = current_node.first;
                    int col = current_node.second;
                    string data = map[row][col];
                    if((data == " " || data == "s" || data == "*"))  {
                        if (is_free(row - 1, col)){
							nodes_queue.push(make_pair(row - 1, col));
							number_of_stored_nodes+=1;
						}
						if (is_free(row + 1, col)){
                        	nodes_queue.push(make_pair(row + 1, col));
                        	number_of_stored_nodes+=1;
						}
                        if (is_free(row, col - 1)){
							nodes_queue.push(make_pair(row, col - 1));
                        	number_of_stored_nodes+=1;
						}
                        if (is_free(row, col + 1)){
							nodes_queue.push(make_pair(row, col + 1));
    	                    number_of_stored_nodes+=1;
						}
                        number_of_visited_nodes++;
                        if(data == "*") {
                            goal_positions.push_back(make_pair(row, col));
                            map[row][col] = "G";
                        } else {
                            map[row][col] = "-";
                        }
                        print_map();
                    }
                }
                print_evaluation_metrics("queue");
            }

            void Agent::dfs() {
                stack<pair<int, int> > nodes_stack;
                pair<int, int> current_node;

                nodes_stack.push(make_pair(initial_pos.first, initial_pos.second));
                number_of_stored_nodes++;

                while (nodes_stack.size() > 0) {
                    current_node = nodes_stack.top();
                    nodes_stack.pop();

                    int row = current_node.first;
                    int col = current_node.second;
                    string data = map[row][col];
                    if(is_free(row, col)) {
                        if (is_free(row - 1, col)){
                            nodes_stack.push(make_pair(row - 1, col));
                            number_of_stored_nodes+=1;
                        }
                        if (is_free(row + 1, col)){
                            nodes_stack.push(make_pair(row + 1, col));
                            number_of_stored_nodes+=1;
                        }
                        if (is_free(row, col - 1)){
                            nodes_stack.push(make_pair(row, col - 1));
                            number_of_stored_nodes+=1;
                        }
                        if (is_free(row, col + 1)){
                            nodes_stack.push(make_pair(row, col + 1));
                            number_of_stored_nodes+=1;
                        }

						number_of_visited_nodes++;
                        if(data == "*") {
                            goal_positions.push_back(make_pair(row, col));
                            map[row][col] = "G";

                        } else {
                            map[row][col] = "-";

                        }
                        print_map();
                    }
                }
                print_evaluation_metrics("stack");

            }

            bool Agent::is_free(int row, int col) {
                return is_free(map[row][col]);
            }

            bool Agent::is_free(string str) {
                return (str == " " || str == "s" || str == "*");
            }

            void Agent::print_evaluation_metrics(string data_structure_name) {
                print_map();
                cout << "All the possible nodes have been explored " << endl;
                cout << "Found " << goal_positions.size() << " of " << number_of_goals
                << endl;
                cout << "Maximum size of the " << data_structure_name << " : "
                << number_of_stored_nodes << endl;
                cout << "Number of stored nodes: " << number_of_stored_nodes << endl;
                cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
                print_goal_positions();
            }

            void Agent::print_goal_positions() {
                cout << "Goals: " << endl;
                for (int i = 0; i < goal_positions.size(); i++) {
                    cout << i + 1 << ": (" << goal_positions[i].first << ", "
                    << goal_positions[i].second << ")" << endl;
                }
            }
