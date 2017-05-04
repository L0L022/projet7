#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP
#include <QDebug>
#include <QVariant>
#include "propertymodel.hpp"

class PlayerItem : public PropertyItem
{
    Q_OBJECT
    Q_PROPERTY(Rights readRights READ readRights NOTIFY readRightsChanged)
    Q_PROPERTY(Rights writeRights READ writeRights NOTIFY writeRightsChanged)

public:
    typedef QList<PropertyItem::Id> Rights;

    explicit PlayerItem(const Id id = 0, QObject *parent = nullptr)
        : PropertyItem(id, parent),
          m_subProperties(this),
          m_readRights(),
          m_writeRights()
    {
        for (const QString &str : {"name", "calling", "age", "height"})
            m_properties[str] = "";

        m_readRights.append(id);
        m_writeRights.append(id);
    }

    Rights readRights() const
    {
        return m_readRights;
    }

    Rights writeRights() const
    {
        return m_writeRights;
    }

    Q_INVOKABLE void addReadRight(const QVariant &id)
    {
        if (m_readRights.contains(id.value<PropertyItem::Id>()))
            return;

        m_readRights.append(id.value<PropertyItem::Id>());
        emit readRightsChanged();
    }

    Q_INVOKABLE void addWriteRight(const QVariant &id)
    {
        if (m_writeRights.contains(id.value<PropertyItem::Id>()))
            return;

        m_writeRights.append(id.value<PropertyItem::Id>());
        emit writeRightsChanged();
    }

    Q_INVOKABLE void removeReadRight(const int index)
    {
        m_readRights.removeAt(index);
        emit readRightsChanged();
    }

    Q_INVOKABLE void removeWriteRight(const int index)
    {
        m_writeRights.removeAt(index);
        emit writeRightsChanged();
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
        object["readRights"] = rightsToJson(m_readRights);
        object["writeRights"] = rightsToJson(m_writeRights);
        return object;
    }

    void fromJson(const QJsonObject &json)
    {
        if (json["subProperties"].isArray()) {
            setProperties(json.toVariantMap());
            m_subProperties.fromJson(json["subProperties"].toArray());
        }
        m_readRights = rightsFromJson(json["readRights"].toArray());
        m_writeRights = rightsFromJson(json["writeRights"].toArray());
    }

signals:
    void readRightsChanged();
    void writeRightsChanged();

private:
    QJsonArray rightsToJson(const Rights &rights) const
    {
        QJsonArray array;
        for(const PropertyItem::Id id : rights)
            array.append(id);
        return array;
    }

    Rights rightsFromJson(const QJsonArray &array)
    {
        Rights rights;
        for(const QJsonValue &value : array)
            rights.append(value.toVariant().value<PropertyItem::Id>());
        return rights;
    }

    PropertyModel m_subProperties;
    Rights m_readRights;
    Rights m_writeRights;
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
