#ifndef DBUS_INTERFACE_H_
# define DBUS_INTERFACE_H_

#include <string>
#include <thread>

#include <eglcontent/browser_delegate.h>

#include "dbus_adaptor.h"

class DbusAdaptor :
  public net::raspberry::RpiLauncher_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor {

  public:

    DbusAdaptor(DBus::Connection &connection);
    ~DbusAdaptor();

    void Load(const std::string& url) override;
    void Stop() override;
    void Reload() override;
    std::string GetURL() override;
    void SetController(
      EGLContent::BrowserDelegate::Controller* controller);

  private:

    EGLContent::BrowserDelegate::Controller* controller_;

};

class DbusInterface {

  public:

    DbusInterface();
    ~DbusInterface();

    void Initialise(
      EGLContent::BrowserDelegate::Controller* controller);
    void Run();

    void LoadingStateChanged(bool loading);
    void LoadProgressed(double progress);
    void TargetURLChanged(std::string& url);

  private:

    DBus::BusDispatcher dispatcher_;
    std::unique_ptr<DbusAdaptor> adaptor_;
    std::thread thread_;
};

#endif /* !DBUS_INTERFACE.H */
