#pragma once

#include <SFML/Graphics/Font.hpp>
#include <array>

//
// Repr�sente l'identifiant d'une police.
// Cette �num�ration est cens�e �tre utilis�e avec le FontsHolder.
//
enum FontID
{
	Default,
	MAX_VALUE
};

//
// S'occuppe de charger, stocker et fournir un acc�s � des polices d'�criture.
//
class FontsHolder
{
public:

	FontsHolder();
	~FontsHolder();

	//
	// Retourne un pointeur vers la police correspondant � l'ID donn�.
	//
	std::shared_ptr<sf::Font> getFontPtr(FontID id);

private:

	//
	// Charge la police correspondant � l'ID donn� et l'ajoute au conteneur.
	//
	void loadFont(FontID id);

	std::map<FontID, std::shared_ptr<sf::Font>> _fonts;

	// Tableau contenant les chemins d'acc�s de tous les fichiers de polices.
	const std::array<std::string, FontID::MAX_VALUE> FONTS_PATHS = { "Assets/fonts/gameplay.ttf" };
};

