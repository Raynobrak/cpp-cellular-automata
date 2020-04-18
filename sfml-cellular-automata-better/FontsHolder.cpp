#include "FontsHolder.h"

#include <iostream>

FontsHolder::FontsHolder()
{
}

FontsHolder::~FontsHolder()
{
}

std::shared_ptr<sf::Font> FontsHolder::getFontPtr(FontID id)
{
	if (_fonts.count(id) == 0)
	{
		loadFont(id);
	}

	return _fonts[id];
}

void FontsHolder::loadFont(FontID id)
{
	auto newFont = std::make_shared<sf::Font>();

	std::string path = FONTS_PATHS[static_cast<size_t>(id)];

	// On essaie de charger la police...
	if (!newFont->loadFromFile(path))
	{
		// Probl�me lors du chargement !
		std::cout << "Probl�me lors du chargement de la police '" << path << "'. Chemin d'acc�s invalide.";
	}
	
	_fonts.emplace(id, newFont);
}
