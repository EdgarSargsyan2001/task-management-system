#ifndef SMTP_H
#define SMTP_H

#include <QObject>

class QTcpSocket;//forward declaration

class SmtpClient : public QObject {
    Q_OBJECT

public:
    SmtpClient(
        const QString& host,
        int port,
        const QString& username,
        const QString& password,
        QObject* parent = nullptr
        );

    void sendEmail(
        const QString& from,
        const QString& to,
        const QString& subject,
        const QString& body
        );

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket* m_socket;
    QString m_host;
    int m_port;
    QString m_username;
    QString m_password;
    QString m_from;
    QString m_to;
    QString m_subject;
    QString m_body;
};
#endif // SMTP_H
