#include <QPoint>
#include <QPointF>
#include <QList>
#include <QPainterPath>
#include <QPainter>
#include "UBCommunicationLine.h"
#include "core/UBApplication.h"
#include "gui/UBFeaturesWidget.h"
#include <QLabel>
#include <QFrame>
#include "gui/UBCreateLinkPalette.h"
#include <QHBoxLayout>
#include <QWidget>
#include "UBPecs.h"


UBCommunicationLine::UBCommunicationLine(QWidget *parent, QGraphicsScene *scene) : QWidget(parent)
    ,mScene(scene)
{
//setAcceptDrops(true);
    //Tenemos que crear un layout horizontal donde añadir cada widget donde se va a alojar cada picto.
    layout = new QHBoxLayout(this);
}

void UBCommunicationLine::paintEvent(QPaintEvent *e)
{
    /**
    // Usamos esta parte del codigo para hacer pruebas.

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    mBackgroundBrush = QBrush(UBSettings::paletteColor);
    painter.setPen(Qt::NoPen);

    // painter.setBrush(mBackgroundBrush);
    painter.setBrush(mBackgroundBrush);

    QPainterPath borderPath;
    borderPath.setFillRule(Qt::WindingFill);


    borderPath.addRoundedRect(0, 0, width(), height(), 15,15);
    borderPath.addRoundedRect(border(), border(), width() - 2 * border(), height() - 2 * border(), 15,15);
    painter.drawPath(borderPath);
    painter.setBrush(QBrush(QColor(170, 170 ,170)));
    painter.drawRoundedRect(border(), border(), width() - 2 * border(), height() - 2 * border(), 15,15);
    */

    qWarning()<<"Entrando en método paintEvent";


     //codigo
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    mBackgroundBrush = QBrush(UBSettings::paletteColor);
    painter.setPen(Qt::NoPen);
    painter.setBrush(mBackgroundBrush);

    //pintamos el recuadro grande
    painter.drawRoundedRect(calculateX(1,20), calculateY(),calculateWidth(1,-50),calculateHeight(1,-20),10,10);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);


    //pintamos el recuadro de relleno
    path.addRoundedRect(calculateX(1,20)+border(),calculateY()+border(),calculateWidth(1,-90),calculateHeight(1,-60),10,10);
    painter.drawPath(path);

    mScene->setSceneRect(calculateX(1,20)+border(),calculateY()+border(),calculateWidth(1,-90),calculateHeight(1,-60));
    qWarning()<< calculateX(1,20)+border() << calculateY()+border() << calculateWidth(1,-90) << calculateHeight(1,-60);
    //layout->setGeometry(mScene->sceneRect().toRect());
    qWarning()<< "Datos de Scene: " << mScene->sceneRect();

    //pintamos el cuadro de drag and drop
    painter.setPen(Qt::DotLine);
    int ancho=calculateWidth(1,-100);
    int pos=posInit(ancho);
    //Lista donde se añade cada casilla de pictos.
    //QList<pictoCommunicationLine*> listPath;
    //Añadida anterior lista como miembro de la clase. Atributo Privado
    if (listPath.count()==0){ //Si no hay elementos los añado
      for (int i=0; i<8; i++)
      {
        //QPainterPath *qpainter =new QPainterPath();
        // Cada recuadro sera un widget que contendra un qPainterPath
        //pictoCommunicationLine *path2 =new pictoCommunicationLine(this,qpainter,i,mScene);

        //QGraphicsPixmapItem *qpainter =new QGraphicsPixmapItem();
        // Cada recuadro sera un widget que contendra un qPainterPath
        pictoCommunicationLine *path2 =new pictoCommunicationLine(0,i,mScene);


        //layout->addWidget(path2);
        //path2->addRoundedRect(calculateX(1,20)+border()+border()+pos,calculateY(1,20)+border()+border(),pictoWidth(),pictoHeight(),10,10);
        //Hay que pasarle un qPainterPath, no se puede pasar un QWidget
        //painter.drawPath(path2->path());

        qreal x = calculateX(1,20)+border()+border()+pos;
        qreal y = calculateY(1,20)+border()+border();
        path2->setPos(x,y);
        pos=pos+pictoWidth()+separatorPicto();
        listPath.append(path2);
        mScene->addItem(path2);
      }
    }else{
        //Recorro la lista de QPainterPath
        for(int i = 0; i < listPath.count(); i++)
        {
            //Hay que pasarle un qPainterPath, no se puede pasar un QWidget
            //painter.drawPath(listPath[i]->path());
            //mScene->addItem(listPath[i]);
        }
    }
    e->accept();
}

