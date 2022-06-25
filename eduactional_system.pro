QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Education/course.cpp \
    Education/institute.cpp \
    Education/manager.cpp \
    Education/student.cpp \
    Education/teacher.cpp \
    Global.cpp \
    course_login.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    manager_menu.cpp \
    manager_sign.cpp \
    manager_stu.cpp \
    manager_tea.cpp \
    stu_alllessions.cpp \
    stu_changeinfo.cpp \
    stu_takelession.cpp \
    student_menu.cpp \
    student_sign.cpp \
    tea_changeinfo.cpp \
    tea_grade.cpp \
    tea_menu.cpp \
    tea_teachlessions.cpp \
    teacher_sign.cpp

HEADERS += \
    Education/course.h \
    Education/initDataBass.h \
    Education/institute.h \
    Education/manager.h \
    Education/student.h \
    Education/teacher.h \
    Global.h \
    course_login.h \
    login.h \
    mainwindow.h \
    manager_menu.h \
    manager_sign.h \
    manager_stu.h \
    manager_tea.h \
    stu_alllessions.h \
    stu_changeinfo.h \
    stu_takelession.h \
    student_menu.h \
    student_sign.h \
    tea_changeinfo.h \
    tea_grade.h \
    tea_menu.h \
    tea_teachlessions.h \
    teacher_sign.h

FORMS += \
    course_login.ui \
    login.ui \
    mainwindow.ui \
    manager_menu.ui \
    manager_sign.ui \
    manager_stu.ui \
    manager_tea.ui \
    stu_alllessions.ui \
    stu_changeinfo.ui \
    stu_takelession.ui \
    student_menu.ui \
    student_sign.ui \
    tea_changeinfo.ui \
    tea_grade.ui \
    tea_menu.ui \
    tea_teachlessions.ui \
    teacher_sign.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
