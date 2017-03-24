#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "propertymodel.hpp"
#include "playeradditionmodel.hpp"

class PlayerItem : public PropertyItem {
    Q_OBJECT

    PlayerAdditionModel _additions;

public:
    PlayerItem(const int id = 0, QObject *parent = nullptr) : PropertyItem(id, parent), _additions(this) {
        _properties["edit"] = false;
        for(const QString &str : {"name", "calling"})
            _properties[str] = "";
        for(const QString &nb : {"age", "height", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            _properties[nb] = 0;
    }

    Q_INVOKABLE PlayerAdditionModel *additions() {
        return &_additions;
    }

    QJsonObject toJson() const {
        QJsonObject object = QJsonObject::fromVariantMap(_properties);
        object["additions"] = _additions.toJson();
        return object;
    }

    void fromJson(const QJsonObject &json) {
        if(json["additions"].isArray()) {
            setProperties(json.toVariantMap());
            _additions.fromJson(json["additions"].toArray());
        }
    }
};

class PlayerModel : public PropertyModel
{
    Q_OBJECT
public:
    PlayerModel(QObject *parent = nullptr) : PropertyModel(parent) {}

protected:
    PropertyItem *makeProperty(const int id) {
        return new PlayerItem(id, this);
    }
};

#endif // PLAYERMODEL_HPP
