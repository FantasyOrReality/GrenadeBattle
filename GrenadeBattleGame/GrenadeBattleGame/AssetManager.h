#pragma once

//Default libraries
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <map>

class AssetManager
{
public:

	static sf::Texture& RequestTexture(std::string textureName);
	static sf::SoundBuffer& RequestSoundBuffer(std::string bufferName);
	static sf::Font& RequestFont(std::string fontName);

	static void DestroyAllAssets();


private:

	static std::map < std::string, sf::Texture> textures;
	//static std::map <std::string, sf::SoundBuffer> soundBuffers;
	//static std::map <std::string, sf::Font> fonts;

};

