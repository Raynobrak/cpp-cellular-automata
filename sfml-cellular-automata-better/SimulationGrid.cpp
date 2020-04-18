#include "SimulationGrid.h"

SimulationGrid::SimulationGrid(unsigned width, unsigned height) {
	for (int i = 0; i < height; ++i) {
		tiles_.emplace_back(); 
		for (int j = 0; j < width; ++j) {
			tiles_[i].emplace_back();
		}
	}
}
