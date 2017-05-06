#include "playermodel.hpp"

PlayerItem::PlayerItem(const Id id, QObject *parent)
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

PlayerItem::Rights PlayerItem::readRights() const
{
    return m_readRights;
}

PlayerItem::Rights PlayerItem::writeRights() const
{
    return m_writeRights;
}

void PlayerItem::addReadRight(const QVariant &id)
{
    if (m_readRights.contains(id.value<PropertyItem::Id>()))
        return;

    m_readRights.append(id.value<PropertyItem::Id>());
    emit readRightsChanged();
}

void PlayerItem::addWriteRight(const QVariant &id)
{
    if (m_writeRights.contains(id.value<PropertyItem::Id>()))
        return;

    addReadRight(id);
    m_writeRights.append(id.value<PropertyItem::Id>());
    emit writeRightsChanged();
}

void PlayerItem::removeReadRight(const int index)
{
    if (index < 0 or index >= m_readRights.size())
        return;

    removeWriteRight(m_writeRights.indexOf(m_readRights[index]));
    m_readRights.removeAt(index);
    emit readRightsChanged();
}

void PlayerItem::removeWriteRight(const int index)
{
    if (index < 0 or index >= m_writeRights.size())
        return;

    m_writeRights.removeAt(index);
    emit writeRightsChanged();
}

PropertyModel *PlayerItem::subProperties()
{
    return &m_subProperties;
}

PropertyItem* PlayerItem::append(const int proposed_id)
{
    QVariantMap properties;
    for (const QString &str : {"name", "description", "category", "CC", "CT", "F", "B", "A", "I", "Desc", "Int", "Soc", "FM"})
        properties[str] = "";

    PropertyItem * property = m_subProperties.append(proposed_id);
    property->setProperties(properties);
    return property;
}

QJsonObject PlayerItem::toJson() const
{
    QJsonObject object = PropertyItem::toJson();
    object["subProperties"] = m_subProperties.toJson();
    object["readRights"] = rightsToJson(m_readRights);
    object["writeRights"] = rightsToJson(m_writeRights);
    return object;
}

void PlayerItem::fromJson(const QJsonObject &json)
{
    if (json["subProperties"].isArray()) {
        setProperties(json.toVariantMap());
        m_subProperties.fromJson(json["subProperties"].toArray());
    }
    m_readRights = rightsFromJson(json["readRights"].toArray());
    m_writeRights = rightsFromJson(json["writeRights"].toArray());
}

QJsonArray PlayerItem::rightsToJson(const Rights &rights) const
{
    QJsonArray array;
    for(const PropertyItem::Id id : rights)
        array.append(id);
    return array;
}

PlayerItem::Rights PlayerItem::rightsFromJson(const QJsonArray &array)
{
    Rights rights;
    for(const QJsonValue &value : array)
        rights.append(value.toVariant().value<PropertyItem::Id>());
    return rights;
}

PlayerModel::PlayerModel(QObject *parent)
    : PropertyModel(parent)
{
}

PlayerItem *PlayerModel::getPlayer(const PropertyItem::Id id) const
{
    return qobject_cast<PlayerItem*>(get(id));
}

PropertyItem *PlayerModel::makeProperty(const int id)
{
    return new PlayerItem(id, this);
}
