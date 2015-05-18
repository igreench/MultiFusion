#ifndef __LOGICOPERATIONS_H__
#define __LOGICOPERATIONS_H__

#include <QDockWidget>

#include "./../../../pluginTool/Plugin.h"
#include "./../../../pluginTool/InterfacePlugin.h"
#include "./../../../interfaces/MainWindowInterface.h"
#include "./../../../interfaces/LogicOperationsInterface.h"
#include "./../../../paintWidget/RPW.h"
#include "./../../../paintWidget/GObject.h"
#include "./../../../paintWidget/GContainer.h"
#include "./../../../paintWidget/GVectorFigure.h"
#include "./../../../interfaces/GObjectInterface.h"
#include "./../../../interfaces/GSRInterface.h"
#include "./../../../interfaces/RPWInterface.h"
#include "./../../../interfaces/PaintWidgetInterface.h"
#include "ui_LogicOperations.h"

#include <QDebug>

enum { SUM, DIFF, OR, XOR };


class LogicOperations:public QWidget, public LogicOperationsInterface, public InterfacePlugin
{
	Q_OBJECT
    Q_INTERFACES( LogicOperationsInterface )
    Q_INTERFACES( InterfacePlugin )

	public:

        virtual void createPlugin(QObject *parent, QString idParent, plugin::PluginsManager *manager)
        {
			mainWin = MAINWINDOW(parent);
            if (mainWin!=0)
			{
                painter = PAINTWIDGETINTERFACE(mainWin->getPaintWidget());
                realPainter = RPWINTEFACE(painter->getRealPaintWidget());
                realPaintWidget = REALPAINTWIDGET(painter->getRealPaintWidget());
                selection = GSRINTEFACE(realPainter->getSelection());

                LogicOperationsWindow = new QDockWidget(mainWin);
                LogicOperationsWindow->setWindowTitle( tr( "Logic Operations" ) );
                this->setParent( LogicOperationsWindow );
                LogicOperationsWindow->setWidget(this);
                mainWin->addDockWidget( Qt::RightDockWidgetArea, LogicOperationsWindow );

                QMenu* objectMenu = mainWin->getObjectMenu();
                QAction* showLogicOperations = objectMenu->addAction(  tr( "&Logic Operations..." ) );
                objectMenu->addSeparator();
                showLogicOperations->setIcon( QIcon( ":/main/images/dialog-align-and-distribute.png" ) );
                connect( showLogicOperations, SIGNAL( triggered( bool ) ), this, SLOT( showLogicOperations() ) );

                manager->addPlugins(this, "Logic Operations");
            }
		}

		virtual QString getName()const
		{
            return "Logic Operations";
		}

        LogicOperations( plugin::PluginsManager *manager )
        {

            logicSignalMapper = new QSignalMapper(this);
            ui.setupUi( this );

            connect(logicSignalMapper, SIGNAL(mapped(int)),this, SLOT(logicOperate(int)));

            logicSignalMapper->setMapping(ui.toolButton, SUM);
            connect(ui.toolButton, SIGNAL(clicked()), logicSignalMapper, SLOT(map()));
            logicSignalMapper->setMapping(ui.toolButton_2, DIFF);
            connect(ui.toolButton_2, SIGNAL(clicked()), logicSignalMapper, SLOT(map()));
            logicSignalMapper->setMapping(ui.toolButton_3, OR);
            connect(ui.toolButton_3, SIGNAL(clicked()), logicSignalMapper, SLOT(map()));
            logicSignalMapper->setMapping(ui.toolButton_4, XOR);
            connect(ui.toolButton_4, SIGNAL(clicked()), logicSignalMapper, SLOT(map()));
        }

        virtual ~LogicOperations()
        {
        }


    public slots:

        void showLogicOperations()
        {
            LogicOperationsWindow->show();
        }


    private slots:

