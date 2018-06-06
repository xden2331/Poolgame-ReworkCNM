#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMouseEvent>
#include "utils.h"


Dialog::Dialog(Game *game, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_game(game)
{
    ui->setupUi(this);

    // for animating (i.e. movement, collision) every animFrameMS
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(nextAnim()));
    aTimer->start(animFrameMS);

    // for drawing every drawFrameMS milliseconds
    dTimer = new QTimer(this);
    connect(dTimer, SIGNAL(timeout()), this, SLOT(tryRender()));
    dTimer->start(drawFrameMS);

    // set the window size to be at least the table size
    this->resize(game->getMinimumWidth(), game->getMinimumHeight());
    if(dynamic_cast<StageThreeGame*>(m_game)){
        // Source: https://blog.csdn.net/mengxiangjia_linxi/article/details/76522510
        QPushButton* button_exec = new QPushButton("Create Ball", this);
        connect(button_exec, SIGNAL(clicked()), this, SLOT(slotButtonClick_createBall()));
        button_exec->setMaximumWidth(100);
        button_exec->move(game->getMinimumWidth()/2-30,
                          game->getMinimumHeight()-30);
    }
}

Dialog::~Dialog()
{
    delete aTimer;
    delete dTimer;
    delete m_game;
    delete ui;
    delete command;
}

void Dialog::tryRender() {
    this->update();
}

void Dialog::nextAnim() {
    m_game->animate(1.0/(double)animFrameMS);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_game->render(painter);
}

void Dialog::mousePressEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseClickFn, event);
}

void Dialog::mouseReleaseEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseRelFn, event);
}
void Dialog::mouseMoveEvent(QMouseEvent* event) {
    evalAllEventsOfTypeSpecified(MouseEventable::EVENTS::MouseMoveFn, event);
}

void Dialog::evalAllEventsOfTypeSpecified(MouseEventable::EVENTS t, QMouseEvent *event) {
    // handle all the clicky events, and remove them if they've xPIRED
    MouseEventable::EventQueue& Qu = m_game->getEventFns();
    for (ssize_t i = Qu.size()-1; i >= 0; i--) {
        if (auto spt = (Qu.at(i)).lock()) {
            if (spt->second == t) {
                spt->first(event);
            }
        } else {
            // remove this element from our vector
            Qu.erase(Qu.begin() + i);
        }
    }
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    StageThreeGame* stageThreeGame =
            dynamic_cast<StageThreeGame*>(m_game);
    if(!stageThreeGame) return;
    stageThreeGame->keyPress(event->key() == Qt::Key_R);
}

void Dialog::slotButtonClick_createBall()
{
    command = new CreateBallCommand(m_game, this);
    if(command) command->execute();
    command = nullptr;
}
