//Classes
#include "AssetManager.h"

//Initialize static data
std::map < std::string, sf::Texture> AssetManager::textures;
std::map <std::string, sf::SoundBuffer> AssetManager::soundBuffers;
std::map <std::string, sf::Font> AssetManager::fonts;



sf::Texture& AssetManager::RequestTexture(std::string textureName)
{
    auto pairFound = textures.find(textureName); //Find values in the map

    if (pairFound != textures.end())
    {

        //We found an existing texture
        return pairFound->second; //the value in the key-value pair

    }
    else
    {
        sf::Texture& newTexture = textures[textureName];
        newTexture.loadFromFile("Assets/Graphics/" + textureName + ".png");
        return newTexture;
    }
}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string bufferName)
{
    auto pairFound = soundBuffers.find(bufferName); //Find values in the map

    if (pairFound != soundBuffers.end())
    {

        //We found an existing sound buffer
        return pairFound->second; //the value in the key-value pair

    }
    else
    {
        sf::SoundBuffer& newBuffer = soundBuffers[bufferName];
        newBuffer.loadFromFile("Assets/Audio/" + bufferName + ".ogg");
        return newBuffer;
    }
}

sf::Font& AssetManager::RequestFont(std::string fontName)
{
    auto pairFound = fonts.find(fontName); //Find values in the map

    if (pairFound != fonts.end())
    {

        //We found an existing font
        return pairFound->second; //the value in the key-value pair

    }
    else
    {
        sf::Font& newFont = fonts[fontName];
        newFont.loadFromFile("Assets/Fonts/" + fontName + ".ttf");
        return newFont;
    }
}

void AssetManager::DestroyAllAssets()
{
    textures.clear();
    soundBuffers.clear();
    fonts.clear();

}
