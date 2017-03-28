#ifndef PLAYERADDITION_HPP
#define PLAYERADDITION_HPP

#include "propertymodel.hpp"

class PlayerAdditionItem : public PropertyItem
{
    Q_OBJECT

public:
    explicit PlayerAdditionItem(const int id = 0, QObject *parent = nullptr)
        : PropertyItem(id, parent)
    {
        for (const QString &str : {"name", "description", "category"})
            setProperty(str, "");

        for (const QString &nb : {"CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            setProperty(nb, 0);
    }
};

class PlayerAdditionModel : public PropertyModel
{
    Q_OBJECT

public:
    explicit PlayerAdditionModel(QObject *parent = nullptr)
        : PropertyModel(parent)
    {
    }

protected:
    PropertyItem *makeProperty(const int id)
    {
        return new PlayerAdditionItem(id, this);
    }
};

#endif // PLAYERADDITION_HPP
