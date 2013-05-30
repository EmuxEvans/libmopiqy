#include <QCoreApplication>
#include "tst_library.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	tst_library tst;
	tst.run();

	return app.exec();
}
