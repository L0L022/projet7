#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "propertymodel.hpp"
#include "playeradditionmodel.hpp"

class PlayerItem : public PropertyItem
{
    Q_OBJECT

public:
    PlayerItem(const int id = 0, QObject *parent = nullptr)
        : PropertyItem(id, parent),
          m_additions(this)
    {
        for (const QString &str : {"name", "calling"})
            setProperty(str, "");

        for (const QString &nb : {"age", "height", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            setProperty(nb, 0);
    }

    Q_INVOKABLE PlayerAdditionModel *additions()
    {
        return &m_additions;
    }

    QJsonObject toJson() const
    {
        QJsonObject object = PropertyItem::toJson();
        object["additions"] = m_additions.toJson();
        return object;
    }

    void fromJson(const QJsonObject &json)
    {
        if (json["additions"].isArray()) {
            setProperties(json.toVariantMap());
            m_additions.fromJson(json["additions"].toArray());
        }
    }

private:
    PlayerAdditionModel m_additions;
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
