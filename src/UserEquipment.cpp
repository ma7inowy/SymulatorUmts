#include "../include/UserEquipment.h"
#include "../include/Cell.h"
#include <iostream>

#include <cstdlib>
#include <ctime>

UserEquipment::UserEquipment(bool connected, ConnectionType connType) : currentCell(nullptr), connected(connected),
                                                                        connType(connType) {

}

bool UserEquipment::isConnected() const {
    return connected;
}

void UserEquipment::setConnected(bool connected) {
    UserEquipment::connected = connected;
}

UserEquipment::ConnectionType UserEquipment::getConnType() const {
    return connType;
}

void UserEquipment::setConnType(UserEquipment::ConnectionType connType) {
    UserEquipment::connType = connType;
}

bool UserEquipment::callEstablishment(shared_ptr<Cell> cell) {
    //asks for random connection
    ConnectionType randomConnType = getRandomConnType();
    if (cell->resourceRequest(randomConnType)) {
        connected = true;
        currentCell = cell;
        connType = randomConnType;
        return true;
    } else {
        return false;
    }

}

bool UserEquipment::handover(const shared_ptr<Cell> &newCell) {
    // only if connected = true;
    if (currentCell->releaseResources(getConnType())) {
        if (newCell->handoverRequest(getConnType())) {
            currentCell = newCell;
            return true;
        }
    } else return false;
    return false;
}

const shared_ptr<Cell> &UserEquipment::getCurrentCell() const {
    return currentCell;
}

UserEquipment::ConnectionType UserEquipment::getRandomConnType() {
    int i = (rand() % 3 + 1); // rand from 1 to 3
    auto randomConnType = static_cast<ConnectionType>(i);
    return randomConnType;
}








