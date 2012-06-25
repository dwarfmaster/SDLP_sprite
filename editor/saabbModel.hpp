#ifndef DEF_SAABBMODEL
#define DEF_SAABBMODEL

#include <guichan.hpp>
#include <SDLP_sprite.hpp>

class SaabbModel : public gcn::ListModel
{
	public:
		SaabbModel(sdl::SpriteEditor* editor);
		SaabbModel(const SaabbModel& cp);

		sdl::SpriteEditor* getEditor() const;

		virtual std::string getElementAt(int i);
		virtual int getNumberOfElements();

	protected:
		sdl::SpriteEditor* m_editor;

		SaabbModel();
		SaabbModel& operator=(const SaabbModel& cp);
};

#endif//DEF_SAABBMODEL
