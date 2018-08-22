#include "dbus_interface.h"

namespace {
  static void ThreadTrampoline(DbusInterface* interface) {
    interface->Run();
  }
}

DbusAdaptor::DbusAdaptor(DBus::Connection &connection)
  : DBus::ObjectAdaptor(connection, "/"),
    controller_(NULL)
{
}

DbusAdaptor::~DbusAdaptor() {
}

void DbusAdaptor::Load(const std::string& url) {
  std::string arg = url;
  if (controller_)
    controller_->LoadURL(arg);
}

void DbusAdaptor::Stop() {
  if (controller_)
    controller_->Stop();
}

void DbusAdaptor::Reload() {
  if (controller_)
    controller_->Reload();
}

std::string DbusAdaptor::GetURL() {
  if (controller_)
    return controller_->GetURL();

  return "";
}

void DbusAdaptor::SetController(
  EGLContent::BrowserDelegate::Controller* controller) {
  controller_ = controller;
}

DbusInterface::DbusInterface()
  : bus_(DBus::Connection::SystemBus()),
    adaptor_(bus_),
    thread_(std::thread(ThreadTrampoline, this)) {
}

DbusInterface::~DbusInterface() {
}

void DbusInterface::Initialise(
  EGLContent::BrowserDelegate::Controller* controller) {
  adaptor_.SetController(controller);
  DBus::default_dispatcher = &dispatcher_;
  bus_.request_name("net.raspberry.RpiLauncher");
}

void DbusInterface::Run() {
  dispatcher_.enter();
}

void DbusInterface::LoadingStateChanged(bool loading) {
  adaptor_.LoadingStateChanged(loading);
}

void DbusInterface::LoadProgressed(double progress) {
  adaptor_.LoadProgressed(progress);
}

void DbusInterface::TargetURLChanged(std::string& url) {
  adaptor_.URLChanged(url);
}
