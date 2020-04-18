#pragma once

#include <SFML/Graphics/Font.hpp>
#include <array>

//
// Représente l'identifiant d'une police.
// Cette énumération est censée être utilisée avec le FontsHolder.
//
enum FontID
{
	Default,
	MAX_VALUE
};

//
// S'occuppe de charger, stocker et fournir un accès à des polices d'écriture.
//
class FontsHolder
{
public:

	FontsHolder();
	~FontsHolder();

	//
	// Retourne un pointeur vers la police correspondant à l'ID donné.
	//
	std::shared_ptr<sf::Font> getFontPtr(FontID id);

private:

	//
	// Charge la police correspondant à l'ID donné et l'ajoute au conteneur.
	//
	void loadFont(FontID id);

	std::map<FontID, std::shared_ptr<sf::Font>> _fonts;

	// Tableau contenant les chemins d'accès de tous les fichiers de polices.
	const std::array<std::string, FontID::MAX_VALUE> FONTS_PATHS = { "Assets/fonts/gameplay.ttf" };
};

