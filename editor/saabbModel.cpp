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
}

int SaabbModel::getNumberOfElements();
{
}

