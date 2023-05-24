//
// Created by Mihai on 5/5/2023.
//

#ifndef OOP_APPEXCEPTIONS_H
#define OOP_APPEXCEPTIONS_H

#include <stdexcept>
#include <string>

class app_exception : public std::runtime_error {
private:
    std::string description;
public:
    app_exception(std::string const& msj);
    app_exception(app_exception const& appexcep);
    app_exception(app_exception&& appexcep);
    app_exception& operator=(app_exception const& appexcep);
    app_exception& operator=(app_exception&& appexcep);
    ~app_exception();

    virtual char const* what() const noexcept override;
};


class missing_reference : public app_exception {
private:
    std::string sourceClass;
    std::string method;
    std::string reference;

    std::string fullMessage;
public:
    missing_reference() = delete;
    missing_reference(std::string srcCls, std::string meth, std::string ref);
    missing_reference(missing_reference const& mref);
    missing_reference(missing_reference&& mref);
    missing_reference& operator=(missing_reference const& mref);
    missing_reference& operator=(missing_reference&& mref);
    ~missing_reference();

    char const* what() const noexcept override;

    std::string const& getSourceClass() const;
    std::string const& getMethod() const;
    std::string const& getReference() const;
};

class math_error : public app_exception {
private:
    std::string description;
public:
    math_error() = delete;
    explicit math_error(std::string desc);
    math_error(math_error const& merr);
    math_error(math_error&& merr);
    math_error& operator=(math_error const& merr);
    math_error& operator=(math_error&& merr);
    ~math_error();

    char const* what() const noexcept override;
};

class unique_bind_error : public app_exception {
private:
    std::string binder;
    std::string bindee;

    std::string fullMessage;
public:
    unique_bind_error()=delete;
    unique_bind_error(std::string binder, std::string bindee);
    unique_bind_error(unique_bind_error const&);
    unique_bind_error(unique_bind_error&&);
    unique_bind_error& operator=(unique_bind_error const&);
    unique_bind_error& operator=(unique_bind_error&&);
    ~unique_bind_error();

    char const* what() const noexcept override;
};

#endif //OOP_APPEXCEPTIONS_H
