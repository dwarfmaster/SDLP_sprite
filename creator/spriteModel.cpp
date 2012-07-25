#include "spriteModel.hpp"

SpriteModel::SpriteModel(const std::vector<std::string>& sprites)
	: gcn::ListModel(), m_sprites(sprites)
{}

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

int SpriteModel::getIndexOf(std::string elem)
{
	for(size_t i=0; i<m_sprites.size(); ++i)
		if(m_sprites[i] == elem)
			return i;
	return -1;
}


