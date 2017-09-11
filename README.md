# 1. QActionManager
A portable component for providing keyboard and mouse input customization functions to applications

## 1.2 Summary

A portable component for providing keyboard and mouse input customization functions to applications

It contains QKeySequence or QMouseSequence and QAction(default) mapping.

Each Action can have/set unique Keyboard/Mouse Sequence.

It has default mapping, and can restore setting.

# 2. QMouseSequence

A simple object provides to serialize mouse inputs like QKeySequence

## 2.2 Summary

QMouseSequence is a class created by mimicking QKeySequence
and holds mouse buttons, wheels, key codes as unique values.

Instances of this class are values rather than objects,
are copyable and comparable, and do not have destructors.
Therefore, you can use this class as QMap's Key or Value.

QMouseSequence is effectively a list of instances of QMouseValue.

A QMouseValue instance can be serialized to a string,
and a QMouseSequence instance can be serialized with ',' separator in one string.

These are a part of [QuickViewer](https://github.com/kanryu/quickviewer).

## License
BSD-2
Copyright (c) 2017, KATO Kanryu

