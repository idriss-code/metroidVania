#ifndef ELEMENTMENU_H
#define ELEMENTMENU_H


class ElementMenu
{
    public:
        ElementMenu(const char* name);
        virtual ~ElementMenu();

        const char* name()const{ return m_name; }

        virtual int action(int val=0){return val;}


    protected:

    private:
        char m_name[20] ;


};

#endif // ELEMENTMENU_H
