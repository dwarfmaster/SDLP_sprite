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
		/*
		virtual void mouseReleased(gcn::MouseEvent& event);
		virtual void mouseEntered(gcn::MouseEvent& event);
		virtual void mouseExited(gcn::MouseEvent& event);
		virtual void mouseDragged(gcn::MouseEvent& event);
		virtual void keyPressed(gcn::KeyEvent& event);
		virtual void keyReleased(gcn::KeyEvent& event);
		virtual void focusLost(const gcn::Event& event);
		//*/

	protected:
		boost::function<void ()> m_callback;
};

#endif//DEF_MYBUTTON
