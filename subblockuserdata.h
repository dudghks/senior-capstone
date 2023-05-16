#ifndef SUBBLOCKUSERDATA_H
#define SUBBLOCKUSERDATA_H

#include <QTextBlockUserData>

class SubblockUserData : public QTextBlockUserData
{
public:
    SubblockUserData(int _subblockType, int _otherData = -1);
    int subblockType();
    int otherData();
    void setSubblockType(int _newSubblockType);
    void setOtherData(int _newData);

private:
    int m_subblockType;
    int m_otherData;
};

#endif // SUBBLOCKUSERDATA_H
