#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "propertymodel.hpp"

class GameItem : public PropertyItem {
    Q_OBJECT
public:
    GameItem(const int id = 0, QObject *parent = nullptr) : PropertyItem(id, parent) {
        for(const QString &str : {"name", "description", "location"})
            _properties[str] = "";
    }
};

class GameModel : public PropertyModel
{
    Q_OBJECT
public:
    GameModel(QObject *parent = nullptr) : PropertyModel(parent) {}

protected:
    PropertyItem *makeProperty(const int id) {
        return new GameItem(id, this);
    }
};

#endif // GAMEMODEL_HPP
