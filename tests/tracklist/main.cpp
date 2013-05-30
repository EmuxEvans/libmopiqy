#include <QCoreApplication>
#include "tst_tracklist.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	tst_tracklist tst;
	tst.run();

	return app.exec();
}
