#include "saabbModel.hpp"

SaabbModel::SaabbModel(sdl::SpriteEditor* editor)
	:m_editor(editor)
{}

SaabbModel::SaabbModel(const SaabbModel& cp)
	:m_editor(cp.getEditor())
{}

sdl::SpriteEditor* SaabbModel::getEditor() const
{
	return m_editor;
}

std::string SaabbModel::getElementAt(int i)
{
	sdl::AABB aabb=m_editor->SAABBS()[i];
	std::string str("");

	str+= sdl::itoa(i);
	str+=". (";
	str+= sdl::itoa(aabb.rect().x);
	str+= ";";
	str+= sdl::itoa(aabb.rect().y);
	str+= ") - ";
	str+= sdl::itoa(aabb.rect().w);
	str+= "x";
	str+= sdl::itoa(aabb.rect().h);

	return str;
}

int SaabbModel::getNumberOfElements()
{
	return m_editor->nbSAABBS();
}

