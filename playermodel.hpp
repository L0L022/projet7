#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "propertymodel.hpp"

class PlayerItem : public PropertyItem
{
    Q_OBJECT

public:
    explicit PlayerItem(const Id id = 0, QObject *parent = nullptr)
        : PropertyItem(id, parent),
          m_subProperties(this)
    {
        for (const QString &str : {"name", "calling", "age", "height"})
            m_properties[str] = "";
    }

    Q_INVOKABLE PropertyModel *subProperties()
    {
        return &m_subProperties;
    }

    Q_INVOKABLE PropertyItem* append(const int proposed_id = 0)
    {
        QVariantMap properties;
        for (const QString &str : {"name", "description", "category", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
            properties[str] = "";

        PropertyItem * property = m_subProperties.append(proposed_id);
        property->setProperties(properties);
        return property;
    }

    QJsonObject toJson() const
    {
        QJsonObject object = PropertyItem::toJson();
        object["subProperties"] = m_subProperties.toJson();
        return object;
    }

    void fromJson(const QJsonObject &json)
    {
        if (json["subProperties"].isArray()) {
            setProperties(json.toVariantMap());
            m_subProperties.fromJson(json["subProperties"].toArray());
        }
    }

private:
    PropertyModel m_subProperties;
};

class PlayerModel : public PropertyModel
{
    Q_OBJECT

public:
    explicit PlayerModel(QObject *parent = nullptr)
        : PropertyModel(parent)
    {
    }

    PlayerItem *getPlayer(const PropertyItem::Id id) const
    {
        return qobject_cast<PlayerItem*>(get(id));
    }

protected:
    PropertyItem *makeProperty(const int id)
    {
        return new PlayerItem(id, this);
    }
};

#endif // PLAYERMODEL_HPP