int UBCommunicationLine::border()
{
    return 20;
}

int UBCommunicationLine::calculateX(double percent, int displaced)
{
    return this->width()*(percent/100)+displaced;
}

int UBCommunicationLine::calculateY(double percent,int displaced)
{
    return this->height()*(percent/100)+displaced;
}

int UBCommunicationLine::calculateWidth(double percent,int displaced)
{
    if (percent==1)
    {
        return this->width()+displaced;
    }
    else
    {
        return this->width()*(percent/100)+displaced;
    }

}

int UBCommunicationLine::calculateHeight(double percent,int displaced)
{
    if (percent==1)
    {
        return this->height()+displaced;
    }
    else
    {
        return this->height()*(percent/100)+displaced;
    }
}

int UBCommunicationLine::pictoWidth()
{
    return 180;
}

int UBCommunicationLine::pictoHeight()
{
    return 180;
}

int UBCommunicationLine::separatorPicto()
{
    return 20;
}

int UBCommunicationLine::posInit(int ancho)
{
    int size = pictoWidth() * 8 + separatorPicto() * 8;
    int resto = ancho - size;
    return resto/2;
}

int UBCommunicationLine::screenHeight()
{
    return QApplication::desktop()->screenGeometry().height();
}

int UBCommunicationLine::screenWidth()
{
    return QApplication::desktop()->screenGeometry().width();
}
/*
void UBCommunicationLine::dragMoveEvent(QDragMoveEvent *event)
{
    QWidget::dragMoveEvent(event);
    event->acceptProposedAction();
}

void UBCommunicationLine::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}
*/
pictoCommunicationLine::pictoCommunicationLine(QGraphicsPixmapItem *parent, int i, QGraphicsScene *scene) : QGraphicsPixmapItem(parent)
    ,numero(i)
    ,mScene(scene)
{
    //Esto deben ser atributos de clase y debe ser dinámico
    int width=180;
    int height=180;

    setAcceptDrops(true);
    QPixmap pixmap = QPixmap(":pecs/pictoBlanco.png");
    setPixmap(pixmap.scaled(width,height,Qt::KeepAspectRatio));
    qWarning()<<"Constructor de pictoCommnication: "<<numero;

}

/*void pictoCommunicationLine::addRoundedRect(int x, int y, int w, int h, int rx, int ry)
{
    //mQPainterPath->addRoundedRect(x,y,w,h,rx,ry);

}
*/
void pictoCommunicationLine::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    //QWidget::dragMoveEvent(event);
    //event->acceptProposedAction();
    event->accept();
}

void pictoCommunicationLine::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    qWarning()<<"Picto en casilla: " << numero;
    event->accept();

}

void pictoCommunicationLine::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QList<QUrl> urls;
    urls = event->mimeData()->urls();
    qWarning()<<urls;
    QList<QUrl>::iterator i;
    for (i=urls.begin();i!=urls.end();i++){
        QPixmap pix = QPixmap(i->path());
        //UBPecs *picto = new UBPecs(pix,0,Qt::red,mScene);
        setPixmap(pix.scaled(180,180,Qt::KeepAspectRatio));
        //Añado
        //picto->setPos(mQPainterPath->currentPosition());

        //qWarning()<< picto->pos().x() << picto->pos().y() << picto->sceneBoundingRect() << picto->boundingRect();
        //mScene->addItem(picto);
     setFlag(QGraphicsItem::ItemIsMovable);
    }

    event->accept();
}
