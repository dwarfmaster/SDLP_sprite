#include "groupModel.hpp"

GroupModel::GroupModel(sdl::SpriteEditor* editor)
	: m_editor(editor)
{}

GroupModel::GroupModel(const GroupModel& cp)
	: m_editor(cp.getEditor())
{}

sdl::SpriteEditor* GroupModel::getEditor() const
{
	return m_editor;
}

int GroupModel::getNumberOfElements()
{
	return m_editor->nbGroups();
}

std::string GroupModel::getElementAt(int i)
{
	return m_editor->groups()[i];
}

