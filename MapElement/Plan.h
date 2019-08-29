#ifndef PLAN_H
#define PLAN_H

#include "MapElement.h"


class Plan : public MapElement
{
    public:
        Plan();
        virtual ~Plan();

        virtual bool isAWall() const {return false;}
        virtual bool doActionOnEnter() const {return false;}
        virtual bool doActionOnAction() const {return false;}
        virtual bool isACombatZone() const {return false;}

        virtual int action() {return 0;}

    protected:

    private:
};

#endif // PLAN_H
