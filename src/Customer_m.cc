//
// Generated file, do not edit! Created by nedtool 4.6 from Customer.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Customer_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}



namespace caiaginillo {

// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(Customer);

Customer::Customer(const char *name, int kind) : ::cPacket(name,kind)
{
    this->creationTime_var = 0;
    this->qct_var = 0;
    this->ct_var = 0;
    this->qwt_var = 0;
    this->wt_var = 0;
    this->hasToWrap_var = 0;
    this->checkedOut_var = 0;
}

Customer::Customer(const Customer& other) : ::cPacket(other)
{
    copy(other);
}

Customer::~Customer()
{
}

Customer& Customer::operator=(const Customer& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Customer::copy(const Customer& other)
{
    this->creationTime_var = other.creationTime_var;
    this->qct_var = other.qct_var;
    this->ct_var = other.ct_var;
    this->qwt_var = other.qwt_var;
    this->wt_var = other.wt_var;
    this->hasToWrap_var = other.hasToWrap_var;
    this->checkedOut_var = other.checkedOut_var;
}

void Customer::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->creationTime_var);
    doPacking(b,this->qct_var);
    doPacking(b,this->ct_var);
    doPacking(b,this->qwt_var);
    doPacking(b,this->wt_var);
    doPacking(b,this->hasToWrap_var);
    doPacking(b,this->checkedOut_var);
}

void Customer::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->creationTime_var);
    doUnpacking(b,this->qct_var);
    doUnpacking(b,this->ct_var);
    doUnpacking(b,this->qwt_var);
    doUnpacking(b,this->wt_var);
    doUnpacking(b,this->hasToWrap_var);
    doUnpacking(b,this->checkedOut_var);
}

simtime_t Customer::getCreationTime() const
{
    return creationTime_var;
}

void Customer::setCreationTime(simtime_t creationTime)
{
    this->creationTime_var = creationTime;
}

simtime_t Customer::getQct() const
{
    return qct_var;
}

void Customer::setQct(simtime_t qct)
{
    this->qct_var = qct;
}

simtime_t Customer::getCt() const
{
    return ct_var;
}

void Customer::setCt(simtime_t ct)
{
    this->ct_var = ct;
}

simtime_t Customer::getQwt() const
{
    return qwt_var;
}

void Customer::setQwt(simtime_t qwt)
{
    this->qwt_var = qwt;
}

simtime_t Customer::getWt() const
{
    return wt_var;
}

void Customer::setWt(simtime_t wt)
{
    this->wt_var = wt;
}

bool Customer::getHasToWrap() const
{
    return hasToWrap_var;
}

void Customer::setHasToWrap(bool hasToWrap)
{
    this->hasToWrap_var = hasToWrap;
}

bool Customer::getCheckedOut() const
{
    return checkedOut_var;
}

void Customer::setCheckedOut(bool checkedOut)
{
    this->checkedOut_var = checkedOut;
}

class CustomerDescriptor : public cClassDescriptor
{
  public:
    CustomerDescriptor();
    virtual ~CustomerDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CustomerDescriptor);

CustomerDescriptor::CustomerDescriptor() : cClassDescriptor("caiaginillo::Customer", "cPacket")
{
}

CustomerDescriptor::~CustomerDescriptor()
{
}

bool CustomerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Customer *>(obj)!=NULL;
}

const char *CustomerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CustomerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int CustomerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CustomerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "creationTime",
        "qct",
        "ct",
        "qwt",
        "wt",
        "hasToWrap",
        "checkedOut",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int CustomerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "creationTime")==0) return base+0;
    if (fieldName[0]=='q' && strcmp(fieldName, "qct")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "ct")==0) return base+2;
    if (fieldName[0]=='q' && strcmp(fieldName, "qwt")==0) return base+3;
    if (fieldName[0]=='w' && strcmp(fieldName, "wt")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hasToWrap")==0) return base+5;
    if (fieldName[0]=='c' && strcmp(fieldName, "checkedOut")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CustomerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "bool",
        "bool",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *CustomerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CustomerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Customer *pp = (Customer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CustomerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Customer *pp = (Customer *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getCreationTime());
        case 1: return double2string(pp->getQct());
        case 2: return double2string(pp->getCt());
        case 3: return double2string(pp->getQwt());
        case 4: return double2string(pp->getWt());
        case 5: return bool2string(pp->getHasToWrap());
        case 6: return bool2string(pp->getCheckedOut());
        default: return "";
    }
}

bool CustomerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Customer *pp = (Customer *)object; (void)pp;
    switch (field) {
        case 0: pp->setCreationTime(string2double(value)); return true;
        case 1: pp->setQct(string2double(value)); return true;
        case 2: pp->setCt(string2double(value)); return true;
        case 3: pp->setQwt(string2double(value)); return true;
        case 4: pp->setWt(string2double(value)); return true;
        case 5: pp->setHasToWrap(string2bool(value)); return true;
        case 6: pp->setCheckedOut(string2bool(value)); return true;
        default: return false;
    }
}

const char *CustomerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *CustomerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Customer *pp = (Customer *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

} // namespace caiaginillo

