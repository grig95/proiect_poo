#ifndef OOP_OBJECTATTACHMENT_H
#define OOP_OBJECTATTACHMENT_H

class Object;

class ObjectAttachment {
protected:
    Object* object;

    void attachTo(Object* obj); ///meant to only be used by Object class
    void detach(); ///meant to only be used by Object class
public:
    ObjectAttachment();
    explicit ObjectAttachment(Object* obj);
    virtual ~ObjectAttachment();

    ///Doesn't actually copy anything, it exists for conveniently copying derivates without copying the attached object.
    ObjectAttachment(ObjectAttachment const& objAtt);
    ///Doesn't actually copy anything, it exists for conveniently copying derivates without copying the attached object.
    ObjectAttachment& operator=(ObjectAttachment const& objAtt);

    bool isAttached() const;
    Object& getObject() const;

    friend class Object;
};


#endif //OOP_OBJECTATTACHMENT_H
