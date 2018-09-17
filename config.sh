#!/bin/sh
export QT5_PATH=/mnt/e/linux/Qt5.7.0/5.7/gcc_64/
export QT5_BIN_DIR=$QT5_PATH/bin/
export Qt5Widgets_DIR=$QT5_PATH/lib/cmake/Qt5Widgets/
export Qt5Core_DIR=$QT5_PATH
export PATH=$QT5_BIN_DIR:$PATH
cmake ..