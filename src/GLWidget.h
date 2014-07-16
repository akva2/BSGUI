#include <set>

#include <QVector3D>
#include <QVector4D>

#include <QGLWidget>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QWheelEvent>

#include "DispObject.h"

#ifndef GLWIDGET_H
#define GLWIDGET_H

#define MAX_FOV 135.0

enum direction { POSX, NEGX, POSY, NEGY, POSZ, NEGZ };


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = NULL);
    virtual ~GLWidget();

    QSize sizeHint() const;

    inline double inclination() { return _inclination; }
    void setInclination(double val, bool fromMouse);

    inline double azimuth() { return _azimuth; }
    void setAzimuth(double val, bool fromMouse);

    inline double fov() { return _fov; }
    void setFov(double val, bool fromMouse);

    inline double zoom() { return _zoom; }
    void setZoom(double val, bool fromMouse);

    inline QVector3D lookAt() { return _lookAt; }
    void setLookAt(QVector3D pt, bool fromMouse);

    inline direction dir() { return _dir; }
    void setDir(direction val);

    inline bool rightHanded() { return _rightHanded; }
    void setRightHanded(bool val);

signals:
    void inclinationChanged(double val, bool fromMouse);
    void azimuthChanged(double val, bool fromMouse);
    void fovChanged(double val, bool fromMouse);
    void zoomChanged(double val, bool fromMouse);
    void lookAtChanged(QVector3D pt, bool fromMouse);
    void dirChanged(direction val);
    void rightHandedChanged(bool val);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void matrices(QMatrix4x4 *, QMatrix4x4 *);
    void multiplyDir(QMatrix4x4 *);

    QOpenGLShaderProgram vcProgram;
    QOpenGLShaderProgram ccProgram;
    QOpenGLShaderProgram lnProgram;

    std::set<DispObject *> objects;
    DispObject *selectedObject;

    bool shiftPressed;
    bool ctrlPressed;
    bool altPressed;

    double _zoom;
    QVector3D _lookAt;
    double _fov;
    double _inclination;
    double _azimuth;
    direction _dir;
    bool _rightHanded;

    bool cameraTracking;
    QPoint cameraOrig;
    double inclinationOrig;
    double azimuthOrig;
    QVector3D lookAtOrig;
};

#endif /* GLWIDGET_H */
