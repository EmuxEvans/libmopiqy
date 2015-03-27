#ifndef MIXERCONTROLLER_H
#define MIXERCONTROLLER_H

#include <QObject>
#include <libmopiqy/libmopiqy_export.h>

class LIBMOPIQY_EXPORT MixerController : public QObject
{
    Q_OBJECT

public slots:
    virtual void getMute() = 0;
    virtual void setMute(bool) = 0;
    virtual void getVolume() = 0;
    virtual void setVolume(int) = 0;

signals:
    void getMuteReceived(const bool &muted);
    void setMuteReceived(const bool &ack);
    void getVolumeReceived(const int &volume);
    void setVolumeReceived(const bool &ack);
};

#endif //MIXERCONTROLLER_H
