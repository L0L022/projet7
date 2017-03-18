#ifndef PROPERTYITEM_HPP
#define PROPERTYITEM_HPP

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QJsonDocument>

class PropertyItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QVariantMap properties READ getProperties WRITE setProperties NOTIFY propertiesChanged)

protected:
    QVariantMap _properties;

signals:
    void propertiesChanged();
    void propertyChanged(const QString &key);
    void propertyRemoved(const QString &key);

public:
    PropertyItem(const int id = 0, QObject *parent = nullptr) : QObject(parent), _properties() {
        _properties["id"] = id;
    }
/*
    PropertyItem(const QVariantMap properties, QObject *parent = nullptr) : QObject(parent), _properties(properties) {
        if(!_properties.contains("id"))
            _properties["id"] = 0;
    }
*/
    int getId() const {
        return _properties["id"].toInt();
    }

    const QVariantMap &getProperties() const {
        return _properties;
    }

    void setProperties(const QVariantMap &properties) {
        if(getId() == properties["id"].toInt()) {
            _properties = properties;
            emit propertiesChanged();
        }
    }

    Q_INVOKABLE QVariant getProperty(const QString &key) const {
        return _properties[key];
    }

    Q_INVOKABLE void setProperty(const QString &key, const QVariant &value) {
        if(value.isValid() && key != "id" && _properties.contains(key)) {
            _properties[key] = value;
            emit propertyChanged(key);
            emit propertiesChanged();
        }
    }

    Q_INVOKABLE void removeProperty(const QString &key) {
        if(key != "id" && _properties.contains(key)) {
            _properties.remove(key);
            emit propertyRemoved(key);
            emit propertiesChanged();
        }
    }
};

#endif // PROPERTYITEM_HPP
