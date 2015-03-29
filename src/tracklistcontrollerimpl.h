#ifndef TRACKLISTCONTROLLERIMPL_H
#define TRACKLISTCONTROLLERIMPL_H

#include "libmopiqy/tracklistcontroller.h"

class MopidyClientPrivate;

class TracklistControllerImpl : public TracklistController
{
    Q_OBJECT

public:
    TracklistControllerImpl(MopidyClientPrivate *parent);
    ~TracklistControllerImpl();

    // process responses

public slots:

private:
    MopidyClientPrivate *m_mcp;
};

#endif //TRACKLISTCONTROLLERIMPL_H
