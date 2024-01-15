#include "qsfmlcanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget* parent, unsigned int frameTime) 
    : QWidget(parent), myInitialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);
    myTimer.setInterval(frameTime);
}

QSFMLCanvas::QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime) 
    : QWidget(parent), myInitialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);
    move(position);
    resize(size);
    myTimer.setInterval(frameTime);
}

QSFMLCanvas::~QSFMLCanvas()
{
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        sf::RenderWindow::create(HWND(winId()));
        onInit();
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(renderCanvas()));
        myTimer.start();

        myInitialized = true;
    }
}

void QSFMLCanvas::onInit()
{
}

void QSFMLCanvas::play()
{
    playing = true;
}

void QSFMLCanvas::pause()
{
    playing = false;
}

void QSFMLCanvas::onUpdate()
{
}

void QSFMLCanvas::onScroll(const double& amt)
{
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
}

void QSFMLCanvas::wheelEvent(QWheelEvent* e)
{
    onScroll(e->angleDelta().y());
}

void QSFMLCanvas::renderCanvas()
{
    onUpdate();
    display();
}