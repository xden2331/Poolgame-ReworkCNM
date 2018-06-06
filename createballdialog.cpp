#include "createballdialog.h"


CreateBallDialog::CreateBallDialog(Game* receiver, QDialog *parent):
    m_receiver(receiver),QDialog(parent)
{
    QLabel* m_greeting = new QLabel("Wanna make a new ball? (Only support creating simple balls)");

    // Position
    QPushButton* button_pos = new QPushButton("Position", this);
    connect(button_pos, SIGNAL(clicked()), this, SLOT(slotButtonClick_pos()));
    m_posXInput = new QLineEdit();
    m_posYInput = new QLineEdit();
    m_submit = new QPushButton("Submit");
    connect(m_submit, SIGNAL(clicked()), this, SLOT(slotButtonClick_submit()));

    //Velocity
    QPushButton* button_vel = new QPushButton("Velocity", this);
    connect(button_vel, SIGNAL(clicked()), this, SLOT(slotButtonClick_vel()));
    m_velXInput = new QLineEdit();
    m_velYInput = new QLineEdit();
    m_submitVel = new QPushButton("Submit");
    connect(m_submitVel, SIGNAL(clicked()), this, SLOT(slotButtonClick_submitVel()));

    //Color
    QPushButton* button_color = new QPushButton("Color select", this);
    connect(button_color, SIGNAL(clicked()), this, SLOT(slotButtonClick_color()));

    //radius
    QLabel* radiusLabel = new QLabel("Radius(double):");
    m_radiusInput = new QLineEdit();
    radiusLabel->setBuddy(m_radiusInput);
    QHBoxLayout* h1layout = new QHBoxLayout();
    h1layout->addWidget(radiusLabel);
    h1layout->addWidget(m_radiusInput);

    //mass
    QLabel* massLabel = new QLabel("Mass(integer):");
    m_massInput = new QLineEdit();
    massLabel->setBuddy(m_massInput);
    QHBoxLayout* h2layout = new QHBoxLayout();
    h2layout->addWidget(massLabel);
    h2layout->addWidget(m_massInput);

    //create Ball
    QPushButton* button_createBall = new QPushButton("Create nowwwww!");
    connect(button_createBall, SIGNAL(clicked(bool)), this, SLOT(slotButtonClick_create()));

    QVBoxLayout * layout = new QVBoxLayout();
    layout->setMargin(10);

    layout->addWidget(m_greeting);
    layout->addWidget(button_pos);
    layout->addWidget(button_vel);
    layout->addWidget(button_color);
    layout->addLayout(h2layout);
    layout->addLayout(h1layout);
    layout->addWidget(button_createBall);

    this->setWindowTitle("Creating a ball...");
    this->setLayout(layout);
}

/* ----------------------------------Color selection dialog---------------------------------- */
void CreateBallDialog::slotButtonClick_color()
{
    QColorDialog color;
    color.setWindowTitle("Choosing ball's color");
    color.exec();
    QColor c = color.selectedColor();
    if(c == Qt::white){
        QMessageBox::warning(this, "Warning", "Cannot choose white.");
        return;
    }
    m_color = new QColor(c);
}
/* -------------------------------------end---------------------------------------- */

void CreateBallDialog::slotButtonClick_pos(){
    QDialog d;
    QVBoxLayout * layout = new QVBoxLayout();
    std::string x_range = "range: [0, " + std::to_string(m_receiver->getMinimumWidth()) + "]";
    QLabel* x_rangeLabel = new QLabel(QString(x_range.c_str()));
    QLabel* xLabel = new QLabel("x-coordinator:");
    xLabel->setBuddy(m_posXInput);
    QHBoxLayout* h1layout = new QHBoxLayout();
    h1layout->addWidget(xLabel);
    h1layout->addWidget(m_posXInput);

    std::string y_range = "range: [0, " + std::to_string(m_receiver->getMinimumHeight()) + "]";
    QLabel* y_rangeLabel = new QLabel(QString(y_range.c_str()));
    QLabel* yLabel = new QLabel("y-coordinator:");
    yLabel->setBuddy(m_posYInput);
    QHBoxLayout* h2layout = new QHBoxLayout();
    h2layout->addWidget(yLabel);
    h2layout->addWidget(m_posYInput);

    layout->setMargin(10);
    layout->addWidget(x_rangeLabel);
    layout->addLayout(h1layout);
    layout->addWidget(y_rangeLabel);
    layout->addLayout(h2layout);
    layout->addWidget(m_submit);
    d.setLayout(layout);
    d.setWindowTitle("Setting position");
    d.exec();
}

