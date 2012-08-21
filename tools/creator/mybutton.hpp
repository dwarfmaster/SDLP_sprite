#ifndef DEF_MYBUTTON
#define DEF_MYBUTTON

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <boost/function.hpp>
#include <iostream>

class MyButton : public gcn::Button
{
	public:
		MyButton();
		MyButton(const std::string& caption);

		bool isCallback() const;
		void setClicCallback(const boost::function<void ()>& callback);
		bool pressed() const;

		virtual void mousePressed(gcn::MouseEvent& event);

	protected:
		boost::function<void ()> m_callback;
};

#endif//DEF_MYBUTTON
