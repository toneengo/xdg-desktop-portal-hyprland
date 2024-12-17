#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include "wlr-virtual-pointer-unstable-v1.hpp"
#include "../shared/Session.hpp"
#include "../dbusDefines.hpp"

class CRemoteDesktopPortal {
  public:
    CRemoteDesktopPortal(SP<CCZwlrVirtualPointerManagerV1> mgr);

    dbUasv        onCreateSession(sdbus::ObjectPath requestHandle, sdbus::ObjectPath sessionHandle, std::string appID,
                                  std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onSelectDevices(sdbus::ObjectPath requestHandle, sdbus::ObjectPath sessionHandle, std::string appID,
                                  std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onStart(sdbus::ObjectPath requestHandle, sdbus::ObjectPath sessionHandle, std::string appID, std::string parentWindow,
                          std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyPointerMotion(sdbus::ObjectPath sessionHandle, double dx, double dy, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyPointerMotionAbsolute(sdbus::ObjectPath sessionHandle, unsigned int stream, double x, double y, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyPointerButton(sdbus::ObjectPath sessionHandle, int button, unsigned int state, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyPointerAxis(sdbus::ObjectPath sessionHandle, double dx, double dy, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyPointerAxisDiscrete(sdbus::ObjectPath sessionHandle, unsigned int axis, int steps, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyKeyboardKeycode(sdbus::ObjectPath sessionHandle, int keycode, unsigned int state, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyKeyboardKeysym(sdbus::ObjectPath sessionHandle, int keysym, unsigned int state, std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyTouchDown(sdbus::ObjectPath sessionHandle, unsigned int stream, unsigned int slot, double x, double y,
                                    std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyTouchMotion(sdbus::ObjectPath sessionHandle, unsigned int stream, unsigned int slot, double x, double y,
                                      std::unordered_map<std::string, sdbus::Variant> opts);
    dbUasv        onNotifyTouchUp(sdbus::ObjectPath sessionHandle, unsigned int slot, std::unordered_map<std::string, sdbus::Variant> opts);
    sdbus::UnixFd onConnectToEIS(sdbus::ObjectPath sessionHandle, std::string appID, std::unordered_map<std::string, sdbus::Variant> opts);

    struct SSession {
        std::string                            appid;
        sdbus::ObjectPath                      requestHandle, sessionHandle;
        std::unique_ptr<SDBusRequest>          request;
        std::unique_ptr<SDBusSession>          session;

        SP<CCZwlrVirtualPointerV1>             pointer;
    };

    std::vector<std::unique_ptr<SSession>> m_vSessions;

  private:
    struct {
        SP<CCZwlrVirtualPointerManagerV1> manager;
    } m_sState;

    std::unique_ptr<sdbus::IObject> m_pObject;

    SSession*                       getSession(sdbus::ObjectPath& path);
    uint                            sessionCounter = 0;

    const sdbus::InterfaceName      INTERFACE_NAME = sdbus::InterfaceName{"org.freedesktop.impl.portal.RemoteDesktop"};
    const sdbus::ObjectPath         OBJECT_PATH    = sdbus::ObjectPath{"/org/freedesktop/portal/desktop"};
};
