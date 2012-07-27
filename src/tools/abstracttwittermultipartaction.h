#ifndef ABSTRACTTWITTERMULTIPARTACTION_H
#define ABSTRACTTWITTERMULTIPARTACTION_H

#include "abstracttwitteraction.h"

class AbstractTwitterMultiPartAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractTwitterMultiPartAction)
public:
    explicit AbstractTwitterMultiPartAction(QObject *parent = 0);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByHeader; }
    bool isMultiPart() const { return true; }
};

#endif // ABSTRACTTWITTERMULTIPARTACTION_H
