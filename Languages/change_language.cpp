#include "change_language.h"
#include "ui_change_language.h"
#include "text/text.h"

#include <QApplication>

change_language::change_language(QTranslator*p, QWidget *parent) :
    QDialog(parent),
    m_translator(p),
    ui(new Ui::change_language)
{
    ui->setupUi(this);

    int index = ui->comboBox->findText(m_translator->objectName());
    ui->comboBox->setCurrentIndex(index);
    ui->comboBox->setItemData(index,0,Qt::UserRole - 1);
}

change_language::~change_language()
{
    delete ui;
}

void change_language::on_comboBox_textActivated(const QString &leng)
{
    if(m_translator->objectName() != Text::english && leng == Text::english){

        qApp->removeTranslator(m_translator);
        m_translator->setObjectName(leng);
        emit change_successful();

    }else if( m_translator->objectName() != Text::armenian && leng == Text::armenian){

        if(m_translator->load(":/Languages/armenian_language.qm")){
            m_translator->setObjectName(leng);
            qApp->installTranslator(m_translator);
            emit change_successful();
        }
    }
    close();
}

