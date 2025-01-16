#include "servak.h"

Servak::Servak(QObject *parent)
    : QObject{parent}
{
    m_logger = new Logger(this, "CORE", true);

    m_mapworker = new MapWorker(this);
    m_networker = new NetWorker(this);

    m_networker->start(8080);

    connect(m_networker, &NetWorker::newPlayerArrived, this, &Servak::newClientArrived);
    connect(m_networker, &NetWorker::playerDisconnected, this, &Servak::onPlayerDisconnect);
    connect(m_networker, &NetWorker::playerCommand, this, &Servak::onPlayerCommand);
}

void Servak::newClientArrived(QByteArray id)
{
    manageNewPlayer(id);
}

void Servak::onPlayerCommand(NetworkParser::Request req)
{
    switch (req.action) {
    case NetworkParser::move:
        processPlayerMove(req.uuid, req.direction);
        break;
    default:
        m_logger->log("INVALID COMMAND RECEIVED");
    }
}

void Servak::processPlayerMove(QByteArray id, NetworkParser::Direction direction)
{
    Player *player = m_players[id];
    Position pos = player->getPosition();
    Position newPos = pos;

    switch (direction) {
    case NetworkParser::up: newPos.y--; break;
    case NetworkParser::down: newPos.y++; break;
    case NetworkParser::left: newPos.x--; break;
    case NetworkParser::right: newPos.x++; break;
    }

    if (m_mapworker->isPositionSteppable(newPos)) {
        char &cell = m_mapworker->getCellAt(newPos);

        if (cell == 's' || cell == 'S') {
            cell = '.';

            m_networker->sendToAll(prepareRequest("", Servak::mapUpdate, NetworkParser::nodirection, m_mapworker->getMapString()));
        }

        player->setPosition(newPos);

        QString additionalInfo = QString("%1,%2,%3").arg(id).arg(newPos.x).arg(newPos.y);
        NetworkParser::Request request = prepareRequest(id, Servak::pos, NetworkParser::nodirection, additionalInfo);
        m_networker->sendToAll(request);
    } else {

        m_logger->log(QString("Player moved wrongly %1: %2,%3").arg(id).arg(newPos.x).arg(newPos.y));
    }
}

NetworkParser::Request Servak::prepareRequest(QByteArray uuid, Servak::Action action, NetworkParser::Direction direction, QString additionalInfo)
{
    NetworkParser::Request request;
    request.uuid = uuid;
    request.action = static_cast<NetworkParser::Action>(action);
    request.direction = direction;
    request.additionalInfo = additionalInfo;

    return request;
}

void Servak::onPlayerDisconnect(QByteArray id)
{
    delete m_players[id];
    m_players.remove(id);
}

void Servak::manageNewPlayer(QByteArray id)
{
    m_networker->sendToPlayer(id, prepareRequest("", Servak::map, NetworkParser::nodirection, m_mapworker->getMapString()));

    m_networker->sendToPlayer(id, prepareRequest("", Servak::assignId, NetworkParser::nodirection, QString::fromLocal8Bit(id)));

    m_networker->sendToAll(prepareRequest("", Servak::pos, NetworkParser::nodirection, id + "," + m_mapworker->getBasicPlayerPositionString()));

    Player *player = new Player(this, QString::fromLocal8Bit(id));
    player->setPosition(m_mapworker->getBasicPlayerPosition());
    m_players[id] = player;

    for (Player *bufferPlayer : m_players) {
        m_networker->sendToPlayer(id, prepareRequest("", Servak::pos, NetworkParser::nodirection, bufferPlayer->getId().toLocal8Bit() + "," + bufferPlayer->getPositionByteArray()));
    }
}
