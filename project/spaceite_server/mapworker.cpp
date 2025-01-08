#include "mapworker.h"

MapWorker::MapWorker(QObject *parent)
    : QObject{parent}
{
    m_logger = new Logger(this, "MAP", true);
    m_defaultPlayerPostion = "0,0";

    if (loadMap() == false) {
        emit mapLoadingError();
    }

    loadDefaultPlayerPosition();
    loadStonePosition();
}

QString MapWorker::getMapString()
{
    QString responce;
    for (int y = 0; y < m_mapData.size(); ++y) {
        for (int x = 0; x < m_mapData[y].size(); ++x) {
            if (x == m_stonePosition.x() && y == m_stonePosition.y()) {
                responce += 'S';
            } else {
                responce += m_mapData[y][x];
            }
        }
        responce += ",";
    }
    return responce;
}



Position MapWorker::getBasicPlayerPosition()
{
    QStringList positionxy = m_defaultPlayerPostion.split(',');
    Position pos;
    pos.x = positionxy[0].toInt();
    pos.y = positionxy[1].toInt();
    return pos;
}

bool MapWorker::isPositionSteppable(Position pos)
{
    return m_mapData[pos.y][pos.x] == '.';
}

bool MapWorker::loadMap()
{
    m_mapData.clear();
    QFile mapFile(":/Resources/misc/map.txt");
    if (mapFile.open(QIODevice::ReadOnly)) {
        QList<QByteArray> rows = mapFile.readAll().split('\n');
        for (QByteArray row : rows) {
            QVector<char> rowElements;
            for (char item : row) {
                rowElements.push_back(item);
            }
            m_mapData.push_back(rowElements);
        }

        mapFile.close();
        m_logger->log("Map loaded successfully!");
        return true;
    }
    m_logger->log(mapFile.errorString());
    return false;
}

bool MapWorker::loadDefaultPlayerPosition()
{
    QFile posFile(":/Resources/misc/playerPos.txt");
    if (posFile.open(QIODevice::ReadOnly)) {
        QList<QByteArray> rows = posFile.readAll().split('\n');
        m_defaultPlayerPostion = rows[0] + "," + rows[1];
        m_logger->log("Loaded default player position: " + m_defaultPlayerPostion);
        return true;
    }
    m_logger->log(posFile.errorString());
    return false;
}

bool MapWorker::loadStonePosition()
{
    QFile stoneFile(":/Resources/misc/stonePos.txt");
    if (stoneFile.open(QIODevice::ReadOnly)) {
        QList<QByteArray> rows = stoneFile.readAll().split('\n');
        if (rows.size() >= 2) {
            m_stonePosition.setX(rows[0].toInt());
            m_stonePosition.setY(rows[1].toInt());
            m_logger->log("Loaded stone position: " + QString::number(m_stonePosition.x()) + "," + QString::number(m_stonePosition.y()));
            return true;
        }
    }
    m_logger->log(stoneFile.errorString());
    return false;
}

