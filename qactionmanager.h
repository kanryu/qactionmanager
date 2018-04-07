#ifndef QACTIONMANAGER_H
#define QACTIONMANAGER_H

#include <QtCore>

/**
 * @brief The QActionManager class
 *
 * A portable component for providing keyboard and mouse input customization functions to applications
 *
 * It contains QKeySequence or QMouseSequence and QAction(default) mapping.
 *
 * Each Action can have/set unique Keyboard/Mouse Sequence.
 *
 * It has default mapping, and can restore setting.
 */
template<typename Key, typename Value, typename Action>
class QActionManager
{
public:
    explicit QActionManager()
    {

    }
    explicit QActionManager(QActionManager& rhs)
        : m_actionByName(rhs.m_actionByName)
        , m_keyByName(rhs.m_keyByName)
        , m_keyByNameDefaults(rhs.m_keyByNameDefaults)
        , m_nameByValue(rhs.m_nameByValue)
        , m_nameByGroup(rhs.m_nameByGroup)
    {
        m_actionByName.detach();
        m_keyByName.detach();
        m_keyByNameDefaults.detach();
        m_nameByValue.detach();
        m_nameByGroup.detach();
    }

    void operator=(QActionManager& rhs)
    {
        m_actionByName = rhs.m_actionByName;
        m_keyByName = rhs.m_keyByName;
        m_keyByNameDefaults = rhs.m_keyByNameDefaults;
        m_nameByValue = rhs.m_nameByValue;
        m_nameByGroup = rhs.m_nameByGroup;
    }
    void registAction(QString name, Action& action, QString group)
    {
        m_actionByName[name] = action;
        m_nameByGroup.insert(group, name);
    }
    void copyActions(QMap<QString, Action>& rhs)
    {
        m_actionByName = rhs;
    }

    void addDefaultKey(QString name, Key key)
    {
        m_keyByNameDefaults[name] = key;
        m_keyByName[name] = key;
        for(int i = 0; i < key.count(); i++) {
            QString keystring = valueToString(key[i]);
            m_nameByValue[keystring] = name;
        }
    }
    QMultiMap<QString, QString>& nameByGroups() { return m_nameByGroup; }
    QMap<QString, Action>& actions() { return m_actionByName; }
    QMap<QString, Key>& keyMaps() { return m_keyByName; }
    Key getKey(const QString& name) { return m_keyByName.contains(name) ? m_keyByName[name] : Key(); }
    Key getKeyDefault(const QString& name) { return m_keyByNameDefaults.contains(name) ? m_keyByNameDefaults[name] : Key(); }
    Action getActionByKey(Value& value) {
        QString keystring = valueToString(value);
        if(!m_nameByValue.contains(keystring))
            return Action();
        QString name = m_nameByValue[keystring];
        return m_actionByName[name];
    }

    QString getNameByValue(Value& value) {
        QString keystring = valueToString(value);
        if(!m_nameByValue.contains(keystring))
            return "";
        return m_nameByValue[keystring];
    }

    bool markCollisions(const QString& name, Key key)
    {
        if(!m_actionByName.contains(name))
            return true;
        for(int i = 0; i < key.count(); i++) {
            QString keystring = valueToString(key[i]);
            if(!m_nameByValue.contains(keystring))
                continue;
            QString nm = m_nameByValue[keystring];
            if(nm != name)
                return true;
        }
        return false;
    }
    QString valueToString(int key)
    {
        return Value(key).toString();
    }
    QString valueToString(Value value)
    {
        return value.toString();
    }

    void updateKey(const QString& name, Key key, bool force=false) {
        if(!force && !m_actionByName.contains(name))
            return;
        Key old = m_keyByName[name];
        for(int i = 0; i < old.count(); i++) {
            QString keystring = valueToString(old[i]);
            if(m_nameByValue[keystring] == name)
                m_nameByValue.remove(keystring);
        }
        m_keyByName[name] = key;
        for(int i = 0; i < key.count(); i++) {
            QString keystring = valueToString(key[i]);
            m_nameByValue[keystring] = name;
        }
    }
    void resetByDefault() {
        clear();
        foreach(const QString& name, m_keyByNameDefaults.keys()) {
            Key key = m_keyByNameDefaults[name];
            m_keyByName[name] = key;
            for(int i = 0; i < key.count(); i++) {
                QString keystring = valueToString(key[i]);
                m_nameByValue[keystring] = name;
            }
        }
    }
    void clear() {
        m_keyByName.clear();
        m_nameByValue.clear();
    }

private:
    QMap<QString, Action> m_actionByName;
    QMultiMap<QString, QString> m_nameByGroup;
    QMap<QString, Key> m_keyByName;
    QMap<QString, Key> m_keyByNameDefaults;
    QMap<QString, QString> m_nameByValue;
};

#endif // QACTIONMANAGER_H
