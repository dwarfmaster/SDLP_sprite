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

int GroupModel::nbGroup(std::string group)
{
	for(int i=0; i < getNumberOfElements(); ++i)
		if(group == getElementAt(i))
			return i;

	return -1; // Error value : group not found
}

int GroupModel::getNumberOfElements()
{
	return m_editor->nbGroups();
}

std::string GroupModel::getElementAt(int i)
{
	if(this->getNumberOfElements() <= 0)
		return "Nothing";
	else
		return m_editor->groups()[i];
}