        void logicOperate(int mode) {
            container = selection->getSelectedAsGContainer();
            int objectCount = container->countObjects();
            //if(objectCount != 2) return;
            QRect rect = selection->getPosition();
            switch(mode){
                case SUM:
                    qDebug() << "SUM";
                    break;
                case DIFF:
                    qDebug() << "DIFF";
                    break;
                case OR:
                    qDebug() << "OR";
                    break;
                case XOR:
                    qDebug() << "XOR";
                    break;
            }

            for (int i = objectCount - 1; i >= 0; i--) {
                GObject *obj = container->object(i);
                QPolygonF poly = obj->points(0);

                int countSplinePoints = ( ( poly.size() - 1 ) / 3 ) * 3;

                for( int j = obj->points(0).size() - 1; j >= 0; j--) {
                    //obj->deletePoint(j);
                }

                /*for( int j = 1; j < ( countSplinePoints + 1 ); j += 3 ) {
                    //obj->addPoint(poly.at(j - 1).toPoint());
                }*/

                //container->add(obj, true);
                //container->add(newObj);
                //obj->addPoint(QPoint(0, 0));
            }

            /*GObjectInterface *g = container->copyObject();
            g->addPoint(QPoint(0, 0));
            g->addPoint(QPoint(10, 0));
            g->addPoint(QPoint(10, 10));
            g->addPoint(QPoint(0, 10));
            painter->deleteSelected();*/
            //container->add(GOBJECT(g));
            //selection->addSelected(g);
            //GObject *obj = container->object(0);
            //realPaintWidget->addNewObject(GOBJECT(g));
            realPaintWidget->addNewObject(container->object(0));


            //L_Polygon p;

            //container->add(GOBJECT(p));

            //GObject *obj = container->object(0);
            //obj->deletePoint()

            /*for( int j = obj->points(0).size() - 1; j >= 0; j--) {
                obj->deletePoint(j);
            }*/

            /*obj->deletePoint(0);
            obj->deletePoint(0);
            obj->deletePoint(0);
            obj->deletePoint(0);*/

            //container->removeAll();
            //selection->getSelected()-
            //painter->deleteFigure(painter->layer(), 0);



            /*
            qDebug() << "0: " << container->objectName(0);
            qDebug() << "1: " << container->objectName(1);
            QPolygonF poly = container->object(0)->points(0).united(container->object(1)->points(0));
            container->object(0)->points(0).clear();
            for (int i = 0; i < poly.size(); i++) {
                QPointF point = poly.at(i);
                container->object(0)->addPoint(point.toPoint());
            }*/

            ////////////////////

            /*int countFigures;
            if(painter->isContainsFrame(painter->layer())) {
                countFigures = painter->countFigures(painter->layer());
                for (int j = countFigures - 1; j >= 0; j--) {
                    painter->deleteFigure(painter->layer(), j);
                }
            }*/


            //         GObject *obj = container->object(0);


            //GContainer *c = GCONTAINER( realPainter->selection.selected( 0 ) );
            //painterlayers[painter.currentLayer]->remove( painter.layers[painter.currentLayer]->objectIndex( c ) );

            /*int count = realPaintWidget->getLayers()[realPaintWidget->getCurrentLayer()]->countObjects();
            for( int i = count - 1; i >= 0; i-- )
            {
                if( realPaintWidget->getSelection().isInside( realPaintWidget->getLayers()[realPaintWidget->getCurrentLayer()]->object( i ) ) ) {
                    //c.add( realPaintWidget->getLayers()[realPaintWidget->currentLayer]->object( i ) );
                    realPaintWidget->getLayers()[realPaintWidget->getCurrentLayer()]->remove(i);
                }
            }*/


            //painter->deleteSelected();


            //GVectorFigure figure(points, false, true, painter->frame());
            //GVectorFigure *figure = new GVectorFigure();


            /*for (int i = objectCount - 1; i >= 0; i--) {
                GObject *obj = container->object(i);


                int countSplinePoints = ( ( obj->points(painter->frame()).size() - 1 ) / 3 ) * 3;
                for( int j = countSplinePoints; j >= 0; j--) {
                    obj->deletePoint(j);
                }

                obj->addPoint(QPoint(0, 0));
                obj->addPoint(QPoint(10, 0));
                obj->addPoint(QPoint(10, 10));
                obj->addPoint(QPoint(0, 10));
            }*/

            //container->getObjects()->
            /*container->addPoint(QPoint(0, 0));
            container->addPoint(QPoint(10, 0));
            container->addPoint(QPoint(10, 10));
            container->addPoint(QPoint(0, 10));*/



            /*GVectorFigure *figure = new GVectorFigure();
            figure->addPoint(QPoint(0, 0));
            figure->addPoint(QPoint(10, 0));
            figure->addPoint(QPoint(10, 10));
            figure->addPoint(QPoint(0, 10));
            container->add(GOBJECT(figure), true);*/

            /*container->addPoint(QPoint(0, 0));
            container->addPoint(QPoint(10, 0));
            container->addPoint(QPoint(0, 10));
            container->addPoint(QPoint(10, 10));*/

            FigureToolInterface::FigureInfo info;

            info.closed = false;
            info.spline = false;
            info.points << QPointF( 0.0, 0.0 );
            info.name = "Polygon";

            //FigureToolInterface tool = FIGURETOOL(realPainter->getCurrentTool());
            //tool.figure() << info;

            //        FigureToolInterface


            //realPaintWidget->addNewObject();
            //GObjectInterface * o = GObject::create(0, QPoint(0, 0), "Polygon" , painter->frame());

//            container->add( GOBJECT(GObject::create(realPainter->getCurrentTool(), QPoint(0, 0), "Polygon" , painter->frame())), true );
    //		layers[currentLayer]->add( GOBJECT(o), true );

            //selection->setSelected( o );
            //selection->setIsNewFigure(true);

            /*

            /*for (int i = objectCount - 1; i >= 0; i--) {
                painter->deleteFigure(painter->layer(), i);
            }*/

            /*int countLayers = painter->countLayers();
            int countFigures;
            for (int i = countLayers - 1; i >= 0; i-- ) {
                if(painter->isContainsFrame(i)) {
                    countFigures = painter->countFigures(i);
                    for (int j = countFigures - 1; j >= 0; j--) {
                        painter->deleteFigure(i, j);
                    }
                }
            }*/

            /*

            GObject *obj = container->object(0);
            QPolygonF poly = obj->points(0);
            int countSplinePoints = ( ( poly.size() - 1 ) / 3 ) * 3;
            for( int j = 1; j < ( countSplinePoints + 1 ); j += 3 ) {
                obj->addPoint(poly.at(j - 1).toPoint());
            }
            container->add(obj, true);
            */

            //painter->getRealPaintWidget()->


            //
/*
            GObject* ob =container->object(0);
            if (!ob->isContainer()) {
                //GVectorFigure* v = GVECTORFIGURE(ob);

                //v->points(0).clear();
                //return (v->isSpline())?1:0;
            }*/

            ////////////////////

            /*for (int i = 0; i < objectCount; i++) {
                GObject *obj = container->object(i);
                //curframe?
                obj->points(0)
                QRectF objectRect = obj->boundingRect();
                obj->move(5, 5);
            }*/

            //selection->mouseRelease(Qt::LeftButton,rect.center(),Qt::NoModifier);
            selection->emitChanged();
            selection->emitStateChanged("LogicOperate");
        }

    private:

		MainWindowInterface* mainWin;
        PaintWidgetInterface* painter;
        QDockWidget *LogicOperationsWindow;
        Ui::LogicOperationsForm ui;

        GSRInterface* selection;
        RPWInterface* realPainter;
        RealPaintWidget* realPaintWidget;
        GContainer* container;

        QSignalMapper *logicSignalMapper;

};


#endif /* __LogicOperations_H__ */
