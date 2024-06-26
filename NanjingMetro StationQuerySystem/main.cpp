#include "stdafx.h"
#include"NanjingMetroStationQuerySystem.h"

#include "LoginWindow.h"

#include <QtWidgets/QApplication>
#include"FileReader.h"

#include"UndergroundLine.h"
#include"LibcurlUtil.h"
#include"JsonUtil.h"


int main(int argc, char *argv[])
{
   
    QApplication a(argc, argv);

    QFont font("arial", 12);
    font.setBold(true);
    QApplication::setFont(font);
    
    FileReader::getAllStations();
    
    LoginWindow w;
    
    w.show();
    return a.exec();
   
      
    
}

