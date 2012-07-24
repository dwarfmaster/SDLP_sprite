#ifndef DEF_CREATOR_AREA
#define DEF_CREATOR_AREA

#include <guichan.hpp>

class Creator;

class CreatorArea : public gcn::ScrollArea
{
	public:
		CreatorArea(Creator* creat);

		virtual void mouseClicked(gcn::MouseEvent& event);

	private:
		Creator* m_creat;
};

#endif//DEF_CREATOR_AREA
