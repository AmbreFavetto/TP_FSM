#include "fsm.h"

fsm::fsm()
{

}

QStringList fsm::stringToList(QString line)
{
    return line.split(" ");
}
