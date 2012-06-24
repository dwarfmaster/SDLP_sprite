#ifndef DEF_GROUPMODEL
#define DEF_GROUPMODEL

#include <SDLP_sprite.hpp>
#include <guichan.hpp>

class GroupModel : public gcn::ListModel
{
	public:
		GroupModel(sdl::SpriteEditor* editor);
		GroupModel(const GroupModel& cp);

		sdl::SpriteEditor* getEditor() const;

		virtual int getNumberOfElements();
		virtual std::string getElementAt(int i);

	protected:
		sdl::SpriteEditor* m_editor;

		GroupModel();
		GroupModel& operator=(const GroupModel& cp);
};

#endif//DEF_GROUPMODEL
