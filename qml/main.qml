import Qt.labs.platform 1.1 as LabsPlatform
import QtQuick.Controls 2.5


LabsPlatform.SystemTrayIcon {
  visible: true
  id: librasofficeApp
  icon.source: "qrc:/qml/assets/images/labis-librasoffice.png"
  tooltip: qsTr("LIBRASOffice - Leitor de telas para língua de sinais")
  property bool signalExibition: true

  menu: LabsPlatform.Menu {
    LabsPlatform.MenuItem {
      id: item1
      text: qsTr("Parar de exibir sinais")
      onTriggered: {
        if(librasofficeApp.signalExibition == true){
          librasofficeApp.signalExibition = false;
          laso_backend.handleSignalExibition(librasofficeApp.signalExibition);
          item1.text = qsTr("Voltar a exibir sinais");
        }
        else{
          librasofficeApp.signalExibition = true;
          laso_backend.handleSignalExibition(librasofficeApp.signalExibition);
          item1.text = qsTr("Parar de exibir sinais");
        }
      }
    }
    LabsPlatform.MenuItem {
      text: qsTr("Sobre")
      property string messageText: {
        "LIBRASOffice é um projeto acadêmico de extensão e pesquisa do LabIS/LIpE/UFRJ que tem como objetivo o auxílio de usuários surdos, que não dominam português, mas sim LIBRAS, na utilização do LibreOffice autônomamente.\nPara mais informações, acesse:\n<a href='http://labis.cos.ufrj.br'>http://labis.cos.ufrj.br</a> "
      }
      onTriggered: {
        showMessage("Sobre o LIBRASOffice",messageText,
                    "",
                    8000
                    )
      }
    }

    LabsPlatform.MenuItem {
      text: qsTr("Fechar")
      onTriggered: {
        Qt.quit()
      }
    }
  }
}
