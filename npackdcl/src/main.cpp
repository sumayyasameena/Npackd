#include <windows.h>
#include <qdebug.h>
#include <qstringlist.h>
#include <qstring.h>
#include <QTimer>

#include "repository.h"
#include "commandline.h"
#include "wpmutils.h"
#include "abstractrepository.h"
#include "dbrepository.h"
#include "version.h"
#include "installedpackages.h"

#include "app.h"

int main(int argc, char *argv[])
{
#if !defined(__x86_64__)
    LoadLibrary(L"exchndl.dll");
#endif

    QCoreApplication ca(argc, argv);

    AbstractRepository::setDefault_(DBRepository::getDefault());

    CoInitializeEx(0, COINIT_MULTITHREADED);

    qRegisterMetaType<JobState>("JobState");
    qRegisterMetaType<Version>("Version");

    InstalledPackages::getDefault()->packageName =
            "com.googlecode.windows-package-manager.NpackdCL";

    App app;

#ifdef TEST
    QTimer::singleShot(0, &app, SLOT(test()));
#else
    QTimer::singleShot(0, &app, SLOT(process()));
#endif

    return ca.exec();
}

