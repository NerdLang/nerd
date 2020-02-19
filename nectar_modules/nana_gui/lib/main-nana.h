#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

using namespace nana;

var __NJS_CreateForm(char* _title, char* _text, char* _button)
{
    form fm;  
    fm.caption(_title);

    label lab{fm, _text};
    lab.format(true);

    //Define a button and answer the click event.
    button btn{fm, _button};
    btn.events().click([&fm]{
        fm.close();
    });

    //Layout management
    fm.div("vert <><<><weight=80% text><>><><weight=24<><button><>><>");
    fm["text"]<<lab;
    fm["button"] << btn;
    fm.collocate();
	
    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    exec();

	return var(UNDEFINED, 0);
}
