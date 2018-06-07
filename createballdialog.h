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
        // We do not need to delete those QWidget pointers, as
        // in the cpp file, their parents are set, and they will take care of
        // the 'delete'

        if(m_pos != nullptr) delete m_pos;
        if(m_color != nullptr) delete m_color;
        if(m_vel != nullptr) delete m_vel;
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

    QPushButton* m_submit = nullptr;
    QPushButton* m_submitVel = nullptr;

    QLineEdit* m_posXInput = nullptr;
    QLineEdit* m_posYInput = nullptr;
    QLineEdit* m_velXInput = nullptr;
    QLineEdit* m_velYInput = nullptr;
    QLineEdit* m_radiusInput = nullptr;
    QLineEdit* m_massInput = nullptr;

    QColor* m_color = nullptr;
    QVector2D* m_pos = nullptr;
    QVector2D* m_vel = nullptr;
    int radius = -1;
    double mass = -1;
};

#endif // CREATBALLDIALOG_H
