#include "subblockuserdata.h"

SubblockUserData::SubblockUserData(int _subblockType, int _otherData) : QTextBlockUserData(),
    m_subblockType(_subblockType), m_otherData(_otherData)
{

}

int SubblockUserData::subblockType() {
    return m_subblockType;
}

int SubblockUserData::otherData() {
    return m_otherData;
}

void SubblockUserData::setSubblockType(int _newSubblockType) {
    m_subblockType = _newSubblockType;
}

void SubblockUserData::setOtherData(int _newData) {
    m_otherData = _newData;
}
