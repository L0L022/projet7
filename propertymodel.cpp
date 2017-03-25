#include "propertymodel.hpp"
#include <QJsonDocument>

PropertyItem::PropertyItem(const int _id, QObject *parent) : QObject(parent), _properties() {
    _properties["id"] = _id;
}

int PropertyItem::id() const {
    return _properties["id"].toInt();
}

const QVariantMap &PropertyItem::properties() const {
    return _properties;
}

void PropertyItem::setProperties(const QVariantMap &prop) {
    if(id() == prop["id"].toInt()) {
        _properties = prop;
        emit propertiesChanged();
        //emit all propertyChanged ?
    }
}

QVariant PropertyItem::property(const QString &key) const {
    return _properties[key];
}

QVariant PropertyItem::operator[](const QString &key) const {
    return property(key);
}

void PropertyItem::setProperty(const QString &key, const QVariant &value) {
    if(value.isValid() && key != "id") {
        _properties[key] = value;
        emit propertyChanged(key);
        emit propertiesChanged();
    }
}

void PropertyItem::removeProperty(const QString &key) {
    if(key != "id" && _properties.contains(key)) {
        _properties.remove(key);
        emit propertyRemoved(key);
        emit propertiesChanged();
    }
}

QJsonObject PropertyItem::toJson() const {
    return QJsonObject::fromVariantMap(_properties);
}

void PropertyItem::fromJson(const QJsonObject &json) {
    setProperties(json.toVariantMap());
}

PropertyModel::PropertyModel(QObject *parent) : QAbstractListModel(parent)
{
}

PropertyItem* PropertyModel::append(const int proposed_id) {
    int id = proposed_id;
    for(int i = 0; i < _properties.size(); ++i) {
        if(id == _properties[i]->id()) {
            ++id;
            i = 0;
        }
    }

    QSharedPointer<PropertyItem> property(makeProperty(id));
    connect(property.data(), &PropertyItem::propertiesChanged, this, [this](){
        PropertyItem *property = qobject_cast<PropertyItem*>(sender());
        QModelIndex index = createIndex(indexOf(property->id()), 0);
        emit dataChanged(index, index, {PropertiesRole}); //add item ?
    });

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _properties.append(property);
    endInsertRows();

    return property.data();
}

PropertyItem *PropertyModel::at(const int index) const {
    return _properties[index].data();
}

void PropertyModel::removeAt(const int index) {
    if(0 > index || index > _properties.size()) return;

    beginRemoveRows(QModelIndex(), index, index);
    _properties.removeAt(index);
    endRemoveRows();
}

bool PropertyModel::removeOne(const int id) {
    int index = indexOf(id);
    if(index >= 0) {
        removeAt(index);
        return true;
    }
    return false;
}

void PropertyModel::clear() {
    beginResetModel();
    _properties.clear();
    endResetModel();
}

int PropertyModel::indexOf(const int id) const {
    int index = -1;
    for(int i = 0; i < _properties.size(); ++i)
        if(_properties[i]->id() == id)
            index = i;

    return index;
}

int PropertyModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _properties.count();
}

QVariant PropertyModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= _properties.count())
        return QVariant();

    PropertyItem *property = at(index.row());
    if (role == ItemRole)
        return QVariant::fromValue(property);
    else if (role == IdRole)
        return property->id();
    else if (role == PropertiesRole)
        return property->properties();

    return QVariant();
}

QJsonArray PropertyModel::toJson() const {
    QJsonArray model;
    for(const QSharedPointer<PropertyItem> pt : _properties)
        model.append(pt->toJson());

    return model;
}

void PropertyModel::fromJson(const QJsonArray &json) {
    clear();
    for(const QJsonValue &value : json) {
        if(value.isObject()) {
            QJsonObject property = value.toObject();
            if(property.contains("id")) {
                PropertyItem * item = append(property["id"].toInt());
                item->fromJson(property);
            }
        }
    }
}

PropertyItem *PropertyModel::makeProperty(const int id) {
    return new PropertyItem(id, this);
}

QHash<int, QByteArray> PropertyModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ItemRole] = "item_role";
    roles[IdRole] = "id_role";
    roles[PropertiesRole] = "properties_role";
    return roles;
}
