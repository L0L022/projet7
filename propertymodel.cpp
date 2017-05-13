#include "propertymodel.hpp"
#include <QJsonDocument>

PropertyItem::PropertyItem(const Id id, QObject *parent)
    : QObject(parent),
      m_properties()
{
    m_properties["id"] = id;
}

PropertyItem::Id PropertyItem::id() const
{
    return m_properties["id"].value<Id>();
}

const QVariantMap &PropertyItem::properties() const
{
    return m_properties;
}

void PropertyItem::setProperties(const QVariantMap &prop)
{
    if (m_properties != prop) {
        PropertyItem::Id oldId = id();
        m_properties = prop;
        m_properties["id"] = oldId;
        emit propertiesChanged();
    }
}

QVariant PropertyItem::property(const QString &key) const
{
    return m_properties[key];
}

QVariant PropertyItem::operator[](const QString &key) const
{
    return m_properties[key];
}

void PropertyItem::setProperty(const QString &key, const QVariant &value)
{
    if (value.isValid() && key != "id" && m_properties[key] != value) {
        m_properties[key] = value;
        emit propertiesChanged();
    }
}

void PropertyItem::removeProperty(const QString &key)
{
    if (key != "id" && m_properties.contains(key)) {
        m_properties.remove(key);
        emit propertiesChanged();
    }
}

QJsonObject PropertyItem::toJson() const
{
    return QJsonObject::fromVariantMap(m_properties);
}

void PropertyItem::fromJson(const QJsonObject &json)
{
    setProperties(json.toVariantMap());
}

PropertyModel::PropertyModel(QObject *parent)
    : QAbstractListModel(parent),
      m_properties()
{
}

PropertyItem* PropertyModel::append(const PropertyItem::Id proposed_id)
{
    PropertyItem::Id id = proposed_id;
    for (int i = 0; i < m_properties.size(); ++i) {
        if (id == m_properties[i]->id()) {
            ++id;
            i = 0;
        }
    }

    QSharedPointer<PropertyItem> property(makeProperty(id));

    connect(property.data(), &PropertyItem::propertiesChanged, this, [this](){
        PropertyItem *property = qobject_cast<PropertyItem*>(sender());
        QModelIndex index = createIndex(indexOf(property->id()), 0);
        emit dataChanged(index, index, {PropertiesRole}); //add item ?
        emit propertyChanged(property);
    });

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_properties.append(property);
    endInsertRows();
    emit propertyInserted(property.data());

    return property.data();
}

void PropertyModel::removeAt(const int index)
{
    if (0 > index || index > m_properties.size())
        return;

    PropertyItem::Id id = m_properties.at(index).data()->id();
    beginRemoveRows(QModelIndex(), index, index);
    m_properties.removeAt(index);
    endRemoveRows();
    emit propertyRemoved(id);
}

bool PropertyModel::removeOne(const PropertyItem::Id id)
{
    int index = indexOf(id);

    if (index >= 0) {
        removeAt(index);
        return true;
    }

    return false;
}

void PropertyModel::clear()
{
    if(!m_properties.isEmpty()) {
        beginResetModel();
        m_properties.clear();
        endResetModel();
    }
}

PropertyItem *PropertyModel::at(const int index) const
{
    if (0 > index || index > m_properties.count())
        return nullptr;

    return m_properties[index].data();
}

const PropertyItem &PropertyModel::operator[](const int index) const
{
    return *m_properties[index];
}

PropertyItem *PropertyModel::get(const PropertyItem::Id id) const
{
    return at(indexOf(id));
}

PropertyItem *PropertyModel::get(const QVariant &id) const
{
    return get(id.value<PropertyItem::Id>());
}

int PropertyModel::indexOf(const PropertyItem::Id id) const
{
    int index = -1;

    for (int i = 0; i < m_properties.size(); ++i)
        if (m_properties[i]->id() == id)
            index = i;

    return index;
}

int PropertyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_properties.count();
}

QVariant PropertyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_properties.count())
        return QVariant();

    PropertyItem *property = at(index.row());

    if (role == PropertyRole)
        return QVariant::fromValue(property);
    else if (role == IdRole)
        return property->id();
    else if (role == PropertiesRole)
        return property->properties();

    return QVariant();
}

QJsonArray PropertyModel::toJson() const
{
    QJsonArray array;

    for (const QSharedPointer<PropertyItem> pt : m_properties)
        array.append(pt->toJson());

    return array;
}

void PropertyModel::fromJson(const QJsonArray &json)
{
    clear();

    for (const QJsonValue &value : json) {
        if (value.isObject()) {
            QJsonObject property = value.toObject();

            if (property.contains("id")) {
                PropertyItem *item = append(property["id"].toVariant().value<PropertyItem::Id>());
                item->fromJson(property);
            }
        }
    }
}

PropertyItem *PropertyModel::makeProperty(const PropertyItem::Id id)
{
    return new PropertyItem(id, this);
}

QHash<int, QByteArray> PropertyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PropertyRole] = "propertyRole";
    roles[IdRole] = "idRole";
    roles[PropertiesRole] = "propertiesRole";
    return roles;
}
