#ifndef DEF_SPRITE_MODEL
#define DEF_SPRITE_MODEL

#include <guichan.hpp>
#include <vector>
#include <string>
#include <algorithm>

class SpriteModel : public gcn::ListModel
{
	public:
		SpriteModel(const std::vector<std::string>& sprites);

		virtual std::string getElementAt(int i);
		virtual int getNumberOfElements();
		int getIndexOf(std::string elem);

	private:
		const std::vector<std::string>& m_sprites;

};

#endif//DEF_SPRITE_MODEL
