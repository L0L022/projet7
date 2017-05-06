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

    explicit PlayerItem(const Id id = 0, QObject *parent = nullptr);

    Rights readRights() const;
    Rights writeRights() const;
    Q_INVOKABLE void addReadRight(const QVariant &id);
    Q_INVOKABLE void addWriteRight(const QVariant &id);
    Q_INVOKABLE void removeReadRight(const int index);
    Q_INVOKABLE void removeWriteRight(const int index);

    Q_INVOKABLE PropertyModel *subProperties();
    Q_INVOKABLE PropertyItem* append(const int proposed_id = 0);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

signals:
    void readRightsChanged();
    void writeRightsChanged();

private:
    QJsonArray rightsToJson(const Rights &rights) const;
    Rights rightsFromJson(const QJsonArray &array);

    PropertyModel m_subProperties;
    Rights m_readRights;
    Rights m_writeRights;
};

class PlayerModel : public PropertyModel
{
    Q_OBJECT

public:
    explicit PlayerModel(QObject *parent = nullptr);

    PlayerItem *getPlayer(const PropertyItem::Id id) const;

protected:
    PropertyItem *makeProperty(const int id);
};

#endif // PLAYERMODEL_HPP
