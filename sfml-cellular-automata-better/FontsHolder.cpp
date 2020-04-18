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
		// Problème lors du chargement !
		std::cout << "Problème lors du chargement de la police '" << path << "'. Chemin d'accès invalide.";
	}
	
	_fonts.emplace(id, newFont);
}
