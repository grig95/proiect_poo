//
// Created by Mihai on 5/5/2023.
//

#include "appexceptions.h"

///app_exception
app_exception::app_exception(std::string const& msj) : std::runtime_error(msj), description(msj) {}

app_exception::app_exception(app_exception const& appexcep) = default;

app_exception::app_exception(app_exception&& appexcep) = default;

app_exception& app_exception::operator=(app_exception const& appexcep) = default;

app_exception& app_exception::operator=(app_exception&& appexcep) = default;

app_exception::~app_exception() = default;

char const* app_exception::what() const noexcept {
    return description.c_str();
}


///missing_reference
missing_reference::missing_reference(std::string srcCls, std::string meth, std::string ref) : app_exception(std::string("Missing reference exception.")), sourceClass(srcCls), method(meth), reference(ref), fullMessage() {
    fullMessage=std::string("Missing reference exception: Object of type ") + sourceClass +
                std::string(" was asked for a reference to its assigned ") + reference +
                std::string(" through method ") + method + std::string(", but referenced object doesn't exist.");
}

missing_reference::missing_reference(missing_reference const& mref) = default;

missing_reference::missing_reference(missing_reference&& mref) = default;

missing_reference& missing_reference::operator=(missing_reference const& mref) = default;

missing_reference& missing_reference::operator=(missing_reference&& mref) = default;

missing_reference::~missing_reference() = default;

char const* missing_reference::what() const noexcept {
    return fullMessage.c_str();
}

std::string const& missing_reference::getSourceClass() const { return sourceClass; }
std::string const& missing_reference::getMethod() const { return method; }
std::string const& missing_reference::getReference() const { return reference; }


///math_error
math_error::math_error(std::string desc) : app_exception("Math error."), description(desc) {}

math_error::math_error(math_error const& merr) = default;

math_error::math_error(math_error&& merr) = default;

math_error& math_error::operator=(math_error const& merr) = default;

math_error& math_error::operator=(math_error&& merr) = default;

math_error::~math_error() = default;

char const* math_error::what() const noexcept {
    return description.c_str();
}


///unique_bind_error
unique_bind_error::unique_bind_error(std::string binder, std::string bindee) : app_exception("Unique bind error."), binder(binder), bindee(bindee), fullMessage() {
    fullMessage=std::string("Unique bind error: Object of class ") + binder + std::string(" attempted to attach to itself an object of class ") +
            bindee + std::string(", but attachee is already bound to another object.");
}

unique_bind_error::unique_bind_error(const unique_bind_error &) = default;

unique_bind_error::unique_bind_error(unique_bind_error &&) = default;

unique_bind_error& unique_bind_error::operator=(unique_bind_error const&) = default;

unique_bind_error& unique_bind_error::operator=(unique_bind_error &&) = default;

unique_bind_error::~unique_bind_error() = default;

char const* unique_bind_error::what() const noexcept { return fullMessage.c_str(); }