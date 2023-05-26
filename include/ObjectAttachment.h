#ifndef OOP_OBJECTATTACHMENT_H
#define OOP_OBJECTATTACHMENT_H

class Object;

class ObjectAttachment {
protected:
    Object* object = nullptr;

    void attachTo(Object* obj); ///meant to only be used by Object class
    void detach(); ///meant to only be used by Object class
public:
    ObjectAttachment();
    explicit ObjectAttachment(Object* obj);
    virtual ~ObjectAttachment();

    ObjectAttachment(ObjectAttachment const&) = delete;
    ObjectAttachment& operator=(ObjectAttachment const&) = delete;

    bool isAttached() const;
    Object& getObject() const;

    friend class Object;
};


#endif //OOP_OBJECTATTACHMENT_H
