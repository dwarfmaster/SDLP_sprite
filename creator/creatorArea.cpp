#include "creatorArea.hpp"
#include "creator.hpp"

CreatorArea::CreatorArea(Creator* creat)
	: ScrollArea(), m_creat(creat)
{}

void CreatorArea::mouseClicked(gcn::MouseEvent& event)
{
	if( event.getX() < getWidth() - getScrollbarWidth() // On vérifie qu'on est dans la zone d'édition et pas sur les scrollbar
			&& event.getY() < getHeight() - getScrollbarWidth() )
	{
		sdl::Pointsi ori(getHorizontalScrollAmount(), getVerticalScrollAmount());
		sdl::Pointsi pos(event.getX() + ori.x, event.getY() + ori.y);

		sdl::AABB sprite(m_creat->getSprite());
		sdl::Pointsi pos2;
		sdl::Pointsi topleft;
		sdl::Pointsi bottomright;

		switch(event.getButton())
		{
			case gcn::MouseEvent::LEFT:
				pos2 = sprite.location(sdl::AABB::BOTTOM_RIGHT);
				topleft = sdl::min(pos, pos2);
				bottomright = sdl::max(pos, pos2);

				if(bottomright.x - topleft.x < 4)
					bottomright.x = topleft.x + 4;
				if(bottomright.y - topleft.y < 4)
					bottomright.y = topleft.y + 4;
				break;
			case gcn::MouseEvent::RIGHT:
				pos2 = sprite.location(sdl::AABB::TOP_LEFT);
				topleft = sdl::min(pos, pos2);
				bottomright = sdl::max(pos, pos2);

				if(bottomright.x - topleft.x < 4)
					bottomright.x = topleft.x + 4;
				if(bottomright.y - topleft.y < 4)
					bottomright.y = topleft.y + 4;
				break;
			default:
				break;
		}

		sprite.set(topleft, bottomright);
		m_creat->changeSprite(sprite);
	}

	ScrollArea::mouseClicked(event);
}
