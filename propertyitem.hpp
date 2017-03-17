#ifndef PROPERTYITEM_HPP
#define PROPERTYITEM_HPP

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>

class PropertyItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QJsonObject properties READ getProperties WRITE setProperties NOTIFY propertiesChanged)

protected:
    QJsonObject _properties;

signals:
    void propertiesChanged();
    void propertyChanged(const QString &key);
    void propertyRemoved(const QString &key);

public:
    PropertyItem(const int id = 0, QObject *parent = nullptr) : QObject(parent), _properties() {
        _properties["id"] = id;
    }

    int getId() const {
        return _properties["id"].toInt();
    }

    const QJsonObject &getProperties() const {
        return _properties;
    }

    void setProperties(const QJsonObject &properties) {
        if(getId() == properties["id"].toInt()) {
            _properties = properties;
            emit propertiesChanged();
        }
    }

    Q_INVOKABLE QVariant getProperty(const QString &key) const {
        return _properties[key].toVariant();
    }

    Q_INVOKABLE void setProperty(const QString &key, const QVariant &value) {
        if(value.isValid() && key != "id") {
            _properties[key] = QJsonValue::fromVariant(value);
            emit propertyChanged(key);
            emit propertiesChanged();
        }
    }

    Q_INVOKABLE void removeProperty(const QString &key) {
        if(key != "id") {
            if(_properties.contains(key)) {
                _properties.remove(key);
                emit propertyRemoved(key);
                emit propertiesChanged();
            }
        }
    }
};

#endif // PROPERTYITEM_HPP
