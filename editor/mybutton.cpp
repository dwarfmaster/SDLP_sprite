#include "mybutton.hpp"

	MyButton::MyButton()
:Button()
{}

	MyButton::MyButton(const std::string& caption)
:Button(caption)
{}

bool MyButton::isCallback() const
{
	return !m_callback.empty();
}

void MyButton::setClicCallback(const boost::function<void ()>& callback)
{
	m_callback = callback;
}

void MyButton::mousePressed(gcn::MouseEvent& event)
{
	if(event.getButton() == gcn::MouseEvent::LEFT
			&& this->isCallback())
		m_callback();
	Button::mousePressed(event);
}

bool MyButton::pressed() const
{
	return this->isPressed();
}

void MyButton::mouseReleased(gcn::MouseEvent& event)
{
	Button::mouseReleased(event);
}

void MyButton::mouseEntered(gcn::MouseEvent& event)
{
	Button::mouseEntered(event);
}

void MyButton::mouseExited(gcn::MouseEvent& event)
{
	Button::mouseExited(event);
}

void MyButton::mouseDragged(gcn::MouseEvent& event)
{
	Button::mouseDragged(event);
}

void MyButton::keyPressed(gcn::KeyEvent& event)
{
	Button::keyPressed(event);
}

void MyButton::keyReleased(gcn::KeyEvent& event)
{
	Button::keyReleased(event);
}

void MyButton::focusLost(const gcn::Event& event)
{
	Button::focusLost(event);
}
