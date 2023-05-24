#include "ObjectAttachment.h"
#include "appexceptions.h"

///constructors, destructor
ObjectAttachment::ObjectAttachment() : object(nullptr) {}

ObjectAttachment::ObjectAttachment(Object* obj) : object(obj) {}

ObjectAttachment::ObjectAttachment(ObjectAttachment const& objAtt) : object(nullptr) {}

ObjectAttachment& ObjectAttachment::operator=(ObjectAttachment const& objAtt) { return *this; }

ObjectAttachment::~ObjectAttachment() = default;

///functionality
void ObjectAttachment::attachTo(Object *obj) { object=obj; }
void ObjectAttachment::detach() { object=nullptr; }
bool ObjectAttachment::isAttached() const { return object!=nullptr; }
Object& ObjectAttachment::getObject() const {
    if(object==nullptr)
        throw missing_reference("ObjectAttachment", "getObject()", "object");
    return *object;
}
