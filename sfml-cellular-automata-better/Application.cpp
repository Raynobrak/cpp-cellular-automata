#include "Application.h"

constexpr unsigned WIN_WIDTH = 1000;
constexpr unsigned WIN_HEIGHT = 500;

constexpr float WIN_WIDTH_F = static_cast<float>(WIN_WIDTH);
constexpr float WIN_HEIGHT_F = static_cast<float>(WIN_HEIGHT);

constexpr unsigned GRID_WIDTH = 60;
constexpr unsigned GRID_HEIGHT = 30;

Application::Application() : grid_(GRID_WIDTH, GRID_HEIGHT) {
	window_.create({ WIN_WIDTH, WIN_HEIGHT }, "Simulation");

	grid_.tiles_[GRID_HEIGHT / 2][GRID_WIDTH / 2] = 10;

	font.loadFromFile("bebas.ttf");
}

void Application::run()
{
	sf::Clock renderClock;

	while (window_.isOpen()) {
		sf::Event event;
		while (window_.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window_.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Space:
					step();
					break;
				case sf::Keyboard::Escape:
					window_.close();
					break;
				case sf::Keyboard::R:
					grid_ = SimulationGrid(GRID_WIDTH, GRID_HEIGHT);
					grid_.tiles_[GRID_HEIGHT / 2][GRID_WIDTH / 2] = 10;
					break;
				}
				break;
			}
		}

		if (renderClock.getElapsedTime().asSeconds() >= 0.1f) {
			step();
			renderClock.restart();
			render();
		}
	}
}

void Application::step() {

	// The "value difference" that will be applied to each cell when the calculations are done.
	std::vector<std::vector<int>> deltas;
	for (int i = 0; i < GRID_HEIGHT; ++i) {
		deltas.emplace_back();
		for (int j = 0; j < GRID_WIDTH; ++j)
			deltas[i].emplace_back();
	}

	// Computing the deltas for each cell in the grid
	for (size_t y = 0; y < GRID_HEIGHT; ++y) {
		for (size_t x = 0; x < GRID_WIDTH; ++x) {
			int valCenter = grid_.tiles_[y][x];

			static const int left_behind = 1;
			int value_transfer = valCenter - left_behind;

			if (valCenter > 0) {

				switch (valCenter % 4) {
				case 0: // Transfer to the left
					if (x > 0) { 
						deltas[y][x] -= value_transfer;
						deltas[y][x - 1] += value_transfer;
					}
					break;
				case 1: // Transfer to the right
					if (x < GRID_WIDTH - 1) { 
						deltas[y][x] -= value_transfer;
						deltas[y][x + 1] += value_transfer;
					}
					break;
				case 2: // Transfer up
					if (y > 0) { 
						deltas[y][x] -= value_transfer;
						deltas[y - 1][x] += value_transfer;
					}
					break;
				case 3: // Transfer down
					if (y < GRID_HEIGHT - 1) { 
						deltas[y][x] -= value_transfer;
						deltas[y + 1][x] += value_transfer;
					}
					break;
				}
			}

			// If the current cell has 4 neighbors...
			if (x > 0 && y > 0 && x < GRID_WIDTH - 1 && y < GRID_HEIGHT - 1) {
				// If the current cell and its neighbors all contain the value 1...
				if (
					valCenter == 1 &&
					grid_.tiles_[y][x + 1] == 1 &&
					grid_.tiles_[y][x - 1] == 1 &&
					grid_.tiles_[y + 1][x] == 1 &&
					grid_.tiles_[y - 1][x] == 1) {
					
					deltas[y][x]++; // Generate +1
				}
			}
		}
	}

	// Applying the deltas to the actual grid.
	for (int y = 0; y < GRID_HEIGHT; ++y)
	{
		for (int x = 0; x < GRID_WIDTH; ++x) {
			auto& val = grid_.tiles_[y][x];
			val += deltas[y][x];
			if (val < 0) {
				val = 0;
			}
		}
	}
}

sf::Color colorFromCellValue(int val) {
	static const auto max = 10;

	if (val > max) 
		val = max;

	int col = static_cast<int>(((255.f / (float)max)) * val);
	auto color = sf::Uint8(col);
	return { color,color,color };
}

void Application::render() {
	window_.clear();

	static constexpr float RECT_WIDTH = WIN_WIDTH_F / GRID_WIDTH;
	static constexpr float RECT_HEIGHT = WIN_HEIGHT_F / GRID_HEIGHT;

	for (int y = 0; y < GRID_HEIGHT; ++y)
		for (int x = 0; x < GRID_WIDTH; ++x) {
			sf::RectangleShape tile;
			tile.setPosition({ x * RECT_WIDTH, y * RECT_HEIGHT });
			tile.setSize({ RECT_WIDTH, RECT_HEIGHT });
			tile.setFillColor(colorFromCellValue(grid_.tiles_[y][x]));

			window_.draw(tile);

			//sf::Text txt;

			//txt.setCharacterSize(15);
			//txt.setFont(font);
			//txt.setFillColor(sf::Color::Magenta);
			//txt.setPosition(sf::Vector2f{ x * RECT_WIDTH, y * RECT_HEIGHT } +tile.getSize() * 0.1f);
			//txt.setString(std::to_string(grid_.tiles_[y][x]));

			//window_.draw(txt);
		}

	window_.display();
}

//int Application::findMaxValue() {
//	std::vector<int> localMaximums;
//	for (int i = 0; i < GRID_HEIGHT; ++i) {
//		localMaximums.push_back(*std::max_element(grid_.tiles_[i].begin(), grid_.tiles_[i].end()));
//	}
//
//	return *std::max_element(localMaximums.begin(), localMaximums.end());
//}
