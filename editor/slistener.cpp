#include "slistener.hpp"

SListener::SListener()
	: SelectionListener()
{}

SListener::SListener(const callback_t& callback)
	: SelectionListener()
{
	m_callback=callback;
}

void SListener::valueChanged(const gcn::SelectionEvent& event)
{
	if(isCallback())
	{
		gcn::ListBox* ori = dynamic_cast<gcn::ListBox*>(event.getSource());
		int idx = ori->getSelected();
		std::string str = ori->getListModel()->getElementAt(idx);
		m_callback(idx, str, *ori);
	}

	SelectionListener::valueChanged(event);
}

void SListener::setCallback(callback_t c)
{
	m_callback=c;
}

bool SListener::isCallback() const
{
	return !m_callback.empty();
}

