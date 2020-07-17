#include <listenercontroller.h>
#include <librasoffice_app.h>
#include <QDebug>
#include <QThread>


int main(int argc, char *argv[])
{
     //QThread *librasoffice_signs = new QThread;
     //PopupWorker *libras_worker = new PopupWorker(argc, argv);
     //libras_worker->moveToThread(librasoffice_signs);
     //QObject::connect(librasoffice_signs, SIGNAL(started()), libras_worker, SLOT(run()));
     LIBRASOffice_App *librasoffice_app = new LIBRASOffice_App(argc, argv);
     //librasoffice_signs->start();
    librasoffice_app->run();
}