void CreateBallDialog::slotButtonClick_submit(){
    std::string xInput = m_posXInput->text().toStdString();
    std::string yInput = m_posYInput->text().toStdString();
    if(m_posXInput->text().isEmpty() || m_posYInput->text().isEmpty()){
        QMessageBox::warning(this,"Empty inputs", "Empty inputs. Please re-enter.");
        return;
    }else if(!(isNum(xInput)) || !(isNum(yInput))){
        QMessageBox::warning(this,"Invalid Input", "Invalid inputs. Please enter numbers.");
        return;
    }
    auto x = std::stoi(xInput);
    auto y = std::stoi(yInput);
    if(x<0 || y<0 || x>m_receiver->getMinimumWidth() || y>m_receiver->getMinimumHeight()){
        QMessageBox::warning(this,"Incorrect coordinators", "Out of range. Please re-enter.");
        return;
    }
    m_pos = new QVector2D(x, y);
    QMessageBox::information(this, "Submitted!", "Submitted successfully! please close this dialog.");
}

void CreateBallDialog::slotButtonClick_vel(){
    QDialog d;
    QVBoxLayout * layout = new QVBoxLayout();
    QLabel* xLabel = new QLabel("x-coordinator:");
    xLabel->setBuddy(m_velXInput);
    QHBoxLayout* h1layout = new QHBoxLayout();
    h1layout->addWidget(xLabel);
    h1layout->addWidget(m_velXInput);

    QLabel* yLabel = new QLabel("y-coordinator:");
    yLabel->setBuddy(m_velYInput);
    QHBoxLayout* h2layout = new QHBoxLayout();
    h2layout->addWidget(yLabel);
    h2layout->addWidget(m_velYInput);
    layout->setMargin(10);
    layout->addLayout(h1layout);
    layout->addLayout(h2layout);
    layout->addWidget(m_submitVel);
    d.setLayout(layout);
    d.setWindowTitle("Setting velocity");
    d.exec();
}

void CreateBallDialog::slotButtonClick_submitVel(){
    std::string xInput = m_velXInput->text().toStdString();
    std::string yInput = m_velYInput->text().toStdString();
    if(m_velXInput->text().isEmpty() || m_velYInput->text().isEmpty()){
        QMessageBox::warning(this,"Empty inputs", "Empty inputs. Please re-enter.");
        return;
    }else if(!(isNum(xInput)) || !(isNum(yInput))){
        QMessageBox::warning(this,"Invalid Input", "Invalid inputs. Please enter numbers.");
        return;
    }
    auto x = std::stoi(xInput);
    auto y = std::stoi(yInput);
    m_vel = new QVector2D(x,y);
    QMessageBox::information(this, "Submitted!", "Submitted successfully! please close this dialog.");
}

void CreateBallDialog::slotButtonClick_create(){
    auto rStr = m_radiusInput->text().toStdString();
    auto mStr = m_massInput->text().toStdString();
    if(!(isNum(rStr)) || !(isNum(mStr))){
        QMessageBox::warning(this,"Invalid Input",
                             "Invalid inputs. Please enter numbers.");
        return;
    }else{
        auto radius = std::stoi(rStr);
        auto mass = std::stod(mStr);
        if(radius <= 0 || mass <= 0){
            QMessageBox::warning(this,"Invalid Input",
                                 "Invalid inputs. Please enter positive numbers.");
            return;
        }
        this->radius = radius;
        this->mass = mass;
    }
    if(m_color == nullptr || m_pos == nullptr
            || m_vel == nullptr || radius == -1 || mass == -1){
        QMessageBox::warning(this, "Incompleted parameters",
                             "Incompleted parameters. Please check the parameters.");
        return;
    }
    int ret = QMessageBox::question(this, "Warning", "Creating new balls"
                                                     "will reset mementoes including the original state."
                                                     "\nThe state after creating balls will be the new original state."
                                                     "Do you want to continue?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No){
        return;
    }

    StageThreeGame* receiver = dynamic_cast<StageThreeGame*>(m_receiver);
    if(receiver != nullptr){
        receiver->createBall(*m_pos, *m_vel, *m_color, radius, mass);
        QMessageBox::information(this, "Success", "The new Ball now is on the table! "
                                                  "Please close this dialog!");
        this->close();
    }
}

bool CreateBallDialog::isNum(std::string str){
    std::stringstream ss(str);
    double d;
    if(!(ss >> d)){
        return false;
    }
    return true;
}
