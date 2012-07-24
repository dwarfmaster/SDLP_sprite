#include "spriteModel.hpp"

SpriteModel::SpriteModel()
	: gcn::ListModel()
{}

void SpriteModel::update(std::vector<std::string> sprites)
{
	m_sprites = sprites;
}

std::string SpriteModel::getElementAt(int i)
{
	if( i >= 0
			&& i < m_sprites.size() )
		return m_sprites[i];
	else
		return std::string("Nothing");
}

int SpriteModel::getNumberOfElements()
{
	return m_sprites.size();
}

