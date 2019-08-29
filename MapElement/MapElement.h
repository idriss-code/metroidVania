#ifndef MAPELEMENT_H
#define MAPELEMENT_H


class MapElement
{
    public:
        MapElement();
        virtual ~MapElement();

        virtual bool isAWall() const = 0;
        virtual bool doActionOnEnter() const = 0;
        virtual bool doActionOnAction() const = 0;
        virtual bool isACombatZone() const = 0;

        virtual int action() = 0;

    protected:

    private:
};

#endif // MAPELEMENT_H
