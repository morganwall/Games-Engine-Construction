#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <assert.h>
#include "Texture2D.h"

class TextureManager
{
public:
	std::unordered_map<std::string, Texture2D> m_Textures; // An unordered map of the game's textures.
	const std::string m_BackupKey{ "Backup.png" }; // The key for the backup texture.

	// Gets the file name from the file path.
	std::string GetFileNameFromPath(const std::string& path) { return path.substr(path.find_last_of("/\\") + 1); }
	// Creates a backup texture, made up of random coloured pixels.
	bool CreateBackupTexture(Texture2D& texture2D);

public:
	// Load texture from given file path, with the texture's size.
	bool LoadTexture(const std::string& path, const Vector2<unsigned int>& size = { 32, 32 });
	// Gets a reference to a texture, from the map, with the key. If the key cannot be found within the map, it will return a reference to the backup texture.
	Texture2D& GetTexture2D(const std::string& key);
	// Returns number of textures.
	size_t GetNumTextures() { return m_Textures.size(); }
	// Gets the key, from the map, at an index.
	std::string GetKeyAtIndex(unsigned int index);

	TextureManager();
	~TextureManager() {}
};