#pragma once

#include <vector>

struct SimulationGrid {
	SimulationGrid(unsigned width, unsigned height);
	std::vector<std::vector<int>> tiles_;
};