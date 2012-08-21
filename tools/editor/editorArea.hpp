#ifndef DEF_EDITORAREA
#define DEF_EDITORAREA

#include <guichan.hpp>
#include <SDLP_sprite.hpp>
class Editor;

class EditorArea : public gcn::ScrollArea
{
	public:
		EditorArea(sdl::SpriteEditor* editor, Editor* fen);
		EditorArea(sdl::SpriteEditor* editor, Editor* fen, gcn::Widget* content);

		virtual void mouseClicked(gcn::MouseEvent& event);

	private:
		sdl::SpriteEditor* m_editor;
		Editor* m_fen;

		EditorArea();
};

#endif//DEF_EDITORAREA
