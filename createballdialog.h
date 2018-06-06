#ifndef CREATBALLDIALOG_H
#define CREATBALLDIALOG_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLine>
#include <QDialog>
#include <QObject>
#include <QColorDialog>
#include <QMouseEvent>
#include <QMessageBox>

#include <sstream>
#include <QMainWindow>

#include "game.h"
#include "stagethreegame.h"
#include "ui_dialog.h"

namespace Ui {
class CreatBallDialog;
}

class CreateBallDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateBallDialog(Game* receiver, QDialog* parent = 0);
    virtual ~CreateBallDialog(){
        delete m_receiver;
        delete m_pos;
        delete m_posXInput;
        delete m_posYInput;
        delete m_color;
        delete m_submit;
        delete m_vel;
        delete m_velXInput;
        delete m_velYInput;
        delete m_radiusInput;
        delete m_massInput;
    }

public slots:
    void slotButtonClick_pos();
    void slotButtonClick_vel();
    void slotButtonClick_submit();
    void slotButtonClick_submitVel();
    void slotButtonClick_create();

    /* ---SOURCE:https://blog.csdn.net/mengxiangjia_linxi/article/details/76522510--- */
    /* -----------------------------Slightly modified---------------------------------*/
    void slotButtonClick_color();   //Choosing color

private:
    bool isNum(std::string str);

private:
    Game* m_receiver;

    QPushButton* m_submit;
    QPushButton* m_submitVel;

    QLineEdit* m_posXInput;
    QLineEdit* m_posYInput;
    QLineEdit* m_velXInput;
    QLineEdit* m_velYInput;
    QLineEdit* m_radiusInput;
    QLineEdit* m_massInput;

    QColor* m_color = nullptr;
    QVector2D* m_pos = nullptr;
    QVector2D* m_vel = nullptr;
    int radius = -1;
    double mass = -1;
};

#endif // CREATBALLDIALOG_H
