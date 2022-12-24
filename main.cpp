#include <QApplication>
#include <QtWidgets>
#include <QTcpSocket>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  // Création de la fenêtre principale
  QWidget* window = new QWidget;
  window->setWindowTitle("Client de chat");

  // Création du layout vertical
  QVBoxLayout* layout = new QVBoxLayout;

  // Création du champ de saisie du message
  QLineEdit* messageEdit = new QLineEdit;

  // Création du bouton d'envoi du message
  QPushButton* sendButton = new QPushButton("Envoyer");

  // Création de la zone de chat
  QTextEdit* chatArea = new QTextEdit;
  chatArea->setReadOnly(true);

  // Ajout du champ de saisie, du bouton d'envoi et de la zone de chat au layout
  layout->addWidget(messageEdit);
  layout->addWidget(sendButton);
  layout->addWidget(chatArea);

  // Création de l'objet socket
  QTcpSocket* socket = new QTcpSocket;

  // Connexion au serveur
  socket->connectToHost("localhost", 1234);

  // Connexion du signal de réception de données au slot de mise à jour de la zone de chat
  QObject::connect(socket, &QTcpSocket::readyRead, [&]()
  {
    chatArea->append(socket->readAll());
  });

  // Connexion du signal de clic sur le bouton d'envoi au slot d'envoi du message
  QObject::connect(sendButton, &QPushButton::clicked, [&]()
  {
    QString message = messageEdit->text();
    socket->write(message.toUtf8());
    messageEdit->clear();
  });

  // Configuration de la fenêtre principale
  window->setLayout(layout);
  window->show();

  return app.exec();
}
