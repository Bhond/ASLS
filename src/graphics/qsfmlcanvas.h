#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <qwidget.h>
#include <qtimer.h>
#include <qobject.h>
#include <qevent.h>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

protected:
    QTimer myTimer;
    bool playing = false;

private:
    bool myInitialized;

public:
    QSFMLCanvas(QWidget* Parent, unsigned int FrameTime = 0);
    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    virtual ~QSFMLCanvas();

public:
    virtual void onInit();

protected:
    virtual void onUpdate();
    virtual void onScroll(const double& amt);
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent* e) override;

public slots:
    void play();
    void pause();
    virtual void reset() = 0;
    void renderCanvas();
};