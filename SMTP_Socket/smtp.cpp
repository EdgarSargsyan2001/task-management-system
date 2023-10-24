#include "SMTP_Socket/smtp.h"

#include <QTcpSocket>
#include <QDebug>
#include <QTextStream>

SmtpClient::SmtpClient(
        const QString& host,
        int port,
        const QString& username,
        const QString& password,
        QObject* parent
    )
    :   QObject(parent),
        m_host(host),
        m_port(port),
        m_username(username),
        m_password(password)
{

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &SmtpClient::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SmtpClient::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &SmtpClient::onReadyRead);

}

void SmtpClient::sendEmail(
        const QString& from,
        const QString& to,
        const QString& subject,
        const QString& body
    )
{

    m_from = from;
    m_to = to;
    m_subject = subject;
    m_body = body;

    m_socket->connectToHost(m_host, m_port);
}

void SmtpClient::onConnected() {

    QTextStream stream(m_socket);
    stream << "EHLO localhost\r\n";
    stream << "AUTH LOGIN\r\n";
    stream << QByteArray(m_username.toUtf8()).toBase64() << "\r\n";
    stream << QByteArray(m_password.toUtf8()).toBase64() << "\r\n";
    stream << "MAIL FROM:<" << m_from << ">\r\n";
    stream << "RCPT TO:<" << m_to << ">\r\n";
    stream << "DATA\r\n";
    stream << "Subject: " << m_subject << "\r\n";
    stream << "From: " << m_from << "\r\n";
    stream << "To: " << m_to << "\r\n";
    stream << "\r\n";
    stream << m_body << "\r\n";
    stream << ".\r\n";
    stream << "QUIT\r\n";

}

void SmtpClient::onDisconnected() {
    //        qDebug() << "Disconnected from SMTP server";
    m_socket->close();
}
void SmtpClient::onReadyRead() {
    QString response = QString::fromUtf8(m_socket->readAll());
    //        qDebug() << response;
}
