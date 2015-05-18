#ifndef __LOGICOPERATIONS_H__
#define __LOGICOPERATIONS_H__

#include <QDockWidget>

#include "./../../../pluginTool/Plugin.h"
#include "./../../../pluginTool/InterfacePlugin.h"
#include "./../../../interfaces/MainWindowInterface.h"
#include "./../../../interfaces/LogicOperationsInterface.h"
#include "./../../../paintWidget/GContainer.h"
#include "./../../../paintWidget/GVectorFigure.h"
#include "./../../../interfaces/GSRInterface.h"
#include "./../../../interfaces/RPWInterface.h"
#include "./../../../interfaces/PaintWidgetInterface.h"
#include "ui_LogicOperations.h"

#include <QDebug>

enum { LEFT, CENTERX, RIGHT, TOP, CENTERY, BOTTOM, GAPSX, GAPSY};
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

            alignSignalMapper = new QSignalMapper(this);

            distributeSignalMapper = new QSignalMapper(this);
            logicSignalMapper = new QSignalMapper(this);
            ui.setupUi( this );

            ui.AlignGroupBox->setVisible(false);
            ui.DistributeGroupBox->setVisible(false);

            connect(alignSignalMapper, SIGNAL(mapped(int)),this, SLOT(align(int)));
            connect(distributeSignalMapper, SIGNAL(mapped(int)),this, SLOT(distribute(int)));

            alignSignalMapper->setMapping(ui.AlignButton_01, LEFT);
            connect(ui.AlignButton_01, SIGNAL(clicked()), alignSignalMapper, SLOT(map()));
            alignSignalMapper->setMapping(ui.AlignButton_02, CENTERX);
            connect(ui.AlignButton_02, SIGNAL(clicked()), alignSignalMapper, SLOT(map()));
            alignSignalMapper->setMapping(ui.AlignButton_03, RIGHT);
            connect(ui.AlignButton_03, SIGNAL(clicked()), alignSignalMapper, SLOT(map()));
            alignSignalMapper->setMapping(ui.AlignButton_04, TOP);
            connect(ui.AlignButton_04, SIGNAL(clicked()), alignSignalMapper, SLOT(map()));
            alignSignalMapper->setMapping(ui.AlignButton_05, CENTERY);
            connect(ui.AlignButton_05, SIGNAL(clicked()), alignSignalMapper, SLOT(map()));
            alignSignalMapper->setMapping(ui.AlignButton_06, BOTTOM);
            connect(ui.AlignButton_06, SIGNAL(clicked()), alignSignalMapper, SLOT(map()));

            distributeSignalMapper->setMapping(ui.DistributeButton_1, LEFT);
            connect(ui.DistributeButton_1, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));
            distributeSignalMapper->setMapping(ui.DistributeButton_2, CENTERX);
            connect(ui.DistributeButton_2, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));
            distributeSignalMapper->setMapping(ui.DistributeButton_3, RIGHT);
            connect(ui.DistributeButton_3, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));
            distributeSignalMapper->setMapping(ui.DistributeButton_5, TOP);
            connect(ui.DistributeButton_5, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));
            distributeSignalMapper->setMapping(ui.DistributeButton_6, CENTERY);
            connect(ui.DistributeButton_6, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));
            distributeSignalMapper->setMapping(ui.DistributeButton_7, BOTTOM);
            connect(ui.DistributeButton_7, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));

            distributeSignalMapper->setMapping(ui.DistributeButton_4, GAPSX);
            connect(ui.DistributeButton_4, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));
            distributeSignalMapper->setMapping(ui.DistributeButton_8, GAPSY);
            connect(ui.DistributeButton_8, SIGNAL(clicked()), distributeSignalMapper, SLOT(map()));

            //
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
            /*bool isX = true;
            qreal x = rect.left(),
                y = rect.top(),
                coeff = 0, // 0 - левая/верхняя сторона  |  0.5 - центр  |  1 - правая/нижняя сторона
                selectionW = rect.width(),
                selectionH = rect.height();*/
            switch(mode){
                case SUM:
                    //coeff = 0.5;
                    qDebug() << "SUM";
                    break;
                case DIFF:
                    //coeff = 1;
                    qDebug() << "DIFF";
                    break;
                case OR:
                    //isX = false;
                    qDebug() << "OR";
                    break;
                case XOR:
                    //isX = false; coeff = 0.5;
                    qDebug() << "XOR";
                    break;
            }



            for (int i = objectCount - 1; i >= 0; i--) {
                GObject *obj = container->object(i);
                QPolygonF poly = obj->points(0);

                int countSplinePoints = ( ( poly.size() - 1 ) / 3 ) * 3;

                for( int j = obj->points(0).size() - 1; j >= 0; j--) {
                    obj->deletePoint(j);
                }

                /*for( int j = 1; j < ( countSplinePoints + 1 ); j += 3 ) {
                    //obj->addPoint(poly.at(j - 1).toPoint());
                }*/

                //container->add(obj, true);
                //container->add(newObj);
                //obj->addPoint(QPoint(0, 0));
            }



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


            for (int i = objectCount - 1; i >= 0; i--) {
                //painter->deleteFigure(painter->layer(), i);
            }

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

            /*

            // сделать массив индексов выделения и массив координат фигур, по которому будет сортировка
            int* indicesArray = new int[objectCount];
            qreal* figureSizes = new qreal[objectCount];
            for(int i=0;i<objectCount;i++){
                indicesArray[i] = i;

                QRectF objectRect = container->object(i)->boundingRect();
                if(isX){
                    figureSizes[i] = objectRect.x() + objectRect.width() * coeff;
                    sum -= objectRect.width();
                }else{
                    figureSizes[i] = objectRect.y() + objectRect.height() * coeff;
                    sum -= objectRect.height();
                }
            }

            // отсортировать индексы так, что бы фигуры, вызываемые из выделения по индексам, были по порядку
            for(int i=0;i<objectCount-1;i++){
                int min = i;
                for(int j=i;j<objectCount;j++)
                    if(figureSizes[ indicesArray[j] ] < figureSizes[ indicesArray[min] ])
                        min = j;
                if(min != i){
                    //swap index[i],index[min]
                    int tmp = indicesArray[i];
                    indicesArray[i] = indicesArray[min];
                    indicesArray[min] = tmp;
                }
            }

            // по порядку расставляем объкты выделения
            if( ! isGaps )
                for(int i=1;i<objectCount-1;i++){
                    GObject *obj = container->object(indicesArray[i]);
                    if(isX)
                        obj->move(figureSizes[ indicesArray[0] ] + i*difference - figureSizes[ indicesArray[i] ],0);
                    else
                        obj->move(0,figureSizes[ indicesArray[0] ] + i*difference - figureSizes[ indicesArray[i] ]);
                }
            else{
                int prevObjIndex = 0;
                for(int i=1;i<objectCount-1;i++){
                    GObject *obj = container->object(indicesArray[i]);
                    if(isX)
                        obj->move(container->object(indicesArray[prevObjIndex])->boundingRect().right() + difference - obj->boundingRect().x(),0);
                    else
                        obj->move(0,container->object(indicesArray[prevObjIndex])->boundingRect().bottom() + difference - obj->boundingRect().y());
                    prevObjIndex = i;
                }
            }

            */


            // что бы рамка изменила свой размер имитируем отпускание кнопки мыши по ней
            //selection->mouseRelease(Qt::LeftButton,rect.center(),Qt::NoModifier);
            // вызываем перерисовку и сохраняем в историю изменений
            selection->emitChanged();
            selection->emitStateChanged("LogicOperate");
        }

        void align(int direction){
            container = selection->getSelectedAsGContainer();
            int objectCount = container->countObjects();
            if(objectCount < 2) return;
            QRect rect = selection->getPosition();
            bool isX = true;
            qreal x = rect.left(),
                y = rect.top(),
                coeff = 0, // 0 - левая/верхняя сторона  |  0.5 - центр  |  1 - правая/нижняя сторона
                selectionW = rect.width(),
                selectionH = rect.height();
            switch(direction){
                case CENTERX:
                    coeff = 0.5; break;
                case RIGHT:
                    coeff = 1; break;
                case TOP:
                    isX = false; break;
                case CENTERY:
                    isX = false; coeff = 0.5; break;
                case BOTTOM:
                    isX = false; coeff = 1; break;
            }
            for(int i=0;i<objectCount;i++){
                GObject *obj = container->object(i);
                QRectF objectRect = obj->boundingRect();
                if(isX)
                    obj->move((x + selectionW * coeff) - (objectRect.x() + objectRect.width() * coeff) , 0);
                else
                    obj->move(0 , (y + selectionH * coeff) - (objectRect.y() + objectRect.height() * coeff));
            }
            // что бы рамка изменила свой размер имитируем отпускание кнопки мыши по ней
            selection->mouseRelease(Qt::LeftButton,rect.center(),Qt::NoModifier);
            // вызываем перерисовку и сохраняем в историю изменений
            selection->emitChanged();
            selection->emitStateChanged("Align");
        }

        void distribute(int direction){
            container = selection->getSelectedAsGContainer();
            int objectCount = container->countObjects();
            if(objectCount < 3) return;
            bool isX = true,
                isGaps = false;
            qreal coeff = 0, // 0 - левая/верхняя сторона  |  0.5 - центр  |  1 - правая/нижняя сторона
                sum = 0; // сумма ширин/высот объектов выделения
            QRect rect = selection->getPosition();
            switch(direction){
                case CENTERX:
                    coeff = 0.5; break;
                case RIGHT:
                    coeff = 1; break;
                case TOP:
                    isX = false; break;
                case CENTERY:
                    isX = false; coeff = 0.5; break;
                case BOTTOM:
                    isX = false; coeff = 1; break;
                case GAPSX:
                    isGaps = true; coeff = 0.5; sum = rect.width(); break;
                case GAPSY:
                    isGaps = true; isX = false; coeff = 0.5; sum = rect.height(); break;
            }

            // сделать массив индексов выделения и массив координат фигур, по которому будет сортировка
            int* indicesArray = new int[objectCount];
            qreal* figureSizes = new qreal[objectCount];
            for(int i=0;i<objectCount;i++){
                indicesArray[i] = i;

                QRectF objectRect = container->object(i)->boundingRect();
                if(isX){
                    figureSizes[i] = objectRect.x() + objectRect.width() * coeff;
                    sum -= objectRect.width();
                }else{
                    figureSizes[i] = objectRect.y() + objectRect.height() * coeff;
                    sum -= objectRect.height();
                }
            }

            // отсортировать индексы так, что бы фигуры, вызываемые из выделения по индексам, были по порядку
            for(int i=0;i<objectCount-1;i++){
                int min = i;
                for(int j=i;j<objectCount;j++)
                    if(figureSizes[ indicesArray[j] ] < figureSizes[ indicesArray[min] ])
                        min = j;
                if(min != i){
                    //swap index[i],index[min]
                    int tmp = indicesArray[i];
                    indicesArray[i] = indicesArray[min];
                    indicesArray[min] = tmp;
                }
            }

            // считаем расстояние между 1й и последней фигурами
            qreal distance;
            if( ! isGaps )
                distance = figureSizes[ indicesArray[objectCount-1] ]
                    - figureSizes[ indicesArray[0] ];
            else
                distance = sum;

            // делим расстояние на количество промежутков между фигурами
            qreal difference = distance / (objectCount-1);

            // по порядку расставляем объкты выделения
            if( ! isGaps )
                for(int i=1;i<objectCount-1;i++){
                    GObject *obj = container->object(indicesArray[i]);
                    if(isX)
                        obj->move(figureSizes[ indicesArray[0] ] + i*difference - figureSizes[ indicesArray[i] ],0);
                    else
                        obj->move(0,figureSizes[ indicesArray[0] ] + i*difference - figureSizes[ indicesArray[i] ]);
                }
            else{
                int prevObjIndex = 0;
                for(int i=1;i<objectCount-1;i++){
                    GObject *obj = container->object(indicesArray[i]);
                    if(isX)
                        obj->move(container->object(indicesArray[prevObjIndex])->boundingRect().right() + difference - obj->boundingRect().x(),0);
                    else
                        obj->move(0,container->object(indicesArray[prevObjIndex])->boundingRect().bottom() + difference - obj->boundingRect().y());
                    prevObjIndex = i;
                }
            }

            // что бы рамка изменила свой размер имитируем отпускание кнопки мыши по ней
            selection->mouseRelease(Qt::LeftButton,rect.center(),Qt::NoModifier);
            // вызываем перерисовку и сохраняем в историю изменений
            selection->emitChanged();
            selection->emitStateChanged("Align");
        }

    private:

		MainWindowInterface* mainWin;
        PaintWidgetInterface* painter;
        QDockWidget *LogicOperationsWindow;
        Ui::LogicOperationsForm ui;

        GSRInterface* selection;
        RPWInterface* realPainter;
        GContainer* container;

        QSignalMapper *alignSignalMapper;
        QSignalMapper *distributeSignalMapper;

        QSignalMapper *logicSignalMapper;

};

#endif /* __LogicOperations_H__ */
