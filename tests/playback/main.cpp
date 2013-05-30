#include <QCoreApplication>
#include "tst_playback.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	tst_playback tst;
	tst.run();

	return app.exec();
}
