#ifndef REPORTFORSPAM_H
#define REPORTFORSPAM_H

#include "abstractblockaction.h"

class ReportForSpam : public AbstractBlockAction
{
    Q_OBJECT
    Q_DISABLE_COPY(ReportForSpam)
public:
    explicit ReportForSpam(QObject *parent = 0);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/report_spam.json"); }
};

#endif // REPORTFORSPAM_H
