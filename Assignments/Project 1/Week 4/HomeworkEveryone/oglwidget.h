/**
 * @file olgwidget.h
 *
 * @author Majbrit Schoettner
 * Contact: mshoettner@stud.hs-bremen.de
 * @author Reeder Ward
 * Contact: rward@stud.hs-bremen.de
 * @author David Melamed
 * Contact: dmelamed@stud.hs-bremen.de
 */

#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <vertex.h>
#include <triangle.h>
#include <readobj.h>


class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT


public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

public slots:
    void stepAnimation();


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


protected:
    QTimer* animtimer; // Timer needed to step animation every x msec
    int animstep;      // Current animation step (used to rotate triangle

};




#endif // OGLWIDGET_H
