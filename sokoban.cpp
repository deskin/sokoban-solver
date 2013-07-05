#include <iostream>
#include <string>
#include <utility>

#include "errors.h"
#include "bfs_simulator.h"

namespace sok = sokoban;

int main(int argc, char **argv) {
	std::string s;
	std::string line;

	while(std::getline(std::cin, line)) {
		s += std::move(line);
		s += "\n";
	}

	try {
		sok::bfs_simulator sim(s);
		sim.run();

		if (sim.win()) {
			const sok::bfs_simulator::steps_type &steps(
				sim.steps());
			std::cout << "Solved in " << steps.size() - 1
				<< " moves." << std::endl;

			std::cout << sim.solve_calls() << " calls to solve()."
				<< std::endl;

			for (size_t i = 0; i < steps.size(); ++i) {
				std::cout << "Step " << i << ":" << std::endl;
				std::cout << steps[i] << std::endl;
			}
		} else {
			std::cout << "Could not solve level." << std::endl;
		}
	} catch (const sok::level_parse_exception &) {
		std::cerr << "Level parsing error!" << std::endl;
	}
}
