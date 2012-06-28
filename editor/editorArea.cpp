#include "editorArea.hpp"
#include "editor.hpp"

	EditorArea::EditorArea(sdl::SpriteEditor* editor, Editor* fen)
: ScrollArea(), m_editor(editor), m_fen(fen)
{}

	EditorArea::EditorArea(sdl::SpriteEditor* editor, Editor* fen, gcn::Widget* content)
: ScrollArea(content), m_editor(editor), m_fen(fen)
{}

void EditorArea::mouseClicked(gcn::MouseEvent& event)
{
	if( event.getX() < getWidth() - getScrollbarWidth()
			&& event.getY() < getHeight() - getScrollbarWidth() )
	{
		sdl::Pointsi ori(getHorizontalScrollAmount(), getVerticalScrollAmount());
		sdl::Pointsi pos(event.getX() + ori.x, event.getY() + ori.y);

		sdl::Pointsi pos2;
		sdl::Pointsi topleft;
		sdl::Pointsi bottomright;
		sdl::AABB aabb;

		switch(event.getButton())
		{
			case gcn::MouseEvent::LEFT: // Set Bottom Left
				pos2 = m_editor->get().location(sdl::AABB::BOTTOM_RIGHT);
				topleft = sdl::min(pos, pos2);
				bottomright = sdl::max(pos, pos2);

				if(bottomright.x - topleft.x < 4)
					bottomright.x = topleft.x + 4;
				if(bottomright.y - topleft.y < 4)
					bottomright.y = topleft.y + 4;

				aabb.set(topleft, bottomright);
				m_editor->modifie(aabb);
				break;

			case gcn::MouseEvent::RIGHT: // Set Bottom Right
				pos2 = m_editor->get().location(sdl::AABB::TOP_LEFT);
				topleft = sdl::min(pos, pos2);
				bottomright = sdl::max(pos, pos2);

				if(bottomright.x - topleft.x < 4)
					bottomright.x = topleft.x + 4;
				if(bottomright.y - topleft.y < 4)
					bottomright.y = topleft.y + 4;

				aabb.set(topleft, bottomright);
				m_editor->modifie(aabb);
				break;

			case gcn::MouseEvent::MIDDLE: // Set hotpoint
				m_editor->setHotPoint(pos);
				break;

			default: // Avoid warnings
				break;
		}
		m_fen->update();
	}

	ScrollArea::mouseClicked(event);
}

