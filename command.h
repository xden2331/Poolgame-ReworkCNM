#ifndef COMMAND_H
#define COMMAND_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLine>
#include <QDialog>
#include <QObject>
#include <QColorDialog>

#include "stagethreegame.h"

#include "createballdialog.h"

class Command
{
protected:
    Game* m_receiver;

public:
    Command(Game* receiver):m_receiver(receiver){}
    virtual ~Command(){
        delete m_receiver;
    }

    virtual void execute() = 0;
};

class CreateBallCommand : public Command
{
public:
    CreateBallCommand(Game* receiver, QDialog* parent = 0):
        Command(receiver), m_createBallDialog(new CreateBallDialog(receiver, parent)){
    }
    virtual ~CreateBallCommand(){
        delete m_createBallDialog;
    }

    virtual void execute() override{
        m_createBallDialog->exec();
    }

private:
    CreateBallDialog* m_createBallDialog;
};

#endif // COMMAND_H
