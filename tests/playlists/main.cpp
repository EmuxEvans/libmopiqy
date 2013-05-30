#include <QCoreApplication>
#include "tst_playlists.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	tst_playlists tst;
	tst.run();

	return app.exec();
}
