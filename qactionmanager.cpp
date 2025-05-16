#include <QtGui>

#include "qactionmanager.h"
#include "qmousesequence.h"

template<typename Key, typename Value, typename Action>
QString QActionManager<Key, Value, Action>::valueToString(Value value)
{
    return value.toString();
}
template<>
QString QActionManager<QKeySequence, QKeyCombination, QAction*>::valueToString(QKeyCombination key)
{
    return QKeySequence(key).toString();
}
template<>
QString QActionManager<QMouseSequence, QMouseValue, QAction*>::valueToString(QMouseValue value)
{
    return value.toString();
}
