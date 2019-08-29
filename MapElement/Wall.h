#ifndef WALL_H
#define WALL_H

#include "MapElement.h"


class Wall : public MapElement
{
    public:
        Wall();
        virtual ~Wall();

        virtual bool isAWall() const {return true;}
        virtual bool doActionOnEnter() const {return false;}
        virtual bool doActionOnAction() const {return false;}
        virtual bool isACombatZone() const {return false;}

        virtual int action() {return 0;}

    protected:

    private:
};

#endif // WALL_H
