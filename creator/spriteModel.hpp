#ifndef DEF_SPRITE_MODEL
#define DEF_SPRITE_MODEL

#include <guichan.hpp>
#include <vector>
#include <string>

class SpriteModel : public gcn::ListModel
{
	public:
		SpriteModel();
		void update(std::vector<std::string> sprites);

		virtual std::string getElementAt(int i);
		virtual int getNumberOfElements();

	private:
		std::vector<std::string> m_sprites;

};

#endif//DEF_SPRITE_MODEL
