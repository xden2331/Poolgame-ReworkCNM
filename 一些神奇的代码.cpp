QDialog *dialog = new QDialog(this);
    QLabel* label = new QLabel(tr("Wanna make a new ball?"));
    lineEdit = new QLineEdit();
    label->setBuddy(lineEdit);

    QPushButton *getMsg = new QPushButton("Make it now!", dialog);

    connect(getMsg,SIGNAL(clicked(bool)),this,SLOT(getInput()));
    QHBoxLayout *topLeftLayout = new QHBoxLayout();
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);
    dialog->setLayout(topLeftLayout);
    dialog->setWindowTitle("Creating a new ball...");
    dialog->exec();
    delete dialog;
