#include "TextureManager.h"

bool TextureManager::CreateBackupTexture(Texture2D& texture2D)
{
    Vector2<unsigned int> size{ texture2D.GetSize() }; // Get the size of the current texture.
    std::vector<sf::Uint8> pixels(size.x * size.y * 4); // Create a vector of pixels. Multiply by 4 as each pixel has 4 components (R, G, B, A).

    for (unsigned int x = 0; x < size.x; x++) // Loop through the pixels.
    {
        for (unsigned int y = 0; y < size.y; y++)
        {
            // Assign random values to the r, g, b, and 255 to alpha.
            pixels[(x + y * size.x) * 4 + 0] = rand() % 256; // R.
            pixels[(x + y * size.x) * 4 + 1] = rand() % 256; // G.
            pixels[(x + y * size.x) * 4 + 2] = rand() % 256; // B.
            pixels[(x + y * size.x) * 4 + 3] = 255; // A.
        }
    }

    if (!texture2D.GetSFTexture().create(size.x, size.y)) // Create the texture with the default size.
    {
        std::cout << "Failed to Create Backup Texture!\n\n";
        return false;
    }
    std::cout << "Backup Texture Created.\n\n";
    texture2D.GetSFTexture().update(pixels.data()); // Update the texture with the pixel data.

    return true;
}

bool TextureManager::LoadTexture(const std::string& path, const Vector2<unsigned int>& size)
{
    Texture2D texture2D; // Temp Texture2D.
    if (!texture2D.GetSFTexture().loadFromFile(path))
    {
        printf("Failed to Create Texture from Path!\nCreating Backup Texture...\n");
        if (!CreateBackupTexture(texture2D)) // Create a backup texture.
            return false;
    }

    std::string fileName{ GetFileNameFromPath(path) }; // Set the file name from the path

    texture2D.SetSize(size); // Set the size of the texture.

    m_Textures[fileName] = texture2D; // Add the texture to the map, with the file name as the key.

    return true;
}

Texture2D& TextureManager::GetTexture2D(const std::string& key)
{
    assert(!m_Textures.empty() && "The Texture Map is Empty!");

    //std::unordered_map<const std::string, Texture2D>::iterator texture{ m_Textures.find(key) };
    
    auto texture{ m_Textures.find(key) }; // Didn't wanna use auto, but works for now. TODO: Maybe replace auto with something else.

    if (texture != m_Textures.end()) // If the texture iterator doesn't equal .end, it means we found a matching key.
        return texture->second;

    // Failed to Find Key.
    std::cout << "Failed to Find " << key << " in the Texture Map!\nUsing Backup Texture.\n\n";
    texture = m_Textures.find(m_BackupKey); // Get the backup texture.

    return texture->second;
}

std::string TextureManager::GetKeyAtIndex(unsigned int index)
{
    if (index > m_Textures.size() || index < 0) // Check that the index is valid.
    {
        std::cout << "Invalid index!\n\n";
        return " ";
    }

    int curIndex{ 0 };
    for (std::pair<const std::string, Texture2D>& texture : m_Textures) // Loop through all of the textures.
    {
        if (curIndex == index)
            return texture.first;
        curIndex++;
    }

    return " ";
}

TextureManager::TextureManager()
{
    LoadTexture("images/" + m_BackupKey, { 32, 32 });
}