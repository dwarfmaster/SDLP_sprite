#ifndef DEF_SLISTENER
#define DEF_SLISTENER

#include <guichan.hpp>
#include <boost/function.hpp>
#include <string>

class SListener : public gcn::SelectionListener
{
	public:
		typedef boost::function<void (int, std::string, gcn::ListBox)> callback_t; // Le premier argument est l'index, le deuxième la valeur associée et le troisième la liste

		SListener();
		SListener(const callback_t& callback);
		virtual void valueChanged(const gcn::SelectionEvent& event);

		void setCallback(callback_t c);
		bool isCallback() const;

	private:
		callback_t m_callback;
};

#endif//DEF_SLISTENER
